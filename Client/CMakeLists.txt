cmake_minimum_required(VERSION 3.6)
project(r-type_client)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
SET(OpenGL_GL_PREFERENCE LEGACY)
set(CMAKE_REQUIRED_LIBRARIES "-L${atomic_lib_dir}" "-latomic")

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
        src/Action/CreateLobbyAction.hpp
        src/Action/JoinLobbyAction.hpp
        src/Action/LeaveLobbyAction.hpp
        src/Action/JoinSuccessfullAction.hpp
        src/Action/ChadAction.hpp
        ../Server/Protocol/UdpServer.hpp
        ../Client/Protocol/UdpClient.hpp
        ../Game/CreateEntities/Init.hpp
        ../Game/Systems/AnimationSystem.hpp
        src/Action/VoidAction.hpp
        src/Action/Action.hpp
        ../Game/Systems/CreateObjectSystem.hpp
        ../Game/Systems/PowerUpSystem.hpp
        ../Game/Systems/GUISystem.hpp
        ../Game/Systems/SoundSystem.hpp
        ../Game/Encapsulation/Event.hpp
        ../Game/Encapsulation/IFont.hpp
        ../Game/Encapsulation/GraphicDataTypes.hpp
        ../Game/Encapsulation/IGraphic.hpp
        ../Game/Encapsulation/IMusic.hpp
        ../Game/Encapsulation/IRectangleShape.hpp
        ../Game/Encapsulation/IRenderWindow.hpp
        ../Game/Encapsulation/ISounds.hpp
        ../Game/Encapsulation/ISprite.hpp
        ../Game/Encapsulation/IText.hpp
        ../Game/Encapsulation/ITexture.hpp
        ../Game/Encapsulation/SFML/Music.hpp
        ../Game/Encapsulation/SFML/RectangleShape.hpp
        ../Game/Encapsulation/SFML/RenderWindow.hpp
        ../Game/Encapsulation/SFML/Sounds.hpp
        ../Game/Encapsulation/SFML/Font.hpp
        ../Game/Encapsulation/SFML/Text.hpp
        ../Game/Encapsulation/SFML/Sprite.hpp
        ../Game/Encapsulation/SFML/Font.hpp
        ../Game/Encapsulation/SFML/Text.hpp
        ../Game/Encapsulation/SFML/Texture.hpp
        ../GameEngine/src/Button.hpp
        ../GameEngine/src/Textbox.hpp
        ../GameEngine/src/Core.hpp
        ../GameEngine/src/MusicPlayer.hpp
        ../GameEngine/src/Sprite.hpp
        ../GameEngine/src/State.hpp
        ../GameEngine/src/StateMachine.hpp
        ../Game/GameState.hpp
        ../GameEngine/src/States/MainState.hpp
        ../GameEngine/src/States/SettingsState.hpp
        ../GameEngine/src/States/JoinLobbyState.hpp
        ../GameEngine/src/States/CreateLobbyState.hpp
        ../Game/Encapsulation/IMouse.hpp
        ../Game/Encapsulation/SFML/Mouse.hpp
        ../Game/Systems/CreatePlayerSystem.hpp
        ../Game/Encapsulation/IGraphicLoader.hpp
        ../Game/Encapsulation/SFML/GraphicLoader.hpp
        ../Game/CreateEntities/AssetLoader.hpp
        ../Server/src/Logger.hpp
        ../Server/src/ServerChadFilter.hpp
        ../GameEngine/src/States/IntroState.hpp
        ../Game/Encapsulation/raylib/RaylibWindow.hpp
        ../Game/Encapsulation/raylib/RaylibSound.hpp
        ../Game/Encapsulation/raylib/RaylibFont.hpp
        ../Game/Encapsulation/raylib/RaylibMouse.hpp
        ../Game/Encapsulation/raylib/RaylibMusic.hpp
        ../Game/Encapsulation/raylib/RaylibText.hpp
        ../Game/Encapsulation/raylib/RaylibTexture.hpp
        ../Game/Encapsulation/raylib/RaylibSprite.hpp
        ../Game/Encapsulation/raylib/RaylibRectangleShape.hpp
        ../Game/Encapsulation/raylib/RaylibGraphicLoader.hpp)

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
        src/Action/ShootAction.cpp
        src/Action/MovementAction.cpp
        src/Action/StateAction.cpp
        src/Action/PosAction.cpp
        src/Action/DamageAction.cpp
        src/Action/CreateAction.cpp
        src/Action/IncreaseAction.cpp
        src/Action/CollisionAction.cpp
        src/Action/DestroyAction.cpp
        src/Action/CreateLobbyAction.cpp
        src/Action/JoinLobbyAction.cpp
        src/Action/LeaveLobbyAction.cpp
        src/Action/JoinSuccessfullAction.cpp
        src/Action/ChadAction.cpp
        ../Game/Timer.cpp
        ../Server/Protocol/UdpServer.cpp
        ../Client/Protocol/UdpClient.cpp
        ../Game/CreateEntities/Init.cpp
        src/main.cpp ../Protocol/IProtocol.cpp
        src/Action/VoidAction.cpp
        src/Action/Action.cpp
        ../Game/Systems/CreateObjectSystem.cpp
        ../Game/Systems/PowerUpSystem.cpp
        ../Game/Systems/GUISystem.cpp
        ../Game/Systems/SoundSystem.cpp
        ../Game/Encapsulation/SFML/Music.cpp
        ../Game/Encapsulation/SFML/RenderWindow.cpp
        ../Game/Encapsulation/SFML/Sounds.cpp
        ../Game/Encapsulation/SFML/Sprite.cpp
        ../Game/Encapsulation/SFML/Text.cpp
        ../Game/Encapsulation/SFML/Font.cpp
        ../Game/Encapsulation/SFML/Texture.cpp
        ../Game/Encapsulation/SFML/Text.cpp
        ../Game/Encapsulation/SFML/Font.cpp
        ../Game/Encapsulation/SFML/RectangleShape.cpp
        ../GameEngine/src/Button.cpp
        ../GameEngine/src/Textbox.cpp
        ../GameEngine/src/Core.cpp
        ../GameEngine/src/MusicPlayer.cpp
        ../GameEngine/src/Sprite.cpp
        ../GameEngine/src/State.cpp
        ../GameEngine/src/StateMachine.cpp
        ../Game/GameState.cpp
        ../GameEngine/src/States/MainState.cpp
        ../GameEngine/src/States/SettingsState.cpp
        ../GameEngine/src/States/JoinLobbyState.cpp
        ../GameEngine/src/States/CreateLobbyState.cpp
        ../Game/Encapsulation/SFML/Mouse.cpp
        ../Game/Systems/CreatePlayerSystem.cpp
        ../Game/Encapsulation/SFML/GraphicLoader.cpp
        ../Game/CreateEntities/AssetLoader.cpp
        ../Server/src/Logger.cpp
        ../Server/src/ServerChadFilter.cpp
        ../GameEngine/src/States/IntroState.cpp
        ../GameEngine/src/States/ProvideUserNameState.cpp
        ../Game/Encapsulation/raylib/RaylibWindow.cpp
        ../Game/Encapsulation/raylib/RaylibSound.cpp
        ../Game/Encapsulation/raylib/RaylibFont.cpp
        ../Game/Encapsulation/raylib/RaylibMouse.cpp
        ../Game/Encapsulation/raylib/RaylibMusic.cpp
        ../Game/Encapsulation/raylib/RaylibText.cpp
        ../Game/Encapsulation/raylib/RaylibTexture.cpp
        ../Game/Encapsulation/raylib/RaylibSprite.cpp
        ../Game/Encapsulation/raylib/RaylibRectangleShape.cpp
        ../Game/Encapsulation/raylib/RaylibGraphicLoader.cpp)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)
