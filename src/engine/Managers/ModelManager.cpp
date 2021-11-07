#include "Managers/ModelManager.h"

#include "Managers/VulkanManager.h"

#include <unordered_map>
#include <tiny_obj_loader.h>
#include <OpenFBX/ofbx.h>
#include <string>
#include <memory>
#include "Model.h"


ModelManager::ModelManager()
{

}

ModelManager::~ModelManager()
{
    for (Model* model : m_pModels)
    {
        delete model;
    }
}

void ModelManager::Update(float DeltaTime, int imageIndex)
{
    for (Model* model : m_pModels)
    {
        model->Update(DeltaTime, imageIndex);
    }
}

Model* ModelManager::CreateModel(std::string path)
{
    Model* newModel = new Model(path);
    m_pModels.push_back(newModel);
    VulkanManager::Instance().UpdateCommandBuffers();

    printf("total models: %zi\n", m_pModels.size());

    return newModel;
}

void ModelManager::Recreate()
{
    for (Model* model : m_pModels)
    {
        model->CreateUniformBuffers();
        model->CreateDescriptorPool();
        model->CreateDescriptorSets();
    }
}

void ModelManager::CleanupUniformBuffers(size_t swapChainImagesSize)
{
    for (Model* model : m_pModels)
    {
        model->CleanupUniformBuffers(swapChainImagesSize);
    }
}

void ModelManager::LoadModel(std::string path, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices)
{
    char end[4]{'\0'};

    memcpy(end, path.c_str() + path.size() - 4, 4);

    std::string type;
    for (char ch : end)
    {
        type.push_back(ch);
    }

    if (type == ".obj")
    {
        LoadObj(path, vertices, indices);
    }
    if (type == ".fbx")
    {
        LoadFbx(path, vertices, indices);
    }
}

void ModelManager::LoadObj(std::string path, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices)
{
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.c_str())) {
        throw std::runtime_error(warn + err);
    }

    std::cout << "verts: " << attrib.vertices.size() << std::endl;
    std::unordered_map<Vertex, uint32_t> uniqueVertices{};

    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            Vertex vertex{};

            vertex.pos = {
                attrib.vertices[3 * index.vertex_index + 0],
                attrib.vertices[3 * index.vertex_index + 1],
                attrib.vertices[3 * index.vertex_index + 2]
            };

            vertex.texCoord = {
                attrib.texcoords[2 * index.texcoord_index + 0],
                1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
            };

            vertex.color = { 1.0f, 0.0f, 1.0f };

            if (uniqueVertices.count(vertex) == 0) {
                uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
                vertices.push_back(vertex);
            }

            indices.push_back(uniqueVertices[vertex]);
        }
    }
}

bool ModelManager::LoadFbx(std::string path, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices)
{
    ofbx::IScene* scene = nullptr;

    FILE* fp;
    fopen_s(&fp, path.c_str(), "rb");

    if (!fp) return false;

    fseek(fp, 0, SEEK_END);
    int file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    ofbx::u8* content = new ofbx::u8[file_size];
    fread(content, 1, file_size, fp);
    scene = ofbx::load((ofbx::u8*)content, file_size, (ofbx::u64)ofbx::LoadFlags::TRIANGULATE);
    if (!scene) 
    {
        printf("no scene");
    }
    else 
    {
        std::unordered_map<Vertex, uint32_t> uniqueVertices{};
        const int meshCount = scene->getMeshCount();
        int totalVerts = 0;

        for (int i = 0; i < meshCount; i++)
        {
            const ofbx::Mesh& mesh = *scene->getMesh(i);
            const ofbx::Geometry& geom = *mesh.getGeometry();
            int vertexCount = geom.getVertexCount();
            const ofbx::Vec3* newVerts = geom.getVertices();

            totalVerts += vertexCount;
            for (int j = 0; j < vertexCount; j++)
            {
                Vertex vertex{};

                vertex.pos.x = newVerts[j].x;
                vertex.pos.y = newVerts[j].y;
                vertex.pos.z = newVerts[j].z;
                
                vertex.texCoord = { 
                    geom.getUVs()[j].x,
                    geom.getUVs()[j].y
                };

                vertex.color = { 1.0f, 0.0f, 1.0f };

                if (uniqueVertices.count(vertex) == 0) {
                    uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
                    vertices.push_back(vertex);
                }

                indices.push_back(uniqueVertices[vertex]);
            }
        }
        std::cout << "verts: " << totalVerts << std::endl;
    }
    delete[] content;
    fclose(fp);

    return true;
}