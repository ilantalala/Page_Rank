cmake_minimum_required(VERSION 3.23)
project(Page_Rank)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Page_Rank
        graph.cpp
        graph.hpp
        main.cpp
        pageRank.cpp
        pageRank.hpp)