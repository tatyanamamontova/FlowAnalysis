#ifndef MANUALFUNCTIONS_H
#define MANUALFUNCTIONS_H

#include <map>
#include <TString.h>
#include <TRandom3.h>
#include <TMath.h>
#include <TF1.h>
#include "./MyDataTree/CTrack.h"
#include "defines.h"

using namespace std;

Float_t GetCentralityClass (Int_t mh) {
	static const Int_t nCentClasses = 8;
 Float_t centClassLimits [nCentClasses+1] = {250, 182, 160, 140, 121, 104, 88,
                                           74, 60};
 Float_t centClassWidth = 0.05;
	if (mh >= centClassLimits [0]) return centClassWidth * 0.5;
	for (Int_t i = 0; i < nCentClasses + 1; i++) {
    if (mh < centClassLimits [i] && mh >= centClassLimits [i+1]) return centClassWidth * (i + 0.5);}
	return -1.0;
}

void GetPsi (map <TString, Float_t> &variables) {
	Float_t psi = gRandom -> Rndm () * 2 * PI;
	for (int i = 0; i < variables ["nHarmonics"]; i++) {
		variables [Form ("psi_%i", i + 1)] = psi;
	}
}

void GetEventVariables (map <TString, Float_t> &variables) {
	const Int_t mhMin = 100, mhMax = 1000;
	variables ["mh"] = static_cast <int> (mhMin + gRandom -> Rndm () * (mhMax - mhMin));
	variables ["cent"] = GetCentralityClass (variables ["mh"]);
}

//TF1 *fPt = new TF1("fPt","TMath::Landau(x,[0],[1], 1)", 0.0, 2.5);
//fPt -> SetParameters (0.181458, 0.0662424);
//TF1 *fEta = new TF1("fEta","TMath::Landau(x,[0],[1], 1)", 1.4, 5.0);
//fEta -> SetParameters (2.55742, 0.523259);
void GetTrackVariables (map <TString, Float_t> &variables) {
	const Float_t ptMin = 0.0, ptMax = 2.5, etaMin = 1.4, etaMax = 5.0;
	Float_t pt, eta;
	Bool_t flag = 0;
	variables ["ptMin"] = ptMin;
	variables ["ptMax"] = ptMax;
	variables ["etaMin"] = etaMin;
	variables ["etaMax"] = etaMax;
	variables ["pid"] = kNID;
	if (gRandom -> Rndm () > 0.5) variables ["charge"] = 1;
	else variables ["charge"] = -1;

	while (!flag){
        pt = ptMin + gRandom -> Rndm () * (ptMax - ptMin);
        eta = etaMin + gRandom -> Rndm () * (etaMax - etaMin);
        if (TMath::Landau(pt, 0.181458, 0.0662424, 1) > 2.7 * gRandom -> Rndm () &&
            TMath::Landau(eta, 2.55742, 0.523259, 1) > 0.345 * gRandom -> Rndm ()) {
            variables ["pt"] = pt;
            variables ["eta"] = eta;
            flag = 1;
        }
	}
}

Float_t v1 (map <TString, Float_t> &variables) {
	return 0.05;
}

Float_t v2 (map <TString, Float_t> &variables) {
	return -0.05;
}

Float_t v1_new (map <TString, Float_t> &variables) {
	Float_t ptMax = variables ["ptMax"];
	Float_t etaMax = variables ["etaMax"];
	ptMax = 2.5;
	etaMax = 5.0;
	Float_t pt = variables ["pt"];
	Float_t eta = variables ["eta"];
	return 0.1 * (TMath::Power((pt / ptMax), .5) * eta / etaMax);
}

Float_t v2_new (map <TString, Float_t> &variables) {
	Float_t ptMax = variables ["ptMax"];
	Float_t etaMax = variables ["etaMax"];
	ptMax = 2.5;
	etaMax = 5.0;
	Float_t pt = variables ["pt"];
	Float_t eta = variables ["eta"];
	return 0.15 * (TMath::Power((pt / ptMax), .5) * eta / etaMax * eta / etaMax);
}

bool AcceptanceFunction1 (CTrack track) {
	return 1;
}

bool AcceptanceFunction2 (CTrack track) {
	Float_t phi = track.GetPhi ();
	if (phi < PI / 6 || phi > 11 * PI / 6)
		return 0;
	else
		return 1;
}

bool AcceptanceFunction3 (CTrack track) {
	Float_t phi = track.GetPhi ();
	if (phi < PI / 3)
		return 0;
	else
		return 1;
}

TF1 *acc  = new TF1 ("acc", "[0] + [1] * cos (x) + [2] * sin (x) + [3] * cos (2 * x) + [4] * sin (2 * x)  + [5] * cos (3 * x)  + [6] * sin (3 * x) + [7] * cos (4 * x) + [8] * sin (4 * x) + [9] * cos (5 * x) + [10] * sin (5 * x) + [11] * cos (6 * x) + [12] * sin (6 * x)", 0.0, 2 * TMath::Pi ());
Double_t fitParameters [13] = {3.09408e+005, -2.52226e+004, -5.11112e+004, 1.89563e+005, 1.83880e+003, 6.85814e+003, -1.16689e+004, -2.71939e+004, -2.57636e+003, 4.59591e+001, 1.41835e+004, -2.00475e+004, 1.44837e+003};
Float_t norm;
bool AcceptanceFunction4 (CTrack track) {
    //acc -> SetParameters (fitParameters);
    //norm =  2 * PI * fitParameters [0];
	Float_t phi = track.GetPhi ();
	if (norm * gRandom -> Rndm () > acc -> Eval (phi))
		return 0;
	else
		return 1;
}

#endif //MANUALFUNCTIONS_H
