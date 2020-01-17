cmake_minimum_required(VERSION 2.8)

project(getStartAndArraySizeForRuns)

#set(CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(getStartAndArraySizeForRuns getStartAndArraySizeForRuns.cc )

add_executable(getFileList getFileList.cc)


EXECUTE_PROCESS(COMMAND source ${CMAKE_SOURCE_DIR}/docker/compile_onMax.sh ${CMAKE_SOURCE_DIR})

EXECUTE_PROCESS(COMMAND ln -sr ${CMAKE_SOURCE_DIR}/run.sh ${CMAKE_SOURCE_DIR}/../workdir/)
EXECUTE_PROCESS(COMMAND ln -sr ${CMAKE_SOURCE_DIR}/build/getFileList ${CMAKE_SOURCE_DIR}/../workdir/)
EXECUTE_PROCESS(COMMAND ln -sr ${CMAKE_SOURCE_DIR}/runParameter_example.run ${CMAKE_SOURCE_DIR}/../workdir/)
EXECUTE_PROCESS(COMMAND ln -sr ${CMAKE_SOURCE_DIR}/sbatchArray.sh ${CMAKE_SOURCE_DIR}/../workdir/)

