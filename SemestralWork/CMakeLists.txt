cmake_minimum_required(VERSION 3.10)
project(SemestralProject VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(SemestralWork
        src/main.cpp
        src/Graph.cpp
        src/BoruvkaSerial.cpp
        src/BoruvkaParallel.cpp
        src/Utils.cpp
)

target_link_libraries(SemestralWork Threads::Threads)