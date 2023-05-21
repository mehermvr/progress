cmake_minimum_required(VERSION 3.16...3.20)
project(progress LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

# provide a progress bar interface target
add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME}
    INTERFACE
        ${PROJECT_SOURCE_DIR}/progress
)

add_executable(example ${PROJECT_SOURCE_DIR}/example/example.cpp)
target_link_libraries(example PUBLIC ${PROJECT_NAME})
