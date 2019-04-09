PROJECT(snapdaqdata)


cmake_minimum_required(VERSION 3.5)
#~ set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic -std=gnu++11")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic -std=gnu++17")
#set (CMAKE_CXX_STANDARD 11)
add_executable(txt2bit txt2bit.cpp)
add_executable(open_example open_example.cpp)

include(../cmake/add_dependency.cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/../cmake/Modules)

#~ add_dependency(DOOCS 18.10.5 COMPONENTS server REQUIRED)
#~ add_dependency(DOOCS 18.10.5 REQUIRED)
add_dependency(DOOCS 18.10.5 COMPONENTS daqreader REQUIRED)


#~ add_dependency(DOOCS 18.10.5 COMPONENTS doocsdaq REQUIRED)
add_dependency(ChimeraTK-ApplicationCore 01.01 REQUIRED)
add_dependency(ChimeraTK-ControlSystemAdapter-DoocsAdapter 00.09 REQUIRED)

add_executable(doocstest doocstest.cpp)

set_target_properties(doocstest PROPERTIES COMPILE_FLAGS "${ChimeraTK-ApplicationCore_CXX_FLAGS} ${DOOCS_CXX_FLAGS}")
set_target_properties(doocstest PROPERTIES LINK_FLAGS "${DOOCS_LINKER_FLAGS} ${ChimeraTK-ApplicationCore_LINK_FLAGS}")
#~ target_link_libraries(doocstest 	OnlineAnalysis ${DOOCS_LIBRARIES} )
target_link_libraries(doocstest ${DOOCS_LIBRARIES} )


