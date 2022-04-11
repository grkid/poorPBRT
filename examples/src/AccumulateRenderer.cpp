#include "AccumulateRenderer.h"

AccumulateRenderer::AccumulateRenderer()
{
}

AccumulateRenderer::AccumulateRenderer(int x, int y, int samples, int depth, int tn, std::shared_ptr<Camera> camera, std::shared_ptr<Background> bg):
    Renderer(x, y, samples, depth, tn, camera,bg)
{
}

void AccumulateRenderer::singleThreadRayTracing(int k)
{
    srand(k);


    for (int s = 0; s < samplesPerPixel; s++) {
        for (int j = ny - k; j >= 0; j -= threadNum)
        {
            for (int i = 0; i < nx; i++)
            {
                SampledSpectrum col(0.0);

                // TODO£º²ÉÑùÔëÉù
                double u = double(i + random_float()) / double(nx);
                double v = double(j + random_float()) / double(ny);
                Ray r = camera->getRay(u, v);
                col += sampleOnce(r, 0);

                col /= double(samplesPerPixel);
                //col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
                rgb3 colRgb = col.toXyz3().toRgb3();
                colRgb[0] = utilClamp(colRgb[0], 0.0, 1.0);
                colRgb[1] = utilClamp(colRgb[1], 0.0, 1.0);
                colRgb[2] = utilClamp(colRgb[2], 0.0, 1.0);

                int _r = 0, _g = 0, _b = 0;
                util::getPixel(i, j, _r, _g, _b);
                

                int ir = int(255.99 * colRgb[0]/samplesPerPixel)+_r;
                int ig = int(255.99 * colRgb[1] / samplesPerPixel)+_g;
                int ib = int(255.99 * colRgb[2] / samplesPerPixel)+_b;
                util::DrawPixel(i, j, ir, ig, ib);
                // util::numPixelRendered++;
            }
        }
    }
}
