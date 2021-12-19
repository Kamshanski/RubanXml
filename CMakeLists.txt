#cmake_minimum_required(VERSION 3.20)
#project(RubanXml)
#
#set(CMAKE_CXX_STANDARD 14)
#
#
#add_executable(RubanXml library.cpp)
#
#include_directories(lib)
#LINK_DIRECTORIES(lib)
##message(${CMAKE_CXX_STANDARD})
#TARGET_LINK_LIBRARIES(RubanXml PRIVATE RubanXmlLib)
#

cmake_minimum_required (VERSION 3.8)

project(RubanXml)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(SOURCE_FILES "main.cpp")

add_subdirectory(lib)
add_subdirectory(testLib)

include_directories("lib")
include_directories("lib/src")
link_directories("lib")
include_directories("testLib")
link_directories("testLib")

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable (RubanXml main.cpp)
add_executable(Tests test/ParserTest.cpp test/VisitorTest.cpp)

target_link_libraries(RubanXml RubanXmlLib)
target_link_libraries(Tests RubanXmlLib)
target_link_libraries(Tests gtest)
target_link_libraries(Tests gtest_main)