find_package(Boost 1.69.0 COMPONENTS chrono system thread REQUIRED)


find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)

find_package(Boost 1.69.0 COMPONENTS chrono system thread REQUIRED)


find_package(OpenGL REQUIRED OPTIONAL_COMPONENTS OpenGL)
include_directories(${OPENGL_INCLUDE_DIR})
add_executable(r-type_client ${CLIENT_SRC} ${CLIENT_HPP})

# Add Raylib
find_package(raylib 4.2.0 QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    FetchContent_Declare(
            raylib
            GIT_REPOSITORY https://github.com/raysan5/raylib.git
            GIT_TAG 4.2.0
    )
        FetchContent_GetProperties(raylib)
        if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
            set(FETCHCONTENT_QUIET NO)
            FetchContent_Populate(raylib)
            set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
            add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
        endif()
    FetchContent_MakeAvailable(raylib)
endif ()

target_link_libraries(r-type_client sfml-graphics sfml-audio ${JSONCPP_LIBRARIES}
        ${OPENGL_LIBRARIES} ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY}
        ${Boost_CHRONO_LIBRARY} raylib)
target_link_directories(r-type_client PUBLIC ${Boost_LIBRARY_DIRS})

target_compile_features(r-type_client PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET r-type_client POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:r-type_client> $<TARGET_FILE_DIR:r-type_client> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS r-type_client)