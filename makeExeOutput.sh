#!/bin/bash

name=random
extension=.cpp
outExtension=.out

for (( i=1; i<21; i=i+1 ))
do
    preProgramName="$name$i$extension"
    nextProgramName=$name$i"N14"$extension
    preProgramOut=$name$i$outExtension
    nextProgramOut=$name$i"N14"$outExtension

    g++ -o $preProgramOut $preProgramName
    g++ -o $nextProgramOut $nextProgramName

    echo "--------->"$preProgramOut >> N7result.txt
    ./$preProgramOut >> N7result.txt

    echo "--------->"$nextProgramOut >> N14result.txt
    ./$nextProgramOut >> N14result.txt

    echo "loop"$i
    echo 

done
