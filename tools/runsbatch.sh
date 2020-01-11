#!/bin/bash
echo "usage: ./runsbatch <runNumber> <runName> <tauDirectory>"
echo "Before starting, define runNumber with start point and array range in setStartAndLengthFromRuns.sh ."
set -e
source setFixedParameter.sh
source setStartAndLengthFromRuns.sh $1

echo sbatch --job-name=$2 --mail-user=${userMail} --array=${arrayRange} startArrayOnMax.sh ${runnumber} ${START}
sbatch --job-name=$2 --mail-user=${userMail} --array=${arrayRange} startArrayOnMax.sh ${runnumber} ${START} $3

