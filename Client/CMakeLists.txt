cmake_minimum_required(VERSION 3.24)
project(r-type_client)



include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

find_package(OpenGL REQUIRED OPTIONAL_COMPONENTS OpenGL)
include_directories(${OPENGL_INCLUDE_DIR})
add_executable(r-type_client src/main.cpp src/Player.cpp src/Player.hpp
        ../ECS/ComponentPool.hpp ../ECS/ECS.hpp ../ECS/EntityManager.hpp
        ../ECS/EntityViewer.hpp ../ECS/DataTypesECS.hpp ../ECS/ISystem.hpp
        src/InputManager/InputManager.cpp src/InputManager/InputManager.hpp
        src/Systems/DisplaySystem.cpp src/Systems/DisplaySystem.hpp
        src/EventQueue.cpp src/EventQueue.hpp src/Systems/MovementSystem.cpp
        src/Systems/MovementSystem.hpp src/Systems/ShootingSystem.cpp
        src/Systems/ShootingSystem.hpp src/Systems/CollisionSystem.cpp
        src/Systems/CollisionSystem.hpp src/Systems/RandomEnemyGeneratorSystem.cpp src/Systems/RandomEnemyGeneratorSystem.hpp)

target_link_libraries(r-type_client PRIVATE ${OPENGL_LIBRARIES} sfml-graphics)


target_compile_features(r-type_client PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET r-type_client POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:r-type_client> $<TARGET_FILE_DIR:r-type_client> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS r-type_client)