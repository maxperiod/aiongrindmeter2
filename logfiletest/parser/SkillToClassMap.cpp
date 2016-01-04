#include "SkillToClassMap.h"

SkillToClassMap* CLASS_SKILLS;

const string& SkillToClassMap::getClass(const string& skill){
	if (skillToClass.count(skill) != 0) return skillToClass[skill];
	else return NO_CLASS;
}