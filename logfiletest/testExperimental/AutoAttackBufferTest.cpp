#include "../experimental/AutoAttackBuffer.h"
#include "gtest/gtest.h"


TEST(AutoAttackBuffer, regularAttack1){
	CombatStatsManager combatStatsManager;
	WeaponSwitch weaponSwitch;

	queue<Attack> attacks;
	AutoAttackBuffer aab(combatStatsManager, weaponSwitch, attacks);
	CombatStats& cs = combatStatsManager.getAllTargetsCombatStats().first;
	//aab.setCombatStats(cs);

	aab.makeAutoAttack(659, "Supraklaw Forager", false);
	aab.makeAutoAttack(65, "Supraklaw Forager", false);
	aab.stopAutoAttack();

	//queue<Attack>& attacks = aab.getAttacks();
	EXPECT_EQ(1, attacks.size());

	Attack attack = attacks.front();
	EXPECT_EQ("", attack.user);
	EXPECT_EQ("Supraklaw Forager", attack.target);
	EXPECT_EQ(659, attack.mainhandDamage);
	EXPECT_EQ(-1, attack.offhandDamage);
	EXPECT_EQ(1, attack.numMainhandMultiStrikes);
	EXPECT_EQ(0, attack.numOffhandMultiStrikes);
	EXPECT_FALSE(attack.blocked);
	EXPECT_FALSE(attack.critical);
	EXPECT_FALSE(attack.parried);
	EXPECT_FALSE(attack.shielded);
	EXPECT_FALSE(attack.reflected);


	EXPECT_EQ(1,cs.numHits);
	EXPECT_EQ(0,cs.numCrits);
	
	EXPECT_EQ(0,cs.enemyBlock);
	EXPECT_EQ(0,cs.enemyParry);
	EXPECT_EQ(0,cs.enemyEvade);
	
	EXPECT_EQ(0,cs.multiStrikes[0]);
	EXPECT_EQ(1,cs.multiStrikes[1]);
	EXPECT_EQ(0,cs.multiStrikes[2]);
	EXPECT_EQ(0,cs.multiStrikes[3]);

	EXPECT_EQ(659+65,cs.totalDamageInflicted); 

	CombatStats& cs2 = combatStatsManager.getIndividualTargetCombatStats("Supraklaw Forager").first;
	
	EXPECT_EQ(1,cs2.numHits);
	EXPECT_EQ(0,cs2.numCrits);
	
	EXPECT_EQ(0,cs2.enemyBlock);
	EXPECT_EQ(0,cs2.enemyParry);
	EXPECT_EQ(0,cs2.enemyEvade);
	
	EXPECT_EQ(0,cs2.multiStrikes[0]);
	EXPECT_EQ(1,cs2.multiStrikes[1]);
	EXPECT_EQ(0,cs2.multiStrikes[2]);
	EXPECT_EQ(0,cs2.multiStrikes[3]);

	EXPECT_EQ(659+65,cs2.totalDamageInflicted); 

	//2014.05.10 11:52:43 : You inflicted 659 damage on Supraklaw Forager. 
	//2014.05.10 11:52:43 : You inflicted 65 damage on Supraklaw Forager. 
}

TEST(AutoAttackBuffer, regularAttack2){
	CombatStatsManager combatStatsManager;
	WeaponSwitch weaponSwitch;

	queue<Attack> attacks;
	AutoAttackBuffer aab(combatStatsManager, weaponSwitch, attacks);
	CombatStats& cs = combatStatsManager.getAllTargetsCombatStats().first;

	aab.makeAutoAttack(1537, "Training Dummy", true);	
	aab.stopAutoAttack();

	Attack attack = attacks.front();
	EXPECT_EQ("", attack.user);
	EXPECT_EQ("Training Dummy", attack.target);
	EXPECT_EQ(1537, attack.mainhandDamage);
	EXPECT_EQ(-1, attack.offhandDamage);
	EXPECT_EQ(0, attack.numMainhandMultiStrikes);
	EXPECT_EQ(0, attack.numOffhandMultiStrikes);
	EXPECT_FALSE(attack.blocked);
	EXPECT_TRUE(attack.critical);
	EXPECT_FALSE(attack.parried);
	EXPECT_FALSE(attack.shielded);
	EXPECT_FALSE(attack.reflected);

	EXPECT_EQ(1,cs.numHits);
	EXPECT_EQ(1,cs.numCrits);
	
	EXPECT_EQ(0,cs.enemyBlock);
	EXPECT_EQ(0,cs.enemyParry);
	EXPECT_EQ(0,cs.enemyEvade);
	
	EXPECT_EQ(1,cs.multiStrikes[0]);
	EXPECT_EQ(0,cs.multiStrikes[1]);
	EXPECT_EQ(0,cs.multiStrikes[2]);
	EXPECT_EQ(0,cs.multiStrikes[3]);

	EXPECT_EQ(1537,cs.totalDamageInflicted);

	//2014.07.15 21:26:22 : Critical Hit! You inflicted 1,537 critical damage on Training Dummy. 
}


TEST(AutoAttackBuffer, regularAttack3){
	CombatStatsManager combatStatsManager;
	WeaponSwitch weaponSwitch;

	queue<Attack> attacks;
	AutoAttackBuffer aab(combatStatsManager, weaponSwitch, attacks);
	CombatStats& cs = combatStatsManager.getAllTargetsCombatStats().first;

	aab.makeAutoAttack(659, "Supraklaw Forager", false);
	aab.makeAutoAttack(65, "Supraklaw Forager", false);
	aab.makeAutoAttack(65, "Supraklaw Forager", false);
	aab.makeAutoAttack(65, "Supraklaw Forager", false);
	aab.stopAutoAttack();

	Attack attack = attacks.front();
	EXPECT_EQ("", attack.user);
	EXPECT_EQ("Supraklaw Forager", attack.target);
	EXPECT_EQ(659, attack.mainhandDamage);
	EXPECT_EQ(-1, attack.offhandDamage);
	EXPECT_EQ(3, attack.numMainhandMultiStrikes);
	EXPECT_EQ(0, attack.numOffhandMultiStrikes);
	EXPECT_FALSE(attack.blocked);
	EXPECT_FALSE(attack.critical);
	EXPECT_FALSE(attack.parried);
	EXPECT_FALSE(attack.shielded);
	EXPECT_FALSE(attack.reflected);

	EXPECT_EQ(1,cs.numHits);
	EXPECT_EQ(0,cs.numCrits);
	
	EXPECT_EQ(0,cs.enemyBlock);
	EXPECT_EQ(0,cs.enemyParry);
	EXPECT_EQ(0,cs.enemyEvade);
	
	EXPECT_EQ(0,cs.multiStrikes[0]);
	EXPECT_EQ(0,cs.multiStrikes[1]);
	EXPECT_EQ(0,cs.multiStrikes[2]);
	EXPECT_EQ(1,cs.multiStrikes[3]);

	EXPECT_EQ(659+65+65+65,cs.totalDamageInflicted);

	//2014.05.10 11:52:43 : You inflicted 659 damage on Supraklaw Forager. 
	//2014.05.10 11:52:43 : You inflicted 65 damage on Supraklaw Forager. 
	//2014.05.10 11:52:43 : You inflicted 65 damage on Supraklaw Forager. 
	//2014.05.10 11:52:43 : You inflicted 65 damage on Supraklaw Forager. 
}


TEST(AutoAttackBuffer, weakrRegularAttack){
	CombatStatsManager combatStatsManager;
	WeaponSwitch weaponSwitch;

	queue<Attack> attacks;
	AutoAttackBuffer aab(combatStatsManager, weaponSwitch, attacks);
	CombatStats& cs = combatStatsManager.getAllTargetsCombatStats().first;

	aab.makeAutoAttack(9, "David Tam", false);
	aab.makeAutoAttack(1, "David Tam", false);
	aab.makeAutoAttack(1, "David Tam", false);

	aab.stopAutoAttack();

	Attack attack = attacks.front();
	EXPECT_EQ("", attack.user);
	EXPECT_EQ("David Tam", attack.target);
	EXPECT_EQ(9, attack.mainhandDamage);
	EXPECT_EQ(-1, attack.offhandDamage);
	EXPECT_EQ(2, attack.numMainhandMultiStrikes);
	EXPECT_EQ(0, attack.numOffhandMultiStrikes);
	EXPECT_FALSE(attack.blocked);
	EXPECT_FALSE(attack.critical);
	EXPECT_FALSE(attack.parried);
	EXPECT_FALSE(attack.shielded);
	EXPECT_FALSE(attack.reflected);

	EXPECT_EQ(1,cs.numHits);
	EXPECT_EQ(0,cs.numCrits);
	
	EXPECT_EQ(0,cs.multiStrikes[0]);
	EXPECT_EQ(0,cs.multiStrikes[1]);
	EXPECT_EQ(1,cs.multiStrikes[2]);
	EXPECT_EQ(0,cs.multiStrikes[3]);
}


