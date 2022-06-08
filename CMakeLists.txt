cmake_minimum_required(VERSION 3.18)
project(FSEG)

# set(CMAKE_CXX_STANDARD 14)
if (MSVC)
    message(STATUS "_MSVC_VER: ${MSVC_VERSION}")
    # /Zc:preprocessor enables a token-based preprocessor that conforms to C99 and C++11 and later standards
    # /Zc:preprocessor option is available starting with VS2019 version 16.5
    # (according to https://docs.microsoft.com/en-us/cpp/build/reference/zc-preprocessor)
    # That version is equivalent to _MSC_VER==1925
    # (according to https://docs.microsoft.com/en-us/cpp/preprocessor/predefined-macros)
    # CMake's ${MSVC_VERSION} is equivalent to _MSC_VER
    # (according to https://cmake.org/cmake/help/latest/variable/MSVC_VERSION.html#variable:MSVC_VERSION)
    if (MSVC_VERSION GREATER_EQUAL 1925)
        add_compile_options(/Zc:preprocessor)
    else()
	message(FATAL_ERROR "MSVC compiler before VS2019 Update5 are not supported")
    endif()
endif()

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
