cmake_minimum_required(VERSION 3.19)
project(fifteen)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -Wpedantic -pipe -DDEBUGME")
set(CMAKE_CXX_FLAGS_RELEASE  "-Ofast -ffast-math -Wall -Wextra -Wpedantic -pipe")
set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CXX_STANDARD_LIBRARIES}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

add_executable(fifteen main.cpp Solution.h State.cpp State.h StatesSet.h AStar.cpp AStar.h BFS.cpp BFS.h DFS.cpp DFS.h)