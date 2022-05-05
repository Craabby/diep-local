cmake_minimum_required(VERSION 3.5.0)
project(diep-local)

set(SRCS
    src/Client/Client.cc
    src/Client/Socket.cc
    src/Game.cc
    src/Gamemodes/SandboxArena.cc
    src/main.cc
    src/Native/Arena.cc
    src/Native/Camera.cc
    src/Native/Entity.cc
    src/Native/FieldGroups.cc
    src/Native/Manager.cc
    src/Physics/CollisionManager.cc)

SET(CMAKE_CXX_FLAGS "-std=c++2a -g")
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)

include_directories(include)

add_executable(diep-local ${SRCS})

target_link_libraries(diep-local PRIVATE Threads::Threads)
