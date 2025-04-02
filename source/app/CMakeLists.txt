cmake_minimum_required(VERSION 3.5)

project(my_app VERSION 1.0.0)

# define the dll version we want to use, if it wasn't provided in the cmd default to 1.0.0
if(NOT DEFINED DLL_VERSION)
    set(DLL_VERSION 1.0.0)
endif()

# specify the source files for the .exe
add_executable(my_app src/main.cpp)

# specify the include directory for our project
target_include_directories(my_app PRIVATE include)

# specify the dll, lib and include locations for our dll
set(DLL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../kits/${DLL_VERSION}")
set(DLL_INC "${CMAKE_CURRENT_SOURCE_DIR}/../dll/include")

# add the dll include to our includes
target_include_directories(my_app PRIVATE "${DLL_INC}")

# add the import library
target_link_libraries(my_app PRIVATE "${DLL_DIR}/libmy_dll.dll.a")

# copy the dll in the directory containing the .exe so it can be found at runtime
add_custom_command(TARGET my_app POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        "${DLL_DIR}/libmy_dll.dll"
        "$<TARGET_FILE_DIR:my_app>"
)