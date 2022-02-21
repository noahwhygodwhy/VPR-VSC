cmake_minimum_required(VERSION 3.0.0)
project(VPR-VSC VERSION 0.1.0)

include(CTest)
enable_testing()


include_directories(include)
include_directories(src)
add_executable(VPR-VSC src/main.cpp)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(external/GLFW)
target_link_libraries(VPR-VSC glfw)


find_package(OpenGL REQUIRED)
target_link_libraries(VPR-VSC OpenGL::GL)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
