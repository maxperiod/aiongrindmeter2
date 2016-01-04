#ifndef ENGLISH_NA_H
#define ENGLISH_NA_H

#include "Language.h"

#include "../lookups/CommandStringsNAEnglish.h"
#include "../lookups/SkillToClassHardCodedNA.h"

class EnglishNA: public Language{
public:
	MessageRules& getMessageRules() {return commandStrings;}
	SkillToClassMap& getSkillToClassMap() {return skillToClass;}
private:
	CommandStringsNAEnglish commandStrings;
	SkillToClassHardCodedNA skillToClass;
};

#endif