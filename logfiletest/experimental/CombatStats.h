#ifndef COMBATSTATS_H
#define COMBATSTATS_H

#include <ctime>
#include <string>
#include <unordered_map>
using namespace std;


#include "SkillDamageStats.h"

struct SkillDamageEntry{
	tm timestamp;
	string target;
	string skill;
	int damage;
	int damage2;
};

struct CombatStats{
	CombatStats(): numHits(0), numCrits(0), enemyBlock(0), 
		enemyParry(0), enemyEvade(0), enemyResist(0),
		enemyShield(0), enemyReflect(0), lastHitDamage(0), lastHitDamage2(0),
		totalDamageInflicted(0), totalDamageReceived(0), skillAttacks(0)
		/*
		AutoAttackMinDamage(0), AutoAttackMaxDamage(0),
		CritAutoAttackMinDamage(0), CritAutoAttackMaxDamage(0),
		AutoAttackMinDamage2(0), AutoAttackMaxDamage2(0),
		CritAutoAttackMinDamage2(0), CritAutoAttackMaxDamage2(0),
		
		countableAutoAttackDamage(0), countableAutoAttackDamage2(0),
		countableCritAutoAttackDamage(0), countableCritAutoAttackDamage2(0),
		countableNumAutoAttacks(0), countableNumAutoAttacks2(0),
		countableCritAutoAttacks(0), countableCritAutoAttacks2(0)
		*/
	{
			multiStrikes[0] = 0;
			multiStrikes[1] = 0;
			multiStrikes[2] = 0;
			multiStrikes[3] = 0;
			
			multiStrikes2[0] = 0;
			multiStrikes2[1] = 0;
			multiStrikes2[2] = 0;
			multiStrikes2[3] = 0;
	}

	int numAttacks;
	int numHits;
	int numCrits;
	
	int enemyBlock;
	int enemyParry;
	int enemyEvade;
	int enemyResist;

	int enemyShield;
	int enemyReflect;	

	int lastHitDamage;
	int lastHitDamage2;

	int totalDamageInflicted;
	int totalDamageReceived;

	int skillAttacks;
	int multiStrikes[4];
	int multiStrikes2[4];
	/*
	int AutoAttackMinDamage;
	int AutoAttackMaxDamage;
	int CritAutoAttackMinDamage;
	int CritAutoAttackMaxDamage;

	int AutoAttackMinDamage2;
	int AutoAttackMaxDamage2;
	int CritAutoAttackMinDamage2;
	int CritAutoAttackMaxDamage2;
	
	int countableAutoAttackDamage;
	int countableAutoAttackDamage2;
	int countableCritAutoAttackDamage;
	int countableCritAutoAttackDamage2;
	int countableNumAutoAttacks;
	int countableNumAutoAttacks2;
	int countableCritAutoAttacks;
	int countableCritAutoAttacks2;
	*/
	
	SkillDamageStats autoDamageStats1;
	SkillDamageStats autoDamageStats2;
	unordered_map<string, SkillDamageStats> skillDamageStats;
	//MultiStrikeCounter multiStrikeCounter;
};

#endif