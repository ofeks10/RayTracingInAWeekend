workspace "RayTracingInAWeekend"
    configurations { "Debug", "Release" }


project "RayTracingInAWeekend"
    kind "ConsoleApp"
    language "C"
    targetdir "bin/%{cfg.buildcfg}"

    files { "**.h", "**.c" }

    filter "Configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "Configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