TEST(AutoAttackBuffer, multiAttack1){
	CombatStatsManager combatStatsManager;
	WeaponSwitch weaponSwitch;

	queue<Attack> attacks;
	AutoAttackBuffer aab(combatStatsManager, weaponSwitch, attacks);
	CombatStats& cs = combatStatsManager.getAllTargetsCombatStats().first;

	aab.makeAutoAttack(776, "Training Dummy", false);
	aab.stopAutoAttack();
	//aab.makeAutoAttack(77, "Training Dummy", false);
	//aab.makeAutoAttack(77, "Training Dummy", false);	
	aab.makeAutoAttack(720, "Training Dummy", false);
	aab.stopAutoAttack();
	//aab.makeAutoAttack(72, "Training Dummy", false);
	//aab.makeAutoAttack(72, "Training Dummy", false);
	aab.makeAutoAttack(1547, "Training Dummy", true);
	aab.makeAutoAttack(154, "Training Dummy", false);
	
	aab.stopAutoAttack();

	Attack attack = attacks.front();
	EXPECT_EQ("", attack.user);
	EXPECT_EQ("Training Dummy", attack.target);
	EXPECT_EQ("", attack.skill);
	EXPECT_EQ(776, attack.mainhandDamage);
	EXPECT_EQ(-1, attack.offhandDamage);
	EXPECT_EQ(0, attack.numMainhandMultiStrikes);
	EXPECT_EQ(0, attack.numOffhandMultiStrikes);
	EXPECT_FALSE(attack.blocked);
	EXPECT_FALSE(attack.critical);
	EXPECT_FALSE(attack.parried);
	EXPECT_FALSE(attack.shielded);
	EXPECT_FALSE(attack.reflected);
	
	attacks.pop();
	attack = attacks.front();
	EXPECT_EQ("", attack.user);
	EXPECT_EQ("Training Dummy", attack.target);
	EXPECT_EQ("", attack.skill);
	EXPECT_EQ(720, attack.mainhandDamage);
	EXPECT_EQ(-1, attack.offhandDamage);
	EXPECT_EQ(0, attack.numMainhandMultiStrikes);
	EXPECT_EQ(0, attack.numOffhandMultiStrikes);
	EXPECT_FALSE(attack.blocked);
	EXPECT_FALSE(attack.critical);
	EXPECT_FALSE(attack.parried);
	EXPECT_FALSE(attack.shielded);
	EXPECT_FALSE(attack.reflected);

	attacks.pop();
	attack = attacks.front();
	EXPECT_EQ("", attack.user);
	EXPECT_EQ("Training Dummy", attack.target);
	EXPECT_EQ("", attack.skill);
	EXPECT_EQ(1547, attack.mainhandDamage);
	EXPECT_EQ(-1, attack.offhandDamage);
	EXPECT_EQ(1, attack.numMainhandMultiStrikes);
	EXPECT_EQ(0, attack.numOffhandMultiStrikes);
	EXPECT_FALSE(attack.blocked);
	EXPECT_TRUE(attack.critical);
	EXPECT_FALSE(attack.parried);
	EXPECT_FALSE(attack.shielded);
	EXPECT_FALSE(attack.reflected);

	EXPECT_EQ(3,cs.numHits);
	EXPECT_EQ(1,cs.numCrits);
	
	EXPECT_EQ(0,cs.enemyBlock);
	EXPECT_EQ(0,cs.enemyParry);
	EXPECT_EQ(0,cs.enemyEvade);
	
	EXPECT_EQ(2,cs.multiStrikes[0]);
	EXPECT_EQ(1,cs.multiStrikes[1]);
	EXPECT_EQ(0,cs.multiStrikes[2]);
	EXPECT_EQ(0,cs.multiStrikes[3]);

	EXPECT_EQ(776+720+1547+154,cs.totalDamageInflicted);
	/*
	2014.07.15 21:26:18 : You inflicted 776 damage on Training Dummy. 
	2014.07.15 21:26:19 : You inflicted 720 damage on Training Dummy.  
	2014.07.15 21:26:21 : Critical Hit! You inflicted 1,547 critical damage on Training Dummy. 
	2014.07.15 21:26:21 : You inflicted 154 damage on Training Dummy. 
	*/
}


TEST(AutoAttackBuffer, multiAttack2){
	CombatStatsManager combatStatsManager;
	WeaponSwitch weaponSwitch;

	queue<Attack> attacks;
	AutoAttackBuffer aab(combatStatsManager, weaponSwitch, attacks);
	CombatStats& cs = combatStatsManager.getAllTargetsCombatStats().first;

	aab.makeAutoAttack(776, "Training Dummy", false);	
	aab.makeAutoAttack(77, "Training Dummy", false);
	aab.makeAutoAttack(77, "Training Dummy", false);
	aab.stopAutoAttack();
	aab.makeAutoAttack(720, "Training Dummy", false);	
	aab.makeAutoAttack(72, "Training Dummy", false);	
	aab.makeAutoAttack(72, "Training Dummy", false);	
	aab.stopAutoAttack();
	aab.makeAutoAttack(1547, "Training Dummy", true);
	aab.makeAutoAttack(154, "Training Dummy", false);
	
	aab.stopAutoAttack();

	Attack attack = attacks.front();
	EXPECT_EQ("", attack.user);
	EXPECT_EQ("Training Dummy", attack.target);
	EXPECT_EQ("", attack.skill);
	EXPECT_EQ(776, attack.mainhandDamage);
	EXPECT_EQ(-1, attack.offhandDamage);
	EXPECT_EQ(2, attack.numMainhandMultiStrikes);
	EXPECT_EQ(0, attack.numOffhandMultiStrikes);
	EXPECT_FALSE(attack.blocked);
	EXPECT_FALSE(attack.critical);
	EXPECT_FALSE(attack.parried);
	EXPECT_FALSE(attack.shielded);
	EXPECT_FALSE(attack.reflected);
	
	attacks.pop();
	attack = attacks.front();
	EXPECT_EQ("", attack.user);
	EXPECT_EQ("Training Dummy", attack.target);
	EXPECT_EQ("", attack.skill);
	EXPECT_EQ(720, attack.mainhandDamage);
	EXPECT_EQ(-1, attack.offhandDamage);
	EXPECT_EQ(2, attack.numMainhandMultiStrikes);
	EXPECT_EQ(0, attack.numOffhandMultiStrikes);
	EXPECT_FALSE(attack.blocked);
	EXPECT_FALSE(attack.critical);
	EXPECT_FALSE(attack.parried);
	EXPECT_FALSE(attack.shielded);
	EXPECT_FALSE(attack.reflected);

	attacks.pop();
	attack = attacks.front();
	EXPECT_EQ("", attack.user);	
	EXPECT_EQ("Training Dummy", attack.target);
	EXPECT_EQ("", attack.skill);
	EXPECT_EQ(1547, attack.mainhandDamage);
	EXPECT_EQ(-1, attack.offhandDamage);
	EXPECT_EQ(1, attack.numMainhandMultiStrikes);
	EXPECT_EQ(0, attack.numOffhandMultiStrikes);
	EXPECT_FALSE(attack.blocked);
	EXPECT_TRUE(attack.critical);
	EXPECT_FALSE(attack.parried);
	EXPECT_FALSE(attack.shielded);
	EXPECT_FALSE(attack.reflected);

	EXPECT_EQ(3,cs.numHits);
	EXPECT_EQ(1,cs.numCrits);
	
	EXPECT_EQ(0,cs.enemyBlock);
	EXPECT_EQ(0,cs.enemyParry);
	EXPECT_EQ(0,cs.enemyEvade);
	
	EXPECT_EQ(0,cs.multiStrikes[0]);
	EXPECT_EQ(1,cs.multiStrikes[1]);
	EXPECT_EQ(2,cs.multiStrikes[2]);
	EXPECT_EQ(0,cs.multiStrikes[3]);

	
	EXPECT_EQ(776+77+77+720+72+72+1547+154,cs.totalDamageInflicted);
	/*
	2014.07.15 21:26:18 : You inflicted 776 damage on Training Dummy. 
	2014.07.15 21:26:18 : You inflicted 77 damage on Training Dummy. 
	2014.07.15 21:26:18 : You inflicted 77 damage on Training Dummy. 
	2014.07.15 21:26:19 : You inflicted 720 damage on Training Dummy. 
	2014.07.15 21:26:19 : You inflicted 72 damage on Training Dummy. 
	2014.07.15 21:26:19 : You inflicted 72 damage on Training Dummy. 
	2014.07.15 21:26:21 : Critical Hit! You inflicted 1,547 critical damage on Training Dummy. 
	2014.07.15 21:26:21 : You inflicted 154 damage on Training Dummy. 
	*/
}

