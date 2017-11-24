#include "CombatModule.h"
#include "../stringFunctions.h"


CombatModule::CombatModule(): autoAttackBuffer(combatStatsManager, weaponSwitch, attacks){
	DECLARE_CRITABLE_MESSAGE_RULE(STR_SKILL_SUCC_SkillATK_Instant_ME_TO_B);
	DECLARE_CRITABLE_MESSAGE_RULE(STR_SKILL_SUCC_CarveSignet_ME_TO_B);
	DECLARE_CRITABLE_MESSAGE_RULE(STR_SKILL_SUCC_DispelBuffCounterATK_ME_TO_B);
	
	DECLARE_CRITABLE_MESSAGE_RULE(STR_SKILL_SUCC_StatDown_ME_TO_B);


	DECLARE_CRITABLE_MESSAGE_RULE(STR_SKILL_SUCC_Blind_ME_TO_B);
	DECLARE_CRITABLE_MESSAGE_RULE(STR_SKILL_SUCC_Confuse_ME_TO_B);
	DECLARE_CRITABLE_MESSAGE_RULE(STR_SKILL_SUCC_Disease_ME_TO_B);
	DECLARE_CRITABLE_MESSAGE_RULE(STR_SKILL_SUCC_Fear_ME_TO_B);
	DECLARE_CRITABLE_MESSAGE_RULE(STR_SKILL_SUCC_Paralyze_ME_TO_B);
	DECLARE_CRITABLE_MESSAGE_RULE(STR_SKILL_SUCC_Root_ME_TO_B);
	DECLARE_CRITABLE_MESSAGE_RULE(STR_SKILL_SUCC_Silence_ME_TO_B);
	DECLARE_CRITABLE_MESSAGE_RULE(STR_SKILL_SUCC_Sleep_ME_TO_B);
	DECLARE_CRITABLE_MESSAGE_RULE(STR_SKILL_SUCC_Spin_ME_TO_B);
	DECLARE_CRITABLE_MESSAGE_RULE(STR_SKILL_SUCC_Stagger_ME_TO_B);
	DECLARE_CRITABLE_MESSAGE_RULE(STR_SKILL_SUCC_Stumble_ME_TO_B);
	DECLARE_CRITABLE_MESSAGE_RULE(STR_SKILL_SUCC_Stun_ME_TO_B);
	DECLARE_CRITABLE_MESSAGE_RULE(STR_SKILL_SUCC_Bind_ME_TO_B);
	DECLARE_CRITABLE_MESSAGE_RULE(STR_SKILL_SUCC_Bleed_ME_TO_B);
	DECLARE_CRITABLE_MESSAGE_RULE(STR_SKILL_SUCC_Curse_ME_TO_B);
	DECLARE_CRITABLE_MESSAGE_RULE(STR_SKILL_SUCC_NoFly_ME_TO_B);
	DECLARE_CRITABLE_MESSAGE_RULE(STR_SKILL_SUCC_OpenAerial_ME_TO_B);
	DECLARE_CRITABLE_MESSAGE_RULE(STR_SKILL_SUCC_Petrification_ME_TO_B);
	DECLARE_CRITABLE_MESSAGE_RULE(STR_SKILL_SUCC_Poison_ME_TO_B);
	DECLARE_CRITABLE_MESSAGE_RULE(STR_SKILL_SUCC_Slow_ME_TO_B);
	DECLARE_CRITABLE_MESSAGE_RULE(STR_SKILL_SUCC_Snare_ME_TO_B);
	DECLARE_CRITABLE_MESSAGE_RULE(STR_SKILL_SUCC_HostileUp_ME_TO_B);

	DECLARE_MESSAGE_RULE(STR_MSG_COMBAT_MY_CRITICAL);
	DECLARE_MESSAGE_RULE(STR_MSG_COMBAT_MY_ATTACK);
	DECLARE_MESSAGE_RULE(STR_MSG_COMBAT_BLOCK_ME_TO_B);
	DECLARE_MESSAGE_RULE(STR_MSG_COMBAT_PARRY_ME_TO_B);
	DECLARE_MESSAGE_RULE(STR_MSG_COMBAT_DODGED_ME_TO_B);
	DECLARE_MESSAGE_RULE(STR_SKILL_DODGED_ME_TO_B);
	DECLARE_MESSAGE_RULE(STR_SKILL_SUCC_Shield_PROTECT_ME_to_B);
	DECLARE_MESSAGE_RULE(STR_SKILL_SUCC_Reflector_PROTECT_ME_to_B);
	DECLARE_MESSAGE_RULE(STR_MSG_COMBAT_RESISTED_ME_TO_B);
	DECLARE_MESSAGE_RULE(STR_SKILL_RESISTED_ME_TO_B);		
	DECLARE_MESSAGE_RULE(STR_MSG_CHANGE_WEAPON);

	
}

