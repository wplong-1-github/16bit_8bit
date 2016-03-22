#!/bin/bash



# line 18 -- flipN[6] --> flipN[up to 20]
# line 58 -- add line while loop
# line 65 -- add frame statement


#function modifyCode() {

#lineNumToReplace=$(nl -ba -w3 $preProgramName | grep "$searchKeyWord" | cut -c1-3)
#echo $lineNumToReplace
#totalLineNum=$(wc -l $preProgramName | cut -c1-3)
#echo $totalLineNum

#head -n $((lineNumToReplace-1)) $preProgramName > $programName
#echo " after head"
#sed ${lineNumToReplace}"q;d" $preProgramName | tail -n 1 | sed "s/${replaceFrom}/${replaceTo}/g" >> $programName
#echo "after sed" 
#tail -n $((totalLineNum-lineNumToReplace)) $preProgramName >> $programName
#echo "after tail"
#}

# from random2.cpp generate rnadom3.cpp

# from random(n).cpp generate random(n+1).cpp

# 1. generate filename
name=random
extension=.cpp

for (( i=3; i<21; i=i+1 ))
# ((innit: limit: step))
do

    preProgramName="$name$((i-1))$extension"
    programName="$name$i$extension"


    searchKeyWord="int flipN"
    replaceFrom=$((i-1))
    replaceTo=$((i))
    lineNumToReplace=$(nl -ba -w3 $preProgramName | grep "$searchKeyWord" | cut -c1-3)


    searchKeyWord2="while (flipN\[1\] == flipN\[0\])"
    lineNumToReplace2=$(nl -ba -w3 $preProgramName | grep "$searchKeyWord2" | cut -c1-3)


    searchKeyWord3="frame\[flipN\[0\]\]"
    replaceFrom2=")"
    replaceTo2=" || flipN[$((i-1))] == flipN[$((i-2))])"
    lineNumToReplace3=$(nl -ba -w3 $preProgramName | grep "$searchKeyWord3" | cut -c1-3)


    searchKeyWord4="frame\[flipN\[$((i-2))\]\]"
    lineNumToReplace4=$(nl -ba -w3 $preProgramName | grep "$searchKeyWord4" | cut -c1-3)


    totalLineNum=$(wc -l $preProgramName | cut -c1-3)


    head -n $((lineNumToReplace-1)) $preProgramName > $programName

# replace "flipN[x]"
    sed ${lineNumToReplace}"q;d" $preProgramName | sed "s/${replaceFrom}/${replaceTo}/g" >> $programName
    echo "after replace flipN[]"
    sed -n "$((lineNumToReplace+1)),$((lineNumToReplace2-1))p" $preProgramName >> $programName

# add line flipN[x] = rand()
    echo "flipN[$((i-1))] = rand() % FRM;" >> $programName
    echo "after addline flipN[]"

    sed -n "$((lineNumToReplace2)),$((lineNumToReplace3-2))p" $preProgramName >> $programName
    echo "after output before whilelooop"
# add character to while condition using replacement
    echo ${replaceFrom2}
    echo ${replaceTo2}

    echo $lineNumToReplace

    sed $((lineNumToReplace3-3))"q;d" $preProgramName | sed "s/${replaceFrom2}/${replaceTo2}/g" >> $programName
    echo "flipN[$((i-1))] = rand() % FRM;" >> $programName

    echo "after addline to while"

    echo $searchKeyWord4
    echo $((lineNumToReplace3))
    echo ${lineNumToReplace4}

    sed -n "$((lineNumToReplace3-1)),${lineNumToReplace4}p" $preProgramName >> $programName
    echo "frame[flipN[$((i-1))]] = !frame[flipN[$((i-1))]];" >> $programName


    tail -n $((totalLineNum-lineNumToReplace4)) $preProgramName >> $programName



    echo "****************************************"
    echo "$programName has been created!"
#cat $preProgramName

done