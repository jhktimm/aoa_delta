cmake_minimum_required(VERSION 3.5)
add_executable(data_test data_test.cpp)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic -std=gnu++17")
# to build stand alone...
#~ include_directories(../matlab_code/)
#~ add_subdirectory(../matlab_code matlab_code)
target_link_libraries(data_test AAnalysis "-ljsoncpp")
