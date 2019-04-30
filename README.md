# aoa_delta
#### build

    mkdir build
    cd build
    cmake ..
    make

# to test with a data set

    ./data_test ../data/data_set_2.json

# daqanalysis, analysis of cavity signals direct on .raw files, 
the program daqanalysis should be ion the build/daq_ana directory
    
    cd ana_daq

    ./daqanalysis <postfix for .dat files> <list of .bit files to execute the analysis>

#### example

    time ./daqanalysis run1143_file2000-2999 ../daq_data/run1143/linac_test_main_run1143_file2???_*.bit > run1143_file2000-2999_xfeluser2.log &

# DO NOT USE, use daqanalysis!!! to analys .bit files from snap daq data do:

    ./daq_aoa <postfix for .dat files> <list of .bit files to execute the analysis>

#### example:

    ./daq_aoa run1143_file2000-2999 ../daq_data/run1143/linac_test_main_run1143_file2???_*.bit

#### or

    time ./daq_aoa run1143_file2000-2999 ../daq_data/run1143/linac_test_main_run1143_file2???_*.bit > run1143_file2000-2999_xfeluser2.log &




# to run live on exfel
    ./aoa_app


env LANG=C cmake -DCMAKE_MODULE_PATH=/home/jhktimm/jhbuild/install/share/cmake-3.5/Modules ..
