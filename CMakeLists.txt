
cmake_minimum_required(VERSION 3.15)

#project
project(Vampires LANGUAGES CXX)


#c++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#I am telling cmake to use vcpkg
#set(CMAKE_TOOLCHAIN_FILE "/Users/lou/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
#ADD the src folder
file(GLOB SOURCES "src/*.cpp")

#add executable
add_executable(${PROJECT_NAME} ${SOURCES}
        src/main.cpp
        src/controls.cpp
        src/game.cpp
        src/rounds.cpp
        src/Game.h
        src/Rounds.h
        src/Buttons.h)


#sdl2

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

target_link_libraries(Vampires PRIVATE
        SDL2::SDL2
        $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>
)