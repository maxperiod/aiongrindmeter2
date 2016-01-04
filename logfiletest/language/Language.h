#ifndef LANGUAGE_H
#define LANGUAGE_H

#include "../lookups/MessageRuleEnums.h"
#include "../parser/MessageRules.h"
#include "../parser/SkillToClassMap.h"

class Language{
public:
	virtual MessageRules& getMessageRules() = 0;
	virtual SkillToClassMap& getSkillToClassMap() = 0;
};
#endif