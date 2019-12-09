#!/bin/bash
#dataDirectory=/beegfs/desy/user/jhktimm/rawdata/                               # !!!!!!!!!!!!!!!
#resultDirectory=/beegfs/desy/user/jhktimm/results/                               # !!!!!!!!!!!!!!!
#aoaDirectory=/home/jhktimm/sources/aoa_delta/                          # !!!!!!!!!!!!!!!
#logDirectory=/beegfs/desy/user/jhktimm/logs/
source ../setFixedParameter.sh

dockerrun -w /space/aoa_delta/build \
  --tmpfs /tmp \
  -v ${aoaDirectory}:/space/aoa_delta  \
  -v ${resultDirectory}:/results  \
  -v ${dataDirectory}:/data  \
  -v ${logDirectory}:/logs  \
  -it jhktimm/aoa bash
