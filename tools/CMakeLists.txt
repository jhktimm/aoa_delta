cmake_minimum_required(VERSION 2.8)

project(getStartAndArraySizeForRuns)

#set(CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lpthread -pthread -O3")

add_executable(getStartAndArraySizeForRuns getStartAndArraySizeForRuns.cc )

add_executable(getFileList getFileList.cc)

add_executable(mergeFiles mergeFiles.cc)

EXECUTE_PROCESS(COMMAND mkdir ${CMAKE_SOURCE_DIR}/../workdir)
EXECUTE_PROCESS(COMMAND ln -sr ${CMAKE_SOURCE_DIR}/run.sh ${CMAKE_SOURCE_DIR}/../workdir/)
EXECUTE_PROCESS(COMMAND ln -sr ${CMAKE_SOURCE_DIR}/build/getFileList ${CMAKE_SOURCE_DIR}/../workdir/)
EXECUTE_PROCESS(COMMAND ln -sr ${CMAKE_SOURCE_DIR}/build/mergeFiles ${CMAKE_SOURCE_DIR}/../workdir/)
EXECUTE_PROCESS(COMMAND ln -sr ${CMAKE_SOURCE_DIR}/maxMergeFiles.sh ${CMAKE_SOURCE_DIR}/../workdir/)
EXECUTE_PROCESS(COMMAND ln -sr ${CMAKE_SOURCE_DIR}/runParameter_example.run ${CMAKE_SOURCE_DIR}/../workdir/)
EXECUTE_PROCESS(COMMAND ln -sr ${CMAKE_SOURCE_DIR}/sbatchArray.sh ${CMAKE_SOURCE_DIR}/../workdir/)
EXECUTE_PROCESS(COMMAND ln -sr ${CMAKE_SOURCE_DIR}/setFixedParameter_template.sh ${CMAKE_SOURCE_DIR}/workdir/)
message("   ---   copy setFixedParameter and adapt it in the tools/ dir  ---")
message("         cp setFixedParameter_template.sh setFixedParameter.sh")


#EXECUTE_PROCESS(COMMAND sbatch ${CMAKE_SOURCE_DIR}/docker/compile_onMax.sh
# WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/docker/
# RESULT_VARIABLE variable_RESULT
# OUTPUT_VARIABLE variable_OUTPUT
# )
#message(STATUS ${variable_RESULT})
#message(STATUS ${variable_OUTPUT})
