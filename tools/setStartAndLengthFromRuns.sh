#!/bin/bash
case "$1" in
    1138) runnumber=$1; START=7; arrayRange=0-2;;
    1143) runnumber=$1; START=1; arrayRange=0-20;;
    1146) runnumber=$1; START=10; arrayRange=0-5;;
    1261) runnumber=$1; START=313; arrayRange=0-15;;
    1262) runnumber=$1; START=0; arrayRange=0-4;;
    *) runnumber=""; START=""; arrayRange="";echo "Runnumber $1 is not defined in setStartAndLengthFromRuns";return 1;;
esac
echo "Set parameter for run to runnumber=${runnumber} START=${START} arrayRange=${arrayRange}"
return 0
