#ifndef CTREECONVERTER_CXX
#define CTREECONVERTER_CXX

#include <iostream>
#include <TMath.h>
#include <TH1F.h> // QA
#include <TH2F.h> // QA
#include <TProfile.h> // QA
#include <THStack.h> // QA
#include <TCanvas.h> // QA
#include <TLegend.h> // QA
#include <TStyle.h> // QA
#include "CTreeConverter.h"

using namespace std;

CTreeConverter::CTreeConverter () {
	initFlag_ = 0;
}


CTreeConverter::CTreeConverter (TString inputFileName, TString outputFileName, TString inputTreeName) {
	initFlag_ = 0;
	SetInputFileName (inputFileName);
	SetOutputFileName (outputFileName);
	SetInputTreeName (inputTreeName);
	SetdEdxSource ();
	SetdEdxSource ();
}

void CTreeConverter::SetInputFileName (TString inputFileName) {
    inputFileName_ = inputFileName;
}

void CTreeConverter::SetOutputFileName (TString outputFileName) {
    outputFileName_ = outputFileName;
}

void CTreeConverter::SetInputTreeName (TString inputTreeName) {
    inputTreeName_ = inputTreeName;
}

Bool_t CTreeConverter::SetInputFile () {
	//if (inputFile_) delete inputFile_;
	inputFile_ = new TFile (inputFileName_ + ".root", "READ");
	if (!inputFile_) {
		cout << "Input file '" << inputFileName_ << "' not found!!!\n";
		return 0;
	}
	return 1;
}


Bool_t CTreeConverter::SetOutputFile () {
	//if (outputFile_) delete outputFile_;
	outputFile_ = new TFile (outputFileName_ + ".root", "RECREATE");
	if (!outputFile_) {
		cout << "Output file '" << outputFileName_ << "' not accessible!!!\n";
		return 0;
	}
	return 1;
}


Bool_t CTreeConverter::SetInputTree () {
	//if (inputTree_) delete inputTree_;
	inputTree_ = (TTree*) inputFile_ -> Get (inputTreeName_);
	if (!inputTree_) {
		cout << "Input tree '" << inputTreeName_ << "' not found!!!\n";
		return 0;
	}
	return 1;
}

void CTreeConverter::SetMhRange (Int_t mhMin, Int_t mhMax) {
    mhMin_ = mhMin;
    mhMax_ = mhMax;
}

void CTreeConverter::SetCentRange (Float_t centMin, Float_t centMax) {
    centMin_ = centMin;
    centMax_ = centMax;
}

void CTreeConverter::SetNbinsMh (Int_t nBinsMh) {
	nBinsMh_ = nBinsMh;
}

void CTreeConverter::SetNbinsCent (Int_t nBinsCent) {
	nBinsCent_ = nBinsCent;
}

void CTreeConverter::SetdEdxSource (Int_t TPCid) {
    dEdxSource_ = TPCid;
}

void CTreeConverter::SetCentralityMethod (Int_t centMethod) {
    centMethod_ = centMethod;
}