TEST(AutoAttackBuffer, multiAttack3){
	CombatStatsManager combatStatsManager;
	WeaponSwitch weaponSwitch;

	queue<Attack> attacks;
	AutoAttackBuffer aab(combatStatsManager, weaponSwitch, attacks);
	CombatStats& cs = combatStatsManager.getAllTargetsCombatStats().first;

	aab.makeAutoAttack(672, "Training Dummy", false);	
	aab.makeAutoAttack(535, "Training Dummy", false);
	aab.makeAutoAttack(53, "Training Dummy", false);

	aab.makeAutoAttack(668, "Training Dummy", false);	
	aab.makeAutoAttack(538, "Training Dummy", false);	
	aab.makeAutoAttack(53, "Training Dummy", false);	

	aab.makeAutoAttack(654, "Training Dummy", false);
	aab.makeAutoAttack(533, "Training Dummy", false);
	aab.makeAutoAttack(53, "Training Dummy", false);

	aab.makeAutoAttack(668, "Training Dummy", false);
	aab.makeAutoAttack(539, "Training Dummy", false);
	aab.makeAutoAttack(53, "Training Dummy", false);

	aab.stopAutoAttack();

	Attack attack = attacks.front();
	EXPECT_EQ("", attack.user);
	EXPECT_EQ("Training Dummy", attack.target);
	EXPECT_EQ("", attack.skill);
	EXPECT_EQ(672, attack.mainhandDamage);
	EXPECT_EQ(535, attack.offhandDamage);
	EXPECT_EQ(0, attack.numMainhandMultiStrikes);
	EXPECT_EQ(1, attack.numOffhandMultiStrikes);
	EXPECT_FALSE(attack.blocked);
	EXPECT_FALSE(attack.critical);
	EXPECT_FALSE(attack.parried);
	EXPECT_FALSE(attack.shielded);
	EXPECT_FALSE(attack.reflected);
	
	attacks.pop();
	attack = attacks.front();
	EXPECT_EQ("", attack.user);
	EXPECT_EQ("Training Dummy", attack.target);
	EXPECT_EQ("", attack.skill);
	EXPECT_EQ(668, attack.mainhandDamage);
	EXPECT_EQ(538, attack.offhandDamage);
	EXPECT_EQ(0, attack.numMainhandMultiStrikes);
	EXPECT_EQ(1, attack.numOffhandMultiStrikes);
	EXPECT_FALSE(attack.blocked);
	EXPECT_FALSE(attack.critical);
	EXPECT_FALSE(attack.parried);
	EXPECT_FALSE(attack.shielded);
	EXPECT_FALSE(attack.reflected);

	attacks.pop();
	attack = attacks.front();
	EXPECT_EQ("", attack.user);
	EXPECT_EQ("Training Dummy", attack.target);
	EXPECT_EQ("", attack.skill);
	EXPECT_EQ(654, attack.mainhandDamage);
	EXPECT_EQ(533, attack.offhandDamage);
	EXPECT_EQ(0, attack.numMainhandMultiStrikes);
	EXPECT_EQ(1, attack.numOffhandMultiStrikes);
	EXPECT_FALSE(attack.blocked);
	EXPECT_FALSE(attack.critical);
	EXPECT_FALSE(attack.parried);
	EXPECT_FALSE(attack.shielded);
	EXPECT_FALSE(attack.reflected);

	attacks.pop();
	attack = attacks.front();
	EXPECT_EQ("", attack.user);
	EXPECT_EQ("Training Dummy", attack.target);
	EXPECT_EQ("", attack.skill);
	EXPECT_EQ(668, attack.mainhandDamage);
	EXPECT_EQ(539, attack.offhandDamage);
	EXPECT_EQ(0, attack.numMainhandMultiStrikes);
	EXPECT_EQ(1, attack.numOffhandMultiStrikes);
	EXPECT_FALSE(attack.blocked);
	EXPECT_FALSE(attack.critical);
	EXPECT_FALSE(attack.parried);
	EXPECT_FALSE(attack.shielded);
	EXPECT_FALSE(attack.reflected);
	/*
	EXPECT_EQ(4,cs.numHits);
	EXPECT_EQ(0,cs.numCrits);
	
	EXPECT_EQ(0,cs.enemyBlock);
	EXPECT_EQ(0,cs.enemyParry);
	EXPECT_EQ(0,cs.enemyEvade);
	
	EXPECT_EQ(0,cs.multiStrikes[0]);
	EXPECT_EQ(4,cs.multiStrikes[1]);
	EXPECT_EQ(0,cs.multiStrikes[2]);
	EXPECT_EQ(0,cs.multiStrikes[3]);
	*/
	
	EXPECT_EQ(672+535+53+668+538+53+654+533+53+668+539+53,cs.totalDamageInflicted);
	/*
2017.12.11 22:56:01 : You inflicted 672 damage on Training Dummy. 
2017.12.11 22:56:01 : You inflicted 535 damage on Training Dummy. 
2017.12.11 22:56:01 : You inflicted 53 damage on Training Dummy. 

2017.12.11 22:56:07 : You inflicted 668 damage on Training Dummy. 
2017.12.11 22:56:07 : You inflicted 538 damage on Training Dummy. 
2017.12.11 22:56:07 : You inflicted 53 damage on Training Dummy. 

2017.12.11 22:56:24 : You inflicted 654 damage on Training Dummy. 
2017.12.11 22:56:24 : You inflicted 533 damage on Training Dummy. 
2017.12.11 22:56:24 : You inflicted 53 damage on Training Dummy. 

2017.12.11 22:56:27 : You inflicted 668 damage on Training Dummy. 
2017.12.11 22:56:27 : You inflicted 539 damage on Training Dummy. 
2017.12.11 22:56:27 : You inflicted 53 damage on Training Dummy. 
	*/
}

TEST(AutoAttackBuffer, skillAttack1){
	CombatStatsManager combatStatsManager;
	WeaponSwitch weaponSwitch;

	queue<Attack> attacks;
	AutoAttackBuffer aab(combatStatsManager, weaponSwitch, attacks);
	CombatStats& cs = combatStatsManager.getAllTargetsCombatStats().first;

	aab.makeSkillAttack(8360, "Chief of Staff Moriata", "Harpist's Pod I", false);		
	
	aab.stopAutoAttack();

	Attack attack = attacks.front();
	EXPECT_EQ("", attack.user);
	EXPECT_EQ("Chief of Staff Moriata", attack.target);
	EXPECT_EQ("Harpist's Pod I", attack.skill);
	EXPECT_EQ(8360, attack.mainhandDamage);
	EXPECT_EQ(-1, attack.offhandDamage);
	EXPECT_EQ(0, attack.numMainhandMultiStrikes);
	EXPECT_EQ(0, attack.numOffhandMultiStrikes);
	EXPECT_FALSE(attack.blocked);
	EXPECT_FALSE(attack.critical);
	EXPECT_FALSE(attack.parried);
	EXPECT_FALSE(attack.shielded);
	EXPECT_FALSE(attack.reflected);

	EXPECT_EQ(1,cs.numHits);
	EXPECT_EQ(0,cs.numCrits);
	
	EXPECT_EQ(0,cs.enemyBlock);
	EXPECT_EQ(0,cs.enemyParry);
	EXPECT_EQ(0,cs.enemyEvade);
	
	EXPECT_EQ(1,cs.skillAttacks);

	EXPECT_EQ(0,cs.multiStrikes[0]);
	EXPECT_EQ(0,cs.multiStrikes[1]);
	EXPECT_EQ(0,cs.multiStrikes[2]);
	EXPECT_EQ(0,cs.multiStrikes[3]);

	EXPECT_EQ(8360,cs.totalDamageInflicted);

	/*
	Morrifay inflicted 8,360 damage on Chief of Staff Moriata by using Harpist's Pod I. 
	*/
}


TEST(AutoAttackBuffer, skillAttack2){
	CombatStatsManager combatStatsManager;
	WeaponSwitch weaponSwitch;

	queue<Attack> attacks;
	AutoAttackBuffer aab(combatStatsManager, weaponSwitch, attacks);
	CombatStats& cs = combatStatsManager.getAllTargetsCombatStats().first;

	aab.makeSkillAttack(4398, "Chief of Staff Moriata", "Spiral Arrow IV", true);	
		
	aab.stopAutoAttack();

	Attack attack = attacks.front();
	EXPECT_EQ("", attack.user);
	EXPECT_EQ("Chief of Staff Moriata", attack.target);
	EXPECT_EQ("Spiral Arrow IV", attack.skill);
	EXPECT_EQ(4398, attack.mainhandDamage);
	EXPECT_EQ(-1, attack.offhandDamage);
	EXPECT_EQ(0, attack.numMainhandMultiStrikes);
	EXPECT_EQ(0, attack.numOffhandMultiStrikes);
	EXPECT_FALSE(attack.blocked);
	EXPECT_TRUE(attack.critical);
	EXPECT_FALSE(attack.parried);
	EXPECT_FALSE(attack.shielded);
	EXPECT_FALSE(attack.reflected);

	EXPECT_EQ(1,cs.numHits);
	EXPECT_EQ(1,cs.numCrits);
	
	EXPECT_EQ(0,cs.enemyBlock);
	EXPECT_EQ(0,cs.enemyParry);
	EXPECT_EQ(0,cs.enemyEvade);
	
	EXPECT_EQ(1,cs.skillAttacks);

	EXPECT_EQ(0,cs.multiStrikes[0]);
	EXPECT_EQ(0,cs.multiStrikes[1]);
	EXPECT_EQ(0,cs.multiStrikes[2]);
	EXPECT_EQ(0,cs.multiStrikes[3]);

	EXPECT_EQ(4398,cs.totalDamageInflicted);

	/*
	Critical Hit!Kallek inflicted 4,398 damage on Chief of Staff Moriata by using Spiral Arrow IV.
	*/
}


