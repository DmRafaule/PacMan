cmake_minimum_required(VERSION 3.13)
project(packman)

file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "dep/*.hpp")
file(GLOB DEPENDENCIES_LIB "dep/SFML/lib/*.so.2.5.1")
set(INCLUDE_DIRECTORIES dep/SFML/include dep)
add_definitions(-ggdb -Wall)
	      
include_directories(${INCLUDE_DIRECTORIES})
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${DEPENDENCIES_LIB})
