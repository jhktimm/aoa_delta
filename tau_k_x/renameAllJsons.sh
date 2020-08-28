#!/bin/bash
tmpDir=`pwd`
for dir in `ls -d */`
do 
  echo Enter dir: ${dir}
  cd $dir
  for fileName in `ls *.json`
  do 
    echo new name: ${fileName:0:20}.json   rest: ${fileName:20}
    [ $# -eq 1 ]  && [ $1 = "-f" ] && mv ${fileName} ${fileName:0:20}.json 
  done 
  cd .. 
done
cd ${tmpDir}

echo
echo ------------------------------------------------------
echo 
echo This would rename all the json files as you see above,
echo but only, if you start this with '-f' to rename it.
echo
