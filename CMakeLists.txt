
cmake_minimum_required(VERSION 3.15)

#project
project(Vampires LANGUAGES CXX)

#c++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


#ADD the src folder
file(GLOB SOURCES "src/*.cpp")

#add executable
add_executable(${PROJECT_NAME} ${SOURCES})

#sdl2

find_package(SDL2 CONFIG REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main)