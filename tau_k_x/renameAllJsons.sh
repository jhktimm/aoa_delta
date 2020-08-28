#!/bin/bash
tmpDir=`pwd`
for dir in `ls -d */`
do 
  echo Enter dir: ${dir}
  cd $dir
  [ $# -eq 1 ]  && [ $1 = "-rm" ] && { rm -rf json/ ; cd .. ; continue ; }
  for fileName in `ls *.json`
    do    
    newFolder=`basename -s .json ${fileName:21}`
    echo new name: ${fileName:0:20}.json and move to folder: $newFolder
    [ $# -eq 1 ]  && [ $1 = "-f" ] && { mkdir -p $newFolder ; mv ${fileName} ${newFolder}/${fileName:0:20}.json ; }
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
