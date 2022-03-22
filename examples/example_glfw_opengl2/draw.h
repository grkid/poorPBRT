#pragma once


#include <iostream>
#include <fstream>
#include "imgui.h"
#include "vec3.h"
#include "point3.h"
// using namespace std;
using std::ofstream;
using std::endl;
class util
{
public:
    // BEGIN GLOBALVAR----------
    static int* framebuffer;
    static int display_w, display_h;
    static int numThread;
    static int nx;
    static int ny;
    static int samplesPerPixel;
    static int maxDepth;

    static int gFov;
    static point3 lookfrom;
    static vec3 lookat;
    static double dist_to_focus;
    static double aperture;

    static long curTime;
    static long totTime;
    static double timeRemaining;

    static ImVec4 clear_color;
    static double progressDone, progressDir;
    static bool gRayTracingBegin;


    static int numPixelTotal;
    static int numPixelRendered;
    static int doneRecord;
    static int framebufferInited;
    static int gFrameFinished;

    static int* lastFrameBuffer;

    static int speedFactor;
    // END GLOBALVAR----------

    static void RGB2Color(int& hex, const int& r, const int& g, const int& b);
    static void Color2RGB(const int& hex, int& r, int& g, int& b);
    static void DrawPixel(int x, int y, int c);
    static void DrawPixel(const int& x, const int& y, const int& r, const int& g, const int& b);
    static void DrawFrame();

    static void Framebuffer2File(int nx, int ny, int ns, int* fb, ofstream& outFile, double& progressDone);

    static void RecordProgressAndTime();
};