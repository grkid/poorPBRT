#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <thread>
#include "vec3.h"
#include "Camera.h"
#include "Material.h"
#include "Hittable.h"
#include "HittableList.h"
#include "Light.h"
#include "Texture.h"
#include "WorldBuilder.h"
#include "draw.h"
#include "background.h"
#include "ConstBackground.h"
#include "SampledSpectrum.h"
#include "rgb3.h"
#include "xyz3.h"
class Renderer
{
	int nx, ny;				// 图片分辨率
	int samplesPerPixel;	// 每像素采样数
	int maxDepth;			// 最大递归深度
	int threadNum;			// 线程数

	std::vector<std::thread> threads;
	std::shared_ptr<Background> background;
	HittableList world;

	std::shared_ptr<Camera> camera;
	std::map<std::string, std::shared_ptr<Material>> materials;
	std::map<std::string, std::shared_ptr<Hittable>> objects;
	//std::map<std::string, std::shared_ptr<Light>> lightMaterials;
	std::map<std::string, std::shared_ptr<Texture>> textures;

	void printError(std::string str);

	SampledSpectrum sampleOnce(const Ray& r, int depth);
public:
	Renderer();
	Renderer(int x, int y, int samples, int depth,int tn,std::shared_ptr<Camera> camera,std::shared_ptr<Background> bg=nullptr);
	void setResolution(int x, int y);
	void setSamples(int n);
	void setCamera(std::shared_ptr<Camera> camera);
	void setMaxDepth(int d);
	void setThreadNum(int tn);
	void setBackground(std::shared_ptr<Background> bg);
	// TODO：把这三个接口用上
	void addMaterial(std::string name, std::shared_ptr<Material> mat);
	void addObject(std::string name, std::shared_ptr<Hittable> obj);
	//void addLight(std::string name, std::shared_ptr<Light> light);
	void addTexture(std::string name, std::shared_ptr<Texture> tex);

	void singleThreadRayTracing(int k);
	void render();

	void rebuildWorld(const WorldBuilder& wb);


};

