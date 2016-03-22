#!/bin/bash
# line 5 -- define NUM 7 -> 14

name=random
extension=.cpp

for (( i=1; i<21; i=i+1 ))
do
    preProgramName="$name$i$extension"
    nextProgramName=$name$i"N14"$extension

    echo $preProgramName
    echo $nextProgramName

    searchKeyWord="define NUM"
    replaceFrom=7
    replaceTo=14
    lineNumToReplace=$(nl -ba -w3 $preProgramName | grep "$searchKeyWord" | cut -c1-3)

    echo $lineNumToReplace

    totalLineNum=$(wc -l $preProgramName | cut -c1-3)


    head -n $((lineNumToReplace-1)) $preProgramName > $nextProgramName

    sed ${lineNumToReplace}"q;d" $preProgramName | sed "s/${replaceFrom}/${replaceTo}/g" >> $nextProgramName

    tail -n $((totalLineNum-lineNumToReplace)) $preProgramName >> $nextProgramName

done