Bool_t CTreeConverter::Init (){
	if (!SetInputFile ()) return 0;
	if (!SetOutputFile ()) return 0;
	if (!SetInputTree ()) return 0;

   inputTree_->SetBranchAddress("nRpcClustCut", &nRpcClustCut, &b_nRpcClustCut);
   inputTree_->SetBranchAddress("nTofHitsCut", &nTofHitsCut, &b_nTofHitsCut);
   inputTree_->SetBranchAddress("trigInd", trigInd, &b_trigInd);
   inputTree_->SetBranchAddress("runId", &runId, &b_runId);
   inputTree_->SetBranchAddress("nWallHitsTot", &nWallHitsTot, &b_nWallHitsTot)
   inputTree_->SetBranchAddress("cuts", cuts, &b_cuts);
   inputTree_->SetBranchAddress("wallModuleIndex", wallModuleIndex, &b_wallModuleIndex);
   inputTree_->SetBranchAddress("wallHitTime", wallHitTime, &b_wallHitTime);
   inputTree_->SetBranchAddress("wallHitCharge", wallHitCharge, &b_wallHitCharge);
   inputTree_->SetBranchAddress("wallHitDistance", wallHitDistance, &b_wallHitDistance);
   inputTree_->SetBranchAddress("wallHitRing", wallHitRing, &b_wallHitRing);
   inputTree_->SetBranchAddress("wallHitPhi", wallHitPhi, &b_wallHitPhi);
   inputTree_->SetBranchAddress("isWallHitOk", isWallHitOk, &b_isWallHitOk);
   inputTree_->SetBranchAddress("nTracks", &nTracks, &b_nTracks);
   inputTree_->SetBranchAddress("vZ", &vZ, &b_vZ);
   inputTree_->SetBranchAddress("pid", pid, &b_pid);
   inputTree_->SetBranchAddress("p", p, &b_p);
   inputTree_->SetBranchAddress("phi", phi, &b_phi);
   inputTree_->SetBranchAddress("theta", theta, &b_theta);
   inputTree_->SetBranchAddress("eta", eta, &b_eta);
   inputTree_->SetBranchAddress("pt", pt, &b_pt);
   inputTree_->SetBranchAddress("rapidity", rapidity, &b_rapidity);
   inputTree_->SetBranchAddress("beta", beta, &b_beta);
   inputTree_->SetBranchAddress("mass", mass, &b_mass);
   inputTree_->SetBranchAddress("charge", charge, &b_charge);
   inputTree_->SetBranchAddress("rToBeam", rToBeam, &b_rToBeam);
   inputTree_->SetBranchAddress("zToBeam", zToBeam, &b_zToBeam);
   inputTree_->SetBranchAddress("pt_corr", pt_corr, &b_pt_corr);

	return 1;
}


Bool_t CTreeConverter::CheckEventCuts () {
    for (Int_t i = 0; i < nCuts; i++){
      if (!cuts[i]) return 0;
    }
    return 1;
}

