#include "gtest/gtest.h"

#include "../parser/LogFileUtility.h"
//#include "../language/EnglishNA.h"

#include "../modules/HuntingModule.h"

#include "testLog/TemporaryLogFile.h"

class HuntingModuleTest: public ::testing::Test{
protected:
	//MaxPeriodParser parser;
	//EnglishNA language;
	
	//PlayerIdentificationModule playerIdentificationModule;
	HuntingModule huntingModule;		

	TemporaryLogFile logFile;

	LogFileUtility logFileUtility;
	
	HuntingModuleTest(): 
			//huntingModule(playerIdentificationModule),
			logFile("testModule/testLog/tests.log", "testModule/testLog/Chat.log"){
	}

	virtual void SetUp(){
		logFile.makeFileCopy();

		//logFileUtility.registerModule(playerIdentificationModule);
		logFileUtility.registerModule(huntingModule);

		string aionDirectory = "testModule/testLog/";
		
		ASSERT_TRUE(logFileUtility.setAionDirectory(aionDirectory));
		/*
		logFileUtility.registerMessageRuleCode(STR_MSG_GET_ITEM_EXTRA_MULTI);
		logFileUtility.registerMessageRuleCode(STR_GET_EXP_VITAL_MAKEUP_BONUS);
		logFileUtility.registerMessageRuleCode(STR_GET_EXP_VITAL_BONUS);
		logFileUtility.registerMessageRuleCode(STR_GET_EXP_MAKEUP_BONUS);
		logFileUtility.registerMessageRuleCode(STR_GET_EXP);
		logFileUtility.registerMessageRuleCode(STR_GET_EXP_PCBANG_VITAL_MAKEUP_BONUS);
		logFileUtility.registerMessageRuleCode(STR_GET_EXP_PCBANG_VITAL_BONUS);
		logFileUtility.registerMessageRuleCode(STR_MSG_COMBAT_HOSTILE_DEATH_TO_ME);
		logFileUtility.registerMessageRuleCode(STR_MSG_COMBAT_HOSTILE_DEATH);
		logFileUtility.registerMessageRuleCode(STR_MSG_COMBAT_HOSTILE_DEATH_TO_B);
		logFileUtility.registerMessageRuleCode(STR_QUEST_SYSTEMMSG_COMPLETE);

		logFileUtility.registerMessageRuleCode(STR_MSG_USEMONEY);
		*/
	}

	virtual void TearDown(){		
		logFile.deleteFileCopy();
	}
};

TEST_F(HuntingModuleTest, test1){

	logFile.appendFile("2014.06.18 17:37:24 : Quest updated: [Coin] Settle the Road ");
	logFile.appendFile("2014.06.18 17:37:24 : Reroute Power Effect has been activated. ");
	logFile.appendFile("2014.06.18 17:37:24 : You have gained 80,714 XP from Fierce Worg (Energy of Repose 23,061). ");
	logFile.appendFile("2014.06.18 17:37:24 : Fierce Worg restored its attack speed. ");
	logFile.appendFile("2014.06.18 17:37:24 : You have gained 29 Abyss Points. ");
	
	logFileUtility.parseLogFile();

	logFile.appendFile("2014.06.18 17:37:52 : You received 431 damage from Fierce Worg. ");
	logFile.appendFile("2014.06.18 17:37:52 : Quest updated: [Coin] Settle the Road ");
	logFile.appendFile("2014.06.18 17:37:52 : You have gained 80,714 XP from Fierce Worg (Energy of Repose 23,061). ");
	logFile.appendFile("2014.06.18 17:37:52 : Fierce Worg restored its attack speed. ");
	logFile.appendFile("2014.06.18 17:37:52 : You have gained 29 Abyss Points. ");

	logFileUtility.parseLogFile();

	logFile.appendFile("2014.06.22 09:38:18 : You have gained 190 Abyss Points. ");
	logFile.appendFile("2014.06.22 09:38:18 : You cannot get any PvP XP for a while as you have gained too many PvP XP in too short a period of time. ");
	logFile.appendFile("2014.06.22 09:38:18 : Kidnt is no longer silenced. ");
	logFile.appendFile("2014.06.22 09:38:18 : Kidnt restored its attack speed. ");
	logFile.appendFile("2014.06.22 09:38:18 : You have defeated Kidnt. ");

	logFileUtility.parseLogFile();


	EXPECT_EQ(2, huntingModule.monstersKilled.getTotalCount());
	EXPECT_EQ(2, huntingModule.monstersKilled.get("Fierce Worg").numGained);
	EXPECT_EQ(2, huntingModule.monstersKilled.get("Fierce Worg").numPackets);
}