TEST(AutoAttackBuffer, skillAttackMulti1){
	CombatStatsManager combatStatsManager;
	WeaponSwitch weaponSwitch;

	queue<Attack> attacks;
	AutoAttackBuffer aab(combatStatsManager, weaponSwitch, attacks);
	CombatStats& cs = combatStatsManager.getAllTargetsCombatStats().first;

	aab.makeSkillAttack(1827, "Sprawling Agrint", "Ferocious Strike VI", true);	
	aab.makeSkillAttack(1930, "Sprawling Agrint", "Robust Blow VI", true);	

	Attack attack = attacks.front();
	EXPECT_EQ("", attack.user);
	EXPECT_EQ("Sprawling Agrint", attack.target);
	EXPECT_EQ("Ferocious Strike VI", attack.skill);
	EXPECT_EQ(1827, attack.mainhandDamage);
	EXPECT_EQ(-1, attack.offhandDamage);
	EXPECT_EQ(0, attack.numMainhandMultiStrikes);
	EXPECT_EQ(0, attack.numOffhandMultiStrikes);
	EXPECT_FALSE(attack.blocked);
	EXPECT_TRUE(attack.critical);
	EXPECT_FALSE(attack.parried);
	EXPECT_FALSE(attack.shielded);
	EXPECT_FALSE(attack.reflected);

	attacks.pop();
	attack = attacks.front();
	EXPECT_EQ("", attack.user);
	EXPECT_EQ("Sprawling Agrint", attack.target);
	EXPECT_EQ("Robust Blow VI", attack.skill);
	EXPECT_EQ(1930, attack.mainhandDamage);
	EXPECT_EQ(-1, attack.offhandDamage);
	EXPECT_EQ(0, attack.numMainhandMultiStrikes);
	EXPECT_EQ(0, attack.numOffhandMultiStrikes);
	EXPECT_FALSE(attack.blocked);
	EXPECT_TRUE(attack.critical);
	EXPECT_FALSE(attack.parried);
	EXPECT_FALSE(attack.shielded);
	EXPECT_FALSE(attack.reflected);

	EXPECT_EQ(2,cs.numHits);
	EXPECT_EQ(2,cs.numCrits);
	
	EXPECT_EQ(0,cs.enemyBlock);
	EXPECT_EQ(0,cs.enemyParry);
	EXPECT_EQ(0,cs.enemyEvade);
	
	EXPECT_EQ(2,cs.skillAttacks);

	EXPECT_EQ(0,cs.multiStrikes[0]);
	EXPECT_EQ(0,cs.multiStrikes[1]);
	EXPECT_EQ(0,cs.multiStrikes[2]);
	EXPECT_EQ(0,cs.multiStrikes[3]);

	EXPECT_EQ(1827+1930,cs.totalDamageInflicted);

	/*
	2014.06.18 17:38:48 : Critical Hit!You inflicted 1,827 damage on Sprawling Agrint by using Ferocious Strike VI. 
	2014.06.18 17:38:49 : Critical Hit!You inflicted 1,930 damage on Sprawling Agrint by using Robust Blow VI. 
	*/
}


TEST(AutoAttackBuffer, dualWield1){
	CombatStatsManager combatStatsManager;
	WeaponSwitch weaponSwitch;

	queue<Attack> attacks;
	AutoAttackBuffer aab(combatStatsManager, weaponSwitch, attacks);
	CombatStats& cs = combatStatsManager.getAllTargetsCombatStats().first;

	aab.makeAutoAttack(190, "Steel Rake Watcher", false);
	aab.makeAutoAttack(219, "Steel Rake Watcher", false);
	aab.makeAutoAttack(19, "Steel Rake Watcher", false);
	
	aab.stopAutoAttack();

	Attack attack = attacks.front();
	EXPECT_EQ("", attack.user);
	EXPECT_EQ("Steel Rake Watcher", attack.target);
	EXPECT_EQ("", attack.skill);
	EXPECT_EQ(190, attack.mainhandDamage);
	EXPECT_EQ(219, attack.offhandDamage);
	EXPECT_EQ(1, attack.numMainhandMultiStrikes);
	EXPECT_EQ(0, attack.numOffhandMultiStrikes);
	EXPECT_FALSE(attack.blocked);
	EXPECT_FALSE(attack.critical);
	EXPECT_FALSE(attack.parried);
	EXPECT_FALSE(attack.shielded);
	EXPECT_FALSE(attack.reflected);

	EXPECT_EQ(1,cs.numHits);
	EXPECT_EQ(0,cs.numCrits);
	
	EXPECT_EQ(0,cs.enemyBlock);
	EXPECT_EQ(0,cs.enemyParry);
	EXPECT_EQ(0,cs.enemyEvade);
	
	EXPECT_EQ(0,cs.multiStrikes[0]);
	EXPECT_EQ(1,cs.multiStrikes[1]);
	EXPECT_EQ(0,cs.multiStrikes[2]);
	EXPECT_EQ(0,cs.multiStrikes[3]);

	EXPECT_EQ(1,cs.multiStrikes2[0]);
	EXPECT_EQ(0,cs.multiStrikes2[1]);
	EXPECT_EQ(0,cs.multiStrikes2[2]);
	EXPECT_EQ(0,cs.multiStrikes2[3]);

	EXPECT_EQ(190+219+19,cs.totalDamageInflicted);

	/*
	2014.11.21 22:14:57 : You inflicted 190 damage on Steel Rake Watcher. 
	2014.11.21 22:14:57 : You inflicted 219 damage on Steel Rake Watcher. 
	2014.11.21 22:14:57 : You inflicted 19 damage on Steel Rake Watcher. 
	*/
}

TEST(AutoAttackBuffer, dualWield2){
	CombatStatsManager combatStatsManager;
	WeaponSwitch weaponSwitch;

	queue<Attack> attacks;
	AutoAttackBuffer aab(combatStatsManager, weaponSwitch, attacks);
	CombatStats& cs = combatStatsManager.getAllTargetsCombatStats().first;

	aab.makeAutoAttack(1651, "Training Dummy", false);
	aab.makeAutoAttack(1120, "Training Dummy", false);
	aab.makeAutoAttack(165, "Training Dummy", false);
	aab.makeAutoAttack(112, "Training Dummy", false);
	
	aab.stopAutoAttack();
	
	Attack attack = attacks.front();
	EXPECT_EQ("", attack.user);
	EXPECT_EQ("Training Dummy", attack.target);
	EXPECT_EQ("", attack.skill);
	EXPECT_EQ(1651, attack.mainhandDamage);
	EXPECT_EQ(1120, attack.offhandDamage);
	EXPECT_EQ(1, attack.numMainhandMultiStrikes);
	EXPECT_EQ(1, attack.numOffhandMultiStrikes);
	EXPECT_FALSE(attack.blocked);
	EXPECT_FALSE(attack.critical);
	EXPECT_FALSE(attack.parried);
	EXPECT_FALSE(attack.shielded);
	EXPECT_FALSE(attack.reflected);

	EXPECT_EQ(1,cs.numHits);
	EXPECT_EQ(0,cs.numCrits);
	
	EXPECT_EQ(0,cs.enemyBlock);
	EXPECT_EQ(0,cs.enemyParry);
	EXPECT_EQ(0,cs.enemyEvade);
	
	EXPECT_EQ(0,cs.multiStrikes[0]);
	EXPECT_EQ(1,cs.multiStrikes[1]);
	EXPECT_EQ(0,cs.multiStrikes[2]);
	EXPECT_EQ(0,cs.multiStrikes[3]);

	EXPECT_EQ(0,cs.multiStrikes2[0]);
	EXPECT_EQ(1,cs.multiStrikes2[1]);
	EXPECT_EQ(0,cs.multiStrikes2[2]);
	EXPECT_EQ(0,cs.multiStrikes2[3]);


	EXPECT_EQ(1651+1120+165+112,cs.totalDamageInflicted);
	//2014.07.15 21:26:29 : Gladiadoroscuro inflicted 1,651 damage on Training Dummy. 
	//2014.07.15 21:26:29 : Gladiadoroscuro inflicted 1,120 damage on Training Dummy. 
	//2014.07.15 21:26:29 : Gladiadoroscuro inflicted 165 damage on Training Dummy. 
	//2014.07.15 21:26:29 : Gladiadoroscuro inflicted 112 damage on Training Dummy. 
}

TEST(AutoAttackBuffer, dualWield3){
	
	CombatStatsManager combatStatsManager;
	WeaponSwitch weaponSwitch;

	queue<Attack> attacks;
	AutoAttackBuffer aab(combatStatsManager, weaponSwitch, attacks);
	CombatStats& cs = combatStatsManager.getAllTargetsCombatStats().first;

	aab.makeAutoAttack(219, "Steel Rake Watcher", false);
	aab.makeAutoAttack(190, "Steel Rake Watcher", false);
	aab.makeAutoAttack(19, "Steel Rake Watcher", false);
	
	aab.makeSkillAttack(231, "Steel Rake Watcher", "Rune Carve III", false);

	aab.makeAutoAttack(198, "Steel Rake Watcher", false);
	aab.makeAutoAttack(183, "Steel Rake Watcher", false);
	aab.makeAutoAttack(18, "Steel Rake Watcher", false);
	
	aab.stopAutoAttack();

	Attack attack = attacks.front();
	EXPECT_EQ("", attack.user);
	EXPECT_EQ("Steel Rake Watcher", attack.target);
	EXPECT_EQ("", attack.skill);
	EXPECT_EQ(219, attack.mainhandDamage);
	EXPECT_EQ(190, attack.offhandDamage);
	EXPECT_EQ(0, attack.numMainhandMultiStrikes);
	EXPECT_EQ(1, attack.numOffhandMultiStrikes);
	EXPECT_FALSE(attack.blocked);
	EXPECT_FALSE(attack.critical);
	EXPECT_FALSE(attack.parried);
	EXPECT_FALSE(attack.shielded);
	EXPECT_FALSE(attack.reflected);

	attacks.pop();
	attack = attacks.front();
	EXPECT_EQ("", attack.user);
	EXPECT_EQ("Steel Rake Watcher", attack.target);
	EXPECT_EQ("Rune Carve III", attack.skill);
	EXPECT_EQ(231, attack.mainhandDamage);
	EXPECT_EQ(-1, attack.offhandDamage);
	EXPECT_EQ(0, attack.numMainhandMultiStrikes);
	EXPECT_EQ(0, attack.numOffhandMultiStrikes);
	EXPECT_FALSE(attack.blocked);
	EXPECT_FALSE(attack.critical);
	EXPECT_FALSE(attack.parried);
	EXPECT_FALSE(attack.shielded);
	EXPECT_FALSE(attack.reflected);

	attacks.pop();
	attack = attacks.front();
	EXPECT_EQ("", attack.user);
	EXPECT_EQ("Steel Rake Watcher", attack.target);
	EXPECT_EQ("", attack.skill);
	EXPECT_EQ(198, attack.mainhandDamage);
	EXPECT_EQ(183, attack.offhandDamage);
	EXPECT_EQ(0, attack.numMainhandMultiStrikes);
	EXPECT_EQ(1, attack.numOffhandMultiStrikes);
	EXPECT_FALSE(attack.blocked);
	EXPECT_FALSE(attack.critical);
	EXPECT_FALSE(attack.parried);
	EXPECT_FALSE(attack.shielded);
	EXPECT_FALSE(attack.reflected);

	EXPECT_EQ(3,cs.numHits);
	EXPECT_EQ(0,cs.numCrits);	
	
	EXPECT_EQ(2,cs.multiStrikes[0]);
	EXPECT_EQ(0,cs.multiStrikes[1]);
	EXPECT_EQ(0,cs.multiStrikes[2]);
	EXPECT_EQ(0,cs.multiStrikes[3]);

	EXPECT_EQ(0,cs.multiStrikes2[0]);
	EXPECT_EQ(2,cs.multiStrikes2[1]);
	EXPECT_EQ(0,cs.multiStrikes2[2]);
	EXPECT_EQ(0,cs.multiStrikes2[3]);
	/*
	2014.11.21 22:14:57 : You inflicted 219 damage on Steel Rake Watcher. 
	2014.11.21 22:14:57 : You inflicted 190 damage on Steel Rake Watcher. 
	2014.11.21 22:14:57 : You inflicted 19 damage on Steel Rake Watcher. 
	
	2014.11.21 22:14:57 : You inflicted 231 damage and the rune carve effect on Steel Rake Watcher by using Rune Carve III. 
	
	2014.11.21 22:14:58 : You inflicted 198 damage on Steel Rake Watcher. 
	2014.11.21 22:14:58 : You inflicted 183 damage on Steel Rake Watcher. 
	2014.11.21 22:14:58 : You inflicted 18 damage on Steel Rake Watcher. 
	*/
}

