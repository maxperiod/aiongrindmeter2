#include "PlayerClassManager.h"
#include "../language/LanguageManager.h"
#include "../lookups/MessageRuleEnums.h"

bool PlayerClassManager::isSuperClass(const string& twoLetterClassCode){
	if (twoLetterClassCode == "WA") return true;
	if (twoLetterClassCode == "SC") return true;
	if (twoLetterClassCode == "MA") return true;
	if (twoLetterClassCode == "CL") return true;
	if (twoLetterClassCode == "EN") return true;
	if (twoLetterClassCode == "AR") return true;
	else return false;
}

const string& PlayerClassManager::getClassName(const string& twoLetterClassCode){
	MessageRules& commandRules = LANGUAGE_MANAGER.getCurrentLanguage().getMessageRules();

	if (twoLetterClassCode == "WA") return commandRules.getRule(STR_CLASS_NAME_WARRIOR);
	if (twoLetterClassCode == "FI") return commandRules.getRule(STR_CLASS_NAME_FIGHTER);
	if (twoLetterClassCode == "KN") return commandRules.getRule(STR_CLASS_NAME_KNIGHT);
		
	if (twoLetterClassCode == "SC") return commandRules.getRule(STR_CLASS_NAME_SCOUT);
	if (twoLetterClassCode == "AS") return commandRules.getRule(STR_CLASS_NAME_ASSASSIN);
	if (twoLetterClassCode == "RA") return commandRules.getRule(STR_CLASS_NAME_RANGER);
		
	if (twoLetterClassCode == "MA") return commandRules.getRule(STR_CLASS_NAME_MAGE);
	if (twoLetterClassCode == "WI") return commandRules.getRule(STR_CLASS_NAME_WIZARD);
	if (twoLetterClassCode == "EL") return commandRules.getRule(STR_CLASS_NAME_ELEMENTALIST);
		
	if (twoLetterClassCode == "CL") return commandRules.getRule(STR_CLASS_NAME_CLERIC);
	if (twoLetterClassCode == "PR") return commandRules.getRule(STR_CLASS_NAME_PRIEST);
	if (twoLetterClassCode == "CH") return commandRules.getRule(STR_CLASS_NAME_CHANTER);
		
	if (twoLetterClassCode == "EN") return commandRules.getRule(STR_CLASS_NAME_ENGINEER);
	if (twoLetterClassCode == "RI") return commandRules.getRule(STR_CLASS_NAME_RIDER);
	if (twoLetterClassCode == "GU") return commandRules.getRule(STR_CLASS_NAME_GUNNER);
		
	if (twoLetterClassCode == "AR") return commandRules.getRule(STR_CLASS_NAME_ARTIST);
	if (twoLetterClassCode == "BA") return commandRules.getRule(STR_CLASS_NAME_BARD);
		

	return commandRules.getRule(STR_UNKNOWN);
}