TEST_F(HuntingModuleTest, test2){
	logFile.appendFile("2014.06.18 17:42:16 : You have gained 964 Abyss Points. ");
	logFile.appendFile("2014.06.18 17:42:16 : You have gained 39,250 XP from Mtdew (Energy of Repose 11,214). ");
	logFile.appendFile("2014.06.18 17:42:16 : Mtdew restored its movement speed. ");
	logFile.appendFile("2014.06.18 17:42:16 : You have defeated Mtdew. ");
	logFile.appendFile("2014.06.18 17:42:16 : Quest updated: [Urgent Order] Diena's Request ");

	logFileUtility.parseLogFile();

	EXPECT_EQ(0, huntingModule.monstersKilled.getTotalCount());
	EXPECT_EQ(huntingModule.monstersKilled.end(), huntingModule.monstersKilled.begin());
	//EXPECT_EQ(0, huntingModule.monstersKilled.get("Mtdew")->second.numGained);
	//EXPECT_EQ(0, huntingModule.monstersKilled.get("Mtdew")->second.numPackets);


	logFile.appendFile("2014.06.22 09:39:07 : You have acquired [item:186000147;ver6;;;;] and stored it in your special cube. ");
	logFile.appendFile("2014.06.22 09:39:07 : You have gained 4,180,096 XP from Erasmus (Energy of Repose 759,003). ");
	logFile.appendFile("2014.06.22 09:39:07 : You have gained 1,184 Abyss Points. ");
	logFile.appendFile("2014.06.22 09:39:07 : You can receive the daily quest again at 9 in the morning. ");
	logFile.appendFile("2014.06.22 09:39:07 : Quest complete: [Service/Daily] Banishing the Shade-Touched ");

	logFileUtility.parseLogFile();

	EXPECT_EQ(0, huntingModule.monstersKilled.getTotalCount());
	EXPECT_EQ(huntingModule.monstersKilled.end(), huntingModule.monstersKilled.begin());
	//EXPECT_EQ(0, huntingModule.monstersKilled.get("Erasmus").numGained);

	logFile.appendFile("2014.06.20 23:10:38 : You have gained 164 Abyss Points. ");
	logFile.appendFile("2014.06.20 23:10:38 : You have gained 5,019 XP from Infiernus. ");
	logFile.appendFile("2014.06.20 23:10:38 : Infiernus is no longer staggering. ");
	logFile.appendFile("2014.06.20 23:10:38 : Infiernus restored its movement speed. ");
	logFile.appendFile("2014.06.20 23:10:38 : Lecinia has defeated Infiernus. ");

	logFileUtility.parseLogFile();

	EXPECT_EQ(0, huntingModule.monstersKilled.getTotalCount());
	EXPECT_EQ(huntingModule.monstersKilled.end(), huntingModule.monstersKilled.begin());

	logFile.appendFile("2014.06.21 16:50:33 : You have gained 413 Abyss Points. ");
	logFile.appendFile("2014.06.21 16:50:33 : You have gained 21,810 XP from iCeCradVQV. ");
	logFile.appendFile("2014.06.21 16:50:33 : iCeCradVQV has died. ");
	logFile.appendFile("2014.06.21 16:50:33 : Quest updated: [Service/Daily] A Stronger Enmity ");
	logFile.appendFile("2014.06.21 16:50:33 : Quest updated: [Service/Daily] Banishing the Shade-Touched ");

	logFileUtility.parseLogFile();

	EXPECT_EQ(0, huntingModule.monstersKilled.getTotalCount());
	EXPECT_EQ(huntingModule.monstersKilled.end(), huntingModule.monstersKilled.begin());

}

