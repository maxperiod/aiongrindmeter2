//#include "ChatLogCommandStringsNAEnglish.h"
//#include "SkillToClassHardCodedNA.h"
//#include "../parser/MessageRules.h"
//#include "../parser/SkillToClassMap.h"
#ifndef LANGUAGE_MANAGER_H
#define LANGUAGE_MANAGER_H

#include "EnglishNA.h"

class LanguageManager{
public:
	enum LanguageID{ENGLISH_NA};
	
	LanguageManager(LanguageID language) {currentLanguage = language;}
	
	Language& getCurrentLanguage();
	

private:
	LanguageID currentLanguage;
	
	//RuleStringsHard
	EnglishNA englishNA;
};

extern LanguageManager LANGUAGE_MANAGER;

#endif