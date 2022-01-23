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

    libdirs { 
        "../lib/glfw/buildvs/src/Release" 
        , "../lib/opengl/"
    }

    links { 
        "glfw3.lib"
        , "opengl32.lib"
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
