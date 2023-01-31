cmake_minimum_required(VERSION 3.24)
project(r-type_client)


include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

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
        ../Game/Systems/CollisionSystem.hpp ../Game/Systems/RandomEnemyGeneratorSystem.cpp ../Game/Systems/RandomEnemyGeneratorSystem.hpp ../Game/Systems/AnimationSystem.cpp ../Game/Systems/AnimationSystem.hpp ../Game/Game.cpp ../Game/Game.hpp)

target_link_libraries(r-type_client PRIVATE ${OPENGL_LIBRARIES} sfml-graphics Threads::Threads)


target_compile_features(r-type_client PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET r-type_client POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:r-type_client> $<TARGET_FILE_DIR:r-type_client> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS r-type_client)