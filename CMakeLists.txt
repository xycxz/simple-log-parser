cmake_minimum_required(VERSION 3.15)
project(LogParser VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(IFACE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/interface)

# For Linux
find_package(Threads REQUIRED)

# Interface library
add_library(logparser_ilogparser INTERFACE)
target_include_directories(logparser_ilogparser INTERFACE ${IFACE_DIR})

# Library for reusable components only
add_library(LogEngine
    ${SRC_DIR}/apachelogparser.cpp
    ${SRC_DIR}/ipregistry.cpp
    ${SRC_DIR}/chunkprocessor.cpp
)

target_include_directories(LogEngine
    PUBLIC  ${INC_DIR}
    PRIVATE ${SRC_DIR}
)

target_link_libraries(LogEngine
    PUBLIC
        logparser_ilogparser
        Threads::Threads
)

target_compile_options(LogEngine PRIVATE -Wall -Wextra -Wpedantic)

# Executable
add_executable(log_analyzer ${SRC_DIR}/main.cpp)
target_link_libraries(log_analyzer PRIVATE LogEngine)