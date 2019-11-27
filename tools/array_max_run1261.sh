#!/bin/bash
#SBATCH --mail-type ALL                           # Type of email notification- BEGIN,END,FAIL,ALL
#SBATCH --mail-user jhktimm@mail.desy.de          # Email to which notifications will be sent. It defaults to <userid@mail.desy.de> if none is set.
#SBATCH --time    0-15:00:00
#SBATCH --nodes            1
#SBATCH --partition maxwell
#SBATCH --no-requeue
#SBATCH --array 0-15                                         # !!!!!!!!!!!!!!!always start at 0!
#SBATCH --cpus-per-task 40
#SBATCH --job-name Mona                              # !!!!!!!!!!!!!1 NAME !!!!!!!!!!!!!
#SBATCH --output    job-%x-%A-%a-%j-%N.out
#SBATCH --error     job-%x-%A-%a-%j-%N.err            # File to which STDERR will be written
export LD_PRELOAD=""
nprocs=40
#export nprocs=$((`/usr/bin/nproc`))
source /etc/profile.d/modules.sh
echo "SLURM_JOB_ID           $SLURM_JOB_ID"
echo "SLURM_JOB_NAME         $SLURM_JOB_NAME"
echo "SLURM_JOB_NODES        $SLURM_JOB_NODES"
echo "SLURM_ARRAY_JOB_ID     $SLURM_ARRAY_JOB_ID"
echo "SLURM_ARRAY_TASK_ID    $SLURM_ARRAY_TASK_ID"
echo "SLURM_ARRAY_TASK_COUNT $SLURM_ARRAY_TASK_COUNT"
echo "SLURM_ARRAY_TASK_MAX   $SLURM_ARRAY_TASK_MAX"
echo "SLURM_ARRAY_TASK_MIN   $SLURM_ARRAY_TASK_MIN"

runnumber=1261                                              # 0 - 5 array!!!!!!!!!!!!!!!
dataDirectory=/beegfs/desy/user/jhktimm/rawdata/                               # !!!!!!!!!!!!!!!
resultDirectory=/beegfs/desy/user/jhktimm/results/                               # !!!!!!!!!!!!!!!
aoaDirectory=/home/jhktimm/sources/aoa_delta/                          # !!!!!!!!!!!!!!!
logDirectory=/beegfs/desy/user/jhktimm/logs/                           # !!!!!!!!!!!!!!!
# !!!!!!!!!!!!!!!
COUNTER=0
START=313                                                            # start !!!!!!!!! 31321-94674...-> 15.8jobs pro (40cpus and 100files)
#arrayRun=0 #!!! ONLY FOR tests
((arrayRun=$SLURM_ARRAY_TASK_ID))
echo nprocs $nprocs
echo real nprocs $((`/usr/bin/nproc`))
echo number $number
((number=$START+($arrayRun*$nprocs)))
echo number $number
docker pull jhktimm/aoa
while [  $COUNTER -lt $nprocs ]; do
  echo The counter is $COUNTER
  postfix=${SLURM_JOB_NAME}_run${runnumber}_file${number}xx
  if [ $number -eq 0 ]
  then
    filepath="/data/linac_test_main_run${runnumber}_file??_*.raw /data/linac_test_main_run${runnumber}_file?_*.raw"
  else
    filepath=/data/linac_test_main_run${runnumber}_file${number}??_*.raw
  fi
  echo "#!/bin/bash" > tmp${number}
  echo "./daqanalysis /results/ ${postfix} ${filepath} >> /logs/log_daq_${SLURM_JOB_NAME}_Array${SLURM_ARRAY_JOB_ID}_ID${SLURM_JOB_ID}_run${runnumber}_job${number}.log" >> tmp${number}
#   echo "sleep 120" >> tmp${number}

  cat tmp${number}

  chmod +x tmp${number}
  pwd
  dockerrun -w /space/aoa_delta/workdir -v ${aoaDirectory}:/space/aoa_delta  -v ${resultDirectory}:/results  -v ${dataDirectory}:/data  -v ${logDirectory}:/logs  -dit jhktimm/aoa  ./tmp${number}
  sleep 0.3
  rm tmp${number}
  
  let COUNTER=COUNTER+1 
  let number=number+1 
done

numberOfRunningDockerContainer=`docker container ls | grep jhktimm | wc -l`
while [[ $numberOfRunningDockerContainer -ne 0 ]] ; do
  numberOfRunningDockerContainer=`docker container ls | grep jhktimm | wc -l`
  echo `date` running docker container: $numberOfRunningDockerContainer
  sleep 60;
#   sleep 1;
done

echo running docker container: $numberOfRunningDockerContainer
echo end job $SLURM_JOB_ID $SLURM_ARRAY_JOB_ID
