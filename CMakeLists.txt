cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

# ---- Guards ----

set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

# ---- Options ----

option(IOS_STD_TESTS_ENABLE_TESTS "Build tests" OFF)

# ---- Project ----

project(ios_std
  VERSION 1.0
  LANGUAGES CXX
)

add_library(ios_std INTERFACE)

target_include_directories(ios_std
  INTERFACE 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# ---- Tests ----

if (IOS_STD_TESTS_ENABLE_TESTS)
  add_subdirectory(tests)
endif()
