#!/bin/bash

#Script to convert trees
user=$(whoami)   
currentDir=$(pwd)

jobScript=${currentDir}/convertTree.sh
input=${1}
output=${2}

ls $input/*.root>$OUTPUT/filelist.txt
filelist=$OUTPUT/filelist.txt
logdir=$output/log
echo "$filelist is created"

env = ${currentDir}/env.sh


if [ "$#" -ne "3" ]
then
    echo "All runs from $filelist will be submitted in "
    echo "3..."
    sleep 1
    echo "2..."
    sleep 1
    echo "1..."
    sleep 1
    maxNumberOfRuns=100000
else
    maxNumberOfRuns=${3}
fi

if [ ! -d $outputdir ]
then
   echo "===> CREATE OUTPUTDIR : $output"
   mkdir -p $output
else
   echo "===> USE OUTPUTDIR : $output"
fi

if [ ! -d $logdir ]
then
   echo "===> CREATE LOGDIR : $logdir"
   mkdir -p $logdir
else
   echo "===> USE LOGDIR : $logdir"
fi

numberOfRuns=0 

for file in $(cat $filelist | sort)
do
    runnumber=$(echo $file | sort| sed -r 's/.*\/tree_//'| sed -r 's/.root//')
    log_err=${logdir}/${runnumber}.err
    log_out=${logdir}/${runnumber}.out
    command="sbatch --error=${log_err} --output=${log_out} ${jobscript} ${env} ${file} ${outputdir}/tree_${runnumber}.root"
    echo " "
    echo "sbatch"
    echo "-error=${log_err} --output=${log_out}"
    echo "${jobscript} ${env} ${exe}"
    echo "${runnumber}"
    echo "${outputdir}/tree_${runnumber}.root -1"
    $command
    ((numberOfRuns+=1))
    if [ ${numberOfRuns} -eq ${maxNumberOfRuns} ]
    then
        echo " "
        echo "${numberOfRuns} jobs have been submitted"
        exit 0
    fi
    runlist=${file}
done
