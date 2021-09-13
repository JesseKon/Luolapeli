workspace "Luolapeli"
    architecture "x86"
    startproject "Luolapeli"
    configurations { "Debug", "Release" }

project "Luolapeli"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir "bin/%{cfg.buildcfg}"

    files {
        "%{prj.name}/**.h",
		"%{prj.name}/**.cpp",
    }

    includedirs {
        "dependencies/include"
    }

    libdirs {
        "dependencies/lib/x86"
    }

    links {
        "SDL2", "SDL2main", "SDL2_mixer"
    }

    filter "configurations:Debug"
        defines "NDEBUG"
        symbols "On"

    filter "configurations:Release"
        optimize "On"