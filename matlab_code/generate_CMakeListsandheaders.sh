#!/bin/bash
echo
echo 'generating header files and CMakeLists.txt for every subdirectory'
echo
echo
echo 'add this to your CMakeLists.txtin this directory'
echo
for directory in *
do
        if [ -d "${directory}" ]
        then
                echo "include_directories($directory)"
                echo "add_subdirectory($directory)"
                cd $directory
                echo "add_library(${directory}  SHARED" > CMakeLists.txt
                ls *.c >> CMakeLists.txt
                echo ")" >> CMakeLists.txt
                echo 'extern "C" {' > ../$directory.h
                for hfile in *.h
                do
                        echo '#include "'$directory/$hfile'"' >> ../$directory.h
                done
                echo '}' >> ../$directory.h
                cd ..
        fi
done
echo
echo "add this to target_link_libraries( "
for directory in *
do
     if [ -d "${directory}" ]
     then
            echo "     $directory"
     fi
done
echo ") also in CMameLists.txt"
echo
echo
echo 'and add to the headers (e.g. AAnalysis.h):'
echo
for hfile in *.h
do
        echo '#include "'../matlab_code/$hfile'"'
done
echo
echo 'to your c file'
echo 'of course, customize the directories'
