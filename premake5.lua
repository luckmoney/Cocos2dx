workspace "Cocos2dx"
    architecture "x86"
    startproject "Cocos2dx"
    location "build"
    systemversion "10.0.17763.0"


    configurations
    {
        "Debug",
        "Release"
    }

    flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Cocos2dx"
    location "build"
    kind "ConsoleApp"
    language "C++"
	staticruntime "on"

    targetdir ("bin/"..outputdir .."/%{prj.name}")
    objdir ("bin-int/"..outputdir .. "/%{prj.name}")

    files 
    {
        "%{prj.name}/**.h",
        "%{prj.name}/**.cpp",
        "%{prj.name}/**.c",
    }

    -- excludes 
    -- {
    --     "%{prj.name}/src/imgui/**"
    -- }

    defines
	{
		--"_CRT_SECURE_NO_WARNINGS"
	}

    includedirs {
        "%{prj.name}/Indepence/GLAD/include",
        "%{prj.name}/Indepence/GLFW/include",
        "%{prj.name}/Indepence/GLM",
        "%{prj.name}/Indepence/Assimp/include",
        "%{prj.name}/src"
    }


    libdirs {
        "%{prj.name}/Indepence/GLFW/lib",
        "%{prj.name}/Indepence/Assimp/lib",
    }

    filter "system:windows"
        systemversion "10.0.17763.0"


    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"
        links {
            "glfw3","opengl32","assimp"
        }

    filter "configurations:Release"
        runtime "Release"
        optimize "on"
        links {
            "glfw3","opengl32","assimp"
        }

    configuration "windows"
        postbuildcommands {
             ("{COPY} %{wks.location}../%{prj.name}/shader    %{wks.location}../bin/"..outputdir .."/%{prj.name}/shader"),
             ("{COPY} %{wks.location}../%{prj.name}/res   %{wks.location}../bin/"..outputdir .."/%{prj.name}/res"),
       
        }

    configuration "Debug"
        buildoptions "/MDd"
 

    configuration "Release"
        buildoptions "/MD"