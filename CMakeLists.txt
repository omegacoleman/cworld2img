project(cworld2img)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
include_directories(include)
link_libraries(FreeImage)
add_executable(${PROJECT_NAME} ${SRC_LIST})

