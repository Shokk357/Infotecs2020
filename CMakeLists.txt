cmake_minimum_required(VERSION 3.15)

project(InfotecsInternship)

set(CMAKE_CXX_STANDARD 14)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -Wall")

add_executable(DataProcessing FstApp/handler.cpp Common/ThreadLogic.cpp Common/BigNum.cpp)

add_executable(DataFilter SndApp/receiver.cpp Common/BigNum.cpp)