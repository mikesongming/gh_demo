cmake_minimum_required(VERSION 3.18)
project(FSEG)

# set(CMAKE_CXX_STANDARD 14)

# add_subdirectory(pybind11)

find_package(pybind11 CONFIG)
if(pybind11_FOUND)
    include(CMakePrintHelpers)
    cmake_print_variables(pybind11_VERSION pybind11_VERSION_TYPE)
    cmake_print_variables(pybind11_INCLUDE_DIRS pybind11_INCLUDE_DIR)
    cmake_print_variables(pybind11_LIBRARIES pybind11_LIBRARY)
    cmake_print_variables(pybind11_DEFINITIONS)
endif(pybind11_FOUND)

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

# EXAMPLE_VERSION_INFO is defined by setup.py and passed into the C++ code as a
# define (VERSION_INFO) here.
target_compile_definitions(_fseg
                           PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})
