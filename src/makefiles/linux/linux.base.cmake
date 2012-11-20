# ------------------------------------------------------------------
# File: src/makefiles/linux/linux.base.cmake
# Purpose: This is the base linux CMake file which sets a bunch of
#    shared flags across all linux builds.
# ------------------------------------------------------------------

# ------------------------------------------------------------------
# Included makefiles
# ------------------------------------------------------------------
include("makefiles/game/${GAME}.cmake")
include("makefiles/shared.cmake")

# ------------------------------------------------------------------
# Hack for Linux CMake.
# ------------------------------------------------------------------
If(NOT CMAKE_BUILD_TYPE)
    Set(CMAKE_BUILD_TYPE Release)
Endif(NOT CMAKE_BUILD_TYPE)

# ------------------------------------------------------------------
# Python directories
# ------------------------------------------------------------------
Set(PYTHONSDK            ${THIRDPARTY_DIR}/python_linux)
Set(PYTHONSDK_INCLUDE    ${PYTHONSDK}/include)
Set(PYTHONSDK_LIB        ${PYTHONSDK}/libs)

# ------------------------------------------------------------------
# Add in the python sdk as an include directory.
# ------------------------------------------------------------------
Include_Directories(
    ${PYTHONSDK_INCLUDE}
)

# ------------------------------------------------------------------
# Link libraries.
# ------------------------------------------------------------------
Set(SOURCEPYTHON_LINK_LIBRARIES
    pthread dl util
    ${SOURCESDK_LIB}/linux/mathlib_i486.a
    ${SOURCESDK_LIB}/linux/interfaces_i486.a
    ${SOURCESDK_LIB}/linux/tier1_i486.a
    ${DYNCALLSDK_LIB}/libdyncall_s.a
    ${DYNCALLSDK_LIB}/libdyncallback_s.a
    ${DYNCALLSDK_LIB}/libdynload_s.a
)

# ------------------------------------------------------------------
# Linux compiler flags.
# ------------------------------------------------------------------
Set(CMAKE_CXX_FLAGS "-D_LINUX -DPOSIX -DLINUX -Dstricmp=strcasecmp -D_stricmp=strcasecmp")
Set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_strnicmp=strncasecmp -Dstrnicmp=strncasecmp") 
Set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_snprintf=snprintf -D_vsnprintf=vsnprintf -D_alloca=alloca")
Set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Dstrcmpi=strcasecmp -Wall -Wno-uninitialized")
Set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mfpmath=sse -msse -DHAVE_STDINT_H -m32 -DCOMPILER_GCC")
Set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-non-virtual-dtor -fno-threadsafe-statics -v")

# ------------------------------------------------------------------
# Link shared objects.
# ------------------------------------------------------------------
Set(CMAKE_SHARED_LINKER_FLAGS   "libtier0.so libvstdlib.so")

# ------------------------------------------------------------------
# Debug / Release compiler flags.
# ------------------------------------------------------------------
If(CMAKE_BUILD_TYPE MATCHES Debug)
    Set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG -DBOOST_DEBUG_PYTHON -D_DEBUG -DPy_DEBUG")
Else()
    Set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_NDEBUG")
EndIf()

# ------------------------------------------------------------------
# Stub these out because cmake doesn't set debug/release libraries
# correctly...
# ------------------------------------------------------------------
Set(SOURCEPYTHON_LINK_LIBRARIES_RELEASE
    ${PYTHONSDK_LIB}/libpython3.3m.a
    ${BOOSTSDK_LIB}/libboost_python.a
    ${PYTHONSDK_LIB}/libpython3.3m.so.1.0    
)

Set(SOURCEPYTHON_LINK_LIBRARIES_DEBUG
    ${PYTHONSDK_LIB}/libpython3.3dm.a
    ${BOOSTSDK_LIB}/libboost_python_d.a
    ${PYTHONSDK_LIB}/libpython3.3dm.so.1.0
)

# ------------------------------------------------------------------
# Need to copy tier0 and vstdlib so files.
# ------------------------------------------------------------------
FILE(COPY ${SOURCESDK_LIB}/linux/libtier0.so DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
FILE(COPY ${SOURCESDK_LIB}/linux/libvstdlib.so DESTINATION ${CMAKE_CURRENT_BINARY_DIR})