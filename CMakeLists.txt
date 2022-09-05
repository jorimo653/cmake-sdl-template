cmake_minimum_required(VERSION 3.23)
project(cmake_sdl_template)

set(CMAKE_C_STANDARD 99)

set(CMAKE_MODULE_PATH "${cmake_sdl_test_SOURCE_DIR}/cmake")
set(BIN_DIR ${cmake_sdl_test}/bin)


add_executable(cmake_sdl_template src/main.c)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

target_include_directories(cmake_sdl_template PRIVATE ${SDL2_INCLUDE_DIRS})
#target_include_directories(cmake_sdl_template ${SDL2_LIBRARY})

message([STATUS] " SDL2_INCLUDE_DIRS    " ${SDL2_INCLUDE_DIRS})
message([STATUS] " SDL2_LIBRARIES       " ${SDL2_LIBRARIES})
message([STATUS] " SDL2_TTF_INCLUDE_DIR " ${SDL2_TTF})
message([STATUS] " SDL2_TTF_LIBRARY     " ${SDL2_TTF_LIBRARY})

target_include_directories(cmake_sdl_template PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(cmake_sdl_template PRIVATE
        ${SDL2_LIBRARIES}
        ${SDL_IMAGE_LIBRARY}
        ${SDL2_TTF_LIBRARY}
        )

include_directories(include)
include_directories(res)
add_compile_options(-framework SDL2_image)
