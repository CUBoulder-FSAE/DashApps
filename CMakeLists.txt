cmake_minimum_required(VERSION 3.16)
project(DashApps LANGUAGES CXX)


set(CMAKE_CXX_COMPILER $ENV{CXX})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include the shared library
add_subdirectory(Common)

# Add each app
add_subdirectory(CAN)
add_subdirectory(UI)
