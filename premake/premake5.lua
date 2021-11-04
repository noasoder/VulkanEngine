workspace "VulkanEngine"
    configurations { "Debug", "Release" }
    location "../src"
    targetdir "../bin"
    platforms { "Win64" }

    filter { "platforms:Win64" }
        system "windows"
        architecture "x86_64"
        cppdialect "C++17"

    includedirs { "C:/VulkanSDK/1.2.182.0/Include", "../lib/glfw-3.3.4.bin.WIN64/include", "../lib/glm", "../lib/stb", "../lib/tiny_obj_loader" , "../lib/OpenFBX", "../lib/imgui", "../include", "../src" }
    libdirs { "C:/VulkanSDK/1.2.182.0/Lib", "../lib/glfw-3.3.4.bin.WIN64/lib-vc2019" }
    links { "vulkan-1.lib", "glfw3.lib" }

project "VulkanEngine"
    location "../src"
    kind "ConsoleApp"
    language "C++"
    files { "../include/**.h", "../src/**.cpp", "../src/**.vert", "../src/**.frag" }

    filter { "configurations:Debug" }
        targetname "VulkanEngine_Debug"
        defines { "DEBUG" }
        symbols "On"

    filter { "configurations:Release" }
        defines { "NDEBUG" }
        optimize "On"