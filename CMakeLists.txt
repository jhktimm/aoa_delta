cmake_minimum_required(VERSION 2.8)
project(aoa)

include(cmake/add_dependency.cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)

add_dependency(ChimeraTK-ApplicationCore 01.01 REQUIRED)
add_dependency(ChimeraTK-ControlSystemAdapter-DoocsAdapter 00.09 REQUIRED)
add_dependency(DOOCS 18.10.5 COMPONENTS daqreader REQUIRED)


include_directories(matlab_code/)
add_subdirectory(matlab_code)

add_executable(daq_aoa src/main.cpp)

  set_target_properties(daq_aoa PROPERTIES COMPILE_FLAGS "${ChimeraTK-ApplicationCore_CXX_FLAGS} ${DOOCS_CXX_FLAGS}")
  set_target_properties(daq_aoa PROPERTIES LINK_FLAGS "${ChimeraTK-ApplicationCore_LINK_FLAGS} ${DOOCS_LINKER_FLAGS}")
	target_link_libraries(daq_aoa 
	#~ ${ChimeraTK-ApplicationCore_LIBRARIES}
	AAnalysis
    ${DOOCS_LIBRARIES}
    ${ChimeraTK-ApplicationCore_LIBRARIES}
	#~ "-ljsoncpp"
	)
  
#  add_executable(data_test test/data_test.cpp)
#
#  set_target_properties(data_test PROPERTIES COMPILE_FLAGS "${ChimeraTK-ApplicationCore_CXX_FLAGS} ${DOOCS_CXX_FLAGS}")
#  set_target_properties(data_test PROPERTIES LINK_FLAGS "${ChimeraTK-ApplicationCore_LINK_FLAGS} ${DOOCS_LINKER_FLAGS}")
#	target_link_libraries(data_test 	OnlineAnalysis ${DOOCS_LIBRARIES})
#
  add_executable(aoa_app src/aoa.cc )

  set_target_properties(aoa_app PROPERTIES COMPILE_FLAGS "${ChimeraTK-ControlSystemAdapter_CXX_FLAGS} ${DOOCS_CXX_FLAGS} -O3 ")
  set_target_properties(aoa_app PROPERTIES LINK_FLAGS "${ChimeraTK-ControlSystemAdapter_LINK_FLAGS} ${ChimeraTK-ControlSystemAdapter-DoocsAdapter_LINK_FLAGS} ${DOOCS_LINKER_FLAGS} ")
  target_include_directories(aoa_app PUBLIC ${ChimeraTK-ApplicationCore_INCLUDE_DIRS})
  target_link_libraries(aoa_app 
		#~ ${PROJECT_NAME}
		#~ ${Boost_LIBRARIES}
    ${DOOCS_LIBRARIES}
		${ChimeraTK-ControlSystemAdapter_LIBRARIES}
		${ChimeraTK-ControlSystemAdapter-DoocsAdapter_LIBRARIES}
		#~ ${LibXML++_LIBRARIES}
		#~ ${glib_LIBRARIES}
		#~ ${HDF5_LIBRARIES}
		AAnalysis
		${ChimeraTK-ApplicationCore_LIBRARIES}
		"-ljsoncpp"
		#~ "-lstdc++"
		)

  # copy config files for 2nd example
  FILE( COPY ${CMAKE_SOURCE_DIR}/dmap_files/aoa.dmap DESTINATION ${PROJECT_BINARY_DIR})
  FILE( COPY ${CMAKE_SOURCE_DIR}/aoa_app.conf DESTINATION ${PROJECT_BINARY_DIR})
  
#end aos
include_directories(data_test/)
add_subdirectory(data_test)

include_directories(daqsnap/)
add_subdirectory(daqsnap)

include_directories(daq_ana/)
add_subdirectory(daq_ana)

EXECUTE_PROCESS(COMMAND mkdir ${PROJECT_BINARY_DIR}/../workdir)
EXECUTE_PROCESS(COMMAND ln -s ${PROJECT_BINARY_DIR}/daq_aoa ${PROJECT_BINARY_DIR}/../workdir/.)
