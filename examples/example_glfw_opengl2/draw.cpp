#include "draw.h"
int util::numThread = 12;
int util::nx = 320*2;
int util::ny = 240*2;
int util::samplesPerPixel = 16;
int util::maxDepth = 32;

int util::gFov = 20;
point3 util::lookfrom(10 / 4, 8 / 4, 20 / 4);
vec3 util::lookat(0, 0, 0);
double util::dist_to_focus = 10.0;
double util::aperture = 0.001;

ImVec4 util::clear_color = ImVec4(0.0f, 0.0f, 0.00f, 1.00f);
double util::progressDone = 0.0f, progressDir = 1.0f;
bool util::gRayTracingBegin = false;

int util::numPixelRendered = 0;
int util::doneRecord = 0;
int util::framebufferInited = false;
int util::gFrameFinished = false;

int util::speedFactor = 1;

// 所有的static都必须初始化
int* util::framebuffer = nullptr;
int* util::lastFrameBuffer = nullptr;
int util::display_h = -1;
int util::display_w = -1;
long util::totTime = -1;
double util::timeRemaining = -1.0;
int util::numPixelTotal = -1;

void util::RGB2Color(int& c, const int& r, const int& g, const int& b)
{
    c = (r << 16) | (g << 8) | b;
}

void util::DrawPixel(int x, int y, int c)
{
    y = ny - y;
    framebuffer[y * display_w + x] = c;
}

void util::DrawPixel(const int& x, const int& y, const int& r, const int& g, const int& b)
{
    int c;
    RGB2Color(c, r, g, b);
    DrawPixel(x, y, c);
}

void util::Color2RGB(const int& c, int& r, int& g, int& b)
{
    r = (0xff << 16 & c) >> 16;
    g = (0xff << 8 & c) >> 8;
    b = 0xff & c;
}


void util::Framebuffer2File(int nx, int ny, int ns, int* fb, ofstream& outFile, double& progressDone)
{
    for (int j = (ny - 1); j >= 0; j--)
    {
        progressDone = double(ny - 1 - j) / (ny - 1);
        for (int i = 0; i < nx; i++)
        {
            int x = i;
            int y = ny - 1 - j;
            int c = fb[y * display_w + x];
            int r, g, b = 0;

            Color2RGB(c, r, g, b);

            outFile << r << " " << g << " " << b << endl;
        }
    }
}

void util::RecordProgressAndTime()
{
    progressDone = double(numPixelRendered) / (numPixelTotal);
    //totTime = (GetCurrentTimeMs() - curTime);
    //timeRemaining = totTime * (1 - progressDone) / progressDone / 1000; //根据过去的平均时间来计算剩余时间 x/t=pTodo/pDone -> x= t*pTodo/pDone = t*(1-pDone) /pDone
}