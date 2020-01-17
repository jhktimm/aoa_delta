#!/bin/bash
echo "usage: ./run <runParameters.run>"
#set -e
source $1
echo "Indexing data director: ${dataDirectory}"
echo "Please wait..."
ls ${dataDirectory} > ${runName}.index
((numberOfFiles=$((`cat ${runName}.index | wc -l`))))
((numberOfArrays=numberOfFiles/(40*100)))
echo "Found ${numberOfFiles} files."
echo "Number of arrays: ${numberOfArrays}."
arrayRange=0-${numberOfArrays}
echo sbatch --job-name=${runName} --mail-user=${userMail} --array=${arrayRange} sbatchArray.sh $1
sbatch --job-name=${runName} --mail-user=${userMail} --array=${arrayRange} sbatchArray.sh $1
