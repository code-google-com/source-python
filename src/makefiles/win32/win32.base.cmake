# ------------------------------------------------------------------
# File: src/makefiles/win32/win32.base.cmake
# Purpose: This is the base Win32 CMake file which sets a bunch of
#    shared flags across all Win32 builds.
# ------------------------------------------------------------------

# ------------------------------------------------------------------
# Include shared
# ------------------------------------------------------------------
include("makefiles/shared.cmake")

# ------------------------------------------------------------------
# Python directories
# ------------------------------------------------------------------
Set(PYTHONSDK            ${THIRDPARTY_DIR}/python_win32)
Set(PYTHONSDK_INCLUDE    ${PYTHONSDK}/include)
Set(PYTHONSDK_LIB        ${PYTHONSDK}/libs)

# ------------------------------------------------------------------
# Add in the python sdk as an include directory.
# ------------------------------------------------------------------
Include_Directories(
    ${PYTHONSDK_INCLUDE}
)

# ------------------------------------------------------------------
# Required to get SP to compile on MSVC for csgo.
# ------------------------------------------------------------------
Add_Definitions(-DCOMPILER_MSVC -DCOMPILER_MSVC32)

# ------------------------------------------------------------------
# Release / Debug flags.
# ------------------------------------------------------------------
Set(CMAKE_CXX_FLAGS_DEBUG   "/DDEBUG /DBOOST_DEBUG_PYTHON /MDd")
Set(CMAKE_CXX_FLAGS_RELEASE "/D_NDEBUG /MD")

# ------------------------------------------------------------------
# The loader should not link to msvcrt libraries. Those will be
# delay loaded in.
# ------------------------------------------------------------------
Set_Target_Properties(source-python PROPERTIES
    LINK_FLAGS_DEBUG "/NODEFAULTLIB:msvcrtd.lib"
    LINK_FLAGS_RELEASE "/NODEFAULTLIB:msvcrt.lib"
)

Set_Target_Properties(core PROPERTIES
    LINK_FLAGS_DEBUG   "/NODEFAULTLIB:libcmt.lib"
    LINK_FLAGS_RELEASE "/NODEFAULTLIB:libcmtd.lib"
)

# ------------------------------------------------------------------
# Link libraries.
# ------------------------------------------------------------------
Set(SOURCEPYTHON_LINK_LIBRARIES
    ${SOURCESDK_LIB}/public/tier0.lib
    ${SOURCESDK_LIB}/public/tier1.lib
    ${SOURCESDK_LIB}/public/tier2.lib
    ${SOURCESDK_LIB}/public/tier3.lib
    ${SOURCESDK_LIB}/public/vstdlib.lib
    ${SOURCESDK_LIB}/public/mathlib.lib
    ${SOURCESDK_LIB}/public/interfaces.lib
    ${DYNCALLSDK_LIB}/libdyncall_s.lib
    ${DYNCALLSDK_LIB}/libdyncallback_s.lib
    ${DYNCALLSDK_LIB}/libdynload_s.lib
)

# ------------------------------------------------------------------
# Debug link libraries
# ------------------------------------------------------------------
Set(SOURCEPYTHON_LINK_LIBRARIES_DEBUG 
    debug ${PYTHONSDK_LIB}/python33_d.lib 
    debug ${BOOSTSDK_LIB}/libboost_python-vc-mt-gyd-1_50.lib
)

# ------------------------------------------------------------------
# Release link libraries
# ------------------------------------------------------------------
Set(SOURCEPYTHON_LINK_LIBRARIES_RELEASE 
    optimized ${PYTHONSDK_LIB}/python33.lib 
    optimized ${BOOSTSDK_LIB}/libboost_python-vc-mt-y-1_50.lib
)

