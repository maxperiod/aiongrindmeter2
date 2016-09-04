#ifndef ENGLISH_NA_H
#define ENGLISH_NA_H

#include "Language.h"

#include "../lookups/CommandStringsNAEnglish.h"
#include "../lookups/SkillToClassHardCodedNA.h"

#include "../parser/ItemIDFileReader.h"

class EnglishNA: public Language{
public:
	EnglishNA(): itemIDFileReader("itemnames_NA_ENU.txt"){}
	MessageRules& getMessageRules() {return commandStrings;}
	SkillToClassMap& getSkillToClassMap() {return skillToClass;}
	ItemIDFileReader& getItemIDFileReader() {return itemIDFileReader;}
private:
	ItemIDFileReader itemIDFileReader;
	CommandStringsNAEnglish commandStrings;
	SkillToClassHardCodedNA skillToClass;
};

#endif