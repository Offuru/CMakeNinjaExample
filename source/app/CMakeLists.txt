cmake_minimum_required(VERSION 3.5)

project(my_app VERSION 1.0.0)

set(DLL_VERSION 1.0.1)

add_executable(my_app src/main.cpp)

target_include_directories(my_app PRIVATE include)

set(DLL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../kits/${DLL_VERSION}")
set(DLL_INC "${CMAKE_CURRENT_SOURCE_DIR}/../dll/include")

target_include_directories(my_app PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../dll/include")

target_link_libraries(my_app PRIVATE "${DLL_DIR}/libmy_dll.dll.a")

add_custom_command(TARGET my_app POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        "${DLL_DIR}/libmy_dll.dll"
        "$<TARGET_FILE_DIR:my_app>"
)