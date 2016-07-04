#ifndef ENGLISH_EU_H
#define ENGLISH_EU_H

#include "Language.h"

#include "../lookups/CommandStringsEUEnglish.h"
#include "../lookups/SkillToClassHardCodedEUEnglish.h"

class EnglishEU: public Language{
public:
	MessageRules& getMessageRules() {return commandStrings;}
	SkillToClassMap& getSkillToClassMap() {return skillToClass;}
private:
	CommandStringsEUEnglish commandStrings;
	SkillToClassHardCodedEUEnglish skillToClass;
};

#endif