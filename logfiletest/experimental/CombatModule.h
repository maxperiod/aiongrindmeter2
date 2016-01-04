
#include "../experimental/AutoAttackBuffer.h"
#include "../experimental/WeaponSwitch.h"

#include "../parser/SkillToClassMap.h"

#include "../Module.h"


class CombatModule: public Module{
public:
	WeaponSwitch weaponSwitch;
	CombatStatsManager combatStatsManager;

	CombatModule();
	
	void executeChatLogCommand(ChatLogCommand& command);

	void endOfTickAction();

private:
	AutoAttackBuffer autoAttackBuffer;//(&weaponSwitch);

};