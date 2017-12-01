#include <iostream>
#include <TROOT.h>
#include <TString.h>
#include <TStopwatch.h>
#include "FlowReconstructor/CFlowReconstructor.h"
#include "ManualFunctions.h"

using namespace std;

int RunFlowAnalysis (TString option = "all", TString histFileName = "", TString nonUniformInputFileName = "", TString uniformInputFileName = "") {
// options: "correlations", "flow", "all"
// histFileName: route to files with histograms without ".root"
// nonUniformInputFileName: route to file with data without ".root"
// nonUniformInputFileName: route to file with simulations without ".root"

//    nonUniformInputFileName = "/lustre/nyx/cbm/users/ogolosov/NA49_conv/3154_full_mh"; // NA49
//    histFileName = "/u/ogolosov/NA49_flow/3154"; // NA49
//    nonUniformInputFileName = "Converted/3154_full_mh"; // NA49
//    histFileName = "Flow/3154"; // NA49
	nonUniformInputFileName = "/lustre/nyx/hades/user/tmamont/gitDir/HADES/treeMaker/output/Nov_28_9_41/AuAu_1_23AGev_gen9_108.list/Converted/tree_12108160806_full_mh";
	histFileName = "/lustre/nyx/hades/user/tmamont/gitDir/HADES/treeMaker/output/Nov_28_9_41/AuAu_1_23AGev_gen9_108.list/Converted/12108160806_flow";

	CFlowReconstructor flowReconstructor;
	flowReconstructor.SetNonUniformInputFileName (nonUniformInputFileName);
//	flowReconstructor.SetUniformInputFileName (uniformInputFileName);
	flowReconstructor.SetHistFileName (histFileName);
	flowReconstructor.UseZeroSubevents (0); // do not touch
//	flowReconstructor.SetSamplingMethod (kBootStrapping);
	flowReconstructor.SetSamplingMethod (kSubsampling);
	flowReconstructor.PropagateResolutionSign ();
    flowReconstructor.SetNsteps (kTwistAndRescale);
//	flowReconstructor.SetComment (comment); // not implemented

	flowReconstructor.AddHarmonic (1);
	flowReconstructor.AddHarmonic (2);
//	flowReconstructor.SetVariable("eta");
	flowReconstructor.SetVariable("y");
	flowReconstructor.SetNbinsBS (100); // number of samples

//	flowReconstructor.SetReferenceOption (1, "x");
//	flowReconstructor.SetReferenceOption (2, "y");
//    flowReconstructor.SetHarmonicFunction (1, v1); // gen_const
//    flowReconstructor.SetHarmonicFunction (2, v2); // gen_const
//    flowReconstructor.SetMhRange (0, 1000); // gen
//    flowReconstructor.AddFlowParticle (kNID); // gen

	flowReconstructor.SetNrunRange (0, 3166);
	flowReconstructor.ExcludeRun (3141);
	flowReconstructor.ExcludeRun (3010);
	flowReconstructor.ExcludeRun (3030);
	flowReconstructor.ExcludeRun (3134);
	flowReconstructor.ExcludeRun (3159);
	flowReconstructor.ExcludeRun (3014);
	flowReconstructor.ExcludeRun (3161);

	flowReconstructor.SetMhRange (10, 200);
	flowReconstructor.SetNbinsMh (190);
	flowReconstructor.SetCentRange (10, 200);
	flowReconstructor.SetNbinsCent (190);
	flowReconstructor.SetCentRangeForFlow (10, 50);
	flowReconstructor.SetMhRangeForFlow (10, 50);

	flowReconstructor.SetPtRange (0.0, 2.5);
	flowReconstructor.SetNbinsPt (10);
	flowReconstructor.SetEtaRange (-0.5, 1.0);
	flowReconstructor.SetNbinsEta (6);
	flowReconstructor.SetNbinsEtaRefl (2);

<<<<<<< HEAD
//THREE SUBEVENT
=======
// THREE SUBEVENT
>>>>>>> 980278127e2a40ad30bf8be23de71301d1cdd2fb
	flowReconstructor.SetResolutionMethod (kThreeSubevents);
	flowReconstructor.SetPtSubeventsLimits (1, 0.1, 2.0, 0.1, 2.0, 0.1, 2.0);
	flowReconstructor.SetPtSubeventsLimits (2, 0.1, 2.0, 0.1, 2.0, 0.1, 2.0);
//	flowReconstructor.SetEtaSubeventsLimits (1, 1.0, 3.0, 1.0, 3.0, 1.0, 3.0);
//    flowReconstructor.SetEtaSubeventsLimits (2, -1.0, 1.0, -1.0, 1.0, -1.0, 0.0);
<<<<<<< HEAD
	flowReconstructor.SetEtaSubeventsLimits (1, -0.5, 0.25, 0.5, 1.0, 0.5, 3.0);
   flowReconstructor.SetEtaSubeventsLimits (2, -0.5, 0.25, 0.5, 1.0, 0.5, 3.0);
   flowReconstructor.AddResolutionParticle (1, 1, kProton);
   flowReconstructor.AddResolutionParticle (1, 2, kProton);
   flowReconstructor.AddResolutionParticle (1, 3, kFW);
   flowReconstructor.AddResolutionParticle (2, 1, kProton);
   flowReconstructor.AddResolutionParticle (2, 2, kProton);
   flowReconstructor.AddResolutionParticle (2, 3, kFW);

	flowReconstructor.AddFlowParticle (kProton);
=======
	flowReconstructor.SetEtaSubeventsLimits (1, 0.5, 3.0, 1.0, 3.0, 0.5, 3.0);
    flowReconstructor.SetEtaSubeventsLimits (2, -3.0, 0.0, 0.5, 1.2, 1.2, 3.0);
    flowReconstructor.AddResolutionParticle (1, 1, kProton);
    flowReconstructor.AddResolutionParticle (1, 2, kPionMinus);
    flowReconstructor.AddResolutionParticle (1, 3, kPionPlus);
    flowReconstructor.AddResolutionParticle (2, 1, kPionMinus);
    flowReconstructor.AddResolutionParticle (2, 1, kPionPlus);
    flowReconstructor.AddResolutionParticle (2, 1, kProton);
    flowReconstructor.AddResolutionParticle (2, 2, kPionMinus);
    flowReconstructor.AddResolutionParticle (2, 2, kPionPlus);
    flowReconstructor.AddResolutionParticle (2, 2, kProton);
    flowReconstructor.AddResolutionParticle (2, 3, kPionMinus);
    flowReconstructor.AddResolutionParticle (2, 3, kPionPlus);
    flowReconstructor.AddResolutionParticle (2, 3, kProton);

	flowReconstructor.AddFlowParticle (kPionMinus);
>>>>>>> 980278127e2a40ad30bf8be23de71301d1cdd2fb
	flowReconstructor.SetPtAveragingRange (1, 0.1, 3.0);
	flowReconstructor.SetPtAveragingRange (2, 0.1, 2.0);
	flowReconstructor.SetEtaAveragingRange (1, 0.0, 1.0);
	flowReconstructor.SetEtaAveragingRange (2, 0.0, 0.5);
<<<<<<< HEAD
   flowReconstructor.SetResolutionSigns(1, -1, -1, -1);
   flowReconstructor.SetResolutionSigns(2, 1, 1, 1);
//END THREE SUBEVENT
=======
    flowReconstructor.SetResolutionSigns(1, -1, -1, -1);
    flowReconstructor.SetResolutionSigns(2, 1, 1, 1);
// END THREE SUBEVENT
>>>>>>> 980278127e2a40ad30bf8be23de71301d1cdd2fb

// THREE SUBEVENT WITH VETO
//	flowReconstructor.SetResolutionMethod (kThreeSubevents);
//	flowReconstructor.SetPtSubeventsLimits (1, 0.1, 2.0, 0.1, 2.0, 0.0, 2.0);
//	flowReconstructor.SetPtSubeventsLimits (2, 0.1, 2.0, 0.1, 2.0, 0.0, 2.0);
//	flowReconstructor.SetEtaSubeventsLimits (1, -3.0, -0.2, 0.2, 3.0, -3.0, 3.0);
//    flowReconstructor.SetEtaSubeventsLimits (2, -3.0, 0.2, 0.2, 3.0, -3.0, 3.0);
//    flowReconstructor.AddResolutionParticle (1, 1, kPionMinus);
//    flowReconstructor.AddResolutionParticle (1, 1, kPionPlus);
//    flowReconstructor.AddResolutionParticle (1, 1, kProton);
//    flowReconstructor.AddResolutionParticle (1, 2, kPionMinus);
//    flowReconstructor.AddResolutionParticle (1, 2, kPionPlus);
//    flowReconstructor.AddResolutionParticle (1, 2, kProton);
//    flowReconstructor.AddResolutionParticle (1, 3, kVeto1);
//    flowReconstructor.AddResolutionParticle (1, 3, kVeto2);
//    flowReconstructor.AddResolutionParticle (1, 3, kVeto3);
//    flowReconstructor.AddResolutionParticle (1, 3, kVeto4);
//    flowReconstructor.AddResolutionParticle (2, 1, kPionMinus);
//    flowReconstructor.AddResolutionParticle (2, 1, kPionPlus);
//    flowReconstructor.AddResolutionParticle (2, 1, kProton);
//    flowReconstructor.AddResolutionParticle (2, 2, kPionMinus);
//    flowReconstructor.AddResolutionParticle (2, 2, kPionPlus);
//    flowReconstructor.AddResolutionParticle (2, 2, kProton);
//    flowReconstructor.AddResolutionParticle (2, 3, kVeto1);
//    flowReconstructor.AddResolutionParticle (2, 3, kVeto2);
//    flowReconstructor.AddResolutionParticle (2, 3, kVeto3);
//    flowReconstructor.AddResolutionParticle (2, 3, kVeto4);
//
//	flowReconstructor.AddFlowParticle (kPionMinus);
//	flowReconstructor.SetPtAveragingRange (1, 0.1, 3.0);
//	flowReconstructor.SetPtAveragingRange (2, 0.1, 2.0);
//	flowReconstructor.SetEtaAveragingRange (1, 0.0, 1.0);
//	flowReconstructor.SetEtaAveragingRange (2, 0.0, 0.5);
//    flowReconstructor.SetResolutionSigns(1, -1, -1, -1);
//    flowReconstructor.SetResolutionSigns(2, 1, 1, 1);
// END THREE SUBEVENT WITH VETO

// RANDOM SUBEVENT
<<<<<<< HEAD
	// flowReconstructor.SetResolutionMethod (kRandomSubevent);
	// flowReconstructor.SetPtSubeventsLimits (1, 0.0, 1.0, 0.0, 1.0);
	// flowReconstructor.SetPtSubeventsLimits (2, 0.0, 1.0, 0.0, 1.0);
	// flowReconstructor.SetEtaSubeventsLimits (1, 0.8, 2.8, 0.8, 2.8);
 //    flowReconstructor.SetEtaSubeventsLimits (2, -0.4, 1.8, -0.4, 1.8);
 //    flowReconstructor.AddResolutionParticle (1, 1, kPionMinus);
 //    flowReconstructor.AddResolutionParticle (1, 1, kPionPlus);
 //    flowReconstructor.AddResolutionParticle (1, 1, kProton);
 //    flowReconstructor.AddResolutionParticle (1, 2, kPionMinus);
 //    flowReconstructor.AddResolutionParticle (1, 2, kPionPlus);
 //    flowReconstructor.AddResolutionParticle (1, 2, kProton);
 //    flowReconstructor.AddResolutionParticle (2, 1, kPionMinus);
 //    flowReconstructor.AddResolutionParticle (2, 1, kPionPlus);
 //    flowReconstructor.AddResolutionParticle (2, 1, kProton);
 //    flowReconstructor.AddResolutionParticle (2, 2, kPionMinus);
 //    flowReconstructor.AddResolutionParticle (2, 2, kPionPlus);
 //    flowReconstructor.AddResolutionParticle (2, 2, kProton);

	// flowReconstructor.AddFlowParticle (kPionMinus);
	// flowReconstructor.SetPtAveragingRange (1, 0.0, 2.0);
	// flowReconstructor.SetPtAveragingRange (2, 0.0, 2.0);
	// flowReconstructor.SetEtaAveragingRange (1, 0.0, 1.8);
	// flowReconstructor.SetEtaAveragingRange (2, 0.0, 1.8);
 //    flowReconstructor.SetResolutionSigns(1, -1, -1, -1);
 //    flowReconstructor.SetResolutionSigns(2, 1, 1, 1);
=======
//	flowReconstructor.SetResolutionMethod (kRandomSubevent);
//	flowReconstructor.SetPtSubeventsLimits (1, 0.0, 1.0, 0.0, 1.0);
//	flowReconstructor.SetPtSubeventsLimits (2, 0.0, 1.0, 0.0, 1.0);
//	flowReconstructor.SetEtaSubeventsLimits (1, 0.8, 2.8, 0.8, 2.8);
//    flowReconstructor.SetEtaSubeventsLimits (2, -0.4, 1.8, -0.4, 1.8);
//    flowReconstructor.AddResolutionParticle (1, 1, kPionMinus);
//    flowReconstructor.AddResolutionParticle (1, 1, kPionPlus);
//    flowReconstructor.AddResolutionParticle (1, 1, kProton);
//    flowReconstructor.AddResolutionParticle (1, 2, kPionMinus);
//    flowReconstructor.AddResolutionParticle (1, 2, kPionPlus);
//    flowReconstructor.AddResolutionParticle (1, 2, kProton);
//    flowReconstructor.AddResolutionParticle (2, 1, kPionMinus);
//    flowReconstructor.AddResolutionParticle (2, 1, kPionPlus);
//    flowReconstructor.AddResolutionParticle (2, 1, kProton);
//    flowReconstructor.AddResolutionParticle (2, 2, kPionMinus);
//    flowReconstructor.AddResolutionParticle (2, 2, kPionPlus);
//    flowReconstructor.AddResolutionParticle (2, 2, kProton);
//
//	flowReconstructor.AddFlowParticle (kPionMinus);
//	flowReconstructor.SetPtAveragingRange (1, 0.0, 2.0);
//	flowReconstructor.SetPtAveragingRange (2, 0.0, 2.0);
//	flowReconstructor.SetEtaAveragingRange (1, 0.0, 1.8);
//	flowReconstructor.SetEtaAveragingRange (2, 0.0, 1.8);
//    flowReconstructor.SetResolutionSigns(1, -1, -1, -1);
//    flowReconstructor.SetResolutionSigns(2, 1, 1, 1);
>>>>>>> 980278127e2a40ad30bf8be23de71301d1cdd2fb
// END RANDOM SUBEVENT

    TStopwatch timer;
    timer.Reset();
    timer.Start();

    if (option == "analysis") {
        flowReconstructor.SetNbinsPt (10);
        flowReconstructor.SetNbinsEta (10);
        flowReconstructor.AnalyzeTree ();
    }
	if (option == "all" || option == "correlations") flowReconstructor.GetCorrelations ();
	if (option == "all" || option == "flow") flowReconstructor.GetFlow ();
//	if (option == "reference" || option == "all" || option == "flow") flowReconstructor.Reference (0.0, 2.5, 1.4, 5.0);

    timer.Stop();
    printf("Real time: %f\n",timer.RealTime());
    printf("CPU time: %f\n",timer.CpuTime());

    cout << "Tada!\n";
    return 0;
}

# ifndef __CINT__
int main (int argc, char *argv []) {
    RunFlowAnalysis ();
    return 0;
}
# endif
