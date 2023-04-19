cmake_minimum_required(VERSION 3.0)
project(cww CXX)
message("MODE ${MODE}")

include(FindPkgConfig)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_image REQUIRED SDL2_image)
pkg_check_modules(SDL2_ttf REQUIRED SDL2_ttf)

add_executable(${PROJECT_NAME}
  src/main.cpp
  src/writer.cpp
  src/document.cpp
)

include_directories(${PROJECT_NAME}
    include/
    ${SDL2_INCLUDE_DIRS}
    ${SDL2IMAGE_INCLUDE_DIR}
    ${SDL2TTF_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    ${SDL2_LIBRARIES}
    ${SDL2IMAGE_LIBRARY}
    ${SDL2TTF_LIBRARY}
)