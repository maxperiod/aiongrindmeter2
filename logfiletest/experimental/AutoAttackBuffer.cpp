#include "AutoAttackBuffer.h"
#include "../language/LanguageManager.h"

AutoAttackBuffer::AutoAttackBuffer(CombatStatsManager& combatStatsManager, WeaponSwitch& weaponSwitch): 
	combatStatsManager(combatStatsManager), 
	weaponSwitch(weaponSwitch),
	numWeapons(0), 
	idleTicks(0), 
	lastActionIsAutoAttack(false)
{
	resetBuffer();
}

void AutoAttackBuffer::makeAutoAttack(int damage, const string &target, bool critical){			

	if (target != lastTarget) stopAutoAttack();		
					
	// auto attack bonus hits (1/10th of main auto attack)
	
	if ((lastDamage / 10 == damage || (lastDamage < 10 && lastDamage > 1 && damage == 1))&& lastActionIsAutoAttack && !critical){
		multiStrike ++;
	}
	else if ((lastDamage2 / 10 == damage || (lastDamage2 < 10 && lastDamage2 > 1 && damage == 1)) && lastActionIsAutoAttack && !critical){
		multiStrike2 ++;
	}
		
	// protective shield
	else if (shielded && lastDamage * 1.33 > damage && lastActionIsAutoAttack && !critical){
		multiStrike ++;
	}
	else if (shielded && lastDamage2 * 1.33 > damage && lastActionIsAutoAttack && !critical){
		multiStrike2 ++;
	}
		
	// Start of auto attack
	else {			
		if (multiStrike > 0 || numWeapons >= 2) stopAutoAttack();
		numWeapons ++;

		//if (numWeapons == 1) autoAttackBaseDmg = damage;
		//else if (numWeapons == 2) autoAttackBaseDmg2 = damage;

		if (numWeapons == 1){
			autoAttackBaseDmg = damage;
			lastDamage = damage;
		}
		else if (numWeapons == 2){
			autoAttackBaseDmg2 = damage;
			lastDamage2 = damage;
		}
		
	}

	if (critical) this->critical = true;
		
	damageBuffer += damage;
	lastTarget = target;		

	lastActionIsAutoAttack = true;
	idleTicks = 0;
}	

void AutoAttackBuffer::makeSkillAttack(int damage, const string &target, const string &skill, bool critical){
		
	bool currentlyBlocked = blocked;
	bool currentlyParried = parried;

	stopAutoAttack();
	
	this->skill = skill;
	combatStatsManager.setLastTarget(lastTarget);

	blocked = currentlyBlocked;
	parried = currentlyParried;

	if (critical) this->critical = true;
	damageBuffer += damage;
	lastTarget = target;

	numWeapons += 1;
	autoAttackBaseDmg += damage;

	applyBufferToCounter(true);
		
	lastActionIsAutoAttack = false;
}

void AutoAttackBuffer::enemyBlocked(const string &target){	
	//nonDamageEffect(target);		
	blocked = true;
}
void AutoAttackBuffer::enemyParried(const string &target){
	//nonDamageEffect(target);
	parried = true;
}
void AutoAttackBuffer::enemyShielded(const string &target){
	nonDamageEffect(target);
	shielded = true;
}
void AutoAttackBuffer::enemyReflected(const string &target){
	nonDamageEffect(target);
	reflected = true;
}
	
void AutoAttackBuffer::enemyEvaded(const string &target){
	stopAutoAttack();
	CombatStats& allTargetsCombatStats = getAllTargetsCombatStatsForCurrentWeaponSet();
	CombatStats& individualTargetCombatStats = getIndividualTargetCombatStatsForCurrentWeaponSet(target);
	allTargetsCombatStats.enemyEvade ++;
	individualTargetCombatStats.enemyEvade ++;

	allTargetsCombatStats.autoDamageStats1.numResists ++;
	individualTargetCombatStats.autoDamageStats1.numResists ++;
}
void AutoAttackBuffer::enemyEvaded(const string &target, const string &skill){
	stopAutoAttack();
	if (isValidPlayerSkill(skill)){
		CombatStats& allTargetsCombatStats = getAllTargetsCombatStatsForCurrentWeaponSet();
		CombatStats& individualTargetCombatStats = getIndividualTargetCombatStatsForCurrentWeaponSet(target);
		allTargetsCombatStats.enemyEvade ++;
		individualTargetCombatStats.enemyEvade ++;

		allTargetsCombatStats.skillDamageStats[skill].numResists ++;
		individualTargetCombatStats.skillDamageStats[skill].numResists ++;
	}
}

void AutoAttackBuffer::enemyResisted(const string &target){
	stopAutoAttack();
	CombatStats& allTargetsCombatStats = getAllTargetsCombatStatsForCurrentWeaponSet();
	CombatStats& individualTargetCombatStats = getIndividualTargetCombatStatsForCurrentWeaponSet(target);
	allTargetsCombatStats.enemyResist ++;
	individualTargetCombatStats.enemyResist ++;

	allTargetsCombatStats.autoDamageStats1.numResists ++;
	individualTargetCombatStats.autoDamageStats1.numResists;
}
void AutoAttackBuffer::enemyResisted(const string &target, const string &skill){
	stopAutoAttack();
	if (isValidPlayerSkill(skill)){
		CombatStats& allTargetsCombatStats = getAllTargetsCombatStatsForCurrentWeaponSet();
		CombatStats& individualTargetCombatStats = getIndividualTargetCombatStatsForCurrentWeaponSet(target);
		allTargetsCombatStats.enemyResist ++;
		individualTargetCombatStats.enemyResist ++;
		allTargetsCombatStats.skillDamageStats[skill].numResists ++;
		individualTargetCombatStats.skillDamageStats[skill].numResists ++;
	}
}


