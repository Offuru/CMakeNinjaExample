cmake_minimum_required(VERSION 3.5)

# in case DLL_VERSION isn't provided in the cmd we give it a default value
if(NOT DEFINED DLL_VERSION)
    set(DLL_VERSION "1.0.0")
endif()

# set the project version to that of DLL_VERSION
project(my_dll VERSION "${DLL_VERSION}")

# this adds the VERSION macro in our dll, notice that in MyClass.cpp we don't define
# the macro, instead we add it here
add_definitions(-DVERSION="${PROJECT_VERSION}")

# specify the source file for the dll, you can specify more if you have multiple
add_library(my_dll SHARED src/MyClass.cpp)

# specify include directory
target_include_directories(my_dll PUBLIC include)

# specify dll version
set_target_properties(my_dll PROPERTIES
    VERSION ${PROJECT_VERSION}
)

# we add a kits directory in which we copy the generated .lib/.a and .dll files
# this is just to separate the dll and lib files for readability
set(KITS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../kits")
set_target_properties(my_dll PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${KITS_DIR}/${PROJECT_VERSION}"
    LIBRARY_OUTPUT_DIRECTORY "${KITS_DIR}/${PROJECT_VERSION}"
    ARCHIVE_OUTPUT_DIRECTORY "${KITS_DIR}/${PROJECT_VERSION}"
)

# build the dll and lib files
build_command(my_dll)

