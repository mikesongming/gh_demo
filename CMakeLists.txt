cmake_minimum_required(VERSION 3.18)
project(FSEG)

# set(CMAKE_CXX_STANDARD 14)

set(FETCHCONTENT_UPDATES_DISCONNECTED ON CACHE BOOL "Disable updating fetched content")

include(FetchContent)

FetchContent_Declare(pybind11
    GIT_REPOSITORY https://github.com/pybind/pybind11.git
    GIT_TAG v2.8.1
)

FetchContent_MakeAvailable(pybind11)

pybind11_add_module(_fseg src/main.cpp
 src/pet.hpp src/animal.hpp src/vec.hpp src/num.hpp)

if(APPLE)
    set_target_properties(_fseg PROPERTIES
       BUILD_RPATH "@loader_path"
    )
elseif(UNIX)
    set_target_properties(_fseg PROPERTIES
       BUILD_RPATH "${ORIGIN}"
    )
endif()

# SDIST_VERSION_INFO is defined by setup.py and passed into the C++ code as a
# define (VERSION_INFO) here.
target_compile_definitions(_fseg
                           PRIVATE VERSION_INFO=${SDIST_VERSION_INFO})
