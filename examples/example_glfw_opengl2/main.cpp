
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl2.h"
#include <stdio.h>
//#include <sys/time.h> // for gettimeofday()
#include <ctime>
//#include <unistd.h>
#include "vec3.h"
#include "draw.h"
#include <cstdlib>
#include <thread>
#include <fstream>
#include <vector>
#include <ctime>
//#include <sys/time.h>
#include<string>
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif
#include <GLFW/glfw3.h>

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

#include "Material.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"

#include "Hittable.h"
#include "HittableList.h"
#include "Sphere.h"
#include "MovingSphere.h"

#include "Camera.h"

#include "Texture.h"



static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

// 真的敢写。
//using namespace std;

long curTime;
long totTime;
double timeRemaining;

//全局变量

ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.00f, 1.00f);
double progressDone = 0.0f, progressDir = 1.0f;
bool gRayTracingBegin = false;


int numPixelTotal;
int numThread = 12;
int numPixelRendered = 0;
int doneRecord = 0;
int framebufferInited = false;
int gFrameFinished = false;

int* lastFrameBuffer;

int gFov = 20;

vec3 lookfrom(13, 2, 3);
vec3 lookat(0, 0, 0);
double dist_to_focus = 10.0;
double aperture = 0.1;

static int speedFactor = 1;

void DrawFrame(int* fb)
{

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, display_w, 0.0, display_h, 0.0, 1.0);
    glBegin(GL_POINTS);

    for (int i = 0; i < display_h; i++)
    {

        int r, g, b;
        for (int j = 0; j < display_w; j++)
        {
            Color2RGB(fb[i * display_w + j], r, g, b);
            glColor3f((double)r / 255, (double)g / 255, (double)b / 255);
            glVertex3f(j + 20, display_h - i - 300, 0);
        }
    }

    glEnd();
}
//记录进度和时间
void RecordProgressAndTime()
{
    progressDone = double(numPixelRendered) / (numPixelTotal);
    // totTime = (GetCurrentTimeMs() - curTime);
    // timeRemaining = totTime * (1 - progressDone) / progressDone / 1000; //根据过去的平均时间来计算剩余时间 x/t=pTodo/pDone -> x= t*pTodo/pDone = t*(1-pDone) /pDone
}

//发射一条射线，并采样该射线最终输出到屏幕的颜色值
vec3 sampleOnce(const Ray& r, HittableList world, int depth) {
    HitRecord rec;
    if (world.hit(r, 0.001, FLT_MAX, rec)) //射线命中物体
    {
        Ray scattered; //散射光线
        vec3 attenuation; //反射率
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
            return attenuation * sampleOnce(scattered, world, depth + 1);
        }
        else
        {
            return vec3(0.0, 0, 0);
        }
    }
    else
    {
        // 取背景色。TODO：图片背景
        vec3 unit_direction = unit_vector(r.direction());
        double t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
    }
}

HittableList random_scene() {
    HittableList world;

    world.add(std::make_shared<Sphere>(
        vec3(0, -1000, 0), 1000, std::make_shared<Lambertian>(vec3(0.5, 0.5, 0.5))));

    int i = 1;
    for (int a = -10; a < 10; a++) {
        for (int b = -10; b < 10; b++) {
            auto choose_mat = random_double();
            vec3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());
            if ((center - vec3(4, .2, 0)).length() > 0.9) {
                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = vec3::random() * vec3::random();
                    world.add(std::make_shared<MovingSphere>(
                        center, center + vec3(0, random_double(0, .5), 0), 0.0, 1.0, 0.2,
                        std::make_shared<Lambertian>(albedo)));
                }
                else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = vec3::random(.5, 1);
                    auto fuzz = random_double(0, .5);
                    world.add(
                        std::make_shared<Sphere>(center, 0.2, std::make_shared<Metal>(albedo, fuzz)));
                    /*world.add(std::make_shared<MovingSphere>(
                        center, center + vec3(0, random_double(0, .5), 0), 0.0, 1.0, 0.2,
                        std::make_shared<Metal>(albedo, fuzz)));*/
                }
                else {
                    // glass
                    world.add(std::make_shared<Sphere>(center, 0.2, std::make_shared<Dielectric>(1.5)));
                    /*world.add(std::make_shared<MovingSphere>(
                        center, center + vec3(0, random_double(0, .5), 0), 0.0, 1.0, 0.2,
                        std::make_shared<Dielectric>(1.5)));*/
                }
            }
        }
    }

    world.add(std::make_shared<Sphere>(vec3(0, 1, 0), 1.0, std::make_shared<Dielectric>(1.5)));
    world.add(std::make_shared<Sphere>(
        vec3(-4, 1, 0), 1.0, std::make_shared<Lambertian>(vec3(0.4, 0.2, 0.1))));
    world.add(std::make_shared<Sphere>(
        vec3(4, 1, 0), 1.0, std::make_shared<Metal>(vec3(0.7, 0.6, 0.5), 0.0)));

    return world;
}

HittableList world;

