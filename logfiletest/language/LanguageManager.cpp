#include "LanguageManager.h"

LanguageManager LANGUAGE_MANAGER(LanguageManager::ENGLISH_NA);

Language& LanguageManager::getCurrentLanguage(){
	switch(currentLanguage){
	case ENGLISH_EU:
		return englishEU;
	default:
		return englishNA;
	}

}