TEST(AutoAttackBuffer, block1){
	CombatStatsManager combatStatsManager;
	WeaponSwitch weaponSwitch;

	queue<Attack> attacks;
	AutoAttackBuffer aab(combatStatsManager, weaponSwitch, attacks);
	CombatStats& cs = combatStatsManager.getAllTargetsCombatStats().first;

	aab.enemyBlocked("Karuken");
	aab.makeAutoAttack(277, "Karuken", false);
	
	aab.stopAutoAttack();

	EXPECT_EQ(1,cs.numHits);
	EXPECT_EQ(0,cs.numCrits);
	
	EXPECT_EQ(1,cs.enemyBlock);
	EXPECT_EQ(0,cs.enemyParry);
	EXPECT_EQ(0,cs.enemyEvade);
	
	EXPECT_EQ(1,cs.multiStrikes[0]);
	EXPECT_EQ(0,cs.multiStrikes[1]);
	EXPECT_EQ(0,cs.multiStrikes[2]);
	EXPECT_EQ(0,cs.multiStrikes[3]);

	EXPECT_EQ(277,cs.totalDamageInflicted);
//2014.06.21 23:15:30 : Karuken blocked Instructor Afrane's attack. 
//2014.06.21 23:15:30 : Karuken received 277 damage from Instructor Afrane. 

}

TEST(AutoAttackBuffer, shieldReflect){
	CombatStatsManager combatStatsManager;
	WeaponSwitch weaponSwitch;

	queue<Attack> attacks;
	AutoAttackBuffer aab(combatStatsManager, weaponSwitch, attacks);
	CombatStats& cs = combatStatsManager.getAllTargetsCombatStats().first;

	aab.enemyReflected("Furiousxado");
	aab.enemyShielded("Furiousxado");
	aab.makeAutoAttack(262, "Furiousxado", true);
	aab.makeAutoAttack(52, "Furiousxado", false);
	aab.makeAutoAttack(52, "Furiousxado", false);
	aab.enemyReflected("Furiousxado");
	aab.enemyShielded("Furiousxado");
	aab.makeAutoAttack(182, "Furiousxado", false);
	aab.stopAutoAttack();

	EXPECT_EQ(2,cs.numHits);
	EXPECT_EQ(1,cs.numCrits);
	
	EXPECT_EQ(0,cs.enemyBlock);
	EXPECT_EQ(0,cs.enemyParry);
	EXPECT_EQ(0,cs.enemyEvade);
	EXPECT_EQ(0,cs.enemyResist);

	EXPECT_EQ(2,cs.enemyReflect);
	EXPECT_EQ(2,cs.enemyShield);
	
	EXPECT_EQ(1,cs.multiStrikes[0]);
	EXPECT_EQ(0,cs.multiStrikes[1]);
	EXPECT_EQ(1,cs.multiStrikes[2]);
	EXPECT_EQ(0,cs.multiStrikes[3]);

	EXPECT_EQ(262+52+52+182,cs.totalDamageInflicted);
/*
2014.06.24 21:12:16 : Your attack on Furiousxado was reflected and inflicted 168 damage on you. 
2014.06.24 21:12:16 : The attack was blocked by the protective shield effect cast on Furiousxado. 
2014.06.24 21:12:16 : Critical Hit! You inflicted 262 critical damage on Furiousxado. 
2014.06.24 21:12:16 : You inflicted 52 damage on Furiousxado. 
2014.06.24 21:12:16 : You inflicted 52 damage on Furiousxado. 
2014.06.24 21:12:16 : Your attack on Furiousxado was reflected and inflicted 168 damage on you. 
2014.06.24 21:12:16 : The attack was blocked by the protective shield effect cast on Furiousxado. 
2014.06.24 21:12:16 : You inflicted 182 damage on Furiousxado by using Ferocious Strike VI. 
*/
}

TEST(AutoAttackBuffer, shield1){
	CombatStatsManager combatStatsManager;
	WeaponSwitch weaponSwitch;

	queue<Attack> attacks;
	AutoAttackBuffer aab(combatStatsManager, weaponSwitch, attacks);
	CombatStats& cs = combatStatsManager.getAllTargetsCombatStats().first;

	aab.enemyShielded("Chief of Staff Moriata");
	aab.makeAutoAttack(71, "Chief of Staff Moriata", false);
	aab.makeAutoAttack(50, "Chief of Staff Moriata", false);
	aab.stopAutoAttack();

	EXPECT_EQ(1,cs.numHits);
	EXPECT_EQ(0,cs.numCrits);
	
	EXPECT_EQ(0,cs.enemyBlock);
	EXPECT_EQ(0,cs.enemyParry);
	EXPECT_EQ(0,cs.enemyEvade);
	EXPECT_EQ(0,cs.enemyResist);

	EXPECT_EQ(0,cs.enemyReflect);
	EXPECT_EQ(1,cs.enemyShield);
	
	EXPECT_EQ(0,cs.multiStrikes[0]);
	EXPECT_EQ(1,cs.multiStrikes[1]);
	EXPECT_EQ(0,cs.multiStrikes[2]);
	EXPECT_EQ(0,cs.multiStrikes[3]);

	EXPECT_EQ(121,cs.totalDamageInflicted);
/*
2014.07.10 10:58:38 : The attack was blocked by the protective shield effect cast on Chief of Staff Moriata. 
2014.07.10 10:58:38 : You inflicted 71 damage on Chief of Staff Moriata. 
2014.07.10 10:58:38 : You inflicted 50 damage on Chief of Staff Moriata. 
*/
}

TEST(AutoAttackBuffer, shield2){
	CombatStatsManager combatStatsManager;
	WeaponSwitch weaponSwitch;

	queue<Attack> attacks;
	AutoAttackBuffer aab(combatStatsManager, weaponSwitch, attacks);
	CombatStats& cs = combatStatsManager.getAllTargetsCombatStats().first;

	aab.enemyShielded("Chief of Staff Moriata");
	aab.makeSkillAttack(374, "Chief of Staff Moriata", "Aerial Shot III", false);
	aab.enemyShielded("Chief of Staff Moriata");
	aab.stopAutoAttack();

	
	aab.enemyShielded("Chief of Staff Moriata");
	aab.makeSkillAttack(374, "Chief of Staff Moriata", "Aerial Shot III", false);
	aab.enemyShielded("Chief of Staff Moriata");
	aab.stopAutoAttack();


	EXPECT_EQ(2,cs.numHits);
	EXPECT_EQ(0,cs.numCrits);
	
	EXPECT_EQ(0,cs.enemyBlock);
	EXPECT_EQ(0,cs.enemyParry);
	EXPECT_EQ(0,cs.enemyEvade);
	EXPECT_EQ(0,cs.enemyResist);

	EXPECT_EQ(0,cs.enemyReflect);
	EXPECT_EQ(2,cs.enemyShield);
	
	/*
2014.07.10 10:58:35 : Chief of Staff Moriata blocked Duckan's attack with the protective shield effect. 
2014.07.10 10:58:35 : Duckan inflicted 374 damage on Chief of Staff Moriata by using Aerial Shot III. 
2014.07.10 10:58:35 : Chief of Staff Moriata blocked Duckan's attack with the protective shield effect. 
2014.07.10 10:58:35 : Chief of Staff Moriata's MP was reduced by 0 because Duckan used Aerial Shot III. 

2014.07.10 10:58:36 : Chief of Staff Moriata blocked Duckan's attack with the protective shield effect. 
2014.07.10 10:58:36 : Duckan inflicted 374 damage on Chief of Staff Moriata by using Aerial Shot III. 
2014.07.10 10:58:36 : Chief of Staff Moriata blocked Duckan's attack with the protective shield effect. 
2014.07.10 10:58:36 : Chief of Staff Moriata's MP was reduced by 0 because Duckan used Aerial Shot III. 
*/
}

