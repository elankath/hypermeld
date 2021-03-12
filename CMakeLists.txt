cmake_minimum_required(VERSION 3.17 FATAL_ERROR)
project(hypermeld VERSION 1.0 LANGUAGES CXX OBJCXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_VERBOSE_MAKEFILE  ON) #enable for debugging
#set(BUILD_SHARED_LIBS on) # let the users of your library choose what flavor to build.

message(STATUS "Building ${PROJECT_NAME} ${PROJECT_VERSION}")

## BEGIN Download CPM.cmake
# See https://github.com/cpm-cmake/CPM.cmake/wiki/Downloading-CPM.cmake-in-CMake
set(CPM_DOWNLOAD_VERSION 0.31.1)
if(CPM_SOURCE_CACHE)
 set(CPM_DOWNLOAD_LOCATION "${CPM_SOURCE_CACHE}/cpm/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
elseif(DEFINED ENV{CPM_SOURCE_CACHE})
 set(CPM_DOWNLOAD_LOCATION "$ENV{CPM_SOURCE_CACHE}/cpm/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
else()
 set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
endif()
if(NOT (EXISTS ${CPM_DOWNLOAD_LOCATION}))
 message(STATUS "Downloading CPM.cmake to ${CPM_DOWNLOAD_LOCATION}")
 file(DOWNLOAD
         https://github.com/TheLartians/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake
         ${CPM_DOWNLOAD_LOCATION}
         )
endif()
include(${CPM_DOWNLOAD_LOCATION})
## END Download CPM.cmake

# BEGIN DEPS
CPMAddPackage("gl:eidheim/tiny-process-library#@2.0.4")
# END DEPS

if (MSVC)
    add_compile_options(/W4 /WX)
else ()
    # See https://foonathan.net/2018/10/cmake-warnings/
    add_compile_options(-Wall -Wextra -Werror -pedantic-errors)
endif ()


#include_directories("${PROJECT_SOURCE_DIR}/include") #global include for all target
add_library(hypermeld-curlbin src/curlbin.cpp)
target_include_directories(hypermeld-curlbin PUBLIC include)
target_link_libraries(hypermeld-curlbin PRIVATE tiny-process-library)
set_target_properties(hypermeld-curlbin PROPERTIES LINKER_LANGUAGE CXX)

#if (APPLE)
#    add_library(hypermeld-macosnative include/meld/hyper/hyper.hpp)
#    target_compile_features(hypermeld-macosnative PUBLIC cxx_std_20)
#    set_target_properties(hypermeld-macosnative PROPERTIES LINKER_LANGUAGE OBJCXX)
#endif ()

add_executable(curlbinsample src/curlbinsample.cpp)
target_link_libraries(curlbinsample PUBLIC hypermeld-curlbin)
target_compile_features(curlbinsample PUBLIC cxx_std_20)


