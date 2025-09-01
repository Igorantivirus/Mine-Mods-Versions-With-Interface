cmake_minimum_required(VERSION 3.16)

project(MinecraftVersionsInterface VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(EXECUTABLE_NAME ${PROJECT_NAME})

if(MSVC)
  add_compile_options(/W4 /permissive-)
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(SOURCES
  src/main.cpp
  src/MinecraftVersionsInterface.cpp
  resources/MinecraftVersionsInterface.qrc
)
set(HEADERS
  src/MinecraftVersionsInterface.hpp
  src/Names.hpp
  src/PathMeneger.hpp
  src/ProgrammPathMeneger.hpp
)
set(UIS
  src/MinecraftVersionsInterface.ui
)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(${EXECUTABLE_NAME} WIN32
    ${SOURCES}
    ${HEADERS}
    ${UIS}
)

target_link_libraries(${EXECUTABLE_NAME} PRIVATE Qt6::Widgets)
target_include_directories(${EXECUTABLE_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})