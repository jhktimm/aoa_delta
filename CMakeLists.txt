cmake_minimum_required(VERSION 2.8)
project(aoa)
#EXECUTE_PROCESS(COMMAND ln -s ${CMAKE_SOURCE_DIR}/tools/run.sh ${CMAKE_SOURCE_DIR}/workdir/.)
#EXECUTE_PROCESS(COMMAND ln -s ${CMAKE_SOURCE_DIR}/tools/runDocker.sh ${CMAKE_SOURCE_DIR}/workdir/.)

include(cmake/add_dependency.cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)

add_dependency(ChimeraTK-ApplicationCore 01.01 REQUIRED)
add_dependency(ChimeraTK-ControlSystemAdapter-DoocsAdapter 00.09 REQUIRED)

# for AAnalysis
include_directories(matlab_code/)
add_subdirectory(matlab_code)

#~ add_executable(daq_aoa src/main.cpp)

#~ set_target_properties(daq_aoa PROPERTIES COMPILE_FLAGS "${ChimeraTK-ApplicationCore_CXX_FLAGS}")
#~ set_target_properties(daq_aoa PROPERTIES LINK_FLAGS "${ChimeraTK-ApplicationCore_LINK_FLAGS}")
#~ target_link_libraries(daq_aoa 
	#~ AAnalysis
	#~ ${ChimeraTK-ApplicationCore_LIBRARIES}
	#~ )


add_executable(aoa_app src/aoa.cc )

set_target_properties(aoa_app PROPERTIES COMPILE_FLAGS "${ChimeraTK-ControlSystemAdapter_CXX_FLAGS} -O3 ")
set_target_properties(aoa_app PROPERTIES LINK_FLAGS "${ChimeraTK-ControlSystemAdapter_LINK_FLAGS} ${ChimeraTK-ControlSystemAdapter-DoocsAdapter_LINK_FLAGS}")
target_include_directories(aoa_app PUBLIC ${ChimeraTK-ApplicationCore_INCLUDE_DIRS})
target_link_libraries(aoa_app 
	${ChimeraTK-ControlSystemAdapter_LIBRARIES}
	${ChimeraTK-ControlSystemAdapter-DoocsAdapter_LIBRARIES}
	AAnalysis
	${ChimeraTK-ApplicationCore_LIBRARIES}
	"-ljsoncpp"
	)
# copy config files for 2nd example
FILE( COPY ${CMAKE_SOURCE_DIR}/dmap_files/aoa.dmap DESTINATION ${PROJECT_BINARY_DIR})
FILE( COPY ${CMAKE_SOURCE_DIR}/aoa_app.conf DESTINATION ${PROJECT_BINARY_DIR})
# FILE( COPY ${CMAKE_SOURCE_DIR}/tools/run.sh DESTINATION ${PROJECT_BINARY_DIR}/daq_ana/)
  

include_directories(data_test/)
add_subdirectory(data_test)

include_directories(daq_ana/)
add_subdirectory(daq_ana)

EXECUTE_PROCESS(COMMAND mkdir ${CMAKE_SOURCE_DIR}/workdir)
#~ EXECUTE_PROCESS(COMMAND ln -s ${PROJECT_BINARY_DIR}/daq_aoa ${PROJECT_BINARY_DIR}/../workdir/)
EXECUTE_PROCESS(COMMAND ln -sr ${PROJECT_BINARY_DIR}/aoa_app ${CMAKE_SOURCE_DIR}/workdir/)
EXECUTE_PROCESS(COMMAND ln -sr ${PROJECT_BINARY_DIR}/daq_ana/daqanalysis ${CMAKE_SOURCE_DIR}/workdir/)
EXECUTE_PROCESS(COMMAND ln -sr ${CMAKE_SOURCE_DIR}/tools/runsbatch.sh ${CMAKE_SOURCE_DIR}/workdir/)
EXECUTE_PROCESS(COMMAND ln -sr ${CMAKE_SOURCE_DIR}/tools/setFixedParameter.sh ${CMAKE_SOURCE_DIR}/workdir/)
EXECUTE_PROCESS(COMMAND ln -sr ${CMAKE_SOURCE_DIR}/tools/setStartAndLengthFromRuns.sh ${CMAKE_SOURCE_DIR}/workdir/)
EXECUTE_PROCESS(COMMAND ln -sr ${CMAKE_SOURCE_DIR}/tools/startArrayOnMax.sh ${CMAKE_SOURCE_DIR}/workdir/)
EXECUTE_PROCESS(COMMAND ln -sr ${CMAKE_SOURCE_DIR}/tools/mergeDat.sh ${CMAKE_SOURCE_DIR}/workdir/)
EXECUTE_PROCESS(COMMAND ln -sr ${CMAKE_SOURCE_DIR}/tools/maxMerge.sh ${CMAKE_SOURCE_DIR}/workdir/)
EXECUTE_PROCESS(COMMAND ln -sr ${CMAKE_SOURCE_DIR}/tools/README ${CMAKE_SOURCE_DIR}/workdir/)

#ADD_CUSTOM_TARGET(link_target All
#	COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/tools/runsbatch.sh ${CMAKE_SOURCE_DIR}/workdir/)

#EXECUTE_PROCESS(COMMAND ln -sr ${PROJECT_BINARY_DIR}/tools/array_max_run1138.sh ${CMAKE_SOURCE_DIR}/workdir/.)
#EXECUTE_PROCESS(COMMAND ln -sr ${PROJECT_BINARY_DIR}/tools/array_max_run1143.sh ${CMAKE_SOURCE_DIR}/workdir/.)
#EXECUTE_PROCESS(COMMAND ln -sr ${PROJECT_BINARY_DIR}/tools/array_max_run1146.sh ${CMAKE_SOURCE_DIR}/workdir/.)
#EXECUTE_PROCESS(COMMAND ln -sr ${PROJECT_BINARY_DIR}/tools/array_max_run1261.sh ${CMAKE_SOURCE_DIR}/workdir/.)
#EXECUTE_PROCESS(COMMAND ln -sr ${PROJECT_BINARY_DIR}/tools/maxMerge.sh ${CMAKE_SOURCE_DIR}/workdir/.)
#EXECUTE_PROCESS(COMMAND ln -sr ${PROJECT_BINARY_DIR}/tools/mergeDat.sh ${CMAKE_SOURCE_DIR}/workdir/.)
# EXECUTE_PROCESS(COMMAND ln -s ${PROJECT_BINARY_DIR}/daq_ana/run.sh ${CMAKE_SOURCE_DIR}/workdir/.)
