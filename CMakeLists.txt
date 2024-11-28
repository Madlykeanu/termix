cmake_minimum_required(VERSION 3.16)
project(termix VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
find_package(CURL REQUIRED)
find_package(spdlog REQUIRED)
find_package(nlohmann_json REQUIRED)

# Source files
set(SOURCES
    src/main.cpp
    src/gui/mainwindow.cpp
    src/api/api_client.h
    src/api/openai_client.cpp
)

# Header files
set(HEADERS
    src/gui/mainwindow.h
    src/api/openai_client.h
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
    spdlog::spdlog
    nlohmann_json::nlohmann_json
)

# Enable automoc for Qt
set_target_properties(${PROJECT_NAME} PROPERTIES
    AUTOMOC ON
    AUTORCC ON
    AUTOUIC ON
)
