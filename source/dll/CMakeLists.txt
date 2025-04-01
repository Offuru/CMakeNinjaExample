cmake_minimum_required(VERSION 3.5)

project(my_dll VERSION 1.0.1)

add_definitions(-DVERSION="${PROJECT_VERSION}")

add_library(my_dll SHARED src/MyClass.cpp)

target_include_directories(my_dll PUBLIC include)

set_target_properties(my_dll PROPERTIES
    VERSION ${PROJECT_VERSION}
)

set(KITS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../kits")
set_target_properties(my_dll PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${KITS_DIR}/${PROJECT_VERSION}"
    LIBRARY_OUTPUT_DIRECTORY "${KITS_DIR}/${PROJECT_VERSION}"
    ARCHIVE_OUTPUT_DIRECTORY "${KITS_DIR}/${PROJECT_VERSION}"
)

build_command(my_dll)

