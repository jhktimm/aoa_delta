#!/bin/bash
#SBATCH --mail-type ALL                           # Type of email notification- BEGIN,END,FAIL,ALL
#SBATCH --mail-user jhktimm@mail.desy.de          # Email to which notifications will be sent. It defaults to <userid@mail.desy.de> if none is set.
#SBATCH --time    0-15:00:00
#SBATCH --nodes            1
#SBATCH --partition maxwell
#SBATCH --no-requeue
#SBATCH --array 0-2                                         # !!!!!!!!!!!!!!!always start at 0! 0-5
#SBATCH --cpus-per-task 40
#SBATCH --job-name maXfelMyAna                           # !!!!!!!!!!!!!!!!!!!!!!!! NAME OF THE JOB !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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

runnumber=1138                                              # 0 - 5 array!!!!!!!!!!!!!!!
dataDirectory=/beegfs/desy/user/jhktimm/rawdata/                               # !!!!!!!!!!!!!!!
resultDirectory=/beegfs/desy/user/jhktimm/results/                               # !!!!!!!!!!!!!!!
aoaDirectory=/home/jhktimm/sources/aoa_delta/                          # !!!!!!!!!!!!!!!
logDirectory=/beegfs/desy/user/jhktimm/logs/                           # !!!!!!!!!!!!!!!
# !!!!!!!!!!!!!!!
COUNTER=0
START=7                                                            # start !!!!!!!!!
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
  filepath=/data/linac_test_main_run${runnumber}_file${number}??_*.raw

  echo "#!/bin/bash" > tmp${number}
  echo "./daqanalysis /results/ ${postfix} ${filepath} >> /logs/log_daq_${SLURM_JOB_NAME}_ID${SLURM_JOB_ID}_run${runnumber}_job${number}.log" >> tmp${number}
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

#rm tmp*
echo running docker container: $numberOfRunningDockerContainer
echo end job $SLURM_JOB_ID $SLURM_ARRAY_JOB_ID
