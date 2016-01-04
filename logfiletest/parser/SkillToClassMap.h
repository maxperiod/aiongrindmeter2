#ifndef SKILLTOCLASSMAP_H
#define SKILLTOCLASSMAP_H

#include <string>
#include <unordered_map>
using namespace std;

class SkillToClassMap{
public:
	SkillToClassMap(): NO_CLASS(""){}

	const string& getClass(const string& skill);

protected:
	const string NO_CLASS;
	unordered_map<string, string> skillToClass;
};

extern SkillToClassMap* CLASS_SKILLS;

#endif