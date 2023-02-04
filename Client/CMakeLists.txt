cmake_minimum_required(VERSION 3.24)
project(r-type_client)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

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

find_package(Boost 1.81.0 COMPONENTS system thread REQUIRED)

find_package(OpenGL REQUIRED OPTIONAL_COMPONENTS OpenGL)
include_directories(${OPENGL_INCLUDE_DIR})
add_executable(r-type_client src/main.cpp
        ../Game/ECS/ComponentPool.hpp ../Game/ECS/ECS.hpp ../Game/ECS/EntityManager.hpp
        ../Game/ECS/EntityViewer.hpp ../Game/ECS/DataTypesECS.hpp ../Game/ECS/ISystem.hpp
        src/InputManager/InputManager.cpp src/InputManager/InputManager.hpp
        ../Game/Systems/DisplaySystem.cpp ../Game/Systems/DisplaySystem.hpp
        ../Game/EventQueue.cpp ../Game/EventQueue.hpp ../Game/Systems/MovementSystem.cpp
        ../Game/Systems/MovementSystem.hpp ../Game/Systems/ShootingSystem.cpp
        ../Game/Systems/ShootingSystem.hpp ../Game/Systems/CollisionSystem.cpp
        ../Game/Systems/CollisionSystem.hpp ../Game/Systems/RandomEnemyGeneratorSystem.cpp
        ../Game/Systems/RandomEnemyGeneratorSystem.hpp ../Game/Systems/AnimationSystem.cpp
        ../Game/Systems/AnimationSystem.hpp ../Game/Game.cpp ../Game/Game.hpp
        src/Action/IAction.cpp src/Action/IAction.hpp ../Game/Timer.hpp src/Action/ShootAction.cpp
        src/Action/ShootAction.hpp src/Action/MovementAction.cpp src/Action/MovementAction.hpp
        src/Action/StateAction.cpp src/Action/StateAction.hpp src/Action/CreateAction.cpp
        src/Action/CreateAction.hpp src/Action/IncreaseAction.cpp src/Action/IncreaseAction.hpp
        src/Action/CollisionAction.cpp src/Action/CollisionAction.hpp ../Game/Timer.cpp
        ../Game/Timer.hpp ../Server/Protocol/UdpServer.cpp ../Server/Protocol/UdpServer.hpp
        ../Client/Protocol/UdpClient.cpp ../Client/Protocol/UdpClient.hpp
        ../Game/CreateEntities/Init.cpp ../Game/CreateEntities/Init.hpp)

target_link_libraries(r-type_client sfml-graphics ${OPENGL_LIBRARIES} ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY})
target_link_directories(r-type_client PUBLIC ${Boost_LIBRARY_DIRS})

target_compile_features(r-type_client PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET r-type_client POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:r-type_client> $<TARGET_FILE_DIR:r-type_client> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS r-type_client)