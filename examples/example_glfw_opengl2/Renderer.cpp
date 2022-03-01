#include "Renderer.h"

void Renderer::printError(std::string str)
{
	std::cout << "ERROR renderer: " << str << std::endl;
}

Renderer::Renderer()
{
}

Renderer::Renderer(int x, int y, int samples, int depth, int tn, std::shared_ptr<Camera> camera)
{
	setResolution(x, y);
	setSamples(samples);
	setCamera(camera);
	setMaxDepth(depth);
	setThreadNum(tn);
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

void Renderer::render()
{
}

void Renderer::rebuildWorld(const WorldBuilder& wb)
{
	wb.build(world);
}
