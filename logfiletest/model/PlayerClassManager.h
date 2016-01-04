#ifndef PLAYER_CLASS_MANAGER
#define PLAYER_CLASS_MANAGER

#include <string>
using namespace std;
//#include "../parser/RuleStrings.h"

namespace PlayerClassManager{
	const string MULTI_CLASS_SKILL = "multi";
	const string PC_AND_NPC_SKILL = "pcnpc";
	//const string UNKNOWN = "Unknown";	
	bool isSuperClass(const string& twoLetterClassCode);

	const string& getClassName(const string& twoLetterClassCode);
};

#endif