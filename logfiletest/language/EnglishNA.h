#ifndef ENGLISH_NA_H
#define ENGLISH_NA_H

#include "Language.h"

#include "../lookups/CommandStringsNAEnglish.h"
#include "../lookups/SkillToClassHardCodedNA.h"

#include "../parser/ItemIDFileReader.h"

class EnglishNA: public Language{
public:
	EnglishNA(): itemIDFileReader("itemnames_ENU.txt"),
		languageCode("ENU(NA)")
	  {}
	MessageRules& getMessageRules() {return commandStrings;}
	SkillToClassMap& getSkillToClassMap() {return skillToClass;}
	ItemIDFileReader& getItemIDFileReader() {return itemIDFileReader;}
	string getLanguageCode() {return languageCode;}
private:
	string languageCode;
	ItemIDFileReader itemIDFileReader;
	CommandStringsNAEnglish commandStrings;
	SkillToClassHardCodedNA skillToClass;
};

#endif