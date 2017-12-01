#!/bin/bash

#Script to convert trees
user=$(whoami)   
currentDir=$(pwd)

jobscript=${currentDir}/convertTree.sh
input=${1}
outputdir=${1}/Converted

if [ ! -d $outputdir ]
then
   echo "===> CREATE OUTPUTDIR : $outputdir"
   mkdir -p $outputdir
else
   echo "===> USE OUTPUTDIR : $outputdir"
fi


ls $input/*.root>$outputdir/filelist.txt
filelist=$outputdir/filelist.txt
logdir=$outputdir/log
echo "$filelist is created"

env=/cvmfs/hades.gsi.de/install/5.34.34/hydra2-4.9u/defall.sh
#. ${env}
#root -l -b -q 'compileLib.C'


if [ "$#" -ne "2" ]
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
    maxNumberOfRuns=${2}
fi


if [ ! -d $logdir ]
then
   echo "===> CREATE LOGDIR : $logdir"
   mkdir -p $logdir
else
   echo "===> USE LOGDIR : $logdir"
fi

numberOfRuns=0 

for file in $(cat $filelist | sort | sed -r 's/.root//')
do
    runnumber=$(echo $file | sort| sed -r 's/.*\/tree_//'| sed -r 's/.root//')
    log_err=${logdir}/${runnumber}.err
    log_out=${logdir}/${runnumber}.out
    command="sbatch --error=${log_err} --output=${log_out} ${jobscript} ${env} ${file} ${outputdir}/tree_${runnumber}"
    echo " "
    echo "sbatch"
    echo "-error=${log_err} --output=${log_out}"
    echo "${jobscript} ${env} ${exe}"
    echo "${runnumber}"
    echo "${outputdir}/tree_${runnumber} -1"
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
