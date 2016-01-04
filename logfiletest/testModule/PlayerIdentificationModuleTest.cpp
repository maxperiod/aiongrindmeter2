#include "../modules/PlayerIdentificationModule.h"
#include "gtest/gtest.h"

#include "../parser/LogFileUtility.h"
#include "../language/EnglishNA.h"

#include "../modules/ItemAcquisitionModule.h"

#include "testLog/TemporaryLogFile.h"

class PlayerIdentificationModuleTest: public ::testing::Test{
protected:
	MaxPeriodParser parser;
	EnglishNA language;
	
	PlayerIdentificationModule playerIdentificationModule;	
	TemporaryLogFile logFile;

	LogFileUtility logFileUtility;
	
	PlayerIdentificationModuleTest(): 
			logFile("testModule/testLog/tests.log", "testModule/testLog/Chat.log")//,
			//logFileUtility(language)
			{
	}

	virtual void SetUp(){
		logFile.makeFileCopy();

		logFileUtility.registerModule(playerIdentificationModule);

		string aionDirectory = "testModule/testLog/";
		
		ASSERT_TRUE(logFileUtility.setAionDirectory(aionDirectory));
		/*
		logFileUtility.registerMessageRuleCode(STR_MSG_GET_ITEM_EXTRA_MULTI);
		logFileUtility.registerMessageRuleCode(STR_SKILL_SUCC_SkillATK_Instant_A_TO_ME);
		logFileUtility.registerMessageRuleCode(STR_SKILL_SUCC_SpellATK_Instant_A_TO_ME);
		logFileUtility.registerMessageRuleCode(STR_SKILL_SUCC_SkillATK_Instant_A_TO_B);
		logFileUtility.registerMessageRuleCode(STR_SKILL_SUCC_SpellATK_Instant_A_TO_B);	
		logFileUtility.registerMessageRuleCode(STR_MSG_COMBAT_HOSTILE_DEATH_TO_ME);
		logFileUtility.registerMessageRuleCode(STR_MSG_COMBAT_MY_DEATH_TO_B);
		logFileUtility.registerMessageRuleCode(STR_MSG_COMBAT_FRIENDLY_DEATH);
		logFileUtility.registerMessageRuleCode(STR_MSG_COMBAT_HOSTILE_DEATH);
		logFileUtility.registerMessageRuleCode(STR_MSG_COMBAT_HOSTILE_DEATH_TO_B);
		logFileUtility.registerMessageRuleCode(STR_MSG_COMBAT_FRIENDLY_DEATH_TO_B);
		*/
	}

	virtual void TearDown(){		
		logFile.deleteFileCopy();
	}
};


TEST_F(PlayerIdentificationModuleTest, identifyClass){
	logFile.appendFile("2014.08.30 16:33:24 : Critical Hit!Horatia inflicted 2,592 damage on HirumaEvans by using Break Power VI. ");
	logFile.appendFile("2014.08.30 16:33:24 : Critical Hit!HirumaEvans is in the weaken Attack state because Horatia used Break Power VI. ");
	logFileUtility.parseLogFile();

	EXPECT_TRUE(playerIdentificationModule.knownPlayers.isPlayer("Horatia"));
	EXPECT_EQ("KN", playerIdentificationModule.knownPlayers.getPlayerClass("Horatia"));
}

TEST_F(PlayerIdentificationModuleTest, unknownClass){
	
	logFile.appendFile("2014.07.30 18:23:31 : David Tam inflicted 780 damage on Cracktooth Ettin by using Frozen Shock III. ");
	logFile.appendFile("2014.07.30 18:23:31 : David Tam knocked Cracktooth Ettin back by using Frozen Shock III. ");
	
	logFileUtility.parseLogFile();

	EXPECT_TRUE(playerIdentificationModule.knownPlayers.isPlayer("David Tam"));
	EXPECT_EQ("", playerIdentificationModule.knownPlayers.getPlayerClass("David Tam"));
}

TEST_F(PlayerIdentificationModuleTest, cannotDeterminePlayerOrNPC){
	
	logFile.appendFile("2014.08.01 22:39:22 : RRHH-TM blocked Beason-TM's attack with the protective shield effect. ");
	logFile.appendFile("2014.08.01 22:39:22 : Beason-TM inflicted 0 damage on RRHH-TM by using Flame Bolt IV. ");
	logFileUtility.parseLogFile();

	EXPECT_FALSE(playerIdentificationModule.knownPlayers.isPlayer("Beason-TM"));
	EXPECT_EQ("", playerIdentificationModule.knownPlayers.getPlayerClass("Beason-TM"));
}

TEST_F(PlayerIdentificationModuleTest, playerDeath){
	logFile.appendFile("2014.06.19 10:09:31 : selmor has died. ");
	logFileUtility.parseLogFile();

	EXPECT_TRUE(playerIdentificationModule.knownPlayers.isPlayer("selmor"));

	logFile.appendFile("2014.06.19 16:28:39 : Ashutosh has defeated Zalirr. ");
	logFileUtility.parseLogFile();

	EXPECT_TRUE(playerIdentificationModule.knownPlayers.isPlayer("Ashutosh"));
	EXPECT_TRUE(playerIdentificationModule.knownPlayers.isPlayer("Zalirr"));

	logFile.appendFile("2014.06.21 09:37:08 : Karem was killed by Vdint's attack. ");
	logFileUtility.parseLogFile();

	EXPECT_TRUE(playerIdentificationModule.knownPlayers.isPlayer("Karem"));
	EXPECT_TRUE(playerIdentificationModule.knownPlayers.isPlayer("Vdint"));

	logFile.appendFile("2014.06.21 09:43:31 : You have defeated Kidnt. ");
	logFileUtility.parseLogFile();

	EXPECT_FALSE(playerIdentificationModule.knownPlayers.isPlayer("You"));
	EXPECT_TRUE(playerIdentificationModule.knownPlayers.isPlayer("Kidnt"));

	logFile.appendFile("2014.06.21 11:17:44 : You were killed by ChickenSlayer's attack. ");
	logFileUtility.parseLogFile();

	EXPECT_FALSE(playerIdentificationModule.knownPlayers.isPlayer("You"));
	EXPECT_TRUE(playerIdentificationModule.knownPlayers.isPlayer("ChickenSlayer"));

}