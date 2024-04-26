cmake_minimum_required(VERSION 3.10)
project(OS)
include_directories(
    ./include/
)

add_executable(Scheduler ./src/Scheduler.cpp)
add_executable(Semaphore ./src/Semaphore.cpp)
add_executable(Filesystem ./src/Filesystem.cpp)

target_link_libraries(
    Semaphore -lpthread
)

target_link_libraries(
    Filesystem -lpthread
)