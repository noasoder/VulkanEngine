#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H

#include "Vulkan.h"

#include <string>
#include <vector>
#include <array>

#define TINYOBJLOADER_IMPLEMENTATION

#include "Utility/Vertex.h"

class Model;

namespace ModelManager
{
    void Init();
    void Destroy();

    void LoadModel(std::string path, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);
    void Update(float DeltaTime, int imageIndex);
    void Recreate();
    void CleanupUniformBuffers(size_t swapChainImagesSize);
    Model* CreateModel(std::string path);
}

#endif // !MODEL_MANAGER_H