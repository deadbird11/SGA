workspace "SGA"
    configurations {"Debug", "Release", "Dist"}
    staticruntime "off"
    architecture "x64"
    startproject "Sandbox"

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    project "SGA"
        kind "StaticLib"
        language "C++17"

        location "SGA"
        
        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

        files {
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp"
        }

        filter "configurations:Debug"
            defines {"DEBUG"}
            symbols "on"
            runtime "MTd"
        
        filter "configurations:Release"
            defines {"NDEBUG"}
            optimize "on"
            runtime "MT"

    project "Sandbox"
        kind "ConsoleApp"
        language "C++17"
        staticruntime "on"
        location "Sandbox"

		targetdir ("bin/" .. outputdir .. "/Sandbox")
		objdir ("bin-int/" .. outputdir .. "/Sandbox")

        files {
            "Sandbox/src/**.h",
            "Sandbox/src/**.cpp"
        }

        includedirs {
            "SGA/src"
        }

        links
        {
            "SGA"
        }

        filter "configurations:Debug"
            defines {"DEBUG"}
            symbols "on"
        
        filter "configurations:Release"
            defines {"NDEBUG"}
            optimize "on"
        