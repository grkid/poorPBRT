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
class Renderer
{
	int nx, ny;				// ͼƬ�ֱ���
	int samplesPerPixel;	// ÿ���ز�����
	int maxDepth;			// ���ݹ����
	int threadNum;			// �߳���

	std::vector<std::thread> threads;
	HittableList world;

	std::shared_ptr<Camera> camera;
	std::map<std::string, std::shared_ptr<Material>> materials;
	std::map<std::string, std::shared_ptr<Hittable>> objects;
	//std::map<std::string, std::shared_ptr<Light>> lightMaterials;
	std::map<std::string, std::shared_ptr<Texture>> textures;

	void printError(std::string str);

public:
	Renderer();
	Renderer(int x, int y, int samples, int depth,int tn,std::shared_ptr<Camera> camera);
	void setResolution(int x, int y);
	void setSamples(int n);
	void setCamera(std::shared_ptr<Camera> camera);
	void setMaxDepth(int d);
	void setThreadNum(int tn);
	// TODO�����������ӿ�����
	void addMaterial(std::string name, std::shared_ptr<Material> mat);
	void addObject(std::string name, std::shared_ptr<Hittable> obj);
	//void addLight(std::string name, std::shared_ptr<Light> light);
	void addTexture(std::string name, std::shared_ptr<Texture> tex);

	void render();

	void rebuildWorld(const WorldBuilder& wb);


};

