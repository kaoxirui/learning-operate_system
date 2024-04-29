cmake_minimum_required(VERSION 3.10)
project(OS)
include_directories(
    ./include/
)

add_executable(Scheduler ./src/Scheduler.cpp)
add_executable(Semaphore ./src/Semaphore.cpp)
add_executable(Filesystem ./src/Filesystem.cpp)
add_executable(DeadLock ./src/DeadLock.cpp)
add_executable(multithread ./src/multithread.cpp)
add_executable(client ./src/client.cpp)
add_executable(server ./src/server.cpp)
add_executable(JobScheduler ./src/JobScheduler.cpp)

target_link_libraries(
    Semaphore -lpthread
)

target_link_libraries(
    Filesystem -lpthread
)

target_link_libraries(
    multithread -lpthread
)