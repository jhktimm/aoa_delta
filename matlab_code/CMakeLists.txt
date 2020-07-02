#~ include_directories(f_generate_online_parityRes1)
#~ add_subdirectory(f_generate_online_parityRes1)
include_directories(f_generate_and_eval_multi_residuals_dwfix)
add_subdirectory(f_generate_and_eval_multi_residuals_dwfix)
#include_directories(f_generate_and_eval_residual8)
#add_subdirectory(f_generate_and_eval_residual8)

add_library(AAnalysis  SHARED
../src/AAnalysis.cc
)

target_include_directories(AAnalysis PUBLIC)
target_link_libraries(
        AAnalysis
        f_generate_and_eval_multi_residuals_dwfix
        "-ljsoncpp"
)
