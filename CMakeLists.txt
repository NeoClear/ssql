# CMakeLists.txt
cmake_minimum_required(VERSION 2.8)

SET (CMAKE_CXX_COMPILER_ENV_VAR "clang++")
SET (CMAKE_CXX_FLAGS "-std=c++17")
SET (CMAKE_CXX_FLAGS_DEBUG   "-g")
SET (CMAKE_CXX_FLAGS_MINSIZEREL  "-Os -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELEASE  "-O4 -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")

project(ssql)

# Go to the subdir and manage files there
add_subdirectory(src)

add_executable(ssql ssql.cpp)

# link library to the executable file
target_link_libraries(ssql libssql)

install(TARGETS ssql DESTINATION bin)