TEST_F(HuntingModuleTest, kromedeQuestUpdate){
	logFile.appendFile("2014.11.06 17:44:46 : You have gained 109,132 XP from Kromede the Corrupt. ");
	logFile.appendFile("2014.11.06 17:44:46 : Quest updated: [Coin/Group] Kromede in the Temple ");

	logFileUtility.parseLogFile();

	EXPECT_EQ(1, huntingModule.monstersKilled.getTotalCount());
	EXPECT_EQ(1, huntingModule.monstersKilled.get("Kromede the Corrupt").numGained);

}

TEST_F(HuntingModuleTest, kromedeQuestUpdate2){
	logFile.appendFile("2014.11.06 17:44:46 : You have gained 109,132 XP from Kromede the Corrupt. ");
	logFile.appendFile("2014.11.06 17:44:46 : Quest updated: [Coin/Group] Kromede in the Temple ");

	logFileUtility.parseLogFile();

	logFile.appendFile("2014.11.06 17:19:41 : You have acquired 40 [item:186000003;ver6;;;;]s and stored them in your special cube. ");
	logFile.appendFile("2014.11.06 17:19:41 : You have gained 1,244,918 XP from Hannet. ");
	logFile.appendFile("2014.11.06 17:19:41 : You learned Evasion Rate Increase III (Level 1). ");
	logFile.appendFile("2014.11.06 17:19:41 : You learned Counterattack III (Level 7). ");
	logFile.appendFile("2014.11.06 17:19:41 : You learned Swift Edge IV (Level 1). ");
	logFile.appendFile("2014.11.06 17:19:41 : You learned Soul Slash III (Level 7). ");
	logFile.appendFile("2014.11.06 17:19:41 : You learned Hide II (Level 1). ");
	logFile.appendFile("2014.11.06 17:19:41 : You learned Weakening Blow I (Level 1). ");
	logFile.appendFile("2014.11.06 17:19:41 : You learned Calming Whisper II (Level 4). ");
	logFile.appendFile("2014.11.06 17:19:41 : You learned Assassination I (Level 4). ");
	logFile.appendFile("2014.11.06 17:19:41 : You learned Dash Attack III (Level 1). ");
	logFile.appendFile("2014.11.06 17:19:41 : You learned Apply Poison II (Level 7). ");
	logFile.appendFile("2014.11.06 17:19:41 : You learned Fang Strike II (Level 7). ");
	logFile.appendFile("2014.11.06 17:19:41 : You learned Beast Kick I (Level 7). ");
	logFile.appendFile("2014.11.06 17:19:41 : You learned Rune Slash II (Level 1). ");
	logFile.appendFile("2014.11.06 17:19:41 : You learned Divine Strike III (Level 1). ");
	logFile.appendFile("2014.11.06 17:19:41 : You learned Blood Rune I (Level 1). ");
	logFile.appendFile("2014.11.06 17:19:41 : You learned Herb Treatment III (Level 1). ");
	logFile.appendFile("2014.11.06 17:19:41 : You learned Mana Treatment III (Level 1). ");
	logFile.appendFile("2014.11.06 17:19:41 : You have acquired the Bloodsworn title. ");
	logFile.appendFile("2014.11.06 17:19:41 : Quest complete: [Group] Hannet's Revenge ");

	logFileUtility.parseLogFile();


	logFile.appendFile("2014.11.06 17:35:17 : You have gained 90,288 XP from Kromede the Corrupt. ");
	logFile.appendFile("2014.11.06 17:35:17 : Quest updated: [Coin/Group] Kromede in the Temple ");

	logFileUtility.parseLogFile();

	logFile.appendFile("2014.11.06 17:37:51 : You have acquired 2 [item:186000003;ver6;;;;]s and stored them in your special cube. ");
	logFile.appendFile("2014.11.06 17:37:51 : You have gained 684,705 XP from Hannet. ");
	logFile.appendFile("2014.11.06 17:37:51 : Quest complete: [Coin/Group] Kromede in the Temple ");
	
	logFileUtility.parseLogFile();

	logFile.appendFile("2014.11.06 17:37:54 : You have acquired 2 [item:186000003;ver6;;;;]s and stored them in your special cube. ");
	logFile.appendFile("2014.11.06 17:37:54 : You have gained 1,244,918 XP from Hannet. ");
	logFile.appendFile("2014.11.06 17:37:54 : Quest complete: [Group] Impede Kromede ");
	logFileUtility.parseLogFile();

	EXPECT_EQ(2, huntingModule.monstersKilled.getTotalCount());
	EXPECT_EQ(2, huntingModule.monstersKilled.get("Kromede the Corrupt").numGained);

}