void CombatModule::executeChatLogCommand(ChatLogCommand& command){
	map<string, string>& params = command.getParams();

	switch(command.getMessageRuleCode()){
	case STR_SKILL_SUCC_SkillATK_Instant_ME_TO_B:
	case STR_SKILL_SUCC_CarveSignet_ME_TO_B:
	case STR_SKILL_SUCC_DispelBuffCounterATK_ME_TO_B:
		autoAttackBuffer.makeSkillAttack(stringToInt(params["%num0"]), params["[%SkillTarget]"], 
			params["[%SkillName]"], command.isCritical());
		break;
	case STR_MSG_COMBAT_MY_CRITICAL:
		autoAttackBuffer.makeAutoAttack(stringToInt(params["%num1"]), params["%0"], true);
		break; 
	case STR_MSG_COMBAT_MY_ATTACK:
		autoAttackBuffer.makeAutoAttack(stringToInt(params["%num1"]), params["%0"], false);
		break;		

	case STR_SKILL_SUCC_StatDown_ME_TO_B: // [%SkillCaster] has weakened [%SkillTarget]'s %0 by using [%SkillName].
		autoAttackBuffer.debuffEnemy(params["%0"], params["[%SkillTarget]"], params["[%SkillName]"], command.isCritical());
		break;

	case STR_SKILL_SUCC_Blind_ME_TO_B: //"You blinded [%SkillTarget] by using [%SkillName].";
	case STR_SKILL_SUCC_Confuse_ME_TO_B: //You confused [%SkillTarget] by using [%SkillName].";
	case STR_SKILL_SUCC_Disease_ME_TO_B: //You diseased [%SkillTarget] by using [%SkillName].";
	case STR_SKILL_SUCC_Fear_ME_TO_B: //You made [%SkillTarget] afraid by using [%SkillName].";
	case STR_SKILL_SUCC_Paralyze_ME_TO_B: //You paralyzed [%SkillTarget] by using [%SkillName].";
	case STR_SKILL_SUCC_Root_ME_TO_B: //You immobilized [%SkillTarget] by using [%SkillName].";
	case STR_SKILL_SUCC_Silence_ME_TO_B: //You silenced [%SkillTarget] by using [%SkillName].";
	case STR_SKILL_SUCC_Sleep_ME_TO_B: //You put [%SkillTarget] to sleep by using [%SkillName].";
	case STR_SKILL_SUCC_Spin_ME_TO_B: //You span [%SkillTarget] around by using [%SkillName].";
	case STR_SKILL_SUCC_Stagger_ME_TO_B: //You knocked [%SkillTarget] back by using [%SkillName].";
	case STR_SKILL_SUCC_Stumble_ME_TO_B: //You knocked [%SkillTarget] over by using [%SkillName].";
	case STR_SKILL_SUCC_Stun_ME_TO_B: //You stunned [%SkillTarget] by using [%SkillName].";
	case STR_SKILL_SUCC_Bind_ME_TO_B: //You used [%SkillName] and [%SkillTarget] became bound.";
	case STR_SKILL_SUCC_Bleed_ME_TO_B: //You caused [%SkillTarget] to bleed by using [%SkillName].";
	case STR_SKILL_SUCC_Curse_ME_TO_B: //You cursed [%SkillTarget] by using [%SkillName].";
	case STR_SKILL_SUCC_NoFly_ME_TO_B: //[%SkillTarget] is unable to fly because you used [%SkillName].";
	case STR_SKILL_SUCC_OpenAerial_ME_TO_B: //You used [%SkillName] to immobilize [%SkillTarget] in mid-air.";
	case STR_SKILL_SUCC_Petrification_ME_TO_B: //You petrified [%SkillTarget] by using [%SkillName].";
	case STR_SKILL_SUCC_Poison_ME_TO_B: //You poisoned [%SkillTarget] by using [%SkillName].";
	case STR_SKILL_SUCC_Slow_ME_TO_B: // [%SkillTarget]'s attack speed has decreased because [%SkillCaster] used [%SkillName].
	case STR_SKILL_SUCC_Snare_ME_TO_B: // [%SkillTarget]'s movement speed decreased as you used [%SkillName].
	case STR_SKILL_SUCC_HostileUp_ME_TO_B: // [%SkillCaster] %0d [%SkillTarget]'s enmity %0 by using [%SkillName].";
		//all untested
		autoAttackBuffer.debuffEnemy("placeholder", params["[%SkillTarget]"], params["[%SkillName]"], command.isCritical());
		break;	

	case STR_MSG_COMBAT_BLOCK_ME_TO_B:
		autoAttackBuffer.enemyBlocked(params["%0"]);
		break;
	case STR_MSG_COMBAT_PARRY_ME_TO_B:
		autoAttackBuffer.enemyParried(params["%0"]);
		break;
	case STR_MSG_COMBAT_DODGED_ME_TO_B:
		//weaponSwitch.getCurrentSet().enemyEvade ++;
		autoAttackBuffer.enemyEvaded(params["%0"]);
		/*
		if (weaponSwitch.getCurrentSet() == 0)
			combatStatsManager.getAllTargetsCombatStats().first.enemyEvade ++;
		else 
			combatStatsManager.getAllTargetsCombatStats().second.enemyEvade ++;
		break;
		*/
	case STR_SKILL_DODGED_ME_TO_B:
		autoAttackBuffer.enemyEvaded(params["[%SkillTarget]"], params["[%SkillName]"]);
		break;
	case STR_SKILL_SUCC_Shield_PROTECT_ME_to_B:
		autoAttackBuffer.enemyShielded(params["[%SkillTarget]"]);
		break;
	case STR_SKILL_SUCC_Reflector_PROTECT_ME_to_B:
		autoAttackBuffer.enemyReflected(params["[%SkillTarget]"]);
		break;
	case STR_MSG_COMBAT_RESISTED_ME_TO_B:
		autoAttackBuffer.enemyResisted(params["%0"]);
		break;
	case STR_SKILL_RESISTED_ME_TO_B:		
		autoAttackBuffer.enemyResisted(params["[%SkillTarget]"], params["[%SkillName]"]);
		/*
		if (LANGUAGE_MANAGER.getCurrentLanguage().getSkillToClassMap().getClass(params["[%SkillName]"]) != ""){ 
			//weaponSwitch.getCurrentSet().enemyResist ++;
			if (weaponSwitch.getCurrentSet() == 0)
				combatStatsManager.getAllTargetsCombatStats().first.enemyResist ++;
			else
				combatStatsManager.getAllTargetsCombatStats().second.enemyResist ++;
		}
		*/
		break;	
	case STR_MSG_CHANGE_WEAPON:
		autoAttackBuffer.stopAutoAttack();
		weaponSwitch.switchWeapons();
		//autoAttackBuffer.setCombatStats(weaponSwitch.getCurrentSet());
		break;
	default:
		autoAttackBuffer.stopAutoAttack();
		break;
	}
	
}

