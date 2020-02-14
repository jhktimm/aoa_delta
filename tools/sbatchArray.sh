#!/bin/bash
#SBATCH --mail-type ALL                           # Type of email notification- BEGIN,END,FAIL,ALL
#SBATCH --time    0-20:00:00
#SBATCH --nodes            1
#SBATCH --partition maxwell
#SBATCH --no-requeue
#SBATCH --cpus-per-task 40
#SBATCH --output    job-%x-%A-%a-%j-%N.out
#SBATCH --error     job-%x-%A-%a-%j-%N.err            # File to which STDERR will be written
export LD_PRELOAD=""
nprocs=10
#nprocs=40
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
filepath=""
postfix=""
source setFixedParameter.sh
source $1
echo "dataDirectory=${dataDirectory}"
echo "parameterDirectory=${parameterDirectory}"
before=$(date +%s)
echo "start at ${before}"
COUNTER=0
((arrayRun=$SLURM_ARRAY_TASK_ID))
#for testing    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#((arrayRun=0)) #for testing    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#for testing    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

echo nprocs $nprocs
echo real nprocs $((`/usr/bin/nproc`))
echo number $number
((number=$START+($arrayRun*$nprocs)))
echo number $number
docker pull jhktimm/aoa
while [  $COUNTER -lt $nprocs ]; do
  echo The counter is $COUNTER
  postfix="${runName}_`./getFileList -coreNumber=${COUNTER} -arrayNumber=${arrayRun} -indexFile=${runName}.index -outputFile=${number}_fileList.txt`"
  echo " postfix: ${postfix}"

  for f in `cat ${number}_fileList.txt`; do
    filepath="${filepath} /data/${f}"
  done

  echo "#!/bin/bash" > tmp${number}
  echo "./ladybug -r=/results/ -p=${postfix} -t=${parameterDirectory} ${filepath} >> /logs/log_daq_${postfix}_Array${SLURM_ARRAY_JOB_ID}_ID${SLURM_JOB_ID}.log" >> tmp${number}
#  echo "./daqanalysis -j=4 -r=/results/ -p=${postfix} -t=${parameterDirectory} ${filepath} >> /logs/log_daq_${postfix}_Array${SLURM_ARRAY_JOB_ID}_ID${SLURM_JOB_ID}.log" >> tmp${number}

#   echo "sleep 120" >> tmp${number}

  cat tmp${number}

  chmod +x tmp${number}
  pwd
  dockerrun -w /space/aoa_delta/workdir -v ${aoaDirectory}:/space/aoa_delta  -v ${resultDirectory}:/results  -v ${dataDirectory}:/data  -v ${logDirectory}:/logs  -dit jhktimm/aoa  ./tmp${number}
  sleep 0.3
  rm tmp${number}
  rm ${number}_fileList.txt
  filepath=""
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
after=$(date +%s)
echo "stop at ${before}"
echo "elapsed time:" $((after - $before)) "seconds"
echo running docker container: $numberOfRunningDockerContainer
echo stop at `date`
echo end job $SLURM_JOB_ID $SLURM_ARRAY_JOB_ID
