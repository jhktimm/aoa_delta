#!/bin/bash
source setFixedParameter.sh
source setStartAndLengthFromRuns.sh $1

echo sbatch --job-name=$2 --mail-user=${userMail} --array=${arrayRange} startArrayOnMax.sh
/bin/bash startArrayOnMax.sh
