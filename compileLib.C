#include <TSystem.h>
#include <TROOT.h>
#include <Riostream.h>

using std::cout;
using std::endl;
void compileLib(){
	TString location = "/lustre/nyx/hades/user/tmamont/gitDir/FlowAnalysis";
	location += "/";
	std::cout << location << std::endl;
	TString debugString="+g";

	gROOT -> LoadMacro (location + "RunConvertation.C" + debugString);
}