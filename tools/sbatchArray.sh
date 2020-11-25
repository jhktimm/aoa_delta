#!/bin/bash
#SBATCH --mail-type ALL                           # Type of email notification- BEGIN,END,FAIL,ALL
#SBATCH --time    0-03:59:00
#SBATCH --nodes            1
#SBATCH --partition maxwell
#SBATCH --no-requeue
#SBATCH --cpus-per-task 40
#SBATCH --output    job-%x-%A-%a-%j-%N.out
#SBATCH --error     job-%x-%A-%a-%j-%N.err            # File to which STDERR will be written

containerName=docker_${SLURM_JOB_ID}
function runningApps () {
   numberOfRunningAppication=$((`docker exec ${containerName} ps | grep $1 | wc -l`))
   echo ${numberOfRunningAppication}
}
#docker_4186235
#SLURM_JOB_ID           4186235

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
filepath=""
postfix=""
source setFixedParameter.sh
source $1
echo "aoaDirectory=${aoaDirectory}"
echo "dataDirectory=${dataDirectory}"
echo "logDirectory=${logDirectory}"
echo "parameterDirectory=${parameterDirectory}"
echo "resultDirectory=${resultDirectory}"
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

###starting container
docker --version
#docker pull jhktimm/aoa
dockerrun \
  -w /space/aoa_delta/workdir \
  -v ${aoaDirectory}:/space/aoa_delta \
  -v ${resultDirectory}:/results \
  -v ${dataVolume}:${dataVolume} \
  -v ${logDirectory}:/logs \
  --name ${containerName} \
  -dit jhktimm/aoa  bash

docker container ls
pwd

while [  $COUNTER -lt $nprocs ]; do
  echo The counter is $COUNTER
  postfix="${runName}_`./getFileList -size=20 -coreNumber=${COUNTER} -arrayNumber=${arrayRun} -indexFile=${runName}.index -outputFile=${number}_fileList.txt`"
  echo " postfix: ${postfix}"

  for f in `cat ${number}_fileList.txt`; do
    #filepath="${filepath} /data/${f}"
    filepath="${filepath} ${dataDirectory}${f}"
  done

  echo "#!/bin/bash" > tmp${number}
  echo "pwd" >> tmp${number}
  echo "./ladybug -r=/results/ -p=${postfix} -t=${parameterDirectory} ${filepath} >> /logs/log_daq_${postfix}_Array${SLURM_ARRAY_JOB_ID}_ID${SLURM_JOB_ID}.log" >> tmp${number}
#  echo "./daqanalysis -r=/results/ -p=${postfix} -t=${parameterDirectory} ${filepath} >> /logs/log_daq_${postfix}_Array${SLURM_ARRAY_JOB_ID}_ID${SLURM_JOB_ID}.log" >> tmp${number}
  cat tmp${number}
  chmod +x tmp${number}
  pwd

  ###execute ladybugs in container
#  dockerexec -d ${containerName} ./tmp${number}
  docker exec -u `id -u`:`id -g` -d ${containerName} ./tmp${number}
#  dockerrun -w /space/aoa_delta/workdir -v ${aoaDirectory}:/space/aoa_delta  -v ${resultDirectory}:/results  -v ${dataDirectory}:/data  -v ${logDirectory}:/logs  -dit jhktimm/aoa  ./tmp${number}
  sleep 0.3

  ###clean up
  rm tmp${number}
  rm ${number}_fileList.txt
  filepath=""
  let COUNTER=COUNTER+1
  let number=number+1
done


###wait for all ladybugs
#numberOfRunningDockerContainer=`docker container ls | grep jhktimm | wc -l`
echo "`runningApps ladybug` ladybugs flying"
while [[ $((`runningApps ladybug`)) -ne 0 ]] ; do
#while [[ $numberOfRunningDockerContainer -ne 0 ]] ; do
#  numberOfRunningDockerContainer=`docker container ls | grep jhktimm | wc -l`
#  echo `date` running docker container: $numberOfRunningDockerContainer
  echo "`runningApps ladybug` ladybugs flying"
  sleep 120;
done
#echo running docker container: $numberOfRunningDockerContainer
docker container stop ${containerName}
docker container rm ${containerName}
after=$(date +%s)
echo "`date` : start ${before}, stop ${after} "
echo "elapsed time: `date -u --date=@$((after - before)) +%H:%M:%S`"
echo "end job ${SLURM_JOB_ID} ${SLURM_ARRAY_JOB_ID}"
