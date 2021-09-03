#pragma once

#include "Vulkan.h"

#include <ofbx.h>
#include <string>
#include <vector>
#include <array>

#define TINYOBJLOADER_IMPLEMENTATION

#include "Utility/Vertex.h"

class VulkanManager;
class Model;

class ModelManager
{
public:
    ModelManager(VulkanManager* pVulkanManager);
    ~ModelManager();

    void LoadModel(std::string path, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);


	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

    Model* pModel;

private:
    void LoadObj(std::string path);
    bool LoadFbx(std::string path);

    VulkanManager* m_pVulkanManager;

    //ofbx::IScene* scene;
};