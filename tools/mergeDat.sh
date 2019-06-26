#!/bin/bash

function merge {
  echo $0 $*
  if [ -z $3 ]; then
    echo "usage: $0 <filenamOfMergedFile> <filesToBeMerged>"
    echo "or   : $0 gui"
  exit 1
  fi  
  #buldinbg the header fron first file
  head -n1 $2 > $1
  #merge all data to am tmp file
  touch $1.tmp
  for file in ${*:2}; do
    tail -n+2 $file >> $1.tmp
  done
  #sort merged file in time
#   cat $1.tmp | sort -k 2 -n >> $1
  #sort merged file in pid
  cat $1.tmp | sort -k 1 -n >> $1
  rm $1.tmp
}

if [ "$1" = "gui" ]; then
  if ! FILES=$(zenity --file-selection --multiple --separator=' ' --file-filter=*.dat --title "Select files to merge." ); then
    exit; 
  fi
  if ! MERGENAME=$(zenity --file-selection --save --confirm-overwrite --separator=' ' --file-filter=*.dat --title "Select one file to save the megred files. File will be overwritten"  ); then
    exit; 
  fi
  merge $MERGENAME $FILES
else  
  if [ -f $1 ]; then
    echo "$1 does already exists."
    exit 1
  fi
  merge $*
fi  


  
