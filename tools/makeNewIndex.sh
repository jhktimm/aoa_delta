#!/bin/bash
echo trying to make index file of the data directory, defined in setFixedParameter.sh
source setFixedParameter.sh
echo "dataDirectory = ${dataDirectory}"
echo this will take same time
ls ${dataDirectory} > index
echo starting getStartAndArraySizeForRuns
./getStartAndArraySizeForRuns index
echo "index done"
