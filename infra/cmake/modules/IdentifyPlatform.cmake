# set host platform to build
if(NOT HOST_ARCH OR "${HOST_ARCH}" STREQUAL "")
  string(TOLOWER ${CMAKE_HOST_SYSTEM_PROCESSOR} HOST_ARCH)
else()
  string(TOLOWER ${HOST_ARCH} HOST_ARCH)
endif()

# set target platform to run
if(NOT TARGET_ARCH OR "${TARGET_ARCH}" STREQUAL "")
  string(TOLOWER ${CMAKE_SYSTEM_PROCESSOR} TARGET_ARCH)
else()
  string(TOLOWER ${TARGET_ARCH} TARGET_ARCH)
endif()

if(NOT DEFINED HOST_OS)
  string(TOLOWER ${CMAKE_HOST_SYSTEM_NAME} HOST_OS)
else()
  string(TOLOWER ${HOST_OS} HOST_OS)
endif()

if(NOT DEFINED TARGET_OS)
  string(TOLOWER ${CMAKE_SYSTEM_NAME} TARGET_OS)
else()
  string(TOLOWER ${TARGET_OS} TARGET_OS)
endif()

# If HOST_ARCH, TARGET_ARCH from CMAKE_HOST_SYSTEM_PROCESSOR, CMAKE_SYSTEM_NAME is arm64
# Change ARCH name to aarch64
if("${HOST_ARCH}" STREQUAL "arm64")
  set(HOST_ARCH "aarch64")
endif()
if("${TARGET_ARCH}" STREQUAL "arm64")
  set(TARGET_ARCH "aarch64")
endif()

if("${HOST_ARCH}" STREQUAL "x86_64")
  set(HOST_ARCH_BASE ${HOST_ARCH})
elseif("${HOST_ARCH}" STREQUAL "armv7l")
  set(HOST_ARCH_BASE "arm")
elseif("${HOST_ARCH}" STREQUAL "aarch64")
  set(HOST_ARCH_BASE "aarch64")
else()
  message(FATAL_ERROR "'${HOST_ARCH}' architecture is not supported")
endif()

if("${TARGET_ARCH}" STREQUAL "x86_64")
  set(TARGET_ARCH_BASE ${TARGET_ARCH})
elseif("${TARGET_ARCH}" STREQUAL "armv7l")
  set(TARGET_ARCH_BASE "arm")
elseif("${TARGET_ARCH}" STREQUAL "aarch64")
  set(TARGET_ARCH_BASE "aarch64")
else()
  message(FATAL_ERROR "'${TARGET_ARCH}' architecture is not supported")
endif()

# host & target platform name
set(HOST_PLATFORM "${HOST_ARCH}-${HOST_OS}")
set(TARGET_PLATFORM "${TARGET_ARCH}-${TARGET_OS}")
