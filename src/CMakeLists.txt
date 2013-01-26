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
    core/modules/engine/engine_trace.h
    core/modules/cvar/cvar_concommand.h
    core/modules/clientcmd/clientcmd_manager.h
)

Set(SOURCEPYTHON_MODULE_SOURCES
    core/modules/export_events.cpp
    core/modules/export_main.cpp
	core/modules/export_player.cpp
	core/modules/export_shared.cpp
)

# ------------------------------------------------------------------
# Engine module
# ------------------------------------------------------------------
Set(SOURCEPYTHON_MODULE_ENGINE_SOURCES
    core/modules/engine/engine_main.cpp
    core/modules/engine/engine_server.cpp
    core/modules/engine/engine_basehandle.cpp
    core/modules/engine/engine_misc.cpp
    core/modules/engine/engine_sound.cpp
    core/modules/engine/engine_trace.cpp
)

# ------------------------------------------------------------------
# Cvar module
# ------------------------------------------------------------------
Set(SOURCEPYTHON_MODULE_CVAR_SOURCES
    core/modules/cvar/cvar_concommandbase.cpp
    core/modules/cvar/cvar_concommand.cpp
    core/modules/cvar/cvar_convar.cpp
    core/modules/cvar/cvar_flags.cpp
    core/modules/cvar/cvar_icvar.cpp
    core/modules/cvar/cvar_main.cpp
)

# ------------------------------------------------------------------
# ClientCmd module
# ------------------------------------------------------------------
Set(SOURCEPYTHON_MODULE_CLIENTCMD_SOURCES
    core/modules/clientcmd/clientcmd_manager.cpp
    core/modules/clientcmd/clientcmd_main.cpp
)

# ------------------------------------------------------------------
# Misc module
# ------------------------------------------------------------------
Set(SOURCEPYTHON_MODULE_MISC_SOURCES
    core/modules/misc/misc_main.cpp
    core/modules/misc/misc_effects.cpp
    core/modules/misc/misc_stringtables.cpp
)

# ------------------------------------------------------------------
# Entity module
# ------------------------------------------------------------------
Set(SOURCEPYTHON_MODULE_ENTITY_HEADERS
    core/modules/entity/entity_generator.h
    core/modules/entity/entity_props.h
)

Set(SOURCEPYTHON_MODULE_ENTITY_SOURCES
    core/modules/entity/entity_main.cpp
    core/modules/entity/entity_edict.cpp
    core/modules/entity/entity_generator.cpp
    core/modules/entity/entity_props.cpp
    core/modules/entity/entity_factory.cpp
)

Set(SOURCEPYTHON_MODULE_ENTITY_FILES
    ${SOURCEPYTHON_MODULE_ENTITY_HEADERS}
    ${SOURCEPYTHON_MODULE_ENTITY_SOURCES}
)

# ------------------------------------------------------------------
# Binutils module
# ------------------------------------------------------------------
Set(SOURCEPYTHON_MODULE_BINUTILS_HEADERS
    core/modules/binutils/binutils_scanner.h
)

Set(SOURCEPYTHON_MODULE_BINUTILS_SOURCES
    core/modules/binutils/binutils_scanner.cpp
    core/modules/binutils/binutils_main.cpp
    core/modules/binutils/binutils_dyncall.cpp
    core/modules/binutils/binutils_memtools.cpp
)

# ------------------------------------------------------------------
# Usermessages module
# ------------------------------------------------------------------

If(SOURCE_ENGINE EQUAL 3)
# As these are not in any LIB files for the SDK, I think this is the best way
# of compiling them for the time being until Allied modders puts them in a .lib
SET (SOURCEPYTHON_MODULE_USERMESSAGES_SOURCES
    core/modules/usermessages/netmessages.pb.cc
)

include("makefiles/game/${GAME}.usermessages.cmake")
EndIf()

