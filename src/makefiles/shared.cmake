# ------------------------------------------------------------------
# File: src/makefiles/shared.cmake
# Purpose: This is the base Win32 CMake file which sets a bunch of
#    shared flags across all Win32 builds.
# ------------------------------------------------------------------

# ------------------------------------------------------------------
# We only need a release and debug configuration.
# ------------------------------------------------------------------
If(CMAKE_CONFIGURATION_TYPES)
   Set(CMAKE_CONFIGURATION_TYPES Debug Release)
   Set(CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}" CACHE STRING
    "Reset the configurations to what we need"
    FORCE)
EndIf()

# ------------------------------------------------------------------
# Setup include paths.
# Note that ${GAME} here is passed on the command line.
# ------------------------------------------------------------------
Set(SOURCESDK_DIR        ${CMAKE_CURRENT_SOURCE_DIR}/sdks)
Set(THIRDPARTY_DIR       ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty)

# ------------------------------------------------------------------
# SDK Directories.
# ------------------------------------------------------------------
Set(SOURCESDK            ${SOURCESDK_DIR}/hl2sdk-${GAME})
Set(SOURCESDK_LIB        ${SOURCESDK}/lib)

# ------------------------------------------------------------------
# Boost specific.
# ------------------------------------------------------------------
Set(BOOSTSDK             ${THIRDPARTY_DIR}/boost)
Set(BOOSTSDK_INCLUDE     ${BOOSTSDK}) # ..needed to allow #include <boost/xx.hpp>
Set(BOOSTSDK_LIB         ${BOOSTSDK}/lib)

# ------------------------------------------------------------------
# Include directories
# ------------------------------------------------------------------
Include_Directories(
    ${SOURCESDK}/public
    ${SOURCESDK}/public/tier0
    ${SOURCESDK}/public/tier1
    ${BOOSTSDK_INCLUDE}
    ${CMAKE_CURRENT_SOURCE_DIR}/core # Hack but required.
)

# ------------------------------------------------------------------
# This is required to get boost to statically link.
# ------------------------------------------------------------------
Add_Definitions(
    -DBOOST_PYTHON_STATIC_LIB
    -DBOOST_PYTHON_SOURCE
    -DBOOST_PYTHON_NO_LIB
)

# ------------------------------------------------------------------
# The project.
# ------------------------------------------------------------------
Project(source-python C CXX)

# ------------------------------------------------------------------
# Get rid of the library prefix for all distributions.
# ------------------------------------------------------------------
# Set(CMAKE_SHARED_LIBRARY_PREFIX "")