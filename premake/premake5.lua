workspace "VulkanEngine"
    configurations { "Debug", "Release" }
    location "../src"
    targetdir "../bin"
    platforms { "Win64", "Linux" }
    
    includedirs 
    { 
        "C:/VulkanSDK/1.2.198.0/Include"
        , "../lib/glfw-3.3.5.bin.WIN64/include"
        , "../lib/glm"
        , "../lib/stb"
        , "../lib/tiny_obj_loader"
        , "../lib/OpenFBX"
        , "../lib/imgui"
        , "../src/engine"
        , "../src/code"
        , "../src/openfbx"
        , "../src/utility" 
    }

    filter { "platforms:Win64" }
        system "windows"
        architecture "x86_64"
        cppdialect "C++17"
        links
        {
            "WS2_32" 
        }
        defines
        {
            "WINDOWS"
        }
        libdirs 
        { 
            "C:/VulkanSDK/1.2.198.0/Lib"
            , "../lib/glfw-3.3.5.bin.WIN64/lib-vc2022" 
        }

    filter { "platforms:Linux" }
        system "linux"
        architecture "x86_64"
        cppdialect "C++17"
        defines
        {
            "LINUX"
        }

    links 
    { 
        "vulkan-1.lib"
        , "glfw3.lib"
    } 

project "VulkanEngine"
    location "../src"
    kind "ConsoleApp"
    language "C++"
    files { 
        "../src/**.h"
        , "../src/**.cpp"
        , "../src/**.c"
        , "../src/**.vert"
        , "../src/**.frag" 
    }

    filter { "configurations:Debug" }
        targetname "VulkanEngine_Debug"
        defines { "DEBUG" }
        symbols "On"

    filter { "configurations:Release" }
        defines { "NDEBUG" }
        optimize "On"
