# ------------------------------------------------------------------
# Set minimum required version of CMake
# ------------------------------------------------------------------
CMake_Minimum_Required(VERSION 2.8)

# ------------------------------------------------------------------
# Loader
# ------------------------------------------------------------------
Set(SOURCEPYTHON_LOADER_HEADERS
    loader/loader_main.h
)

Set(SOURCEPYTHON_LOADER_SOURCES
    loader/loader_main.cpp
)

Set(SOURCEPYTHON_LOADER_FILES
    ${SOURCEPYTHON_LOADER_HEADERS}
    ${SOURCEPYTHON_LOADER_SOURCES}
)

# ------------------------------------------------------------------
# Utility
# ------------------------------------------------------------------
Set(SOURCEPYTHON_UTIL_HEADERS
    core/utility/wrap_macros.h
	core/utility/mrecipientfilter.h
  core/utility/ipythongenerator.h
)

Set(SOURCEPYTHON_UTIL_SOURCES
	core/utility/mrecipientfilter.cpp
)

Set(SOURCEPYTHON_UTIL_FILES
    ${SOURCEPYTHON_UTIL_HEADERS}
    ${SOURCEPYTHON_UTIL_SOURCES}
)

# ------------------------------------------------------------------
# Core
# ------------------------------------------------------------------
Set(SOURCEPYTHON_CORE_HEADERS 
	core/core/sp_python.h
	core/core/sp_main.h
    core/core/sp_gamedir.h
)

Set(SOURCEPYTHON_CORE_SOURCES
	core/core/sp_python.cpp
	core/core/sp_main.cpp
    core/core/sp_gamedir.cpp
)

Set(SOURCEPYTHON_CORE_FILES
	${SOURCEPYTHON_CORE_HEADERS}
	${SOURCEPYTHON_CORE_SOURCES}
)

# ------------------------------------------------------------------
# Addon system
# ------------------------------------------------------------------
Set(SOURCEPYTHON_ADDON_HEADERS
    core/addons/sp_addon.h
)

Set(SOURCEPYTHON_ADDON_SOURCES
    core/addons/sp_addon.cpp
)

Set(SOURCEPYTHON_ADDON_FILES
    ${SOURCEPYTHON_ADDON_HEADERS}
    ${SOURCEPYTHON_ADDON_SOURCES}
)

# ------------------------------------------------------------------
# Modules
# ------------------------------------------------------------------
Set(SOURCEPYTHON_MODULE_HEADERS
    core/modules/export_main.h
    core/modules/export_player.h
    core/modules/export_entity.h
)

Set(SOURCEPYTHON_MODULE_SOURCES
    core/modules/export_events.cpp
    core/modules/export_main.cpp
	core/modules/export_player.cpp
	core/modules/export_entity.cpp
	core/modules/export_shared.cpp
	core/modules/export_cvar.cpp
    core/modules/export_misc.cpp
)

# ------------------------------------------------------------------
# Engine module
# ------------------------------------------------------------------
Set(SOURCEPYTHON_MODULE_ENGINE_SOURCES
    core/modules/engine/engine_main.cpp
    core/modules/engine/engine_server.cpp
    core/modules/engine/engine_basehandle.cpp
    core/modules/engine/engine_misc.cpp
)

# ------------------------------------------------------------------
# Cvar module
# ------------------------------------------------------------------
Set(SOURCEPYTHON_MODULE_CVAR_SOURCES
    core/modules/cvar/cvar_concommandbase.cpp
    core/modules/cvar/cvar_convar.cpp
    core/modules/cvar/cvar_flags.cpp
    core/modules/cvar/cvar_icvar.cpp
)

# ------------------------------------------------------------------
# All module fiels
# ------------------------------------------------------------------
Set(SOURCEPYTHON_MODULE_FILES
    ${SOURCEPYTHON_MODULE_HEADERS}
    ${SOURCEPYTHON_MODULE_SOURCES}
    
    ${SOURCEPYTHON_MODULE_ENGINE_SOURCES}
    ${SOURCEPYTHON_MODULE_CVAR_SOURCES}
)

