#!/bin/bash
echo 'generating header files and CMakeLists.txt for every subdirectory'
echo
for directory in *
do
        if [ -d "${directory}" ]
        then
                echo "include_directories(example2/lib/$directory)"
                echo "add_subdirectory(example2/lib/$directory)"
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
echo 'add this to your CMakeLists.txt and target_link_libraries(...) and the headers'
echo
for hfile in *.h
do
        echo '#include "'lib/$hfile'"'
done
echo
echo 'to your c file'
echo 'of course, customize the directories'
