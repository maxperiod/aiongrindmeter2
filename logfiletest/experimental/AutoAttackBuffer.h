//#include <list>
#include <string>
#include "WeaponSwitch.h"
#include "CombatStatsManager.h"
#include "WeaponSwitch.h"

#include "Attack.h"
#include <queue>

using namespace std;

class AutoAttackBuffer{
public:
	AutoAttackBuffer(CombatStatsManager& combatStatsManager, WeaponSwitch& weaponSwitch, queue<Attack>& attacks); 
	  
	
	//void setCombatStats(CombatStats& combatStats) {cs[0] = &combatStats;}
	//void setIndividualCombatStats(unordered_map<string, CombatStats>& combatStatsByTarget) {csByTarget = &combatStatsByTarget;}

	void makeAutoAttack(int damage, const string &target, bool critical);

	void makeSkillAttack(int damage, const string &target, const string &skill, bool critical);

	void debuffEnemy(string debuff, const string &target, const string &skill, bool critical);

	void enemyBlocked(const string &target);
	void enemyParried(const string &target);
	void enemyShielded(const string &target);
	void enemyReflected(const string &target);	
	
	void enemyEvaded(const string &target);
	void enemyEvaded(const string &target, const string &skill);

	void enemyResisted(const string &target);
	void enemyResisted(const string &target, const string &skill);

	void stopAutoAttack();

	void applyBufferToCounter(bool isSkill);

	void resetBuffer();
	void endOfTick();

private:
	CombatStatsManager& combatStatsManager;
	WeaponSwitch& weaponSwitch;
	queue<Attack>& attacks;

	int damageBuffer;
	int numWeapons;
	
	bool critical;
	bool blocked;
	bool parried;
	   
	bool shielded;
	bool reflected;
	
	int autoAttackBaseDmg;
	int autoAttackBaseDmg2;

	int lastDamage;
	int lastDamage2;

	int multiStrike;
	int multiStrike2;

	bool lastActionIsAutoAttack;

	bool nextAttackLineIsBlocked;
	bool nextAttackLineIsParried;

	int idleTicks;
	//WeaponSwitch* ws;
	//CombatStats* cs;
	//CombatStats* combatStats[2];
	//unordered_map<string, CombatStats>* csByTarget;

	
	//list<Attack> attacks;
	string lastTarget;
	string skill;

	void createAttackObject();

	void nonDamageEffect(const string& target);

	CombatStats& getAllTargetsCombatStatsForCurrentWeaponSet();
	CombatStats& getIndividualTargetCombatStatsForCurrentWeaponSet(const string& target);

	bool isValidPlayerSkill(const string& skill);
};