TEST(AutoAttackBuffer, shield3){
	CombatStatsManager combatStatsManager;
	WeaponSwitch weaponSwitch;

	queue<Attack> attacks;
	AutoAttackBuffer aab(combatStatsManager, weaponSwitch, attacks);
	CombatStats& cs = combatStatsManager.getAllTargetsCombatStats().first;

	aab.enemyShielded("David Tam");
	aab.makeAutoAttack(79, "David Tam", false);
	aab.enemyShielded("David Tam");
	aab.makeAutoAttack(52, "David Tam", false);
	aab.stopAutoAttack();	
	aab.enemyShielded("David Tam");
	aab.makeSkillAttack(246, "David Tam", "Hot Shot III", false);
	//aab.enemyShielded("David Tam");
	//aab.stopAutoAttack();	
	//aab.enemyShielded("David Tam");
	//aab.stopAutoAttack();
	
	EXPECT_EQ(2,cs.numHits);
	EXPECT_EQ(0,cs.numCrits);
	
	EXPECT_EQ(0,cs.enemyBlock);
	EXPECT_EQ(0,cs.enemyParry);
	EXPECT_EQ(0,cs.enemyEvade);
	EXPECT_EQ(0,cs.enemyResist);

	EXPECT_EQ(0,cs.enemyReflect);
	EXPECT_EQ(2,cs.enemyShield);

	EXPECT_EQ(1,cs.multiStrikes[0]);
	EXPECT_EQ(0,cs.multiStrikes[1]);
	EXPECT_EQ(0,cs.multiStrikes[2]);
	EXPECT_EQ(0,cs.multiStrikes[3]);

	EXPECT_EQ(1,cs.multiStrikes2[0]);
	EXPECT_EQ(0,cs.multiStrikes2[1]);
	EXPECT_EQ(0,cs.multiStrikes2[2]);
	EXPECT_EQ(0,cs.multiStrikes2[3]);
	/*
2014.06.21 11:15:05 : You blocked ChickenSlayer's attack with the protective shield effect. 
2014.06.21 11:15:05 : You received 79 damage from ChickenSlayer. 
2014.06.21 11:15:05 : You blocked ChickenSlayer's attack with the protective shield effect. 
2014.06.21 11:15:05 : You received 52 damage from ChickenSlayer. 
2014.06.21 11:15:06 : You blocked ChickenSlayer's attack with the protective shield effect. 
2014.06.21 11:15:06 : ChickenSlayer has inflicted 246 damage on you by using Hot Shot III. 
2014.06.21 11:15:06 : You blocked ChickenSlayer's attack with the protective shield effect. 
2014.06.21 11:15:06 : ChickenSlayer has weakened Momomomoo's Fire Resist by using Hot Shot III. 
2014.06.21 11:15:06 : You blocked ChickenSlayer's attack with the protective shield effect. 
2014.06.21 11:15:06 : Your attack speed has decreased because ChickenSlayer used Hot Shot III. 
*/
}

TEST(AutoAttackBuffer, shield4){
	CombatStatsManager combatStatsManager;
	WeaponSwitch weaponSwitch;

	queue<Attack> attacks;
	AutoAttackBuffer aab(combatStatsManager, weaponSwitch, attacks);
	CombatStats& cs = combatStatsManager.getAllTargetsCombatStats().first;

	aab.enemyShielded("xKyonx");
	aab.makeAutoAttack(220, "xKyonx", false);
	aab.enemyShielded("xKyonx");
	aab.makeAutoAttack(212, "xKyonx", false);
	aab.makeAutoAttack(42, "xKyonx", false);
	//aab.stopAutoAttack();
	aab.enemyShielded("xKyonx");
	aab.makeSkillAttack(300, "xKyonx", "Soul Slash VI", true);
	
	aab.enemyShielded("xKyonx");
	aab.makeAutoAttack(196, "xKyonx", false);
	aab.enemyShielded("xKyonx");
	aab.makeAutoAttack(205, "xKyonx", false);
	aab.enemyShielded("xKyonx");
	aab.makeSkillAttack(161, "xKyonx", "Fang Strike V", false);
	aab.enemyShielded("xKyonx");
	aab.makeSkillAttack(131, "xKyonx", "Beast Kick IV", false);
	//aab.stopAutoAttack();

	aab.enemyShielded("xKyonx");
	aab.makeAutoAttack(62, "xKyonx", false);
	aab.enemyShielded("xKyonx");
	aab.makeAutoAttack(49, "xKyonx", false);
	aab.makeAutoAttack(12, "xKyonx", false);
	aab.stopAutoAttack();

	EXPECT_EQ(6,cs.numHits);
	EXPECT_EQ(1,cs.numCrits);
	
	EXPECT_EQ(0,cs.enemyBlock);
	EXPECT_EQ(0,cs.enemyParry);
	EXPECT_EQ(0,cs.enemyEvade);
	EXPECT_EQ(0,cs.enemyResist);

	EXPECT_EQ(0,cs.enemyReflect);
	EXPECT_EQ(6,cs.enemyShield);
		
	/*
	EXPECT_EQ(2,cs.multiStrikes[0]);
	EXPECT_EQ(1,cs.multiStrikes[1]);
	EXPECT_EQ(0,cs.multiStrikes[2]);
	EXPECT_EQ(0,cs.multiStrikes[3]);

	EXPECT_EQ(2,cs.multiStrikes2[0]);
	EXPECT_EQ(1,cs.multiStrikes2[1]);
	EXPECT_EQ(0,cs.multiStrikes2[2]);
	EXPECT_EQ(0,cs.multiStrikes2[3]);
	*/
/*
2014.08.09 22:57:53 : xKyonx blocked Poolz's attack with the protective shield effect. 
2014.08.09 22:57:53 : Poolz inflicted 220 damage on xKyonx. 
2014.08.09 22:57:53 : xKyonx blocked Poolz's attack with the protective shield effect. 
2014.08.09 22:57:53 : Poolz inflicted 212 damage on xKyonx. 
2014.08.09 22:57:53 : Poolz inflicted 42 damage on xKyonx. 
2014.08.09 22:57:53 : xKyonx blocked Poolz's attack with the protective shield effect. 
2014.08.09 22:57:53 : Critical Hit!Poolz inflicted 445 damage on xKyonx by using Soul Slash VI. 
2014.08.09 22:57:54 : xKyonx blocked Poolz's attack with the protective shield effect. 
2014.08.09 22:57:54 : Poolz inflicted 196 damage on xKyonx. 
2014.08.09 22:57:54 : xKyonx blocked Poolz's attack with the protective shield effect. 
2014.08.09 22:57:54 : Poolz inflicted 205 damage on xKyonx. 
2014.08.09 22:57:54 : xKyonx blocked Poolz's attack with the protective shield effect. 
2014.08.09 22:57:54 : Poolz inflicted 161 damage and the rune carve effect on xKyonx by using Fang Strike V. 
2014.08.09 22:57:55 : xKyonx blocked Poolz's attack with the protective shield effect. 
2014.08.09 22:57:55 : Poolz inflicted 131 damage and the rune carve effect on xKyonx by using Beast Kick IV. 
2014.08.09 22:57:55 : xKyonx blocked Poolz's attack with the protective shield effect. 

2014.08.09 22:58:03 : xKyonx blocked Poolz's attack with the protective shield effect. 
2014.08.09 22:58:03 : Poolz inflicted 62 damage on xKyonx. 
2014.08.09 22:58:03 : xKyonx blocked Poolz's attack with the protective shield effect. 
2014.08.09 22:58:03 : Poolz inflicted 49 damage on xKyonx. 
2014.08.09 22:58:03 : Poolz inflicted 12 damage on xKyonx. 
*/
}

TEST(AutoAttackBuffer, shield5){
	CombatStatsManager combatStatsManager;
	WeaponSwitch weaponSwitch;

	queue<Attack> attacks;
	AutoAttackBuffer aab(combatStatsManager, weaponSwitch, attacks);
	CombatStats& cs = combatStatsManager.getAllTargetsCombatStats().first;

	aab.enemyShielded("Chief of Staff Moriata");
	aab.makeAutoAttack(73, "Chief of Staff Moriata", false); 	
	aab.makeAutoAttack(51, "Chief of Staff Moriata", false); 	
	aab.enemyShielded("Chief of Staff Moriata");
	aab.makeSkillAttack(227, "Chief of Staff Moriata", "Ferocious Strike VI", true);

	

	EXPECT_EQ(2,cs.numHits);
	EXPECT_EQ(1,cs.numCrits);
	
	EXPECT_EQ(0,cs.enemyBlock);
	EXPECT_EQ(0,cs.enemyParry);
	EXPECT_EQ(0,cs.enemyEvade);
	EXPECT_EQ(0,cs.enemyResist);

	EXPECT_EQ(0,cs.enemyReflect);
	EXPECT_EQ(2,cs.enemyShield);

	EXPECT_EQ(0,cs.multiStrikes[0]);
	EXPECT_EQ(1,cs.multiStrikes[1]);
	EXPECT_EQ(0,cs.multiStrikes[2]);
	EXPECT_EQ(0,cs.multiStrikes[3]);

	/*
2014.06.21 15:50:31 : The attack was blocked by the protective shield effect cast on Chief of Staff Moriata. 
2014.06.21 15:50:31 : You inflicted 73 damage on Chief of Staff Moriata. 
2014.06.21 15:50:31 : You inflicted 51 damage on Chief of Staff Moriata. 
2014.06.21 15:50:31 : The attack was blocked by the protective shield effect cast on Chief of Staff Moriata. 
2014.06.21 15:50:31 : Critical Hit!You inflicted 227 damage on Chief of Staff Moriata by using Ferocious Strike VI.
*/
}


