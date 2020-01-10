#!/bin/bash

case "$1" in
    1138) runnumber=$1; START=7; arrayRange=0-2;;
    1143) runnumber=$1; START=0; arrayRange=0-19;;
    1146) runnumber=$1; START=0; arrayRange=0-5;;
    1261) runnumber=$1; START=313; arrayRange=0-15;;
    1262) runnumber=$1; START=0; arrayRange=0-4;;
    1279) runnumber=$1; START=141; arrayRange=0-7;;
    1280) runnumber=$1; START=0; arrayRange=0-0;;
    1281) runnumber=$1; START=0; arrayRange=0-0;;
    1282) runnumber=$1; START=0; arrayRange=0-0;;
    1283) runnumber=$1; START=0; arrayRange=0-0;;
    1284) runnumber=$1; START=0; arrayRange=0-19;;
    1286) runnumber=$1; START=0; arrayRange=0-0;;
    1287) runnumber=$1; START=0; arrayRange=0-0;;
    *) runnumber=""; START=""; arrayRange="";echo "Runnumber $1 is not defined in setStartAndLengthFromRuns";return 1;;
esac

echo "Set parameter for run to runnumber=${runnumber} START=${START} arrayRange=${arrayRange}"
return 0
