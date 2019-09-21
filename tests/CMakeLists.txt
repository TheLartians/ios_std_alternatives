cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# ---- Options ----

option(ENABLE_TEST_COVERAGE "Enable test coverage" OFF)

# ---- Dependencies ----

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  find_package(ios_std_alternatives REQUIRED)
endif()

include(../cmake/CPM.cmake)

CPMAddPackage(
  NAME doctest
  GITHUB_REPOSITORY onqtam/doctest
  VERSION 2.3.2
  GIT_TAG 2.3.2
)

# ---- Create binary ----

file(GLOB ios_std_alternatives_test_sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

if (IOS)
  add_library(ios_std_alternatives_test ${ios_std_alternatives_test_sources})
else()
  add_executable(ios_std_alternatives_test ${ios_std_alternatives_test_sources})
endif()

target_link_libraries(ios_std_alternatives_test doctest ios_std_alternatives)
set_target_properties(ios_std_alternatives_test PROPERTIES CXX_STANDARD 17 COMPILE_FLAGS "-Wall -pedantic -Wextra -Werror")

# ---- Add Tests to cmake ----

ENABLE_TESTING()
ADD_TEST(ios_std_alternatives_test ios_std_alternatives_test)

# ---- code coverage ----

if (${ENABLE_TEST_COVERAGE})
  set_target_properties(ios_std_alternatives PROPERTIES CXX_STANDARD 17 COMPILE_FLAGS "-O0 -g -fprofile-arcs -ftest-coverage --coverage")
  target_link_options(ios_std_alternatives PUBLIC "--coverage")
endif()
