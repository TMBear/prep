cmake_minimum_required(VERSION 2.8)

project(prep)

set(CMAKE_BUILD_TYPE Debug)

add_executable(prep src/utils.cpp
                    src/testOstream.cpp
                    src/current.cpp
                    src/downToZero2.cpp
                    src/avlTree.cpp
                    src/connectedComponents.cpp
                    src/flySkyscrapers.cpp
                    src/breadthSearch.cpp
                    src/gameOfTwoStacks.cpp
                    src/plusOne.cpp
                    src/simpleTextEditor.cpp
                    src/splitLinkedListInParts.cpp
                    src/printInOrder.cpp
                    src/shortestPath.cpp
                    src/validSquare.cpp
                    src/fractionToRecurringDecimal.cpp
                    src/trappingRainWater.cpp
                    src/concatenatedWords.cpp
                    src/largestPlusSign.cpp
                    src/integerToEnglish.cpp
                    src/superUglyNumber.cpp
                    src/minPathSum.cpp
                    src/leastOperationsToExpressNumber.cpp
                    src/gameOfLife.cpp
                    src/burstBaloons.cpp)

set_property(TARGET prep PROPERTY CXX_STANDARD 17)
