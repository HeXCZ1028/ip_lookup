cmake_minimum_required(VERSION 3.24)
project(ip_lookup)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ip_lookup
        IpFind.cpp
        IpFind.h
        IpInfo.h
        main.cpp)
