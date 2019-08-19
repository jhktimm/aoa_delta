# aoa_delta
#### Build

    mkdir build
    cd build
    cmake ..
    make

## Intro

### Directories

#### docker/
#### include/ and src/
#### data_test/
This is for Test with data stort as .json file also located in this directory.

#### daq_ana
Here are the source files for the offline analyse as well as an example for open single doocs daq raw files.

#### matlab_code/
Here is the automatic generated code from matlab for analysis.
##### Add new code
Just unpack new code and copy the directory into matlab_code/ .
Then run ./generate_CMakeListsandheaders.sh in directory matlab_code/ to create automatic header files.
Do not forget to customize the CMakeLists.txt in directory matlab_code/ ,
    include_directories(pathToNewDirectory)
    add_subdirectory(pathToNewDirectory)
and add this also to `target_link_libraries` .

If the used function changed his variables, of course you have to customize your code as well.
For example src/AAnalysis.cpp and include/AAnalysis.h .

#### tau_k_x/
Here is stired some data used from the analysis as .json files.

#### tolls/
Some bash scripts to run jobs an Maxwell Cluster like [tools/array_max_run1138.sh](tools/array_max_run1138.sh).
Attention! Use these scripts in workdir/ directory!
To merge the results as job on Maxwell see [tools/maxMerge.sh](tools/maxMerge.sh).
To merge the results manually see [tools/mergeDat.sh](tools/mergeDat.sh).

#### workdir/
Cmake links all executeble and scrits in this directory.
`cd` in this to work here and run jobs on maxwell etc.

# Test with a data set

    ./data_test ../data/data_set_2.json

# Daqanalysis, analysis of cavity signals direct on .raw files,
the program daqanalysis should be ion the build/daq_ana directory
    
    cd ana_daq

    ./daqanalysis <postfix for .dat files> <list of .bit files to execute the analysis>

#### Example

    time ./daqanalysis run1143_file2000-2999 ../daq_data/run1143/linac_test_main_run1143_file2???_*.bit > run1143_file2000-2999_xfeluser2.log &

# DO NOT USE, use daqanalysis!!! to analys .bit files from snap daq data do:

    ./daq_aoa <postfix for .dat files> <list of .bit files to execute the analysis>

#### Example:

    ./daq_aoa run1143_file2000-2999 ../daq_data/run1143/linac_test_main_run1143_file2???_*.bit

#### or

    time ./daq_aoa run1143_file2000-2999 ../daq_data/run1143/linac_test_main_run1143_file2???_*.bit > run1143_file2000-2999_xfeluser2.log &

# Docker container with all dependencies

## Build the container
    cd docker
    docker build -t yourNameOfContainer .

## Upload it to your repo
    docker push yourNameOfContainer

## run bash in container with all data directories on maxwekk cluster
Of course log in into the maxwell cluster with ssh.
See [docker/runBash.sh](docker/runBash.sh)

##

# Run offline on data on the Maxwell Cluster


# Run live on XFEL
    ./aoa_app


env LANG=C cmake -DCMAKE_MODULE_PATH=/home/jhktimm/jhbuild/install/share/cmake-3.5/Modules ..
