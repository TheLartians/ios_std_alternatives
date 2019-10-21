cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

# ---- Guards ----

set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

# ---- Options ----

option(ios_std_alternatives_ENABLE_TESTS "Build tests" OFF)

# ---- Project ----

project(ios_std_alternatives
  VERSION 1.0
  LANGUAGES CXX
)

# ---- Dependencies ----

include(cmake/CPM.cmake)

CPMAddPackage(
  NAME mpark_variant
  URL https://github.com/mpark/variant/archive/v1.4.0.zip
  VERSION 1.4.0
)

# ---- Library ----

add_library(ios_std_alternatives INTERFACE)
target_link_libraries(ios_std_alternatives INTERFACE mpark_variant)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  # remove constuctor warning
  target_compile_definitions(ios_std_alternatives INTERFACE "-Wno-deprecated-copy")
endif()


target_include_directories(ios_std_alternatives
  INTERFACE 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# ---- Install ----

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
  "${PROJECT_BINARY_DIR}/ios_std_alternativesConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
)

install(
  TARGETS ios_std_alternatives
  EXPORT ios_std_alternativesTargets
  LIBRARY DESTINATION lib COMPONENT Runtime
  ARCHIVE DESTINATION lib COMPONENT Development
  RUNTIME DESTINATION bin COMPONENT Runtime
  PUBLIC_HEADER DESTINATION include COMPONENT Development
  BUNDLE DESTINATION bin COMPONENT Runtime
)

configure_package_config_file(
  "${PROJECT_SOURCE_DIR}/cmake/ios_std_alternativesConfig.cmake.in"
  "${PROJECT_BINARY_DIR}/ios_std_alternativesConfig.cmake"
  INSTALL_DESTINATION lib/cmake/ios_std_alternatives
)

install(
  EXPORT ios_std_alternativesTargets 
  DESTINATION lib/cmake/ios_std_alternatives
)

install(
  FILES 
    "${PROJECT_BINARY_DIR}/ios_std_alternativesConfigVersion.cmake"
    "${PROJECT_BINARY_DIR}/ios_std_alternativesConfig.cmake"
  DESTINATION 
    lib/cmake/ios_std_alternatives
)

install(
  DIRECTORY ${PROJECT_SOURCE_DIR}/include/
  DESTINATION include
)

# ---- Tests ----

if (ios_std_alternatives_ENABLE_TESTS)
  add_subdirectory(tests)
endif()
