# ------------------------------------------------------------------
# Set minimum required version of CMake
# ------------------------------------------------------------------
CMake_Minimum_Required(VERSION 2.8)

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
)

# ------------------------------------------------------------------
# Loader
# ------------------------------------------------------------------
Set(EVENTSCRIPTS_LOADER_HEADERS
    loader/loader_main.h
)

Set(EVENTSCRIPTS_LOADER_SOURCES
    loader/loader_main.cpp
)

Set(EVENTSCRIPTS_LOADER_FILES
    ${EVENTSCRIPTS_LOADER_HEADERS}
    ${EVENTSCRIPTS_LOADER_SOURCES}
)

# ------------------------------------------------------------------
# Utility
# ------------------------------------------------------------------
Set(EVENTSCRIPTS_UTIL_HEADERS
    core/utility/wrap_macros.h
)

Set(EVENTSCRIPTS_UTIL_SOURCES
)

Set(EVENTSCRIPTS_UTIL_FILES
    ${EVENTSCRIPTS_UTIL_HEADERS}
    ${EVENTSCRIPTS_UTIL_SOURCES}
)

# ------------------------------------------------------------------
# Core
# ------------------------------------------------------------------
Set(EVENTSCRIPTS_CORE_HEADERS 
	core/core/es_python.h
	core/core/es_main.h
    core/core/es_gamedir.h
)

Set(EVENTSCRIPTS_CORE_SOURCES
	core/core/es_python.cpp
	core/core/es_main.cpp
    core/core/es_gamedir.cpp
)

Set(EVENTSCRIPTS_CORE_FILES
	${EVENTSCRIPTS_CORE_HEADERS}
	${EVENTSCRIPTS_CORE_SOURCES}
)

# ------------------------------------------------------------------
# Addon system
# ------------------------------------------------------------------
Set(EVENTSCRIPTS_ADDON_HEADERS
    core/addons/es_addon.h
)

Set(EVENTSCRIPTS_ADDON_SOURCES
    core/addons/es_addon.cpp
)

Set(EVENTSCRIPTS_ADDON_FILES
    ${EVENTSCRIPTS_ADDON_HEADERS}
    ${EVENTSCRIPTS_ADDON_SOURCES}
)

# ------------------------------------------------------------------
# Modules
# ------------------------------------------------------------------
Set(EVENTSCRIPTS_MODULE_HEADERS
    core/modules/export_main.h
)

Set(EVENTSCRIPTS_MODULE_SOURCES
    core/modules/export_events.cpp
    core/modules/export_engine.cpp
    core/modules/export_main.cpp
	core/modules/export_player.cpp
	core/modules/export_entity.cpp
)

Set(EVENTSCRIPTS_MODULE_FILES
    ${EVENTSCRIPTS_MODULE_HEADERS}
    ${EVENTSCRIPTS_MODULE_SOURCES}
)

# ------------------------------------------------------------------
# Create source groups for everything to make our projects nice and 
# clean.
# ------------------------------------------------------------------
Source_Group("Header Files\\Addons"  FILES ${EVENTSCRIPTS_ADDON_HEADERS})
Source_Group("Source Files\\Addons"  FILES ${EVENTSCRIPTS_ADDON_SOURCES})

Source_Group("Header Files\\Core"    FILES ${EVENTSCRIPTS_CORE_HEADERS})
Source_Group("Source Files\\Core"    FILES ${EVENTSCRIPTS_CORE_SOURCES})

Source_Group("Header Files\\Modules" FILES ${EVENTSCRIPTS_MODULE_HEADERS})
Source_Group("Source Files\\Modules" FILES ${EVENTSCRIPTS_MODULE_SOURCES})

Source_Group("Header Files\\Util"    FILES ${EVENTSCRIPTS_UTIL_HEADERS})
Source_Group("Source Files\\Util"    FILES ${EVENTSCRIPTS_UTIL_SOURCES})

# ------------------------------------------------------------------
# All Eventscripts source files. Ideally we break out each group of 
# files into their own defines (as above with EVENTSCRIPTS_CORE_FILES.
# ------------------------------------------------------------------

# ------------------------------------------------------------------
# This basically creates the Eventscripts project. Certain project 
# attributes like Target_Link_Libraries need to be declared after 
# this line.
# ------------------------------------------------------------------
Add_Library(Core SHARED 
	${EVENTSCRIPTS_CORE_FILES}
    ${EVENTSCRIPTS_ADDON_FILES}
    ${EVENTSCRIPTS_MODULE_FILES}
    ${EVENTSCRIPTS_UTIL_FILES}
)

Add_Library(Eventscripts SHARED
    ${EVENTSCRIPTS_LOADER_FILES}
)

# ------------------------------------------------------------------
# Setup link libraries for this project.
# ------------------------------------------------------------------
Target_Link_Libraries(Core          ${EVENTSCRIPTS_LINK_LIBRARIES})
Target_Link_Libraries(Eventscripts  ${EVENTSCRIPTS_LINK_LIBRARIES})

# ------------------------------------------------------------------
# This is a hack for linux which doesn't seem to have proper
# configurations which breaks link libraries.
# ------------------------------------------------------------------
If(UNIX)
    If(CMAKE_BUILD_TYPE MATCHES Debug)
        Target_Link_Libraries(Core ${EVENTSCRIPTS_LINK_LIBRARIES_DEBUG})
    Else()
        Target_Link_Libraries(Core ${EVENTSCRIPTS_LINK_LIBRARIES_RELEASE})
    EndIf()
Else()
    # Do it the correct way.
    Target_Link_Libraries(Core ${EVENTSCRIPTS_LINK_LIBRARIES_DEBUG})
    Target_Link_Libraries(Core ${EVENTSCRIPTS_LINK_LIBRARIES_RELEASE})
EndIf()
