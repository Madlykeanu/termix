cmake_minimum_required(VERSION 3.16)

# Set vcpkg configuration
set(VCPKG_TARGET_TRIPLET "x64-mingw-static" CACHE STRING "Vcpkg target triplet")
set(CMAKE_TOOLCHAIN_FILE "C:/Users/ksorc/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

project(termix VERSION 1.0.0 LANGUAGES CXX)

# Set MinGW paths
set(CMAKE_C_COMPILER "C:/Qt/Tools/mingw1310_64/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/Qt/Tools/mingw1310_64/bin/g++.exe")
set(CMAKE_MAKE_PROGRAM "C:/Qt/Tools/mingw1310_64/bin/mingw32-make.exe")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set Qt path for MinGW
set(CMAKE_PREFIX_PATH "C:/Qt/6.8.0/mingw_64")

# Add vcpkg installed path to prefix path
list(APPEND CMAKE_PREFIX_PATH "C:/Users/ksorc/vcpkg/installed/x64-mingw-static")

# Debug output
message(STATUS "CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")
message(STATUS "Looking for CURL in: ${CMAKE_PREFIX_PATH}")

# Find required packages
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
find_package(CURL CONFIG REQUIRED)
find_package(spdlog REQUIRED)
find_package(nlohmann_json REQUIRED)

# Source files
set(SOURCES
    src/main.cpp
    src/gui/mainwindow.cpp
    src/api/openai_client.cpp
    src/api/api_client.cpp
    src/utils/config.cpp
)

# Header files
set(HEADERS
    src/gui/mainwindow.h
    src/api/api_client.h
    src/api/openai_client.h
    src/utils/config.h
)

# Create executable
add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Widgets
    CURL::libcurl
    spdlog::spdlog_header_only
    nlohmann_json::nlohmann_json
)

# Enable automoc for Qt
set_target_properties(${PROJECT_NAME} PROPERTIES
    AUTOMOC ON
    AUTORCC ON
    AUTOUIC ON
)
