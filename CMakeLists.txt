cmake_minimum_required(VERSION 3.30)
project(learnopengl)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)

pkg_check_modules(GLFW REQUIRED glfw3)

include_directories(
    ${OpenGL_INCLUDE_DIRS}
    ${GLFW_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include
)
link_directories(${GLFW_LIBRARY_DIRS})

add_library(glad STATIC external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

set(ALL_LIBRARIES
    ${OpenGL_LIBRARIES}
    ${GLFW_LIBRARIES}
    glad
)

file(GLOB SRC_FILES "./src/*.cpp")

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} ${ALL_LIBRARIES})
