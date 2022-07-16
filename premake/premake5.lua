workspace "VulkanEngine"
    configurations { "Debug", "Release" }
    location "../src"
    targetdir "../bin"
    platforms { "Win64" }

    filter { "platforms:Win64" }
        system "windows"
        architecture "x86_64"
        cppdialect "C++17"
        defines {
            "WINDOWS"
        }

    includedirs { 
        "../lib/glfw/include"
        , "../lib/glew/include"
        , "../lib/glm"
        , "../lib/tiny_obj_loader"
        , "../lib/OpenFBX"
        , "../lib/imgui"
        , "../lib/vulkan/Include"

        , "../src/engine"
        , "../src/code"
        , "../src/utility" 

        , "../src/stb"
        , "../src/json"
        , "../src/openfbx"
    }

    libdirs { 
        "../lib/glfw/buildvs/src/Release" 
        , "../lib/glew/lib"
        , "../lib/opengl"
        , "../lib/vulkan/Lib"
    }

    links { 
        "glfw3.lib"
        , "glew32s.lib"
        , "vulkan-1.lib"
        , "opengl32"
        , "WS2_32" 
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

project "Editor"
    location "../editor"
    kind "ConsoleApp"
    configurations { "Editor" }
    language "C++"
    files { 
        "../editor/**.h"
        , "../editor/**.cpp"
        , "../editor/**.c"
    }