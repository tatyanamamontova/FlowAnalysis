#!/bin/bash
#SBATCH -J convertTree
#SBATCH --time=1:00:00
#SBATCH -D /lustre/nyx/hades/user/tmamont/gitDir/FlowAnalysis


if [ $# -lt 1 ]
then
        echo "Usage : jobScript.sh par1 par2 par3"
        sleep 3
        exit
fi

echo "==> running enironment script ${par1}"
. $1

echo "==> root"
root.exe -b -l -q 'RunFlowAnalysis.C("correlations","'$2'","'$3'")'
status=$?

if [ $status -ne 0 ]
then
    echo "JOB: $JOB_ID CRASHED ON HOST: $host WITH OUTFILE $outfile_wo_path"
fi

format='+%Y/%m/%d-%H:%M:%S'

echo ""               
echo "--------------------------------"
echo "Job with params "
echo "par1 = ${1}"  
echo "par2 = ${2}"  
echo "par3 = ${3}"   
echo "finished!"      
echo "--------------------------------"
echo ""
date $format


sleep 2 