TEST(AutoAttackBuffer, BlockTest){
	CombatStatsManager combatStatsManager;
	WeaponSwitch weaponSwitch;

	queue<Attack> attacks;
	AutoAttackBuffer aab(combatStatsManager, weaponSwitch, attacks);
	CombatStats& cs = combatStatsManager.getAllTargetsCombatStats().first;

	aab.enemyBlocked("Emeyno");
	aab.enemyShielded("Emeyno");
	aab.enemyShielded("Emeyno");
	aab.makeSkillAttack(0, "Emeyno", "Absorbing Fury V", false);
	aab.enemyBlocked("Emeyno");
	aab.enemyShielded("Emeyno");
	aab.makeSkillAttack(0, "Emeyno", "Shock Wave IV", false);

	EXPECT_EQ(2,cs.numHits);
	EXPECT_EQ(0,cs.numCrits);
	
	EXPECT_EQ(2,cs.enemyBlock);
	EXPECT_EQ(0,cs.enemyParry);
	EXPECT_EQ(0,cs.enemyEvade);
	EXPECT_EQ(0,cs.enemyResist);

	EXPECT_EQ(0,cs.enemyReflect);
	EXPECT_EQ(2,cs.enemyShield);

	EXPECT_EQ(0,cs.multiStrikes[0]);
	EXPECT_EQ(0,cs.multiStrikes[1]);
	EXPECT_EQ(0,cs.multiStrikes[2]);
	EXPECT_EQ(0,cs.multiStrikes[3]);
	/*
2014.06.21 10:32:19 : Emeyno blocked Cutkopi's attack. 
2014.06.21 10:32:19 : Emeyno blocked Cutkopi's attack with the protective shield effect. 
2014.06.21 10:32:19 : Emeyno blocked Cutkopi's attack with the protective shield effect. 
2014.06.21 10:32:19 : Cutkopi inflicted 0 damage on Emeyno by using Absorbing Fury V. 
2014.06.21 10:32:20 : Emeyno blocked Cutkopi's attack. 
2014.06.21 10:32:20 : Emeyno blocked Cutkopi's attack with the protective shield effect. 
2014.06.21 10:32:20 : Cutkopi inflicted 0 damage on Emeyno by using Shock Wave IV. 
*/

}

TEST(AutoAttackBuffer, BlockNormalAttack){
	CombatStatsManager combatStatsManager;
	WeaponSwitch weaponSwitch;

	queue<Attack> attacks;
	AutoAttackBuffer aab(combatStatsManager, weaponSwitch, attacks);
	CombatStats& cs = combatStatsManager.getAllTargetsCombatStats().first;

	aab.enemyBlocked("Zadra Spellweaver");
	aab.makeAutoAttack(781, "Zadra Spellweaver", false);
	aab.enemyBlocked("Zadra Spellweaver");
	aab.makeAutoAttack(78, "Zadra Spellweaver", false);
	aab.enemyBlocked("Zadra Spellweaver");
	aab.makeAutoAttack(78, "Zadra Spellweaver", false);
	aab.stopAutoAttack();

	EXPECT_EQ(1,cs.numHits);
	EXPECT_EQ(0,cs.numCrits);
	
	EXPECT_EQ(1,cs.enemyBlock);
	EXPECT_EQ(0,cs.enemyParry);
	EXPECT_EQ(0,cs.enemyEvade);
	EXPECT_EQ(0,cs.enemyResist);

	EXPECT_EQ(0,cs.enemyReflect);
	EXPECT_EQ(0,cs.enemyShield);

	EXPECT_EQ(0,cs.multiStrikes[0]);
	EXPECT_EQ(0,cs.multiStrikes[1]);
	EXPECT_EQ(1,cs.multiStrikes[2]);
	EXPECT_EQ(0,cs.multiStrikes[3]);
	/*
2014.10.19 00:03:20 : Zadra Spellweaver blocked the attack. 
2014.10.19 00:03:20 : You inflicted 781 damage on Zadra Spellweaver. 
2014.10.19 00:03:20 : Zadra Spellweaver blocked the attack. 
2014.10.19 00:03:20 : You inflicted 78 damage on Zadra Spellweaver. 
2014.10.19 00:03:20 : Zadra Spellweaver blocked the attack. 
2014.10.19 00:03:20 : You inflicted 78 damage on Zadra Spellweaver. 
*/
}

TEST(AutoAttackBuffer, BlockNormalAndSkill){
	CombatStatsManager combatStatsManager;
	WeaponSwitch weaponSwitch;

	queue<Attack> attacks;
	AutoAttackBuffer aab(combatStatsManager, weaponSwitch, attacks);
	CombatStats& cs = combatStatsManager.getAllTargetsCombatStats().first;

	aab.enemyBlocked("Enraged Krotan Lord");
	aab.makeAutoAttack(1363, "Enraged Krotan Lord", true);
	aab.enemyBlocked("Enraged Krotan Lord");
	aab.makeAutoAttack(136, "Enraged Krotan Lord", false);
	aab.enemyBlocked("Enraged Krotan Lord");
	aab.makeSkillAttack(1200, "Enraged Krotan Lord", "Provoking Severe Blow V", false);
	aab.enemyBlocked("Enraged Krotan Lord");
	aab.stopAutoAttack();

	EXPECT_EQ(2,cs.numHits);
	EXPECT_EQ(1,cs.numCrits);
	
	EXPECT_EQ(2,cs.enemyBlock);
	EXPECT_EQ(0,cs.enemyParry);
	EXPECT_EQ(0,cs.enemyEvade);
	EXPECT_EQ(0,cs.enemyResist);

	EXPECT_EQ(0,cs.enemyReflect);
	EXPECT_EQ(0,cs.enemyShield);

	EXPECT_EQ(0,cs.multiStrikes[0]);
	EXPECT_EQ(1,cs.multiStrikes[1]);
	EXPECT_EQ(0,cs.multiStrikes[2]);
	EXPECT_EQ(0,cs.multiStrikes[3]);
	/*
2014.09.17 00:14:02 : Enraged Krotan Lord blocked the attack. 
2014.09.17 00:14:02 : Critical Hit! You inflicted 1,363 critical damage on Enraged Krotan Lord. 
2014.09.17 00:14:02 : Enraged Krotan Lord blocked the attack. 
2014.09.17 00:14:02 : You inflicted 136 damage on Enraged Krotan Lord. 
2014.09.17 00:14:02 : Enraged Krotan Lord blocked the attack. 
2014.09.17 00:14:02 : You inflicted 1,200 damage on Enraged Krotan Lord by using Provoking Severe Blow V. 
2014.09.17 00:14:02 : Enraged Krotan Lord blocked the attack. 
*/
}

TEST(AutoAttackBuffer, ParryNormalAttack){
	CombatStatsManager combatStatsManager;
	WeaponSwitch weaponSwitch;

	queue<Attack> attacks;
	AutoAttackBuffer aab(combatStatsManager, weaponSwitch, attacks);
	CombatStats& cs = combatStatsManager.getAllTargetsCombatStats().first;

	aab.makeAutoAttack(550, "Unstable Kaluva the Fourth", false);
	aab.makeAutoAttack(55, "Unstable Kaluva the Fourth", false);
	aab.stopAutoAttack();

	aab.enemyParried("Unstable Kaluva the Fourth");
	aab.makeAutoAttack(416, "Unstable Kaluva the Fourth", false);
	aab.enemyParried("Unstable Kaluva the Fourth");
	aab.makeAutoAttack(41, "Unstable Kaluva the Fourth", false);
	aab.stopAutoAttack();

	EXPECT_EQ(2,cs.numHits);
	EXPECT_EQ(0,cs.numCrits);
	
	EXPECT_EQ(0,cs.enemyBlock);
	EXPECT_EQ(1,cs.enemyParry);
	EXPECT_EQ(0,cs.enemyEvade);
	EXPECT_EQ(0,cs.enemyResist);

	EXPECT_EQ(0,cs.enemyReflect);
	EXPECT_EQ(0,cs.enemyShield);

	EXPECT_EQ(0,cs.multiStrikes[0]);
	EXPECT_EQ(2,cs.multiStrikes[1]);
	EXPECT_EQ(0,cs.multiStrikes[2]);
	EXPECT_EQ(0,cs.multiStrikes[3]);
/*
2014.09.01 18:29:09 : You inflicted 550 damage on Unstable Kaluva the Fourth. 
2014.09.01 18:29:09 : You inflicted 55 damage on Unstable Kaluva the Fourth. 
2014.09.01 18:29:10 : Unstable Kaluva the Fourth received 1,243 damage due to the effect of Flame Cage V. 
2014.09.01 18:29:10 : nasvara inflicted 2,827 damage on Unstable Kaluva the Fourth by using Crosstrigger IV. 
2014.09.01 18:29:10 : Unstable Kaluva the Fourth's MP was reduced by 0 because nasvara used Crosstrigger IV. 
2014.09.01 18:29:10 : Blindness has been activated. 
2014.09.01 18:29:10 : Unstable Kaluva the Fourth parried the attack. 
2014.09.01 18:29:10 : You inflicted 416 damage on Unstable Kaluva the Fourth. 
2014.09.01 18:29:10 : Unstable Kaluva the Fourth parried the attack. 
2014.09.01 18:29:10 : You inflicted 41 damage on Unstable Kaluva the Fourth. 
*/
}

