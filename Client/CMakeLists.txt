cmake_minimum_required(VERSION 3.6)
project(r-type_client)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

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
                ../Game/Systems/DestroySystem.hpp 
                ../Game/Systems/CollisionSystem.hpp 
                ../Game/Systems/RandomEnemyGeneratorSystem.hpp 
                ../Game/Game.hpp
                src/Action/IAction.hpp
                inc/GameState.hpp
                ../Game/Timer.hpp
                src/Action/ShootAction.hpp
        src/Action/MovementAction.hpp
        src/Action/StateAction.hpp
        src/Action/PosAction.hpp
        src/Action/CreateAction.hpp
        src/Action/IncreaseAction.hpp
        src/Action/CollisionAction.hpp
        src/Action/DestroyAction.hpp
        ../Server/Protocol/UdpServer.hpp
        ../Client/Protocol/UdpClient.hpp
        ../Game/CreateEntities/Init.hpp
        ../Game/Systems/AnimationSystem.hpp
        src/Action/VoidAction.hpp
        src/Action/Action.hpp
        ../Game/Systems/CreateObjectSystem.cpp
        ../Game/Systems/CreateObjectSystem.hpp)

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
                ../Game/Systems/DestroySystem.cpp 
                ../Game/Game.cpp
                src/GameState.cpp
                src/Action/IAction.cpp
        src/Action/ShootAction.cpp
        src/Action/MovementAction.cpp
        src/Action/StateAction.cpp
        src/Action/PosAction.cpp
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
        src/Action/Action.cpp ../Game/Systems/CreateObjectSystem.cpp ../Game/Systems/CreateObjectSystem.hpp)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

if (NOT Boost_FOUND)
    message("Boost not found--> downloading and building")
    include(FetchContent)
    FetchContent_Declare(Boost
            GIT_REPOSITORY https://github.com/boostorg/boost.git
            GIT_TAG boost-1.81.0
            )
    FetchContent_MakeAvailable(Boost)
endif()

find_package(Boost 1.69.0 COMPONENTS chrono system thread REQUIRED)

find_package(OpenGL REQUIRED OPTIONAL_COMPONENTS OpenGL)
include_directories(${OPENGL_INCLUDE_DIR})
add_executable(r-type_client ${CLIENT_SRC} ${CLIENT_HPP})

target_link_libraries(r-type_client sfml-graphics sfml-audio
        ${OPENGL_LIBRARIES} ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_CHRONO_LIBRARY})
target_link_directories(r-type_client PUBLIC ${Boost_LIBRARY_DIRS})

target_compile_features(r-type_client PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET r-type_client POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:r-type_client> $<TARGET_FILE_DIR:r-type_client> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS r-type_client)