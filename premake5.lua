workspace "RayTracingInAWeekend"
    configurations { "Debug", "Release" }


project "RayTracingInAWeekend"
    kind "ConsoleApp"
    language "C"
    targetdir "bin/%{cfg.buildcfg}"

    files { "src/**.h", "src/**.c" }

    links "m"

    filter "Configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "Configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
