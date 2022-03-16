workspace "CCoMaS"
   configurations { "Debug", "Release" }

project "CCoMaS"
   kind "ConsoleApp"
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"

   files { "src/**.h", "src/**.c", "src/**.cpp", "src/**.hpp" }
   includedirs { "vendor", "src" }
   links { "lua" }
   cppdialect "c++20"

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"