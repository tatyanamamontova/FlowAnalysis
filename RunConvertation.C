#include <iostream>
#include <TStopwatch.h>
#include "TreeConverter/CTreeConverter.h"

void RunConvertation (TString inputFileName = "../Source", TString outputFileName = "../Converted") {
	clock_t begin = clock();
//	inputFileName = "/lustre/nyx/cbm/users/ogolosov/NA49_data/3154";
//	outputFileName = "/lustre/nyx/cbm/users/ogolosov/NA49_conv/3154";
//	inputFileName = "/lustre/nyx/hades/user/tmamont/gitDir/HADES/treeMaker/output/tree_1210823565";
//	outputFileName = "/lustre/nyx/hades/user/tmamont/gitDir/FlowAnalysis/Converted_0112/tree_1210823565";

    Int_t dEdxSource = 3;
    Int_t centMethod = 1;
	TString source, method;
	if (dEdxSource == 2) source = "MTPC";
	if (dEdxSource == 3) source = "full";
	if (centMethod == 1) method = "mh";
	if (centMethod == 2) method = "E";

	CTreeConverter treeConverter;
	treeConverter.SetInputFileName (inputFileName);
	treeConverter.SetOutputFileName (outputFileName);// + "_" + source + "_" + method);
	treeConverter.SetInputTreeName ("tree");
	treeConverter.SetdEdxSource (dEdxSource);
	treeConverter.SetCentralityMethod (centMethod);  // 1 - multiplicity, 2 - Eveto

	treeConverter.SetSNN (1.23); // GeV
	treeConverter.SetNbinsMh (10);
	treeConverter.SetMhRange (10, 200);
	treeConverter.SetNbinsCent (10);
	treeConverter.SetCentRange (0, 50);


    TStopwatch timer;
    timer.Reset();
    timer.Start();

	treeConverter.ConvertTree ();

    timer.Stop();
    printf("/nReal time: %f\n",timer.RealTime());
    printf("CPU time: %f\n",timer.CpuTime());
    printf("\nConverted!\n");
}

# ifndef __CINT__
int main (int argc, char *argv []) {
    RunConvertation ();
    return 0;
}
# endif