TEST_F(HuntingModuleTest, noExpQuest){

	logFile.appendFile("2015.10.10 09:47:51 : Unstable Triroan: Dkdldhs ehdwjq cjsaksdmf gidgo wjswls...!! ");
	logFile.appendFile("2015.10.10 09:47:51 : You have gained 5,741 XP from Unstable Triroan. (Energy of Repose 1,640) ");
	logFile.appendFile("2015.10.10 09:47:52 : Unstable Triroan restored its attack speed. ");
	logFileUtility.parseLogFile();
	logFileUtility.parseLogFile();
	logFileUtility.parseLogFile();
	logFile.appendFile("2015.10.10 09:49:02 : Quest updated: [Event/Daily] Trouble Brewing ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2015.10.10 09:49:03 : You have acquired 5 [item:160010239;ver6;;;;](s). ");
	logFile.appendFile("2015.10.10 09:49:03 : You have acquired [item:186000190;ver6;;;;] and stored it in your special cube. ");
	logFile.appendFile("2015.10.10 09:49:03 : You can receive the daily quest again at 9 in the morning. ");
	logFile.appendFile("2015.10.10 09:49:03 : Quest complete: [Event/Daily] Trouble Brewing ");

	logFileUtility.parseLogFile();

	EXPECT_EQ(1, huntingModule.monstersKilled.getTotalCount());
	EXPECT_EQ(1, huntingModule.monstersKilled.get("Unstable Triroan").numGained);
}

