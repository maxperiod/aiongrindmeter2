#ifndef ATTACK_H
#define ATTACK_H

using namespace std;

struct Attack{
	Attack():
		critical(false),
		blocked(false),
		parried(false),
		shielded(false),
		reflected(false),
		mainhandDamage(-1),
		offhandDamage(-1),		
		numMainhandMultiStrikes(0),
		numOffhandMultiStrikes(0),
		mainhandMultiStrikeDamage(-1),
		offhandMultiStrikeDamage(-1)
	{}

	string skill;
	string user;
	string target;

	bool critical;
	bool blocked;
	bool parried;
	   
	bool shielded;
	bool reflected;

	int mainhandDamage;
	int offhandDamage;

	int mainhandMultiStrikeDamage;
	int offhandMultiStrikeDamage;

	//Multi strikes count does not include main strike
	int numMainhandMultiStrikes;
	int numOffhandMultiStrikes;
};

#endif