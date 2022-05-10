cmake_minimum_required(VERSION 3.5.0)
project(diep-local)

set(SRCS
    src/Client/Client.cc
    src/Client/Socket.cc
    src/Coder/Reader.cc
    src/Coder/Writer.cc
    src/Game.cc
    src/Gamemodes/SandboxArena.cc
    src/main.cc
    src/Native/Arena.cc
    src/Native/Camera.cc
    src/Native/Component/Arena.cc
    src/Native/Component/Barrel.cc
    src/Native/Component/Camera.cc
    src/Native/Component/Example.cc
    src/Native/Component/Health.cc
    src/Native/Component/Name.cc
    src/Native/Component/Physics.cc
    src/Native/Component/Position.cc
    src/Native/Component/Relations.cc
    src/Native/Component/Score.cc
    src/Native/Component/Style.cc
    src/Native/Component/Team.cc
    src/Native/Entity.cc
    src/Native/EntityFactory.cc
    src/Native/Manager.cc
    src/Physics/CollisionManager.cc)

set(CMAKE_CXX_FLAGS "-std=c++17 -g3")
set(THREADS_PREFER_PTHREAD_FLAG ON)
set(CMAKE_CXX_COMPILER "/usr/bin/g++-8")

find_package(Threads REQUIRED)

include_directories(include)
include_directories(ThirdParty/entt/src)

add_executable(diep-local ${SRCS})

target_link_libraries(diep-local PRIVATE Threads::Threads)
