#include "Renderer.h"
#include "SpectrumUtil.h"

void Renderer::printError(std::string str)
{
	std::cout << "ERROR renderer: " << str << std::endl;
}

Renderer::Renderer()
{
}

Renderer::Renderer(int x, int y, int samples, int depth, int tn, std::shared_ptr<Camera> camera,std::shared_ptr<Background> bg)
{
	setResolution(x, y);
	setSamples(samples);
	setCamera(camera);
	setMaxDepth(depth);
	setThreadNum(tn);
    setBackground(bg);
}

void Renderer::setResolution(int x, int y)
{
	if (x <= 0 || y <= 0)
	{
		//std::cout << "ERROR Renderer: illegal resolution" << std::endl;
		printError("illegal resolution");
		nx = 320;
		ny = 240;
	}
	else
	{
		nx = x;
		ny = y;
	}

}

void Renderer::setSamples(int n)
{
	if (n <= 0)
	{
		printError("illegal samples per pixel");
		samplesPerPixel = 16;
	}
	else
		samplesPerPixel = n;
}

void Renderer::setCamera(std::shared_ptr<Camera> cam)
{
	camera = cam;
}

void Renderer::setMaxDepth(int d)
{
	if (d <= 0)
	{
		printError("illegal max depth");
		maxDepth = 32;
	}
	else
		maxDepth = d;
}

void Renderer::setThreadNum(int tn)
{
	if (tn <= 0)
	{
		printError("illegal thread num");
		threadNum = 4;
	}
	else
		threadNum = tn;
}

void Renderer::setBackground(std::shared_ptr<Background> bg)
{
    // 默认的背景为(0.1,0.1,0.1)
    if (bg)
        background = bg;
    else
        background = std::make_shared<ConstBackground>(rgb3(0.1, 0.1, 0.1));
}

void Renderer::addMaterial(std::string name, std::shared_ptr<Material> mat)
{
	materials.insert(std::pair<std::string,std::shared_ptr<Material>>(name, mat));
}

void Renderer::addObject(std::string name, std::shared_ptr<Hittable> obj)
{
	objects.insert(std::pair<std::string, std::shared_ptr<Hittable>>(name, obj));
}

void Renderer::addTexture(std::string name, std::shared_ptr<Texture> tex)
{
	textures.insert(std::pair<std::string, std::shared_ptr<Texture>>(name, tex));
}

SampledSpectrum Renderer::sampleOnce(const Ray& r, int depth)
{
    HitRecord rec;
    // 视距0.001到FLT_MAX
    util::RecordProgressAndTime();
    if (world.hit(r, 0.001, FLT_MAX, rec)) //射线命中物体
    {
        Ray scattered; //散射光线
        SampledSpectrum attenuation; //反射率
        if (depth >= maxDepth) {
            return SampledSpectrum(0.0);
        }
        else
        {
            SampledSpectrum emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);
            if (!rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
                return emitted;
            }
            else{
                return emitted+ attenuation * sampleOnce(scattered, depth + 1);
            }
        }
    }
    else
    {
        // 无法hit到任何物体，从background采样
        return background->sample(r);
    }
}

void Renderer::singleThreadRayTracing(int k)
{
	srand(k);

    for (int j = ny - k; j >= 0; j -= threadNum)
    {
        for (int i = 0; i < nx; i++)
        {
            SampledSpectrum col(0.0);
            for (int s = 0; s < samplesPerPixel; s++)
            {
                // TODO：采样噪声
                double u = double(i + random_float()) / double(nx);
                double v = double(j + random_float()) / double(ny);
                Ray r = camera->getRay(u, v);
                col += sampleOnce(r, 0);
            }
            col /= double(samplesPerPixel);
            //col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
            rgb3 colRgb = col.toXyz3().toRgb3();
            colRgb[0] = utilClamp(colRgb[0], 0.0, 1.0);
            colRgb[1] = utilClamp(colRgb[1], 0.0, 1.0);
            colRgb[2] = utilClamp(colRgb[2], 0.0, 1.0);

            int ir = int(255.99 * colRgb[0]);
            int ig = int(255.99 * colRgb[1]);
            int ib = int(255.99 * colRgb[2]);
            util::DrawPixel(i, j, ir, ig, ib);
            util::numPixelRendered++;
        }
    }
}

void Renderer::render()
{
	for (int k = 0; k < threadNum; k++) {
		threads.push_back(std::thread(&Renderer::singleThreadRayTracing,this, k));
	}

	for (int i = 0; i < threadNum; i++)
		threads[i].join();
}

void Renderer::rebuildWorld(const WorldBuilder& wb)
{
    world.clear();
	wb.build(world);
}
