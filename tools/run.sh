 #!/bin/bash
run="run1143"
#~ run="run1138"
echo "srthsth${run}kjhkjhg"
if [ "$1" == "" ] 
    then
        echo "Use: '. run.sh 23 test' for running:"
        echo "time ./daqanalysis ${run}_file23000-23999 /daq_data/xfel/USR1/LLRF/linac_test_main_${run}_file23???_*.raw > ${run}_file23000-23999_test.log &"

    else
        echo "files from $1000 to $1999 wil be analysed."
        echo "see log file: ${run}_file$1000-$1999_$2.log"
        echo "./daqanalysis ${run}_file$1000-$1999 /daq_data/xfel/USR1/LLRF/linac_test_main_${run}_file$1???_*.raw > ${run}_file$1000-$1999_$2.log" >> .log
        time ./daqanalysis ${run}_file$1000-$1999 /daq_data/xfel/USR1/LLRF/linac_test_main_${run}_file$1???_*.raw > ${run}_file$1000-$1999_$2.log

fi
 
numberOfNans=`cat *${run}_file$1000-$1999*.dat | grep nan | wc -l`
echo "cat *${run}_file$1000-$1999*.dat | grep nan | wc -l = $numberOfNans" >> ${run}_file$1000-$1999_$2.log
