workspace "MyWorkspace"
   configurations { "Debug", "Release" }

project "VulkanEngine"
   kind "ConsoleApp"
   language "C++"
   files { "Scripts/**.h", "Scripts/**.cpp" }

   filter { "configurations:Debug" }
      defines { "DEBUG" }
      symbols "On"

   filter { "configurations:Release" }
      defines { "NDEBUG" }
      optimize "On"

    libdirs { "" }