TEST(AutoAttackBuffer, ParryNormalAttack2){

	CombatStatsManager combatStatsManager;
	WeaponSwitch weaponSwitch;

	queue<Attack> attacks;
	AutoAttackBuffer aab(combatStatsManager, weaponSwitch, attacks);
	CombatStats& cs = combatStatsManager.getAllTargetsCombatStats().first;



	aab.enemyParried("1s36C7DF");
	aab.makeAutoAttack(52, "1s36C7DF", false);
	aab.enemyParried("1s36C7DF");
	aab.makeAutoAttack(5, "1s36C7DF", false);
	aab.stopAutoAttack();	

	EXPECT_EQ(1, attacks.size());

	Attack attack = attacks.front();
	EXPECT_EQ("", attack.user);
	EXPECT_EQ("1s36C7DF", attack.target);
	EXPECT_EQ("", attack.skill);
	EXPECT_EQ(52, attack.mainhandDamage);
	EXPECT_EQ(-1, attack.offhandDamage);
	EXPECT_EQ(1, attack.numMainhandMultiStrikes);
	EXPECT_EQ(0, attack.numOffhandMultiStrikes);
	EXPECT_FALSE(attack.blocked);
	EXPECT_FALSE(attack.critical);
	EXPECT_TRUE(attack.parried);
	EXPECT_FALSE(attack.shielded);
	EXPECT_FALSE(attack.reflected);
/*
2017.11.18 12:16:40 : 1s36C7DF parried the attack. 
2017.11.18 12:16:40 : You inflicted 52 damage on 1s36C7DF. 
2017.11.18 12:16:40 : 1s36C7DF parried the attack. 
2017.11.18 12:16:40 : You inflicted 5 damage on 1s36C7DF. 
*/
}

/*
TEST(AutoAttackBuffer, resist){
	AutoAttackBuffer aab;
	CombatStats cs;
	aab.setCombatStats(cs);

	EXPECT_TRUE(false);
/*
2014.06.28 09:48:06 : BabyHealMe resisted Infernal Blaze I. 
2014.06.28 09:48:06 : You recovered 123 HP by using Light of Rejuvenation V. 
2014.06.28 09:48:07 : Critical Hit!Horatia has inflicted 550 damage on you by using Doom Lure I. 
2014.06.28 09:48:07 : BabyHealMe recovered 1,927 HP by using Light of Recovery III. 
2014.06.28 09:48:07 : Withmilk is in the boost skill state after using Stopping Power. 
2014.06.28 09:48:07 : Withmilk is in the boost PvP Attack state because Withmilk used Stopping Power. 
2014.06.28 09:48:07 : BabyHealMe resisted Blackburrow's Chastise III. 
2014.06.28 09:48:07 : Critical Hit! You inflicted 536 critical damage on BabyHealMe. 
2014.06.28 09:48:07 : You inflicted 53 damage on BabyHealMe. 
2014.06.28 09:48:07 : Critical Hit!You inflicted 719 damage on BabyHealMe by using Hallowed Strike VI. 

}
*/


TEST(AutoAttackBuffer, nonBlockSkillFollowingBlockedAutoAttack){
	CombatStatsManager combatStatsManager;
	WeaponSwitch weaponSwitch;

	queue<Attack> attacks;
	AutoAttackBuffer aab(combatStatsManager, weaponSwitch, attacks);
	CombatStats& cs = combatStatsManager.getAllTargetsCombatStats().first;

	aab.enemyBlocked("1s16BE07");
	aab.makeAutoAttack(55, "1s16BE07", false);	
	aab.stopAutoAttack();
	
	aab.makeSkillAttack(1201, "1s16BE07", "Sure Strike", false);
	
	aab.stopAutoAttack();

	Attack attack = attacks.front();
	EXPECT_EQ("", attack.user);
	EXPECT_EQ("1s16BE07", attack.target);
	EXPECT_EQ("", attack.skill);
	EXPECT_EQ(55, attack.mainhandDamage);
	EXPECT_EQ(-1, attack.offhandDamage);
	EXPECT_EQ(0, attack.numMainhandMultiStrikes);
	EXPECT_EQ(0, attack.numOffhandMultiStrikes);
	EXPECT_TRUE(attack.blocked);
	EXPECT_FALSE(attack.critical);
	EXPECT_FALSE(attack.parried);
	EXPECT_FALSE(attack.shielded);
	EXPECT_FALSE(attack.reflected);

	attacks.pop();
	attack = attacks.front();
	EXPECT_EQ("", attack.user);
	EXPECT_EQ("1s16BE07", attack.target);
	EXPECT_EQ("Sure Strike", attack.skill);
	EXPECT_EQ(1201, attack.mainhandDamage);
	EXPECT_EQ(-1, attack.offhandDamage);
	EXPECT_EQ(0, attack.numMainhandMultiStrikes);
	EXPECT_EQ(0, attack.numOffhandMultiStrikes);
	EXPECT_FALSE(attack.blocked);
	EXPECT_FALSE(attack.critical);
	EXPECT_FALSE(attack.parried);
	EXPECT_FALSE(attack.shielded);
	EXPECT_FALSE(attack.reflected);

	EXPECT_EQ(2,cs.numHits);
	EXPECT_EQ(0,cs.numCrits);
	
	EXPECT_EQ(1,cs.enemyBlock);
	EXPECT_EQ(0,cs.enemyParry);
	EXPECT_EQ(0,cs.enemyEvade);
	EXPECT_EQ(0,cs.enemyResist);
/*
2017.11.16 15:54:55 : 1s16BE07 blocked the attack. 
2017.11.16 15:54:55 : You inflicted 55 damage on 1s16BE07. 
2017.11.16 15:54:55 : Expedition Trainee inflicted 2,244 damage on Training Dummy. 
2017.11.16 15:54:55 : You inflicted 1,201 damage on 1s16BE07 by using Sure Strike. 
*/
}

TEST(AutoAttackBuffer, nonBlockSkillFollowingBlockedAutoAttack2){
	CombatStatsManager combatStatsManager;
	WeaponSwitch weaponSwitch;

	queue<Attack> attacks;
	AutoAttackBuffer aab(combatStatsManager, weaponSwitch, attacks);
	CombatStats& cs = combatStatsManager.getAllTargetsCombatStats().first;

	aab.enemyBlocked("1s36C7DF");
	aab.makeSkillAttack(931, "1s36C7DF", "Break Power", false);
	aab.enemyBlocked("1s36C7DF");
	aab.debuffEnemy("Attack", "1s36C7DF", "Break Power", false);
	aab.stopAutoAttack();

	//aab.makeAutoAttack(55, "1s16BE07", false);	
	//aab.stopAutoAttack();
	
	aab.makeSkillAttack(992, "1s36C7DF", "Punishing Thrust", false);
	
	aab.stopAutoAttack();

	Attack attack = attacks.front();
	EXPECT_EQ("", attack.user);
	EXPECT_EQ("1s36C7DF", attack.target);
	EXPECT_EQ("Break Power", attack.skill);
	EXPECT_EQ(931, attack.mainhandDamage);
	EXPECT_EQ(-1, attack.offhandDamage);
	EXPECT_EQ(0, attack.numMainhandMultiStrikes);
	EXPECT_EQ(0, attack.numOffhandMultiStrikes);
	EXPECT_TRUE(attack.blocked);
	EXPECT_FALSE(attack.critical);
	EXPECT_FALSE(attack.parried);
	EXPECT_FALSE(attack.shielded);
	EXPECT_FALSE(attack.reflected);

	attacks.pop();
	attack = attacks.front();
	EXPECT_EQ("", attack.user);
	EXPECT_EQ("1s36C7DF", attack.target);
	EXPECT_EQ("Punishing Thrust", attack.skill);
	EXPECT_EQ(992, attack.mainhandDamage);
	EXPECT_EQ(-1, attack.offhandDamage);
	EXPECT_EQ(0, attack.numMainhandMultiStrikes);
	EXPECT_EQ(0, attack.numOffhandMultiStrikes);
	EXPECT_FALSE(attack.blocked);
	EXPECT_FALSE(attack.critical);
	EXPECT_FALSE(attack.parried);
	EXPECT_FALSE(attack.shielded);
	EXPECT_FALSE(attack.reflected);

	EXPECT_EQ(2,cs.numHits);
	EXPECT_EQ(0,cs.numCrits);
	
	EXPECT_EQ(1,cs.enemyBlock);
	EXPECT_EQ(0,cs.enemyParry);
	EXPECT_EQ(0,cs.enemyEvade);
	EXPECT_EQ(0,cs.enemyResist);

	EXPECT_EQ(931,cs.skillDamageStats.at("Break Power").blocks.totalDamage);
	EXPECT_EQ(992,cs.skillDamageStats.at("Punishing Thrust").normals.totalDamage);
	/*
2017.11.16 18:57:39 : 1s36C7DF blocked the attack. 
2017.11.16 18:57:39 : You inflicted 931 damage on 1s36C7DF by using Break Power. 
2017.11.16 18:57:39 : 1s36C7DF blocked the attack. 
2017.11.16 18:57:39 : 1s16BE07 has weakened 1s36C7DF's Attack by using Break Power. 
2017.11.16 18:57:39 : Expedition Trainee inflicted 2,313 damage on Training Dummy. 
2017.11.16 18:57:39 : 1s36C7DF is no longer shocked.  

2017.11.16 18:58:43 : You inflicted 992 damage on 1s36C7DF by using Punishing Thrust. 
*/
}

