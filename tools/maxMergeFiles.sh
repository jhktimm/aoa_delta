#!/bin/bash
#SBATCH --mail-type ALL                           # Type of email notification- BEGIN,END,FAIL,ALL
#SBATCH --mail-user jhktimm@mail.desy.de          # Email to which notifications will be sent. It defaults to <userid@mail.desy.de> if none is set.
#SBATCH --time    0-04:00:00
#SBATCH --nodes            1
#SBATCH --partition maxwell
#SBATCH --no-requeue                                               # !!!!!!!!!!!!!!!
#SBATCH --job-name mergeFiles
#SBATCH --output    job-%x-%A-%a-%j-%N.out
#SBATCH --error     job-%x-%A-%a-%j-%N.err            # File to which STDERR will be written

source setFixedParameter.sh
numberOfFilesPerMerge=100

#./mergeFiles -o -outDir=${mergeDirectory} -size=${numberOfFilesPerMerge} ${resultDirectory}*${1}*


echo "./mergeFiles -o -outDir=${mergeDirectory} -size=${numberOfFilesPerMerge} -inputDir=${resultDirectory} -searchPattern=${1}"
./mergeFiles -o -outDir=${mergeDirectory} -size=${numberOfFilesPerMerge} -inputDir=${resultDirectory} -searchPattern=${1}



# if file list too long... does not work, full path hase to be input
#find  ${resultDirectory} -name "*${1}*" -print0 | xargs -0 ./mergeFiles -o -outDir=${mergeDirectory} -size=${numberOfFilesPerMerge}

wait
echo `date` jobs are finnish
