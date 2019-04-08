#!/bin/bash
for inputfile in $@; do
echo Convert file: $inputfile
kot=${inputfile##*/};xmlfile=${kot%.*}.xml
echo Write $xmlfile
echo "<DAQREQ> <File name='$inputfile'/> </DAQREQ>" > .temp2.xml
echo "<DAQREQ>" > $xmlfile
echo "<Exp  name='llrf_snap'/>" >> $xmlfile
echo "<DDir name='/daq_data/xfel/LLRF/'/>" >> $xmlfile
echo "<CDir name='/daq/xfel/adm/'/>" >> $xmlfile

./user_test -xml .temp2.xml | while read line; do
#echo $line;
p=${line%%]*};
pre="$(echo $p | head -c 1)"
n=${line#*: };
na=${n%%Type*};
name=${na%% *};
nn=${name#*/};
nnn=${nn%/*};

events=${line##*:};
if [ "$pre" == "[" ]
	then
	if [ ${events} -gt 0 ] 
	then
		if [ "$nnn" == "LLRF.CONTROLLER.DAQ" ]
		then
			#if [ "$fl" == "C" ] 
			#then
#				echo "<Chan name='$name' />" >> $xmlfile;
                		echo "<Chan name='$name' dtype='52'/>" >> $xmlfile;
			#fi
		fi

	fi
fi
done;
echo "<File name='$inputfile'/>" >> $xmlfile;
echo "</DAQREQ>" >> $xmlfile;

# kot=${inputfile##*/};fout=${kot%.*}.txt

# echo output file: $fout

#./user_test -xml $xmlfile -nbunch 200 -out $fout &
#./user_test -xml $xmlfile -out $fout

done
rm .temp2.xml
echo Convert finish


