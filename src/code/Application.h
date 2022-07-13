#ifndef APPLICATION_H
#define APPLICATION_H

#include <string>

class Engine;
class NetHandler;

class Application
{
public:
    Application();
    ~Application();
    void Run();

private:
    const std::string MODEL_ROOM_PATH = "../bin/Assets/Models/viking_room.obj";
    //const std::string TEXTURE_PATH = "../bin/Assets/Textures/viking_room.png";
    const std::string TEXTURE_PATH = "../bin/Assets/Textures/DefaultTex.png";

    const std::string MODEL_CUBE_OBJ_PATH = "../bin/Assets/Models/Primitives/Cube.obj";
    const std::string MODEL_CUBE_FBX_PATH = "../bin/Assets/Models/Primitives/Cube.fbx";
    const std::string MODEL_ICOSPHERE_FBX_PATH = "../bin/Assets/Models/Primitives/Icosphere.fbx";
    const std::string TEXTURE_CUBE_PATH = "../bin/Assets/Textures/Texture.png";

    Engine* m_pEngine;

    NetHandler* m_pNetHandler = nullptr;
};

#endif // !APPLICATION_H