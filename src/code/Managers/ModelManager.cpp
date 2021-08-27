#include "ModelManager.h"

#include "VulkanManager.h"

//#include "FBX/ofbx.h"
#include <unordered_map>
#include <tiny_obj_loader.h>
#include <string>
#include <memory>
#include "Model.h"


ModelManager::ModelManager(VulkanManager* pVulkanManager)
: m_pVulkanManager(pVulkanManager)
//, g_scene(nullptr)
{
    //pModel = new Model(pVulkanManager->m_pApplication, MODEL_CUBE_OBJ_PATH);
}

ModelManager::~ModelManager()
{

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
        LoadObj(path);
    }
    if (type == ".fbx")
    {
        LoadFbx(path);
    }
}

void ModelManager::LoadObj(std::string path)
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

            vertex.color = { 1.0f, 1.0f, 1.0f };

            if (uniqueVertices.count(vertex) == 0) {
                uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
                vertices.push_back(vertex);
            }

            indices.push_back(uniqueVertices[vertex]);
        }
    }
}

bool ModelManager::LoadFbx(std::string path)
{
    printf("load fbx");

    //FILE* fp = fopen(path.c_str(), "rb");

    //if (!fp) return false;

    //fseek(fp, 0, SEEK_END);
    //long file_size = ftell(fp);
    //fseek(fp, 0, SEEK_SET);
    //auto* content = new ofbx::u8[file_size];
    //fread(content, 1, file_size, fp);
    //scene = ofbx::load((ofbx::u8*)content, file_size, (ofbx::u64)ofbx::LoadFlags::TRIANGULATE);
    //if (!scene) {
    //    //OutputDebugString(ofbx::getError());
    //    printf("no g_scene");
    //}
    //else {
    //    //saveAsOBJ(*g_scene, "out.obj");
    //}
    //delete[] content;
    //fclose(fp);

    return true;
}