void RayTracingInOneThread(int k)
{
    double R = cos(M_PI / 4);

    Camera cam(lookfrom, lookat, vec3(0, 1, 0), 20, double(nx) / double(ny), aperture, dist_to_focus,0.0,1.0);

    for (int j = ny - k; j >= 0; j -= numThread)
    {
        for (int i = 0; i < nx; i++)
        {
            RecordProgressAndTime();
            vec3 col(0, 0, 0);
            for (int s = 0; s < samplesPerPixel; s++)
            {
                // TODO：采样噪声
                double u = double(i + random_float()) / double(nx);
                double v = double(j + random_float()) / double(ny);
                Ray r = cam.getRay(u, v);
                col += sampleOnce(r, world, 0);
            }
            col /= double(samplesPerPixel);
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);
            DrawPixel(i, j, ir, ig, ib);
            numPixelRendered++;
        }
    }
}

void RayTracing()
{
    /*nx = 300;
    ny = 200;
    samplesPerPixel = 100;*/
    // hittable *world = random_scene();
    world = random_scene();
    numPixelTotal = nx * ny;
    while (true)
    {
        while (!gRayTracingBegin)
        {
            //wait until begin
        }

        // curTime = GetCurrentTimeMs();
        gFrameFinished = false;
        if (!framebufferInited)
        {
            framebuffer = new int[display_w * display_h];
            lastFrameBuffer = new int[display_w * display_h];

            for (int i = 0; i < display_h * display_w; i++)
            {
                lastFrameBuffer[i] = 0;
            }
            framebufferInited = true;
        }
        numPixelRendered = 0;

        using std::ofstream;
        using std::to_string;
        using std::vector;
        using std::thread;

        ofstream outFile("output_" + to_string(nx) + "x" + to_string(ny) + ".ppm");
        outFile << "P3\n"
            << nx << " " << ny << "\n255\n";
        vector<thread> threads;

        for (int k = 0; k < numThread; k++)
        {
            threads.push_back(thread(RayTracingInOneThread, k));
        }

        for (auto& thread : threads)
        {
            thread.join();
        }
        gFrameFinished = true;
        Framebuffer2File(nx, ny, samplesPerPixel, framebuffer, outFile, progressDone);
        for (int i = 0; i < display_h * display_w; i++)
        {
            lastFrameBuffer[i] = framebuffer[i];
        }
        gRayTracingBegin = false;
    }

    return;
}

int main(int, char**)
{
    totTime = 0;
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    using std::thread;

    thread t(RayTracing);

    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;
    GLFWwindow* window = glfwCreateWindow(1800, 900, "Ray Tracing", NULL, NULL);
    if (window == NULL)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    //IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL2_Init();

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;

    // Main loop
    while (!glfwWindowShouldClose(window))
    {

        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            static double f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Ray Tracing"); // Create a window called "Hello, world!" and append into it.

            if (ImGui::Button("Start")) // Buttons return true when clicked (most widgets return true when edited/activated)
            {
                gRayTracingBegin = true;
            }

            ImGui::ProgressBar(progressDone, ImVec2(0.0f, 0.0f));
            // ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
            ImGui::InputInt(" speed", &speedFactor);
            // ImGui::SameLine();
            ImGui::Text("Thread Num: %d ", numThread);
            ImGui::Text("Image Size:  %d x %d ", nx, ny);
            ImGui::Text("Camera fov:  %d ", gFov);
            ImGui::Text("Camera aperture: %.3f ", (double)aperture);
            ImGui::Text("Camera dist to focus: %.3f ", (double)dist_to_focus);

            // ImGui::Text("Progress Bar");
            ImGui::Text("Total time %.3f s", (double)totTime / 1000);
            ImGui::Text("timeRemaining time %.3f s", timeRemaining);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window); // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }

        ImGui::Render();

        glfwGetFramebufferSize(window, &display_w, &display_h);

        glViewport(0, 0, display_w, display_h);
        glClearColor(0.0f, 0.0f, 0.00f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (framebufferInited)
        {
            if (gFrameFinished)
            {
                DrawFrame(framebuffer);
            }
            else
            {
                // DrawFrame(lastFrameBuffer);
                DrawFrame(framebuffer);
            }
            // DrawFrame(framebuffer);
        }


        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

        glfwMakeContextCurrent(window);

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

/*
* 一个简单的光追渲染器，目标是把它搞成乞丐版PBRT。
* 支持：
* 光源
* EXR全景图作为光源
* mesh支持
* UV支持 x 优先级靠后
* OBJ导入 x OBJ处理后导入
* 多种类型的相机
* 纹理 x 优先级靠后
* disney principled BRDF（万能BRDF）
* transparent BSDF（玻璃材质即可）
* 某一个BSSRDF
* spectrum （优先）
* CUDA渲染加速 （最优先）
* BVH加速结构
* json场景定义
* 导出PNG
* 
* 原则：
* 不导入任何平台相关的动态库和静态库
* 仅仅引入header-only库
* 
* 争取在一年之内做得差不离。 2022.2.23
*/
