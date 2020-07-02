PROJECT(daqanalysis)
cmake_minimum_required(VERSION 3.5)
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic -std=gnu++17")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -fPIC -Wextra -Wuninitialized -pedantic -std=c++17")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -fno-inline -std=c++17")

#~ include_directories(../matlab_code/)
#~ add_subdirectory(../matlab_code matlab_code)

include(../cmake/add_dependency.cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/../cmake/Modules)

add_dependency(DOOCS 18.10.5 COMPONENTS daqreader REQUIRED)

add_library(MyAna SHARED
        ../src/myana.cc
        )

add_executable(daqanalysis daqanalysis.cpp)

set_target_properties(daqanalysis PROPERTIES COMPILE_FLAGS "${DOOCS_CXX_FLAGS}")
set_target_properties(daqanalysis PROPERTIES LINK_FLAGS "${DOOCS_LINKER_FLAGS}")
target_link_libraries(daqanalysis  MyAna	AAnalysis ${DOOCS_LIBRARIES} )


add_executable(doocsRawOpenExample doocsRawOpenExample.cpp)

set_target_properties(doocsRawOpenExample PROPERTIES COMPILE_FLAGS "${DOOCS_CXX_FLAGS}")
set_target_properties(doocsRawOpenExample PROPERTIES LINK_FLAGS "${DOOCS_LINKER_FLAGS}")
target_link_libraries(doocsRawOpenExample	AAnalysis ${DOOCS_LIBRARIES} )


add_executable(ladybug ladybug.cpp ttf2Looper.cc)

set_target_properties(ladybug PROPERTIES COMPILE_FLAGS "${DOOCS_CXX_FLAGS}")
set_target_properties(ladybug PROPERTIES LINK_FLAGS "${DOOCS_LINKER_FLAGS}")
target_link_libraries(ladybug	AAnalysis ${DOOCS_LIBRARIES} )



