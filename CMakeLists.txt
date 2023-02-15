cmake_minimum_required(VERSION 3.6)
project(r-type_client)

message("Das CMake-Binary-Verzeichnis ist: ${CMAKE_BINARY_DIR}")
message("Das CMake-Source-Verzeichnis ist: ${CMAKE_SOURCE_DIR}")
message("Das CMake-Current-Verzeichnis ist: ${CMAKE_CURRENT_SOURCE_DIR}")
SET(CMAKE_BUILD_DIR ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BUILD_DIR})

SET(CMAKE_CXX_STANDARD 17)


SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)


SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

include(${CMAKE_BUILD_DIR}/conanbuildinfo.cmake)

conan_basic_setup()

message("test conan libs" ${CONAN_LIBS})

SET(CLIENT_HPP GameEngine/inc/Button.hpp
        GameEngine/inc/Core.hpp
        Client/inc/MainState.hpp
        Client/inc/PlayState.hpp
        Client/inc/SettingsState.hpp
        GameEngine/inc/Sprite.hpp
        GameEngine/inc/State.hpp
        GameEngine/inc/StateMachine.hpp
        GameEngine/inc/MusicPlayer.hpp
        Game/ECS/ComponentPool.hpp
        Game/ECS/ECS.hpp
        Game/ECS/EntityManager.hpp
        Game/ECS/EntityViewer.hpp
        Game/ECS/DataTypesECS.hpp
        Game/ECS/ISystem.hpp
        Client/src/InputManager/InputManager.hpp
        Game/Systems/DisplaySystem.hpp
        Game/EventQueue.hpp
        Game/Systems/MovementSystem.hpp
        Game/Systems/ShootingSystem.hpp
        Game/Systems/DestroySystem.hpp
        Game/Systems/CollisionSystem.hpp
        Game/Systems/RandomEnemyGeneratorSystem.hpp
        Game/Systems/DamageSystem.hpp
        Game/Game.hpp
        Client/src/Action/IAction.hpp
        Client/inc/GameState.hpp
        Game/Timer.hpp
        Client/src/Action/ShootAction.hpp
        Client/src/Action/MovementAction.hpp
        Client/src/Action/StateAction.hpp
        Client/src/Action/PosAction.hpp
        Client/src/Action/CreateAction.hpp
        Client/src/Action/IncreaseAction.hpp
        Client/src/Action/CollisionAction.hpp
        Client/src/Action/DamageAction.hpp
        Client/src/Action/DestroyAction.hpp
        Server/Protocol/UdpServer.hpp
        Client/Protocol/UdpClient.hpp
        Game/CreateEntities/Init.hpp
        Game/Systems/AnimationSystem.hpp
        Client/src/Action/VoidAction.hpp
        Client/src/Action/Action.hpp
        Game/Systems/CreateObjectSystem.hpp
        Game/Systems/PowerUpSystem.hpp
        Game/Systems/SoundSystem.hpp)

set(CLIENT_SRC GameEngine/src/Button.cpp
        GameEngine/src/Core.cpp
        Client/src/MainState.cpp
        Client/src/PlayState.cpp
        Client/src/SettingsState.cpp
        GameEngine/src/Sprite.cpp
        GameEngine/src/State.cpp
        GameEngine/src/StateMachine.cpp
        GameEngine/src/MusicPlayer.cpp
        Game/Systems/DisplaySystem.cpp
        Client/src/InputManager/InputManager.cpp
        Game/EventQueue.cpp
        Game/Systems/MovementSystem.cpp
        Game/Systems/ShootingSystem.cpp
        Game/Systems/CollisionSystem.cpp
        Game/Systems/RandomEnemyGeneratorSystem.cpp
        Game/Systems/AnimationSystem.cpp
        Game/Systems/DestroySystem.cpp
        Game/Systems/DamageSystem.cpp
        Game/Game.cpp
        Client/src/GameState.cpp
        Client/src/Action/IAction.cpp
        Client/src/Action/ShootAction.cpp
        Client/src/Action/MovementAction.cpp
        Client/src/Action/StateAction.cpp
        Client/src/Action/PosAction.cpp
        Client/src/Action/DamageAction.cpp
        Client/src/Action/CreateAction.cpp
        Client/src/Action/IncreaseAction.cpp
        Client/src/Action/CollisionAction.cpp
        Client/src/Action/DestroyAction.cpp
        Game/Timer.cpp
        Server/Protocol/UdpServer.cpp
        Client/Protocol/UdpClient.cpp
        Game/CreateEntities/Init.cpp
        Client/src/main.cpp Protocol/IProtocol.cpp
        Client/src/Action/VoidAction.cpp
        Client/src/Action/Action.cpp
        Game/Systems/CreateObjectSystem.cpp
        Game/Systems/PowerUpSystem.cpp
        Game/Systems/SoundSystem.cpp)

include(FetchContent)

find_package(Boost 1.69.0 COMPONENTS chrono system thread REQUIRED)

if (NOT Boost_FOUND)
    message("Boost not found--> downloading and building")
    include(FetchContent)
    FetchContent_Declare(Boost
            GIT_REPOSITORY https://github.com/boostorg/boost.git
            GIT_TAG boost-1.81.0
            )
    FetchContent_MakeAvailable(Boost)
endif()


find_package(OpenGL REQUIRED OPTIONAL_COMPONENTS OpenGL)
include_directories(${OPENGL_INCLUDE_DIR}, ${Boost_INCLUDE_DIRS})
add_executable(r-type_client ${CLIENT_SRC} ${CLIENT_HPP})

target_link_libraries(r-type_client ${CONAN_LIBS}
        ${OPENGL_LIBRARIES} ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_CHRONO_LIBRARY})
target_link_directories(r-type_client PUBLIC ${Boost_LIBRARY_DIRS})

target_compile_features(r-type_client PRIVATE cxx_std_17)

if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET r-type_client POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:r-type_client> $<TARGET_FILE_DIR:r-type_client> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS r-type_client)