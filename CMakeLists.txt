cmake_minimum_required(VERSION 3.27)
project(AED2G135)

set(CMAKE_CXX_STANDARD 17)

add_executable(AED2G135
        main.cpp
        src/controller.cpp
        include/Graph.h
        src/Airport.cpp
        include/Airport.h
        src/Airline.cpp
        include/Airline.h
        src/Flight.cpp
        include/Flight.h
        src/CSVParser.cpp
        include/CSVParser.h
        src/Controller.cpp
        include/Controller.h)