Float_t CTreeConverter::GetCentralityClass (Int_t mh) {
 static const Int_t nCentClasses = 8;
 Float_t centClassLimits [nCentClasses+1] = {250, 182, 160, 140, 121, 104, 88,
                                           74, 60}
 Float_t centClassWidth = 0.05;
	if (mh >= centClassLimits [0]) return centClassWidth * 0.5;
	for (Int_t i = 0; i < nCentClasses + 1; i++) {
    if (mh < centClassLimits [i] && mh >= centClassLimits [i+1]) return centClassWidth * ((i + 0.5);}
	  if (mh < centClassLimits [nCentClasses + 1]) return 0.4;
	return -1.0;
}

Float_t CTreeConverter::GetCentralityClass (Float_t Eveto) {
 //    Float_t Ebeam = 8.32e3;
 //    Float_t r = Eveto / Ebeam;
 //    static const Int_t nCentClasses = 6;
	// Float_t centClassLimits [nCentClasses - 1] = {0.169, 0.314, 0.509, 0.66, 0.778};
 //    Float_t centClassWidth = 100.0 / (Float_t) nCentClasses;
	// if (r <= centClassLimits [0]) return centClassWidth * 0.5;
	// for (Int_t i = 1; i < nCentClasses - 1; i++) {
 //        if (r > centClassLimits [i - 1] && r <= centClassLimits [i]) return centClassWidth * (i + 0.5);
	// }
	// if (r > centClassLimits [nCentClasses - 2]) return 100.0 - centClassWidth * 0.5;
	// return -1.0;
}

void CTreeConverter::SetSNN (Float_t sNN) {
    sNN_ = sNN;
}

Float_t CTreeConverter::GetRapidity (Float_t pt, Float_t eta, Int_t pid) {
 //    Float_t mProton = 938.2720814;
 //    Float_t m = particleMass [pid];
 //    if (pid == 0) return -999.0;
 //    Float_t yBeam = TMath::Log (sNN_ * 1.0e3 / mProton);
 //    Float_t a = TMath::Sqrt (pt * pt * 1.0e6 * TMath::CosH(eta) * TMath::CosH(eta) + m * m);
 //    Float_t b = pt * 1.0e3 * TMath::SinH (eta);
	// return 0.5 * TMath::Log ((a + b) / (a - b)) - yBeam;
}

Bool_t CTreeConverter::CheckTrackCuts (Int_t itrack) {
  //Kardan's cuts for tracks
    if ( pid[itrack]==14 && pt_corr[itrack]>250 && pt_corr[itrack]<1700 &&
                 TMath::Abs(zToBeam[itrack]-vZ)<15. && TMath::Abs(rToBeam[itrack])<15. &&
                 beta[itrack]<1 && mass[itrack]>600 && mass[itrack]<1200) return 1;
    return 0;
}


Int_t CTreeConverter::GetTrackPid (Int_t itrack) {
    if (pid[itrack] == 14) return kProton;
    if (pid[itrack] == 8) return kPionPlus;
    if (pid[itrack] == 9) return kPionMinus;
    return kNID;
}

Bool_t CTreeConverter::ConvertTree () {
	if (!Init ()) return 0;
	CEvent* event_ = new CEvent;
	outputTree_ = new TTree ("Tree", "Converted tree");
	outputTree_ -> Branch ("Event", &event_, 128000, 4);
	outputFile_ -> cd();


	Int_t trackIndex, nRun, mh, mh_cut, pid_;
	Float_t cent;

    cout << "Converting Tree: " << inputFileName_ << endl;
	Long64_t nentries = inputTree_ -> GetEntries ();
	for (Long64_t jentry = 0; jentry < nentries; jentry++) {
		cout << "\rEvent " << jentry + 1 << " from " << nentries;
		inputTree_ -> GetEntry (jentry);
		if (!CheckEventCuts ()) continue;
		mh = nTracks;
		mh_cut = 0;

		for (Int_t itrack = 0; itrack < mh; itrack++) {
		    if (!CheckTrackCuts (itrack)) continue;
            mh_cut++;
		}

		if (mh_cut < 10) continue;

    //centrality classes - ToF+RPC
		if (centMethod_ == 1) cent = GetCentralityClass (nRpcClustCut[jentry]+nTofHitsCut[jentry]);
		if (centMethod_ == 2) cent = GetCentralityClass (fEveto);
		if (cent < centMin_ || cent > centMax_) continue;
		trackIndex = 0;

    //!still dont have run number
		nRun = 0;

		event_ -> SetNrun (nRun);
		event_ -> SetCent (cent);
		//event_ -> SetEvetoFull (fEveto);
		//event_ -> SetEveto (fVeto_fAdcHadron);

		for (Int_t itrack = 0; itrack < mh; itrack++) {
		    if (!CheckTrackCuts (itrack)) continue;
		    trackIndex++;
		    if (phi[itrack] > PI) phi[itrack] -= 2 * PI;
		    pid_ = GetTrackPid (itrack);

        event_ -> AddTrack (pt[itrack], eta[itrack], phi[itrack], charge[itrack], pid_);
        event_ -> GetTrack (trackIndex) -> SetP (p[itrack]);
        event_ -> GetTrack (trackIndex) -> SetRap (rapidity[itrack]);
      }
	   //END track loop;

    for (Int_t j = 0; j < nWallHitsTot; j++){
      trackIndex++;
      event_ -> AddTrack (wallHitTime[j], wallHitRing[j], wallHitPhi[j], wallHitCharge[j], kFW);
      event_ -> GetTrack(trackIndex) ->SetRap(wallHitDistance[j]);
    }
      //END FW hits loop


		outputTree_ -> Fill ();
		event_ -> Clear ();
	}
	Finish ();
	return 1;
}


void CTreeConverter::Finish () {
	outputFile_ -> Write ();
	outputFile_ -> Close ();
}

#endif // CTREECONVERTER_CXX
