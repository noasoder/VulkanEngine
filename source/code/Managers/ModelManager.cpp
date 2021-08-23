#include "ModelManager.h"

#include "VulkanManager.h"

#include <tiny_obj_loader.h>


ModelManager::ModelManager(VulkanManager* pVulkanManager)
: m_pVulkanManager(pVulkanManager)
{

}

ModelManager::~ModelManager()
{

}

void ModelManager::LoadModel()
{
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, MODEL_PATH.c_str())) {
        throw std::runtime_error(warn + err);
    }

    for (const auto& shape : shapes)
    {
        for (const auto& index : shape.mesh.indices) {
            Vertex vertex{};

            vertices.push_back(vertex);
            indices.push_back(indices.size());

            vertex.pos = {
                attrib.vertices[3 * index.vertex_index + 0],
                attrib.vertices[3 * index.vertex_index + 1],
                attrib.vertices[3 * index.vertex_index + 2]
            };

            vertex.texCoord = {
                attrib.texcoords[2 * index.texcoord_index + 0],
                1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
            };

            vertex.color = { 1.0f, 1.0f, 1.0f };
        }
    }
}