# ------------------------------------------------------------------
# All module files
# ------------------------------------------------------------------
Set(SOURCEPYTHON_MODULE_FILES
    ${SOURCEPYTHON_MODULE_HEADERS}
    ${SOURCEPYTHON_MODULE_SOURCES}
    
    ${SOURCEPYTHON_MODULE_BINUTILS_HEADERS}
    ${SOURCEPYTHON_MODULE_USERMESSAGES_HEADERS}
    ${SOURCEPYTHON_MODULE_USERMESSAGES_GAME_HEADERS}
    
    
    ${SOURCEPYTHON_MODULE_ENGINE_SOURCES}
    ${SOURCEPYTHON_MODULE_CVAR_SOURCES}
    ${SOURCEPYTHON_MODULE_CLIENTCMD_SOURCES}    
    ${SOURCEPYTHON_MODULE_MISC_SOURCES}
    ${SOURCEPYTHON_MODULE_ENTITY_SOURCES}
    ${SOURCEPYTHON_MODULE_BINUTILS_SOURCES}
    ${SOURCEPYTHON_MODULE_USERMESSAGES_SOURCES}
    ${SOURCEPYTHON_MODULE_USERMESSAGES_GAME_SOURCES})

# ------------------------------------------------------------------
# Create source groups for everything to make our projects nice and 
# clean.
# ------------------------------------------------------------------
Source_Group("Header Files\\Addons"                             FILES ${SOURCEPYTHON_ADDON_HEADERS})
Source_Group("Header Files\\Core"                               FILES ${SOURCEPYTHON_CORE_HEADERS})
Source_Group("Header Files\\Util"                               FILES ${SOURCEPYTHON_UTIL_HEADERS})
Source_Group("Header Files\\Modules"                            FILES ${SOURCEPYTHON_MODULE_HEADERS})
Source_Group("Header Files\\Modules\\Entity"                    FILES ${SOURCEPYTHON_MODULE_ENTITY_HEADERS})
Source_Group("Header Files\\Modules\\Binutils"                  FILES ${SOURCEPYTHON_MODULE_BINUTILS_HEADERS})

Source_Group("Source Files\\Addons"                             FILES ${SOURCEPYTHON_ADDON_SOURCES})
Source_Group("Source Files\\Core"                               FILES ${SOURCEPYTHON_CORE_SOURCES})
Source_Group("Source Files\\Modules"                            FILES ${SOURCEPYTHON_MODULE_SOURCES})

Source_Group("Source Files\\Modules\\Engine"                    FILES ${SOURCEPYTHON_MODULE_ENGINE_SOURCES})
Source_Group("Source Files\\Modules\\Cvar"                      FILES ${SOURCEPYTHON_MODULE_CVAR_SOURCES})
Source_Group("Source Files\\Modules\\Misc"                      FILES ${SOURCEPYTHON_MODULE_MISC_SOURCES})
Source_Group("Source Files\\Modules\\Entity"                    FILES ${SOURCEPYTHON_MODULE_ENTITY_SOURCES})
Source_Group("Source Files\\Modules\\ClientCmd"                 FILES ${SOURCEPYTHON_MODULE_CLIENTCMD_SOURCES})
Source_Group("Source Files\\Modules\\Binutils"                  FILES ${SOURCEPYTHON_MODULE_BINUTILS_SOURCES})
Source_Group("Source Files\\Modules\\Usermessages"              FILES ${SOURCEPYTHON_MODULE_USERMESSAGES_SOURCES})
Source_Group("Source Files\\Modules\\Usermessages"              FILES ${SOURCEPYTHON_MODULE_USERMESSAGES_GAME_SOURCES})
Source_Group("Source Files\\Util"                               FILES ${SOURCEPYTHON_UTIL_SOURCES})

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
# Definitions
# ------------------------------------------------------------------
Add_Definitions(
	-DSOURCE_ENGINE=${SOURCE_ENGINE}
    -DBOOST_PYTHON_MAX_ARITY=18
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
