#!/bin/bash
#SBATCH --mail-type ALL                           # Type of email notification- BEGIN,END,FAIL,ALL
#SBATCH --mail-user jhktimm@mail.desy.de          # Email to which notifications will be sent. It defaults to <userid@mail.desy.de> if none is set.
#SBATCH --time    0-01:00:00
#SBATCH --nodes            1
#SBATCH --partition maxwell
#SBATCH --no-requeue                                               # !!!!!!!!!!!!!!!
#SBATCH --job-name comp
#SBATCH --output    job-%x-%A-%a-%j-%N.out
#SBATCH --error     job-%x-%A-%a-%j-%N.err            # File to which STDERR will be written

containerName=testC
function runningApps () {
   numberOfRunningAppication=$((`docker exec ${containerName} ps | grep $1 | wc -l`))
   echo ${numberOfRunningAppication}
}

export LD_PRELOAD=""
#nprocs=10
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
echo "dataDirectory=${dataDirectory}"
echo "parameterDirectory=${parameterDirectory}"
echo "aoaDirectory=${aoaDirectory}"
before=$(date +%s)
echo "start at ${before}"


echo "#!/bin/bash" > ${aoaDirectory}/workdir/tmp
echo "echo Hallo from container" >> ${aoaDirectory}/workdir/tmp
echo "ps" >> ${aoaDirectory}/workdir/tmp
echo "sleep 18" >> ${aoaDirectory}/workdir/tmp
echo "echo fino container > fino.txt" >> ${aoaDirectory}/workdir/tmp

chmod +x ${aoaDirectory}/workdir/tmp


docker run -it \
  -d\
  -w /space/aoa_delta/workdir \
  --tmpfs /tmp \
  -v ${aoaDirectory}:/space/aoa_delta  \
  --name ${containerName} \
  jhktimm/aoa \
  bash

docker container ls

docker exec -d ${containerName} ./tmp
docker exec -d ${containerName} ./tmp

while [[ $((`runningApps sleep`)) -ne 0 ]] ; do
  sleep $((2*3))
  echo "`runningApps tmp` tmp running"
  echo "`runningApps sleep` sleep running"
done
docker container stop ${containerName}
docker container rm ${containerName}
after=$(date +%s)
echo "`date` : start ${before}, stop ${after} "
echo "elapsed time: `date -u --date=@$((after - before)) +%H:%M:%S`"
