cmake_minimum_required(VERSION 3.24)
project(r-type_server)
set(CMAKE_CXX_STANDARD 23)


if (NOT Boost_FOUND)
    message("Boost not found--> downloading and building")
    include(FetchContent)
    FetchContent_Declare(Boost
            GIT_REPOSITORY https://github.com/boostorg/boost.git
            GIT_TAG boost-1.81.0
            )
    FetchContent_MakeAvailable(Boost)
endif ()

message("Installed!")
find_package(Boost 1.81.0 COMPONENTS system thread REQUIRED)

add_executable(r-type_server main.cpp ../Protocol/IProtocol.hpp
        ../Protocol/mainClient.cpp
        ../Protocol/Tcp.cpp ../Protocol/UdpClient.cpp ../Protocol/Tcp.hpp
        ../Protocol/UdpClient.hpp ../Protocol/UdpServer.cpp
        ../Protocol/UdpServer.hpp ../Protocol/UdpSession.cpp
        ../Protocol/UdpSession.hpp)

include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(r-type_server
        ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY})

