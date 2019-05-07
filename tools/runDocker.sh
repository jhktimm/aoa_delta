#!/bin/bash
sshfs jhktimm@xfeluser1:/export/space/POOL /daq_data/xfel/USR1 -o allow_other
# run="run1146"
run="run1143"
#~ run="run1138"
# echo "srthsth${run}kjhkjhg"
dockerid="8d4de434a052"
echo $0 $1 $2 $3 $4 $5
if [ "$1" == "" ] 
    then
        echo "Use: '. runDocker.sh 23 test' for running:"
        echo "time ./daqanalysis ${run}_file23000-23999 /daq_data/xfel/USR1/LLRF/linac_test_main_${run}_file23???_*.raw > ${run}_file23000-23999_test.log &"

    else
        echo "files from $1000 to $1999 wil be analysed."
        echo "see log file: ${run}_file$1000-$1999_$2.log"
#         echo "./daqanalysis ${run}_file$1000-$1999 /daq_data/xfel/USR1/LLRF/linac_test_main_${run}_file$1???_*.raw > ${run}_file$1000-$1999_$2.log" >> .log
#         time ./daqanalysis ${run}_file$1000-$1999 /daq_data/xfel/USR1/LLRF/linac_test_main_${run}_file$1???_*.raw > ${run}_file$1000-$1999_$2.log
        echo "sudo docker run -i -v ${PWD}/results:/results -v /daq_data/xfel/USR1:/daqdata ${dockerid} sh -c './daqanalysis ${run}_file$1000-$1999 /daqdata/LLRF/linac_test_main_${run}_file$1???_*.raw && cp * /results' > ${run}_file$1000-$1999_$2.log" >> .log
#         sudo docker run -i -v ${PWD}/results:/results -v /daq_data/xfel/USR1:/daqdata ${dockerid} sh -c './daqanalysis '${run}_file$1000-$1999' '/daqdata/LLRF/linac_test_main_${run}_file$1???_*.raw' && cp * /results && echo '${run}_file$1000-$1999''
        sudo docker run -i -v ${PWD}/results:/results -v /daq_data/xfel/USR1:/daqdata ${dockerid} sh -c './daqanalysis '${run}_file$1000-$1999' '/daqdata/LLRF/linac_test_main_${run}_file$1???_*.raw' && cp * /results' > ${run}_file$1000-$1999_$2.log
#         docker run -i -v ${PWD}/results:/results -v /daq_data/xfel/USR1:/daqtest 8d4de434a052 sh -c './daqanalysis ttt /daqtest/LLRF/linac_test_main_run1146_file9999_* && cp * /results'
fi
 
numberOfNans=`cat results/*${run}_file$1000-$1999*.dat | grep nan | wc -l`
echo "cat results/*${run}_file$1000-$1999*.dat | grep nan | wc -l = $numberOfNans" >> ${run}_file$1000-$1999_$2.log
