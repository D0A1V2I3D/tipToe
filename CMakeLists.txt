cmake_minimum_required(VERSION 3.22)
project(tipToe)
set(CMAKE_CXX_STANDARD 23)

find_package(OpenGL REQUIRED)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(LIBS GL SDL2 SDL2main SDL2_image ${SDL2_LIBRARIES})

file(GLOB_RECURSE IMGUI_SRC_FILES include/imgui/*.cpp)

add_executable(${PROJECT_NAME} src/main.cpp ${IMGUI_SRC_FILES} src/initSDL.cpp src/initSDL.h src/initDialog.cpp src/initDialog.h src/app/appmain.cpp src/app/appmain.h)

target_link_libraries(${PROJECT_NAME} ${LIBS})
