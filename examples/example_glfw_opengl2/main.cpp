
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
#include "Surface.h"
#include "Camera.h"
#include "Texture.h"
#include "Light.h"
#include "Renderer.h"
#include "BasicWorldBuilder.h"
#include "CuboidWorldBuilder.h"
#include "InitBackground.h"
#include "SampledSpectrum.h"

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

void DrawFrame(int* fb)
{

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, util::display_w, 0.0, util::display_h, 0.0, 1.0);
    glBegin(GL_POINTS);

    for (int i = 0; i < util::display_h; i++)
    {

        int r, g, b;
        for (int j = 0; j < util::display_w; j++)
        {
            util::Color2RGB(fb[i * util::display_w + j], r, g, b);
            glColor3f((double)r / 255, (double)g / 255, (double)b / 255);
            glVertex3f(j + 20, util::display_h - i - 300, 0);
        }
    }

    glEnd();
}

void globalInit()
{
    SampledSpectrum::init();
}

void entrance()
{   
    auto cam=std::make_shared<Camera>(util::lookfrom, util::lookat, vec3(0, 0, 1), 20, double(util::nx) / double(util::ny), util::aperture, util::dist_to_focus, 0.0, 0.0);
    Renderer r(util::nx, util::ny, util::samplesPerPixel, util::maxDepth, util::numThread, cam,std::make_shared<ConstBackground>(rgb3(1.5,1.5,1.5)));
    r.rebuildWorld(BasicWorldBuilder());
    r.render();
}


void RayTracing()
{
    util::numPixelTotal = util::nx * util::ny;
    while (true)
    {
        while (!util::gRayTracingBegin)
        {
            //wait until begin
        }

        // curTime = GetCurrentTimeMs();
        util::gFrameFinished = false;
        if (!util::framebufferInited)
        {
            util::framebuffer = new int[util::display_w * util::display_h];
            util::lastFrameBuffer = new int[util::display_w * util::display_h];

            for (int i = 0; i < util::display_h * util::display_w; i++)
            {
                util::lastFrameBuffer[i] = 0;
            }
            util::framebufferInited = true;
        }
        util::numPixelRendered = 0;

        using std::ofstream;
        using std::to_string;
        using std::vector;
        using std::thread;

        ofstream outFile("output_" + to_string(util::nx) + "x" + to_string(util::ny) + ".ppm");
        outFile << "P3\n"
            << util::nx << " " << util::ny << "\n255\n";
       
        // 外面的代码不再修改
        entrance();

        util::gFrameFinished = true;
        util::Framebuffer2File(util::nx, util::ny, util::samplesPerPixel, util::framebuffer, outFile, util::progressDone);
        for (int i = 0; i < util::display_h * util::display_w; i++)
        {
            util::lastFrameBuffer[i] = util::framebuffer[i];
        }
        util::gRayTracingBegin = false;
    }

    return;
}

int main(int, char**)
{
    globalInit();

    util::totTime = 0;
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
                util::gRayTracingBegin = true;
            }

            ImGui::ProgressBar(util::progressDone, ImVec2(0.0f, 0.0f));
            // ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
            ImGui::InputInt(" speed", &util::speedFactor);
            // ImGui::SameLine();
            ImGui::Text("Thread Num: %d ", util::numThread);
            ImGui::Text("Image Size:  %d x %d ", util::nx, util::ny);
            ImGui::Text("Camera fov:  %d ", util::gFov);
            ImGui::Text("Camera aperture: %.3f ", (double)util::aperture);
            ImGui::Text("Camera dist to focus: %.3f ", (double)util::dist_to_focus);

            // ImGui::Text("Progress Bar");
            ImGui::Text("Total time %.3f s", (double)util::totTime / 1000);
            ImGui::Text("timeRemaining time %.3f s", util::timeRemaining);
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

        glfwGetFramebufferSize(window, &util::display_w, &util::display_h);

        glViewport(0, 0, util::display_w, util::display_h);
        glClearColor(0.0f, 0.0f, 0.00f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (util::framebufferInited)
        {
            if (util::gFrameFinished)
            {
                DrawFrame(util::framebuffer);
            }
            else
            {
                // DrawFrame(lastFrameBuffer);
                DrawFrame(util::framebuffer);
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
* 光源 done
* EXR全景图作为光源
* mesh支持
* UV支持 x 优先级靠后
* OBJ导入 x OBJ处理后导入
* 多种类型的相机
* 纹理 图片纹理
* disney principled BRDF（万能BRDF）
* transparent BSDF（玻璃材质即可）
* 某一个BSSRDF
* spectrum （优先）
* CUDA渲染加速 （最优先）
* BVH加速结构
* json场景定义
* 导出PNG
* 几个噪声算法
* 背景
* 
* 原则：
* 不导入任何平台相关的动态库和静态库
* 仅仅引入header-only库
* 
* 争取在一年之内做得差不离。 2022.2.23
* 
* Moving需要做解耦。
* 
* 2022.2.28:出现与视角相关的pattern。可能是Camera的实现问题。
* 
* 2022.3.35：Spectrum完成。抄的PBRT实现。
*/