# ------------------------------------------------------------------
# Create source groups for everything to make our projects nice and 
# clean.
# ------------------------------------------------------------------
Source_Group("Header Files\\Addons"  FILES ${SOURCEPYTHON_ADDON_HEADERS})
Source_Group("Source Files\\Addons"  FILES ${SOURCEPYTHON_ADDON_SOURCES})

Source_Group("Header Files\\Core"    FILES ${SOURCEPYTHON_CORE_HEADERS})
Source_Group("Source Files\\Core"    FILES ${SOURCEPYTHON_CORE_SOURCES})

Source_Group("Header Files\\Modules" FILES ${SOURCEPYTHON_MODULE_HEADERS})
Source_Group("Source Files\\Modules" FILES ${SOURCEPYTHON_MODULE_SOURCES})

Source_Group("Header Files\\Modules\\Engine" FILES ${SOURCEPYTHON_MODULE_ENGINE_HEADERS})
Source_Group("Source Files\\Modules\\Engine" FILES ${SOURCEPYTHON_MODULE_ENGINE_SOURCES})

Source_Group("Header Files\\Util"    FILES ${SOURCEPYTHON_UTIL_HEADERS})
Source_Group("Source Files\\Util"    FILES ${SOURCEPYTHON_UTIL_SOURCES})

# ------------------------------------------------------------------
# All SourcePython source files. Ideally we break out each group of 
# files into their own defines (as above with SOURCEPYTHON_CORE_FILES.
# ------------------------------------------------------------------

# ------------------------------------------------------------------
# This basically creates the SourcePython project. Certain project 
# attributes like Target_Link_Libraries need to be declared after 
# this line.
# ------------------------------------------------------------------
Add_Library(core SHARED 
	${SOURCEPYTHON_CORE_FILES}
    ${SOURCEPYTHON_ADDON_FILES}
    ${SOURCEPYTHON_MODULE_FILES}
    ${SOURCEPYTHON_UTIL_FILES}
)

Add_Library(source-python SHARED
    ${SOURCEPYTHON_LOADER_FILES}
)

# ------------------------------------------------------------------
# Include the base makefile.
# ------------------------------------------------------------------
If(WIN32)
	include("makefiles/win32/win32.base.cmake")
Else()
	include("makefiles/linux/linux.base.cmake")
EndIf()

# ------------------------------------------------------------------
# Include the game makefile.
# ------------------------------------------------------------------
include("makefiles/game/${GAME}.cmake")

# ------------------------------------------------------------------
# Definitions
# ------------------------------------------------------------------
Add_Definitions(
	-DSOURCE_ENGINE=${SOURCE_ENGINE}
    -DBOOST_PYTHON_MAX_ARITY=16
)

# ------------------------------------------------------------------
# Setup link libraries for this project.
# ------------------------------------------------------------------
Target_Link_Libraries(core          ${SOURCEPYTHON_LINK_LIBRARIES})
Target_Link_Libraries(source-python ${SOURCEPYTHON_LINK_LIBRARIES})

# ------------------------------------------------------------------
# This is a hack for linux which doesn't seem to have proper
# configurations which breaks link libraries.
# ------------------------------------------------------------------
If(UNIX)
    If(CMAKE_BUILD_TYPE MATCHES Debug)
        Target_Link_Libraries(core ${SOURCEPYTHON_LINK_LIBRARIES_DEBUG})
    Else()
        Target_Link_Libraries(core ${SOURCEPYTHON_LINK_LIBRARIES_RELEASE})
    EndIf()
Else()
    # Do it the correct way.
    Target_Link_Libraries(core ${SOURCEPYTHON_LINK_LIBRARIES_DEBUG})
    Target_Link_Libraries(core ${SOURCEPYTHON_LINK_LIBRARIES_RELEASE})
EndIf()