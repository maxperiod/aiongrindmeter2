//#include "ChatLogCommandStringsNAEnglish.h"
//#include "SkillToClassHardCodedNA.h"
//#include "../parser/MessageRules.h"
//#include "../parser/SkillToClassMap.h"
#ifndef LANGUAGE_MANAGER_H
#define LANGUAGE_MANAGER_H

#include "EnglishNA.h"
#include "EnglishEU.h"

class LanguageManager{
public:
	enum LanguageID{ENGLISH_NA, ENGLISH_EU};
	
	LanguageManager(LanguageID language) {currentLanguage = language;}
	
	Language& getCurrentLanguage();
	
	void setToEnglishEU() {currentLanguage = ENGLISH_EU;}

private:
	LanguageID currentLanguage;
	
	//RuleStringsHard
	EnglishNA englishNA;
	EnglishEU englishEU;
};

extern LanguageManager LANGUAGE_MANAGER;

#endif