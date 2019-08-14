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

resultDirectory=/beegfs/desy/user/jhktimm/merged/
dataToMergeDirectory=/beegfs/desy/user/jhktimm/results/
interludefix=maXfel_Eval
newPreFix=test

for run in  1138 ; do
#for run in  1138 1143 1146 ; do

  for module in {1..4} ; do
    for cavity in {1..8} ; do
      echo ${resultDirectory}A17.L3.M${module}.C${cavity}_run${run}.dat ${dataToMergeDirectory}A17.L3.M${module}.C${cavity}_${interludefix}_run${run}_file${fileNumber}*.dat
      ./mergeDat.sh ${resultDirectory}${newPreFix}_A17.L3.M${module}.C${cavity}_run${run}.dat ${dataToMergeDirectory}A17.L3.M${module}.C${cavity}_${interludefix}_run${run}_file${fileNumber}*.dat &
    done
  done
done  
