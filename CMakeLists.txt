cmake_minimum_required(VERSION 3.20)

# Don't allow in-source building
if (CMAKE_BINARY_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  message(FATAL_ERROR "Building in-source is not supported! Create a build dir and remove ${CMAKE_SOURCE_DIR}/CMakeCache.txt")
endif()

project(lab LANGUAGES CXX VERSION 0.1)

# Make sure we are on a systems that is 64 bits
if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
    message (FATAL_ERROR "Only 64 bit systems are supported")
endif(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)

# Set up project wide defaults GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER ${CMAKE_CXX_COMPILER})
set(CMAKE_C_COMPILER ${CMAKE_C_COMPILER})

## Identify debug vs release builds with a postfix
set(CMAKE_DEBUG_POSTFIX d)

## Options
option(COVERAGE "Compile for code coverage using lcov" OFF)

# control where the static and shared libraries are built so that on windows
# we don't need to tinker with the path to run the executable
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

find_package(Sanitizers)

## Add the src to the build
add_subdirectory(src)
add_subdirectory(app)

## Add the tests to the build
enable_testing()
add_subdirectory(tests)

## Packaging
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${lab_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${lab_VERSION_MINOR}")
set(CPACK_SOURCE_GENERATOR "ZIP")
set(CPACK_PACKAGE_NAME "starter-code")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}")
set(CPACK_SOURCE_IGNORE_FILES
    /.git
    /dist
    /out
    /.*build.*
    /\\\\.DS_Store
    solution\.cpp
    test-solution\.cpp
)
include(CPack)
