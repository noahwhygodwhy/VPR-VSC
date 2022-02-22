cmake_minimum_required(VERSION 3.12)
project(VPR-VSC VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB_RECURSE SOURCES
"src/*.cpp"
"src/*.c"
)
file(GLOB_RECURSE HEADERS
"src/*.hpp"
"src/*.h"
)
include_directories(include)
include_directories(src)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_executable(VPR-VSC src/main.cpp ${SOURCES} ${HEADERS})
 
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/../)

add_subdirectory(external/GLFW)
target_link_libraries(VPR-VSC glfw)


add_subdirectory(external/GLM)
target_link_libraries(VPR-VSC glm)

find_package(OpenGL REQUIRED)
target_link_libraries(VPR-VSC OpenGL::GL)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
