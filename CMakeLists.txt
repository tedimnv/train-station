cmake_minimum_required(VERSION 3.15...3.31)

project(
  TrainStation
  VERSION 0.1
  DESCRIPTION "An example project with CMake"
  LANGUAGES CXX)

file(GLOB SOURCES *.cpp *.h)

set(CMAKE_CXX_STANDARD 20)

add_executable(TrainStation ${SOURCES})