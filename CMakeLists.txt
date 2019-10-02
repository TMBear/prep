cmake_minimum_required(VERSION 2.8)

project(prep)

set(CMAKE_BUILD_TYPE Debug)

add_executable(prep src/current.cpp
                    src/downToZero2.cpp
                    src/avlTree.cpp
                    src/connectedComponents.cpp
                    src/flySkyscrapers.cpp
                    src/breadthSearch.cpp)
set_property(TARGET prep PROPERTY CXX_STANDARD 17)