void AutoAttackBuffer::stopAutoAttack(){
	if (numWeapons > 0){			
		applyBufferToCounter(false);
	}
}


void AutoAttackBuffer::applyBufferToCounter(bool isSkill){
	combatStatsManager.setLastTarget(lastTarget);

	CombatStats* cs[2];	

	if (weaponSwitch.getCurrentSet() == 0){
		cs[0] = &combatStatsManager.getAllTargetsCombatStats().first;
		cs[1] = &combatStatsManager.getIndividualTargetCombatStats(lastTarget).first;
	}
	else {
		cs[0] = &combatStatsManager.getAllTargetsCombatStats().second;
		cs[1] = &combatStatsManager.getIndividualTargetCombatStats(lastTarget).second;
	}

	// 0: combat stats for all targets
	// 1: combat stats for specified target (lastTarget)
	for (int i = 0; i < 2; i ++){	
		cs[i]->numHits ++;
		if (critical) cs[i]->numCrits ++;
		if (blocked) cs[i]->enemyBlock ++;
		if (parried) cs[i]->enemyParry ++;
		if (shielded) cs[i]->enemyShield ++;
		if (reflected) cs[i]->enemyReflect ++;
		cs[i]->totalDamageInflicted += damageBuffer;
		
		if (!isSkill){
			cs[i]->multiStrikes[multiStrike] ++;
			if (numWeapons == 2) cs[i]->multiStrikes2[multiStrike2] ++;
		}
		else {
			cs[i]->skillAttacks ++;
		}

		if (!shielded){
			int damage = autoAttackBaseDmg;
			
			for (int j = 0; j < numWeapons; j ++){
				SkillDamageStats* stats;
					
				if (isSkill){
					stats = &cs[i]->skillDamageStats[skill];
					//stats->numUses ++;
				}
				else{
					switch(j){
						case 0:
							stats = &cs[i]->autoDamageStats1;
							break;
						case 1:
							stats = &cs[i]->autoDamageStats2;
							damage = autoAttackBaseDmg2;
							break;
					}
				}
				stats->numUses ++;

				DamageStatEntry* damageStatEntry;
				if (critical){
					if (blocked){
						damageStatEntry = &stats->critBlocks;
					}
					else if (parried){
						damageStatEntry = &stats->critParrys;
					}
					else{
						damageStatEntry = &stats->crits;
					}
				}
				else {
					if (blocked){
						damageStatEntry = &stats->blocks;
					}
					else if (parried){
						damageStatEntry = &stats->parrys;
					}
					else{
						damageStatEntry = &stats->normals;
					}
				}
					
				damageStatEntry->totalDamage += damage;				
				damageStatEntry->numHits ++;
				if (damage > damageStatEntry->maxDamage){
					damageStatEntry->maxDamage = damage;
				}
				if (damage < damageStatEntry->minDamage || damageStatEntry->minDamage == 0)
					damageStatEntry->minDamage = damage;
			}

	
		}
		
	}
	resetBuffer();
}

void AutoAttackBuffer::resetBuffer(){
	damageBuffer = 0;
	numWeapons = 0;
	
	critical = false;
	blocked = false;
	parried = false;

	shielded = false;
	reflected = false;

	lastDamage = 0;
	lastDamage2 = 0;

	multiStrike = 0;
	multiStrike2 = 0;

	autoAttackBaseDmg = 0;
	autoAttackBaseDmg2 = 0;

	lastActionIsAutoAttack = false;
}

void AutoAttackBuffer::endOfTick(){
	idleTicks ++;
	if (idleTicks >= 2) stopAutoAttack();
}

// ========================================================================
// P R I V A T E   M E T H O D S
// ========================================================================

void AutoAttackBuffer::nonDamageEffect(const string& target){
	//if (target != lastTarget || numWeapons >= 2) stopAutoAttack();
	if (target != lastTarget || multiStrike > 0 || numWeapons >= 2) stopAutoAttack();
	lastActionIsAutoAttack = false;
	lastTarget = target;
}

CombatStats& AutoAttackBuffer::getAllTargetsCombatStatsForCurrentWeaponSet(){
	if (weaponSwitch.getCurrentSet() == 0){
		return combatStatsManager.getAllTargetsCombatStats().first;		
	}
	else {
		return combatStatsManager.getAllTargetsCombatStats().second;		
	}
}

CombatStats& AutoAttackBuffer::getIndividualTargetCombatStatsForCurrentWeaponSet(const string& target){
	if (weaponSwitch.getCurrentSet() == 0){		
		return combatStatsManager.getIndividualTargetCombatStats(target).first;
	}
	else {		
		return combatStatsManager.getIndividualTargetCombatStats(target).second;
	}
}

bool AutoAttackBuffer::isValidPlayerSkill(const string& skill){
	if (LANGUAGE_MANAGER.getCurrentLanguage().getSkillToClassMap().getClass(skill) != "")
		return true;
	else return false;
}