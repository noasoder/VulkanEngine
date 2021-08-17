workspace "VulkanEngine"
    configurations { "Debug", "Release" }
    location "../Scripts"
    platforms { "Win64" }

    filter { "platforms:Win64" }
        system "windows"
        architecture "x86_64"
        cppdialect "C++17"

    includedirs { "C:/VulkanSDK/1.2.182.0/Include", "C:/Libraries/glfw-3.3.4.bin.WIN64/include", "C:/Libraries/glm" }
    libdirs { "C:/VulkanSDK/1.2.182.0/Lib", "C:/Libraries/glfw-3.3.4.bin.WIN64/lib-vc2019" }
    links { "vulkan-1.lib", "glfw3.lib" }

project "VulkanEngine"
    location "../Scripts"
    kind "ConsoleApp"
    language "C++"
    files { "../Scripts/**.h", "../Scripts/**.cpp" }

    filter { "configurations:Debug" }
        defines { "DEBUG" }
        symbols "On"

    filter { "configurations:Release" }
        defines { "NDEBUG" }
        optimize "On"