void CombatModule::endOfTickAction(){
	autoAttackBuffer.stopAutoAttack();
}

/*
void CombatModule::processLines(){
	logFile.readLines(lines);		

	while(!lines.empty()){						

		bool isMultiHit = false;			

		string line = lines.front();

		bool critical = parser->isCrit(line);
		
		if (parser->resemblesRule(line, "STR_SKILL_SUCC_SkillATK_Instant_ME_TO_B", params, critical)				
				 
			|| parser->resemblesRule(line, "STR_SKILL_SUCC_CarveSignet_ME_TO_B", params, critical)
			|| parser->resemblesRule(line, "STR_SKILL_SUCC_DispelBuffCounterATK_ME_TO_B", params, critical)
			)
		{
			int damage = stringToInt(params["%num0"]);	
			autoAttackBuffer.makeSkillAttack(damage, params["[%SkillTarget]"], params["[%SkillName]"], critical);
				
		}
		else if (parser->resemblesRule(line, "STR_MSG_COMBAT_MY_CRITICAL", params))					
		{				
			int damage = stringToInt(params["%num1"]);				
			autoAttackBuffer.makeAutoAttack(damage, params["%0"], true);		
		}
		else if (parser->resemblesRule(line, "STR_MSG_COMBAT_MY_ATTACK", params))
		{
			int damage = stringToInt(params["%num1"]);								

			autoAttackBuffer.makeAutoAttack(damage, params["%0"], false);

		}
		else if (parser->resemblesRule(line, "STR_MSG_COMBAT_BLOCK_ME_TO_B", params))
		{
			autoAttackBuffer.enemyBlocked(params["%0"]);
			//weaponSwitch.getCurrentSet()->enemyBlock ++;
		}
	
		else if (parser->resemblesRule(line, "STR_MSG_COMBAT_PARRY_ME_TO_B", params))
		{
			autoAttackBuffer.enemyParried(params["%0"]);
			//weaponSwitch.getCurrentSet()->enemyParry ++;
		}
			

		else if (parser->resemblesRule(line, "STR_MSG_COMBAT_DODGED_ME_TO_B", params))
		{
			weaponSwitch.getCurrentSet().enemyEvade ++;
		}
		else if (parser->resemblesRule(line, "STR_SKILL_DODGED_ME_TO_B", params))
		{
			if (CLASS_SKILLS->getClass(params["[%SkillName]"]) != "")
				weaponSwitch.getCurrentSet().enemyEvade ++;
		}
		
		else if (parser->resemblesRule(line, "STR_SKILL_SUCC_Shield_PROTECT_ME_to_B", params))
		{
			autoAttackBuffer.enemyShielded(params["%0"]);
		}
		
		else if (parser->resemblesRule(line, "STR_SKILL_SUCC_Reflector_PROTECT_ME_to_B", params))
		{
			autoAttackBuffer.enemyReflected(params["[%SkillTarget]"]);
		}
		else if (parser->resemblesRule(line, "STR_MSG_COMBAT_RESISTED_ME_TO_B", params))
		{
			if (CLASS_SKILLS->getClass(params["[%SkillName]"]) != ""){}
		}
		
		else if (parser->resemblesRule(line, "STR_MSG_CHANGE_WEAPON", params))
		{
			weaponSwitch.switchWeapons();
			autoAttackBuffer.setCombatStats(weaponSwitch.getCurrentSet());
		}
		
		
			
		//if (!isMultiHit) weaponSwitch.getCurrentSet()->multiStrikeCounter.endMultiHits();
			

		lines.pop();
		if (lines.empty()) autoAttackBuffer.stopAutoAttack();
	}
}
*/