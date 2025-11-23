cmake_minimum_required(VERSION 3.19)

project(learn_itk LANGUAGES CXX)

if(WIN32)
    # Windows: MSVC is the default, no special setup needed usually.
    message(STATUS "Configuring for Windows.")
elseif(UNIX AND NOT APPLE)
    # Linux: Prefer g++, fallback to clang++.
    message(STATUS "Configuring for Linux.")
    if(NOT CMAKE_CXX_COMPILER)
        find_program(GCC_COMPILER NAMES g++)
        find_program(CLANG_COMPILER NAMES clang++)
        if(GCC_COMPILER)
            set(CMAKE_CXX_COMPILER ${GCC_COMPILER})
        elseif(CLANG_COMPILER)
            set(CMAKE_CXX_COMPILER ${CLANG_COMPILER})
        else()
            message(FATAL_ERROR "Could not find g++ or clang++.")
        endif()
    endif()
    message(STATUS "Using C++ compiler: ${CMAKE_CXX_COMPILER}")
endif()

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)


set(ITK_SKIP_PATH_LENGTH_CHECKS ON CACHE BOOL "Skip ITK path length checks")
# dep handling
set(FETCH_DEPENDENCIES ON CACHE BOOL "Fetch dependencies with FetchContent")
if(FETCH_DEPENDENCIES)
    include(FetchContent)
        
    set(FETCHCONTENT_BASE_DIR
        "${CMAKE_SOURCE_DIR}/deps"
        CACHE PATH "Base directory for all FetchContent dependencies" FORCE
    )
    
    set(ITK_GIT_TAG "v5.4.0" CACHE STRING "ITK version to fetch" FORCE)
    FetchContent_Declare(
        ITK
        GIT_REPOSITORY https://github.com/InsightSoftwareConsortium/ITK.git
        GIT_TAG        ${ITK_GIT_TAG}
    )
    FetchContent_MakeAvailable(ITK)
    SET(ITK_DIR ${itk_BINARY_DIR})

endif(FETCH_DEPENDENCIES)
find_package(ITK CONFIG REQUIRED)
INCLUDE(${ITK_USE_FILE})

add_executable(learn_itk
    src/learn_itk_win.cpp
    src/learn_itk_win.h      # 头文件列在这里是为了 IDE 显示，实际上编译不需要
)

target_include_directories(learn_itk
    PRIVATE
        "${PROJECT_ROOT}/src"
)

target_link_libraries(learn_itk PUBLIC ${ITK_LIBRARIES})
