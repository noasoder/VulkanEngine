workspace "VulkanEngine"
    configurations { "Debug", "Release" }
    location "../source"
    targetdir "../Build"
    platforms { "Win64" }

    filter { "platforms:Win64" }
        system "windows"
        architecture "x86_64"
        cppdialect "C++17"

    includedirs { "C:/VulkanSDK/1.2.182.0/Include", "../Libraries/glfw-3.3.4.bin.WIN64/include", "../Libraries/glm", "../Libraries/stb", "../Libraries/tiny_obj_loader" , "../Libraries/OpenFBX", "../source/code" }
    libdirs { "C:/VulkanSDK/1.2.182.0/Lib", "../Libraries/glfw-3.3.4.bin.WIN64/lib-vc2019" }
    links { "vulkan-1.lib", "glfw3.lib" }

project "VulkanEngine"
    location "../source"
    kind "ConsoleApp"
    language "C++"
    files { "../source/**.h", "../source/**.cpp", "../source/**.vert", "../source/**.frag" }

    filter { "configurations:Debug" }
        targetname "VulkanEngine_Debug"
        defines { "DEBUG" }
        symbols "On"

    filter { "configurations:Release" }
        defines { "NDEBUG" }
        optimize "On"
