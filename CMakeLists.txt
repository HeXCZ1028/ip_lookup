cmake_minimum_required(VERSION 3.24)
project(ip_lookup)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

# Set the path to the MySQL Connector/C++ directory
set(FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR /usr)

# Include the header files from the MySQL Connector/C++ directory
include_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/include)
include_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/include/cppconn)

# Link the library from the MySQL Connector/C++ directory
link_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/lib)


add_executable(ip_lookup
        IpFind.cpp
        IpFind.h
        IpInfo.h
        main.cpp)

target_link_libraries(ip_lookup mysqlcppconn)
