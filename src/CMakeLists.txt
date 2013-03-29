# ------------------------------------------------------------------
# Set minimum required version of CMake
# ------------------------------------------------------------------
CMake_Minimum_Required(VERSION 2.8)

# ------------------------------------------------------------------
# Includes the CMake file for the current game.
# ------------------------------------------------------------------
include("makefiles/game/${GAME}.cmake")

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
# Generic plugin stuff.
# ------------------------------------------------------------------
Set(SOURCEPYTHON_GENERIC_HEADERS
	core/modules/export_main.h
	core/modules/cvar/cvar_concommand.h
)

Set(SOURCEPYTHON_GENERIC_SOURCES
	core/modules/export_main.cpp
	core/modules/cvar/cvar_concommand.cpp
)

Set(SOURCEPYTHON_GENERIC_FILES
	${SOURCEPYTHON_GENERIC_HEADERS}
	${SOURCEPYTHON_GENERIC_SOURCES}
)

# ------------------------------------------------------------------
# Engine module.
# ------------------------------------------------------------------
Set(SOURCEPYTHON_ENGINE_MODULE_HEADERS
	core/modules/engine/eiface_wrap.h
    core/modules/engine/eiface_engine_base.h
    core/modules/engine/engine${SOURCE_ENGINE}/eiface_engine_implementation.h
)

Set(SOURCEPYTHON_ENGINE_MODULE_SOURCES
    core/modules/engine/eiface_wrap.cpp
    core/modules/engine/eiface_engine_base.cpp
    core/modules/engine/engine${SOURCE_ENGINE}/eiface_engine_implementation.cpp
    core/modules/engine/eiface_wrap_python.cpp
)

Set(SOURCEPYTHON_ENGINE_MODULE_FILES
	${SOURCEPYTHON_ENGINE_MODULE_HEADERS}
	${SOURCEPYTHON_ENGINE_MODULE_SOURCES}
)

# ------------------------------------------------------------------
# Engine / Usermessage module.
# ------------------------------------------------------------------
Set(SOURCEPYTHON_ENGINE_USERMESSAGE_MODULE_HEADERS
    core/modules/engine/usermessage/usermessage.h
    core/modules/engine/usermessage/usermessage_implementation_base.h
    core/modules/engine/usermessage/${SOURCE_GAME}/usermessage_implementation.h
)

Set(SOURCEPYTHON_ENGINE_USERMESSAGE_MODULE_SOURCES
    core/modules/engine/usermessage/usermessage.cpp
    core/modules/engine/usermessage/usermessage_implementation_base.cpp
    core/modules/engine/usermessage/${SOURCE_GAME}/usermessage_implementation.cpp
)

Set(SOURCEPYTHON_ENGINE_USERMESSAGE_MODULE_FILES
	${SOURCEPYTHON_ENGINE_USERMESSAGE_MODULE_HEADERS}
	${SOURCEPYTHON_ENGINE_USERMESSAGE_MODULE_SOURCES}
)

# ------------------------------------------------------------------
# Event module.
# ------------------------------------------------------------------
Set(SOURCEPYTHON_EVENT_MODULE_HEADERS
    core/modules/events/events_wrap.h
)

Set(SOURCEPYTHON_EVENT_MODULE_SOURCES
    core/modules/events/events_wrap.cpp
    core/modules/events/events_wrap_python.cpp
)

# ------------------------------------------------------------------
# Entities module
# ------------------------------------------------------------------
Set(SOURCEPYTHON_ENTITY_MODULE_HEADERS
    core/modules/entities/entities_wrap.h
    core/modules/entities/entities_props.h
)

Set(SOURCEPYTHON_ENTITY_MODULE_SOURCES
    core/modules/entities/entities_props.cpp
    core/modules/entities/entities_wrap.cpp
    core/modules/entities/entities_wrap_python.cpp
)

# ------------------------------------------------------------------
# All module source files
# ------------------------------------------------------------------
Set(SOURCEPYTHON_MODULE_FILES
	${SOURCEPYTHON_ENGINE_MODULE_FILES}
    ${SOURCEPYTHON_ENGINE_USERMESSAGE_MODULE_FILES}
    
    ${SOURCEPYTHON_EVENT_MODULE_HEADERS}
    ${SOURCEPYTHON_EVENT_MODULE_SOURCES}
    
    ${SOURCEPYTHON_ENTITY_MODULE_HEADERS}
    ${SOURCEPYTHON_ENTITY_MODULE_SOURCES}
)

# ------------------------------------------------------------------
# Create source groups for everything to make our projects nice and 
# clean.
# ------------------------------------------------------------------
Source_Group("Header Files\\Addons"			                FILES ${SOURCEPYTHON_ADDON_HEADERS})
Source_Group("Header Files\\Core"   		                FILES ${SOURCEPYTHON_CORE_HEADERS})
Source_Group("Header Files\\Util"   		                FILES ${SOURCEPYTHON_UTIL_HEADERS})
Source_Group("Header Files\\Generic"		                FILES ${SOURCEPYTHON_GENERIC_HEADERS})
Source_Group("Header Files\\Module\\Engine"	                FILES ${SOURCEPYTHON_ENGINE_MODULE_HEADERS})
Source_Group("Header Files\\Module\\Engine\\Usermessages"	FILES ${SOURCEPYTHON_ENGINE_USERMESSAGE_MODULE_HEADERS})
Source_Group("Header Files\\Module\\Event"	                FILES ${SOURCEPYTHON_EVENT_MODULE_HEADERS})
Source_Group("Header Files\\Module\\Entities"               FILES ${SOURCEPYTHON_ENTITY_MODULE_HEADERS})

Source_Group("Source Files\\Addons" 		                FILES ${SOURCEPYTHON_ADDON_SOURCES})
Source_Group("Source Files\\Core"   		                FILES ${SOURCEPYTHON_CORE_SOURCES})
Source_Group("Source Files\\Util"   		                FILES ${SOURCEPYTHON_UTIL_SOURCES})
Source_Group("Source Files\\Generic"		                FILES ${SOURCEPYTHON_GENERIC_SOURCES})
Source_Group("Source Files\\Module\\Engine"	                FILES ${SOURCEPYTHON_ENGINE_MODULE_SOURCES})
Source_Group("Source Files\\Module\\Engine\\Usermessages"	FILES ${SOURCEPYTHON_ENGINE_USERMESSAGE_MODULE_SOURCES})
Source_Group("Source Files\\Module\\Event"	                FILES ${SOURCEPYTHON_EVENT_MODULE_SOURCES})
Source_Group("Source Files\\Module\\Entities"               FILES ${SOURCEPYTHON_ENTITY_MODULE_SOURCES})

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
	${SOURCEPYTHON_GENERIC_FILES}
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
# Definitions
# ------------------------------------------------------------------
Add_Definitions(
	-DSOURCE_ENGINE=${SOURCE_ENGINE}
    -DBOOST_PYTHON_MAX_ARITY=18
    -DSOURCE_GAME=${SOURCE_GAME}
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
