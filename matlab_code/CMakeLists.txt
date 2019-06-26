#~ include_directories(f_generate_online_parityRes1)
#~ add_subdirectory(f_generate_online_parityRes1)
#~ include_directories(f_generate_online_parityRes2)
#~ add_subdirectory(f_generate_online_parityRes2)
#~ include_directories(f_generate_online_UKF_residual)
#~ add_subdirectory(f_generate_online_UKF_residual)
#~ include_directories(f_get_calCoeff_codegen)
#~ add_subdirectory(f_get_calCoeff_codegen)
include_directories(f_generate_and_eval_residual)
add_subdirectory(f_generate_and_eval_residual)
# include_directories(f_calib_and_res_gen_ukf)
# add_subdirectory(f_calib_and_res_gen_ukf)

add_library(AAnalysis  SHARED
../src/AAnalysis.cc
)

#~ message("{ChimeraTK-ApplicationCore_INCLUDE_DIRS} ${ChimeraTK-ApplicationCore_INCLUDE_DIRS}")
#~ target_include_directories(AAnalysis PUBLIC ${ChimeraTK-ApplicationCore_INCLUDE_DIRS})
target_include_directories(AAnalysis PUBLIC)
target_link_libraries(AAnalysis
                                #~ f_get_calCoeff_codegen
                                #~ f_generate_online_UKF_residual
                                #~ f_generate_online_parityRes1
                                #~ f_generate_online_parityRes2
								f_generate_and_eval_residual
                                "-ljsoncpp"
                                #~ ${ChimeraTK-ApplicationCore_LIBRARIES}
)