TEST_F(HuntingModuleTest, pvpKill){

	logFile.appendFile("2015.11.01 09:08:22 : Critical Hit!You inflicted 1,639 damage on Alduin by using Holy Punishment. ");
	logFile.appendFile("2015.11.01 09:08:22 : You woke up. ");
	logFile.appendFile("2015.11.01 09:08:22 : You inflicted 637 damage on Alduin by using Body Smash. ");
	logFile.appendFile("2015.11.01 09:08:22 : You parried Ancient Drakan Warrior's attack. ");
	logFile.appendFile("2015.11.01 09:08:22 : You received 337 damage from Ancient Drakan Warrior. ");
	logFile.appendFile("2015.11.01 09:08:22 : You have gained 345 Abyss Points. ");
	logFile.appendFile("2015.11.01 09:08:22 : You are now a Protector. ");
	logFile.appendFile("2015.11.01 09:08:22 : You have gained 326 XP from Alduin. (Energy of Repose 93) ");
	logFile.appendFile("2015.11.01 09:08:22 : Alduin is no longer blind. ");
	logFile.appendFile("2015.11.01 09:08:22 : Alduin restored its movement speed. ");
	logFile.appendFile("2015.11.01 09:08:22 : Alduin restored its attack speed. ");
	logFile.appendFile("2015.11.01 09:08:22 : You have defeated Alduin. ");

	logFileUtility.parseLogFile();

	EXPECT_EQ(0, huntingModule.monstersKilled.getTotalCount());
	EXPECT_EQ(1, huntingModule.playersKilled.getTotalKills());
	EXPECT_EQ(0, huntingModule.playersKilled.getTotalAssists());
	EXPECT_EQ(1, huntingModule.playersKilled.getUniqueKills());

	logFile.appendFile("2015.11.01 09:08:22 : Critical Hit!You inflicted 1,639 damage on Alduin by using Holy Punishment. ");
	logFile.appendFile("2015.11.01 09:08:22 : You woke up. ");
	logFile.appendFile("2015.11.01 09:08:22 : You inflicted 637 damage on Alduin by using Body Smash. ");
	logFile.appendFile("2015.11.01 09:08:22 : You parried Ancient Drakan Warrior's attack. ");
	logFile.appendFile("2015.11.01 09:08:22 : You received 337 damage from Ancient Drakan Warrior. ");
	logFile.appendFile("2015.11.01 09:08:22 : You have gained 345 Abyss Points. ");
	logFile.appendFile("2015.11.01 09:08:22 : You are now a Protector. ");
	logFile.appendFile("2015.11.01 09:08:22 : You have gained 326 XP from Alduin. (Energy of Repose 93) ");
	logFile.appendFile("2015.11.01 09:08:22 : Alduin is no longer blind. ");
	logFile.appendFile("2015.11.01 09:08:22 : Alduin restored its movement speed. ");
	logFile.appendFile("2015.11.01 09:08:22 : Alduin restored its attack speed. ");
	logFile.appendFile("2015.11.01 09:08:22 : You have defeated Alduin. ");

	logFileUtility.parseLogFile();

	EXPECT_EQ(0, huntingModule.monstersKilled.getTotalCount());
	EXPECT_EQ(2, huntingModule.playersKilled.getTotalKills());
	EXPECT_EQ(0, huntingModule.playersKilled.getTotalAssists());
	EXPECT_EQ(1, huntingModule.playersKilled.getUniqueKills());
}

TEST_F(HuntingModuleTest, pvpAssist){

	logFile.appendFile("2015.11.03 00:16:16 : You inflicted 520 damage on CookeTim by using Aether Leash. ");
	logFile.appendFile("2015.11.03 00:16:16 : CookeTim's movement speed decreased as you used Aether Leash. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2015.11.03 00:16:17 : You inflicted 459 damage on CookeTim. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2015.11.03 00:16:18 : Critical Hit!You inflicted 1,133 damage on CookeTim by using Body Smash. ");
	logFile.appendFile("2015.11.03 00:16:18 : Cirse inflicted 729 damage on CookeTim by using Infernal Blaze. ");
	logFile.appendFile("2015.11.03 00:16:18 : CookeTim became stunned because Cirse used Infernal Blaze. ");
	logFile.appendFile("2015.11.03 00:16:18 : You inflicted 665 damage on CookeTim by using Blood Pact. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2015.11.03 00:16:19 : Cyrano inflicted 783 damage on CookeTim by using Inquisitor's Blow. ");
	logFile.appendFile("2015.11.03 00:16:19 : You have gained 414 Abyss Points. ");
	logFile.appendFile("2015.11.03 00:16:19 : You cannot get any PvP XP from the current target for a while. ");
	logFile.appendFile("2015.11.03 00:16:19 : CookeTim restored its movement speed. ");
	logFile.appendFile("2015.11.03 00:16:19 : Cyrano has defeated CookeTim. ");
	logFile.appendFile("2015.11.03 00:16:19 : Quest updated: [Daily] Rage Against the Asmodians ");
	logFileUtility.parseLogFile();

	EXPECT_EQ(0, huntingModule.monstersKilled.getTotalCount());
	EXPECT_EQ(0, huntingModule.playersKilled.getTotalKills());
	EXPECT_EQ(1, huntingModule.playersKilled.getTotalAssists());
	EXPECT_EQ(0, huntingModule.playersKilled.getUniqueKills());
}