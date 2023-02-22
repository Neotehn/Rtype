cmake_minimum_required(VERSION 3.6)
project(r-type_client)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

message("Das CMake-Binary-Verzeichnis ist: ${CMAKE_BINARY_DIR}")
message("Das CMake-Source-Verzeichnis ist: ${CMAKE_SOURCE_DIR}")
message("Das CMake-Current-Verzeichnis ist: ${CMAKE_CURRENT_SOURCE_DIR}")


SET(CMAKE_BUILD_DIR ${CMAKE_SOURCE_DIR}/build)
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

include(${CMAKE_BUILD_DIR}/conanbuildinfo.cmake)
conan_basic_setup()


if (MSVC)
    set (CMAKE_GENERATOR "Visual Studio 17" CACHE INTERNAL "" FORCE)
    add_compile_definitions(WIN32_LEAN_AND_MEAN)
    add_compile_definitions(_WIN32_WINNT=0x0601)
else()
    set (CMAKE_GENERATOR "Unix Makefiles" CACHE INTERNAL "" FORCE)
    add_compile_options(-g3 -pthread )
endif()


set(CLIENT_HPP ../Game/ECS/ComponentPool.hpp
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
        ../Game/Systems/DestroySystem.hpp
        ../Game/Systems/CollisionSystem.hpp
        ../Game/Systems/RandomEnemyGeneratorSystem.hpp
        ../Game/Systems/DamageSystem.hpp
        src/Action/IAction.hpp
        ../Game/Timer.hpp
        src/Action/ShootAction.hpp
        src/Action/MovementAction.hpp
        src/Action/StateAction.hpp
        src/Action/PosAction.hpp
        src/Action/CreateAction.hpp
        src/Action/IncreaseAction.hpp
        src/Action/CollisionAction.hpp
        src/Action/DamageAction.hpp
        src/Action/DestroyAction.hpp
        ../Server/Protocol/UdpServer.hpp
        ../Client/Protocol/UdpClient.hpp
        ../Game/CreateEntities/Init.hpp
        ../Game/Systems/AnimationSystem.hpp
        src/Action/VoidAction.hpp
        src/Action/Action.hpp
        ../Game/Systems/CreateObjectSystem.hpp
        ../Game/Systems/PowerUpSystem.hpp
        ../Game/Systems/SoundSystem.hpp
        ../Game/Encapsulation/Event.hpp
        ../Game/Encapsulation/GraphicDataTypes.hpp
        ../Game/Encapsulation/IGraphic.hpp
        ../Game/Encapsulation/IMusic.hpp
        ../Game/Encapsulation/IRectangleShape.hpp
        ../Game/Encapsulation/IRenderWindow.hpp
        ../Game/Encapsulation/ISounds.hpp
        ../Game/Encapsulation/ISprite.hpp
        ../Game/Encapsulation/ITexture.hpp
        ../Game/Encapsulation/SFML/Music.hpp
        ../Game/Encapsulation/SFML/RectangleShape.hpp
        ../Game/Encapsulation/SFML/RenderWindow.hpp
        ../Game/Encapsulation/SFML/Sounds.hpp
        ../Game/Encapsulation/SFML/Sprite.hpp
        ../Game/Encapsulation/SFML/Texture.hpp
        ../GameEngine/src/Button.hpp
        ../GameEngine/src/Core.hpp
        ../GameEngine/src/MusicPlayer.hpp
        ../GameEngine/src/Sprite.hpp
        ../GameEngine/src/State.hpp
        ../GameEngine/src/StateMachine.hpp
        ../Game/GameState.hpp
        ../GameEngine/src/States/MainState.hpp
        ../GameEngine/src/States/SettingsState.hpp
        ../Game/Encapsulation/IMouse.hpp
        ../Game/Encapsulation/SFML/Mouse.hpp
        ../Game/Systems/CreatePlayerSystem.hpp)

set(CLIENT_SRC ../Game/Systems/DisplaySystem.cpp
        src/InputManager/InputManager.cpp
        ../Game/EventQueue.cpp
        ../Game/Systems/MovementSystem.cpp
        ../Game/Systems/ShootingSystem.cpp
        ../Game/Systems/CollisionSystem.cpp
        ../Game/Systems/RandomEnemyGeneratorSystem.cpp
        ../Game/Systems/AnimationSystem.cpp
        ../Game/Systems/DestroySystem.cpp
        ../Game/Systems/DamageSystem.cpp
        src/Action/IAction.cpp
        src/Action/ShootAction.cpp
        src/Action/MovementAction.cpp
        src/Action/StateAction.cpp
        src/Action/PosAction.cpp
        src/Action/DamageAction.cpp
        src/Action/CreateAction.cpp
        src/Action/IncreaseAction.cpp
        src/Action/CollisionAction.cpp
        src/Action/DestroyAction.cpp
        ../Game/Timer.cpp
        ../Server/Protocol/UdpServer.cpp
        ../Client/Protocol/UdpClient.cpp
        ../Game/CreateEntities/Init.cpp
        src/main.cpp ../Protocol/IProtocol.cpp
        src/Action/VoidAction.cpp
        src/Action/Action.cpp
        ../Game/Systems/CreateObjectSystem.cpp
        ../Game/Systems/PowerUpSystem.cpp
        ../Game/Systems/SoundSystem.cpp
        ../Game/Encapsulation/SFML/Music.cpp
        ../Game/Encapsulation/SFML/RenderWindow.cpp
        ../Game/Encapsulation/SFML/Sounds.cpp
        ../Game/Encapsulation/SFML/Sprite.cpp
        ../Game/Encapsulation/SFML/Texture.cpp
        ../Game/Encapsulation/SFML/RectangleShape.cpp
        ../GameEngine/src/Button.cpp
        ../GameEngine/src/Core.cpp
        ../GameEngine/src/MusicPlayer.cpp
        ../GameEngine/src/Sprite.cpp
        ../GameEngine/src/State.cpp
        ../GameEngine/src/StateMachine.cpp
        ../Game/GameState.cpp
        ../GameEngine/src/States/MainState.cpp
        ../GameEngine/src/States/SettingsState.cpp
        ../Game/Encapsulation/SFML/Mouse.cpp
        ../Game/Systems/CreatePlayerSystem.cpp)


include(FetchContent)


add_executable(r-type_client ${CLIENT_SRC} ${CLIENT_HPP})
target_link_libraries(r-type_client ${CONAN_LIBS})

target_compile_features(r-type_client PRIVATE cxx_std_17)


install(TARGETS r-type_client)
