# ------------------------------------------------------------------
# File: src/makefiles/shared.cmake
# Purpose: This is the base Win32 CMake file which sets a bunch of
#    shared flags across all Win32 builds.
# ------------------------------------------------------------------

# ------------------------------------------------------------------
# We only need a release and debug configuration.
# ------------------------------------------------------------------
Set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING 
	"Only do Release and Debug" 
	FORCE
)

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
# Dyncall specific.
# ------------------------------------------------------------------
Set(DYNCALLSDK           ${THIRDPARTY_DIR}/dyncall)
Set(DYNCALLSDK_INCLUDE   ${DYNCALLSDK}/include)
Set(DYNCALLSDK_LIB       ${DYNCALLSDK}/lib)

# ------------------------------------------------------------------
# Protobuf specific.
# ------------------------------------------------------------------
Set(PROTOBUF		${THIRDPARTY_DIR}/protobuf/protobuf-2.3.0)
Set(PROTOBUF_INCLUDE	${PROTOBUF}/src)

# ------------------------------------------------------------------
# Include directories
# ------------------------------------------------------------------
Include_Directories(
    ${SOURCESDK}
    ${SOURCESDK}/game/shared
    ${SOURCESDK}/game/server
    ${SOURCESDK}/public
    ${SOURCESDK}/public/tier0
    ${SOURCESDK}/public/tier1
    ${SOURCESDK}/public/engine/protobuf
    ${DYNCALLSDK_INCLUDE}
    ${BOOSTSDK_INCLUDE}
    ${PROTOBUF_INCLUDE}
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