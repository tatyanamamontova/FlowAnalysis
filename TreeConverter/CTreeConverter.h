#ifndef CTREECONVERTER_H
#define CTREECONVERTER_H

#include <TString.h>
#include <TFile.h>
#include <TTree.h>
#include "../MyDataTree/CEvent.h"
#include "../defines.h"
#include "../ManualFunctions.h"

class CTreeConverter {

public:
	CTreeConverter ();
	CTreeConverter (TString inputFileName, TString outputFileName, TString inputTreeName);
	void SetInputFileName (TString inputFileName = "../Source.root");
	void SetOutputFileName (TString outputFileName = "../Converted.root");
	void SetInputTreeName (TString inputTreeName);
	void SetMhRange (Int_t mhMin, Int_t mhMax);
	void SetNbinsMh (Int_t nBinsMh);
	void SetCentRange (Float_t centMin, Float_t centMax);
	void SetNbinsCent (Int_t nBinsCent);
	void SetdEdxSource (Int_t TPCid = 3);
	void SetCentralityMethod (Int_t centMethod = 1); // 1 - multiplicity, 2 - Eveto
    void SetSNN (Float_t sNN);
	Bool_t ConvertTree ();

private:
	TFile* inputFile_;
	TFile* outputFile_;
	TTree* inputTree_;
	TTree* outputTree_;
	TString inputFileName_;
	TString outputFileName_;
	TString inputTreeName_;
	Bool_t initFlag_;
	Int_t nBinsMh_, nBinsCent_;
	Int_t mhMin_, mhMax_;
	Float_t centMin_, centMax_;
	Int_t dEdxSource_;
    Int_t centMethod_;
    Float_t sNN_;


	static const Int_t mhMax = 5000;
   const Short_t nCuts = 8;
   const Short_t nTrigger = 4;
   const Short_t maxNWallHits = 200;
   const Short_t maxNTracks = 200; 

	// Declaration of leaf types
   Int_t nRpcClustCut;                      //number of RPC hits with time cut
   Int_t nTofHitsCut;                       //number of TOF hits with time cut
   Bool_t          trigInd[nTrigger];
   Short_t         runId;
   Short_t         nWallHitsTot;
   Bool_t          cuts[nCuts];
   Short_t         wallModuleIndex[maxNWallHits];
   Short_t         wallHitTime[maxNWallHits];
   Short_t         wallHitCharge[maxNWallHits];
   Short_t         wallHitDistance[maxNWallHits];
   Short_t         wallHitRing[maxNWallHits];
   Short_t         wallHitPhi[maxNWallHits];
   Short_t         isWallHitOk[maxNWallHits];
   Short_t         nTracks;
   Float_t         vZ;
   Short_t         pid[maxNTracks];   
   Float_t         phi[maxNTracks];   
   Float_t         theta[maxNTracks];   
   Float_t         pt[maxNTracks];   
   Float_t         rapidity[maxNTracks];
   Float_t         eta[maxNTracks];  
   Float_t         beta[maxNTracks];   
   Float_t         mass[maxNTracks];   
   Short_t         charge[maxNTracks];   
   Float_t         rToBeam[maxNTracks];   
   Float_t         zToBeam[maxNTracks];   
   Float_t         pt_corr[maxNTracks];   
   Float_t         p[maxNTracks];

   // List of branches
   TBranch        *b_nRpcClustCut;   
   TBranch        *b_nTofHitsCut;   
   TBranch        *b_trigInd;   
   TBranch        *b_runId;   
   TBranch        *b_cuts; 
   TBranch        *b_nWallHitsTot;  
   TBranch        *b_wallModuleIndex;   
   TBranch        *b_wallHitTime;   
   TBranch        *b_wallHitCharge;   
   TBranch        *b_wallHitDistance;  
   TBranch        *b_wallHitRing;   
   TBranch        *b_wallHitPhi;   
   TBranch        *b_isWallHitOk;   
   TBranch        *b_nTracks;   
   TBranch        *b_vZ;   
   TBranch        *b_pid;   
   TBranch        *b_phi;   
   TBranch        *b_theta;  
   TBranch        *b_pt;   
   TBranch        *b_rapidity;  
   TBranch        *b_beta;   
   TBranch        *b_mass;   
   TBranch        *b_charge;   
   TBranch        *b_rToBeam;   
   TBranch        *b_zToBeam;   
   TBranch        *b_pt_corr;
   TBranch        *b_p;  
   TBranch        *b_eta; 

	Bool_t SetInputFile ();
	Bool_t SetOutputFile ();
	Bool_t SetInputTree ();
	Bool_t Init ();
	Bool_t CheckEventCuts ();
   Float_t GetCentralityClass (Int_t mh);
	Float_t GetCentralityClass (Float_t Eveto);
	Bool_t CheckTrackCuts (Int_t itrack);
	Int_t GetTrackPid (Int_t itrack);
	Float_t GetRapidity (Float_t pt, Float_t eta, Int_t pid);
	void Finish ();

};

#endif // CTREECONVERTER_H
