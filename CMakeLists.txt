cmake_minimum_required(VERSION 3.20)
project(MessageHandler LANGUAGES CXX)

# Set C++ version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Handle compilers automatically for Qt targets
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Necessary to define path on macOS (for Mqtt)
set (CMAKE_PREFIX_PATH "/usr/local/Cellar/qt/6.1.3")

# Find and import packages
find_package(Qt6 COMPONENTS Core REQUIRED)
find_package(Qt6 COMPONENTS Mqtt REQUIRED)

# Include header files
include_directories(include)

set(HEADERS
    include/MqttHandler.hpp
    include/testmqtt.hpp
)

# Include source files
set(SOURCES
    src/MqttHandler.cpp
    src/testmqtt.cpp
)

add_executable(MessageHandler Program.cpp ${HEADERS} ${SOURCES})

# Hide qDebug messages in Release build
target_compile_definitions(MessageHandler PUBLIC QT_DEBUG_NO_OUTPUT)

target_link_libraries(MessageHandler PRIVATE
    Qt6::Core
    Qt6::Mqtt
)
