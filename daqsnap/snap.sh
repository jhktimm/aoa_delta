#!/bin/bash
echo "usage: . snap /daq_data/xfel/LLRF/llrf_snap_stream_1_run909_file1_20190123T162220.1.raw "

for inputfile in $@; do
	start=$(date +%s)
	echo Convert file: $inputfile

	echo "<DAQREQ> <File name='$inputfile'/> </DAQREQ>" > .temp2.xml
	echo "<DAQREQ>" > .temp.xml
	echo "<Exp  name='llrf_snap'/>" >> .temp.xml
	#~ echo "<DDir name='/daq_data/xfel/LLRF/'/>" >> .temp.xml
	echo "<CDir name='/daq/xfel/adm/'/>" >> .temp.xml
	#echo "" >> .temp.xml
	#echo "" >> .temp.xml
	#echo "" >> .temp.xml
	stop0=$(date +%s)
	./user_test -xml .temp2.xml | while read line; do
	stop1=$(date +%s)
	#echo $line;
	p=${line%%]*};
	pre="$(echo $p | head -c 1)"
	n=${line#*: };
	na=${n%%Type*};
	name=${na%% *};
	nn=${name#*/};
	nnn=${nn%/*};
	#last=${name##*/};
	#fl="$(echo $last | head -c 1)"
	#echo $last
	#echo $nnn;
	events=${line##*:};
	if [ "$pre" == "[" ]
		then
		if [ ${events} -gt 0 ] 
		then
			if [ "$nnn" == "LLRF.CONTROLLER.DAQ" ]
			then
				#if [ "$fl" == "C" ] 
				#then
	#				echo "<Chan name='$name' />" >> .temp.xml;
							echo "<Chan name='$name' dtype='52'/>" >> .temp.xml;
				#fi
			fi

		fi
	fi
	done;
	echo "<File name='$inputfile'/>" >> .temp.xml;
	echo "</DAQREQ>" >> .temp.xml;


	kot=${inputfile##*/};fout=${kot%.*}.txt

	echo output file: $fout
	stop2=$(date +%s)
	#~ ./user_test -xml .temp.xml -nbunch 1820 -out $fout -start 1
	#~ ./user_test -xml .temp.xml -nbunch 1 -out $fout &
	#~ ./user_test -xml .temp.xml -out $fout 
	./user_test -xml .temp.xml -out $fout -dumpall
	stop3=$(date +%s)
	./txt2bit $fout 
	stop4=$(date +%s)
	rm -f $fout
	stop5=$(date +%s)

	echo "user_test first time:" $((stop1 - stop0)) "seconds"
	echo "writeing second xml file time:" $((stop2 - stop1)) "seconds"
	echo "user_test second time:" $((stop3 - stop2)) "seconds"
	echo "txt2bittime:" $((stop4 - stop3)) "seconds"
	echo "rm:" $((stop5 - stop4)) "seconds"
done
rm .temp2.xml .temp.xml
echo Convert finish

