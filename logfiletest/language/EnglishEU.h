#ifndef ENGLISH_EU_H
#define ENGLISH_EU_H

#include "Language.h"

#include "../lookups/CommandStringsEUEnglish.h"
#include "../lookups/SkillToClassHardCodedEUEnglish.h"

class EnglishEU: public Language{
public:
	EnglishEU(): 
		itemIDFileReader("itemnames_ENG.txt"),
		languageCode("ENG(EU)")
		{}
	MessageRules& getMessageRules() {return commandStrings;}
	SkillToClassMap& getSkillToClassMap() {return skillToClass;}
	ItemIDFileReader& getItemIDFileReader() {return itemIDFileReader;}
	string getLanguageCode() {return languageCode;}
private:
	string languageCode;
	ItemIDFileReader itemIDFileReader;
	CommandStringsEUEnglish commandStrings;
	SkillToClassHardCodedEUEnglish skillToClass;
};

#endif