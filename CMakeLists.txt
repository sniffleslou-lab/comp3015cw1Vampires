
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
        src/Buttons.h
        src/Guests.cpp
        src/guests.cpp
        src/Guests.h
)


#sdl2

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)


include_directories(${SDL2_INCLUDE_DIRS})

target_link_libraries(Vampires PRIVATE
        SDL2::SDL2
        $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>
        $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>
        nlohmann_json::nlohmann_json

)
target_compile_definitions(${PROJECT_NAME} PRIVATE ASSETS_PATH="${CMAKE_SOURCE_DIR}/assets")