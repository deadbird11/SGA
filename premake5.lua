workspace "SGA"
    configurations {"Debug", "Release", "Dist"}
    staticruntime "off"
    architecture "x64"
    startproject "Sandbox"

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    project "SGA"
        kind "StaticLib"
        language "C++"

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
        
        filter "configurations:Release"
            defines {"NDEBUG"}
            optimize "on"

    project "Sandbox"
        kind "ConsoleApp"
        language "C++"
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
        