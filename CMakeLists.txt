cmake_minimum_required(VERSION 3.26.0)
project(C2C VERSION 0.1.0 LANGUAGES C)

set (FullOutputDir "${CMAKE_SOURCE_DIR}/bin")
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${FullOutputDir}/Static Libraries")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${FullOutputDir}")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${FullOutputDir}")

set (SrcPath "${CMAKE_SOURCE_DIR}/src/Source Files")
set (HeaderPath "${CMAKE_SOURCE_DIR}/src/Header Files")
file (GLOB_RECURSE Sources CONFIGURE_DEPENDS "${SrcPath}/*.c")

include_directories(${HeaderPath} $ENV{OPENGL_PATH})
link_directories($ENV{OPENGL_PATH})

link_libraries("opengl32" "glad" "glfw3")

add_executable(${PROJECT_NAME} ${Sources})

