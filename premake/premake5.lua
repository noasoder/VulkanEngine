workspace "VulkanEngine"
    configurations { "Debug", "Release" }
    location "../src"
    targetdir "../bin"
    platforms { "Win64" }

    filter { "platforms:Win64" }
        system "windows"
        architecture "x86_64"
        cppdialect "C++17"

    includedirs { "C:/VulkanSDK/1.2.182.0/Include", "../lib/glfw-3.3.4.bin.WIN64/include", "../lib/glm", "../lib/stb", "../lib/tiny_obj_loader" , "../lib/OpenFBX", "../lib/imgui", "../src/engine", "../src/code", "../src/openfbx" }
    libdirs { "C:/VulkanSDK/1.2.182.0/Lib", "../lib/glfw-3.3.4.bin.WIN64/lib-vc2019", "-LC:/Program Files (x86)/Windows Kits/10/Lib/10.0.20348.0/um/x86" }
    links { "vulkan-1.lib", "glfw3.lib", "-lWS2_32.lib" }

project "VulkanEngine"
    location "../src"
    kind "ConsoleApp"
    language "C++"
    files { "../src/**.h", "../src/**.cpp", "../src/**.c", "../src/**.vert", "../src/**.frag" }

    filter { "configurations:Debug" }
        targetname "VulkanEngine_Debug"
        defines { "DEBUG" }
        symbols "On"

    filter { "configurations:Release" }
        defines { "NDEBUG" }
        optimize "On"
