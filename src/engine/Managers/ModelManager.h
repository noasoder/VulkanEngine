#pragma once

#include "Vulkan.h"

#include <string>
#include <vector>
#include <array>

#define TINYOBJLOADER_IMPLEMENTATION

#include "Utility/Vertex.h"
#include "Utility/Singleton.h"

class Model;

class ModelManager : public Singleton<ModelManager>
{
public:
    ModelManager();
    ~ModelManager();

    void LoadModel(std::string path, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);
    void Update(float DeltaTime, int imageIndex);
    void Recreate();
    void CleanupUniformBuffers(size_t swapChainImagesSize);
    Model* CreateModel(std::string path);

	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

    std::vector<Model*> m_pModels;

private:
    void LoadObj(std::string path, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);
    bool LoadFbx(std::string path, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);
};