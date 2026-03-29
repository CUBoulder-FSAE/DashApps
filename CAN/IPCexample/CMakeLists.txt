cmake_minimum_required(VERSION 3.16)

project(ipcExample)

add_executable(send)
add_executable(recv)
target_sources(send
    PRIVATE
        send.cpp
)

target_sources(recv
    PRIVATE
        recv.cpp
)