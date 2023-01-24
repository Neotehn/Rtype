cmake_minimum_required(VERSION 3.24)
project(r-type_client)

set(CLIENT_HPP src/gameEngine/inc/Menu.hpp
                src/gameEngine/inc/Button.hpp)
set(CLIENT_SRC src/gameEngine/src/Menu.cpp
                src/gameEngine/src/Button.cpp
                src/main.cpp)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

find_package(OpenGL REQUIRED OPTIONAL_COMPONENTS OpenGL)
include_directories(${OPENGL_INCLUDE_DIR})
add_executable(r-type_client ${CLIENT_SRC} ${CLIENT_HPP})

target_link_libraries(r-type_client PRIVATE ${OPENGL_LIBRARIES} sfml-graphics)


target_compile_features(r-type_client PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET r-type_client POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:r-type_client> $<TARGET_FILE_DIR:r-type_client> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS r-type_client)