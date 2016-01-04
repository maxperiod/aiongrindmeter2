#include "LanguageManager.h"

LanguageManager LANGUAGE_MANAGER(LanguageManager::ENGLISH_NA);

Language& LanguageManager::getCurrentLanguage(){
	switch(currentLanguage){
	default:
		return englishNA;
	}

}