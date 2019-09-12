#!/bin/bash
#!/bin/bash
#SBATCH --mail-type ALL                           # Type of email notification- BEGIN,END,FAIL,ALL
#SBATCH --mail-user jhktimm@mail.desy.de          # Email to which notifications will be sent. It defaults to <userid@mail.desy.de> if none is set.
#SBATCH --time    0-04:00:00
#SBATCH --nodes            1
#SBATCH --partition maxwell
#SBATCH --no-requeue                                               # !!!!!!!!!!!!!!!
#SBATCH --job-name maXfelMerge
#SBATCH --output    job-%x-%A-%a-%j-%N.out
#SBATCH --error     job-%x-%A-%a-%j-%N.err            # File to which STDERR will be written

function nrwait() {
  local nrwait_my_arg
  if [[ -z $1 ]] ; then
    nrwait_my_arg=$(grep "processor" < /proc/cpuinfo | wc -l)
#      nrwait_my_arg=2
  else
    nrwait_my_arg=$1
  fi

  while [[ $(jobs -p | wc -l) -ge $nrwait_my_arg ]] ; do
    sleep 0.33;
  done
}

resultDirectory=/beegfs/desy/user/jhktimm/merged/
dataToMergeDirectory=/beegfs/desy/user/jhktimm/results/
#interludefix=maXfelQ
interludefix=Kvelertak
station=A17
newPreFix=Kvelertak

#for run in  1138 ; do
#for run in  1143 1146 ; do
for run in  1143 ; do
#for run in  1146 ; do
#for run in  1138 1143 1146 ; do

  for module in {1..4} ; do
    for cavity in {1..8} ; do
      echo ${resultDirectory}${newPreFix}_${station}.L3.M${module}.C${cavity}_run${run}.dat ${dataToMergeDirectory}${station}.L3.M${module}.C${cavity}_${interludefix}_run${run}_file${fileNumber}*.dat
      ./mergeDat.sh ${resultDirectory}${newPreFix}_${station}.L3.M${module}.C${cavity}_run${run}.dat ${dataToMergeDirectory}${station}.L3.M${module}.C${cavity}_${interludefix}_run${run}_file${fileNumber}*.dat &
#      echo $! >> .tmp
      echo `date` `jobs -l`
      nrwait
    done
  done
done  
jobs -l

wait
echo `date` jobs are finnish
#rm .tmp
