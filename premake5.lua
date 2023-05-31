workspaceName = "SadGameEngine"

workspace (workspaceName)
    configurations { "WinX64", "PSP" }
    cdialect "C99"

project (workspaceName)
    kind "ConsoleApp"
    language "C"
    location "build"
    targetdir "bin/%{cfg.buildcfg}"

    files {
        "src/**.h",
        "src/**.c"
    }

    defines {
        "NDEBUG"
    }

    optimize "On"

-- Win64 Settings
    filter { "configurations:WinX64" }

        architecture "x86_64"

        includedirs { "third-party/stb" }
        includedirs { "third-party/glew/include" }
        libdirs { "third-party/glew/lib/Release/x64" }

        links { "opengl32.lib" }
        links { "glew32s.lib" }
        links { "xinput.lib" }

-- PSP Settings
    filter { "configurations:PSP" }

        local PSPDEV = os.getenv("PSPDEV")
        local PSPSDK = os.getenv("PSPSDK")

    if PSPDEV ~= nil and  PSPSDK ~= nil
    then

        includedirs {
            PSPDEV .. "/psp/include",
            PSPSDK .. "/include"
        }
        
        libdirs {
            PSPDEV .. "/psp/lib",
            PSPSDK .. "/lib"
        }

        links {
            --os.getenv("PSPSDK") .. "/lib/prxexports.o",
            "pspdebug", "pspdisplay", "pspge", "pspctrl", "pspnet", "pspnet_apctl", "pspgu", "pspgum"
        }

        linkoptions {
            "-Wl,-zmax-page-size=128",
            "-D_PSP_FW_VERSION=150"
        }

        buildoptions {
            "-D_PSP_FW_VERSION=150"
        }

        makesettings {
            "CC = psp-gcc"
        }

        defines {
            
        }

        postbuildcommands {
            "psp-fixup-imports ../bin/%{cfg.buildcfg}/%{prj.name}",
            "mksfo '%{prj.name}' PARAM.SFO",
            "psp-strip ../bin/%{cfg.buildcfg}/%{prj.name} -o ../bin/%{cfg.buildcfg}/%{prj.name}_stripped",
            "pack-pbp ../bin/%{cfg.buildcfg}/EBOOT.PBP PARAM.SFO NULL NULL NULL NULL NULL ../bin/%{cfg.buildcfg}/%{prj.name}_stripped NULL"
        }

    end