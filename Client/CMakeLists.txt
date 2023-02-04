cmake_minimum_required(VERSION 3.24)
project(r-type_client)

set(CLIENT_HPP ../GameEngine/inc/Button.hpp
                ../GameEngine/inc/Core.hpp
                inc/MainState.hpp
                inc/PlayState.hpp
                inc/SettingsState.hpp
                ../GameEngine/inc/Sprite.hpp
                ../GameEngine/inc/State.hpp
                ../GameEngine/inc/StateMachine.hpp
                ../GameEngine/inc/MusicPlayer.hpp
                ../Game/ECS/ComponentPool.hpp
                ../Game/ECS/ECS.hpp 
                ../Game/ECS/EntityManager.hpp
                ../Game/ECS/EntityViewer.hpp 
                ../Game/ECS/DataTypesECS.hpp 
                ../Game/ECS/ISystem.hpp
                src/InputManager/InputManager.hpp
                ../Game/Systems/DisplaySystem.hpp
                ../Game/EventQueue.hpp 
                ../Game/Systems/MovementSystem.hpp 
                ../Game/Systems/ShootingSystem.hpp 
                ../Game/Systems/CollisionSystem.hpp 
                ../Game/Systems/RandomEnemyGeneratorSystem.hpp 
                ../Game/Systems/AnimationSystem.hpp)

set(CLIENT_SRC ../GameEngine/src/Button.cpp
                ../GameEngine/src/Core.cpp
                src/MainState.cpp
                src/PlayState.cpp
                src/SettingsState.cpp
                ../GameEngine/src/Sprite.cpp
                ../GameEngine/src/State.cpp
                ../GameEngine/src/StateMachine.cpp
                ../GameEngine/src/MusicPlayer.cpp
                ../Game/Systems/DisplaySystem.cpp
                src/InputManager/InputManager.cpp
                ../Game/EventQueue.cpp 
                ../Game/Systems/MovementSystem.cpp
                ../Game/Systems/ShootingSystem.cpp
                ../Game/Systems/CollisionSystem.cpp
                ../Game/Systems/RandomEnemyGeneratorSystem.cpp 
                ../Game/Systems/AnimationSystem.cpp 
                src/main.cpp)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

find_package(OpenGL REQUIRED OPTIONAL_COMPONENTS OpenGL)
include_directories(${OPENGL_INCLUDE_DIR})
add_executable(r-type_client ${CLIENT_SRC} ${CLIENT_HPP})

target_link_libraries(r-type_client PRIVATE ${OPENGL_LIBRARIES} sfml-graphics sfml-audio)


target_compile_features(r-type_client PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET r-type_client POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:r-type_client> $<TARGET_FILE_DIR:r-type_client> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS r-type_client)