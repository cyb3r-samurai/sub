cmake_minimum_required(VERSION 3.22)
project(SUB2 VERSION 1.0.1)

set(CMAKE_CXX_STANDARD 17)
#add_compile_options(--std=c++17)


add_executable(main 
    main.cpp
    RwLock.cpp
    CircularQueue.cpp
    Message.cpp 
    Subscriber.cpp
)
target_link_libraries(main pthread rt)
