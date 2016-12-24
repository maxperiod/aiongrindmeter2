#include "gtest/gtest.h"
//#include "../parser/MaxPeriodParser.h"
//#include "../lookups/RuleStringsHardCodedNA.h"
#include "../modules/ProfessionModule.h"

#include "../parser/LogFileUtility.h"
#include "testLog/TemporaryLogFile.h"


class GatheringTest: public ::testing::Test{
protected:
	//MaxPeriodParser parser;
	//RuleStringsHardCodedNA rules;	

	ProfessionModule professionModule;
	TemporaryLogFile logFile;

	LogFileUtility logFileUtility;
	
	GatheringTest(): logFile("testModule/testLog/tests.log", "testModule/testLog/Chat.log") {
	}

	virtual void SetUp(){
		logFile.makeFileCopy();

		//logFileUtility.registerModule(playerIdentificationModule);
		logFileUtility.registerModule(professionModule);

		string aionDirectory = "testModule/testLog/";
		
		ASSERT_TRUE(logFileUtility.setAionDirectory(aionDirectory));								

	}

	virtual void TearDown(){		
		logFile.deleteFileCopy();
	}
};

TEST_F(GatheringTest, lowbieCollection){
	logFile.appendFile("2013.11.08 17:42:59 : You are gathering Aria. ");	
	logFileUtility.parseLogFile();
	logFile.appendFile("2013.11.08 17:43:00 : Striped Kerub inflicted 14 damage on robotmaxman-TM. ");
	logFile.appendFile("2013.11.08 17:43:00 : robotmaxman-TM inflicted 100 damage on Striped Kerub by using Smite I. ");
	logFile.appendFile("2013.11.08 17:43:01 : Your Collection skill has been upgraded to 2 points. ");
	logFile.appendFile("2013.11.08 17:43:01 : You have gained 80 XP. ");
	logFile.appendFile("2013.11.08 17:43:01 : You have gathered successfully. ");
	logFile.appendFile("2013.11.08 17:43:01 : You have acquired [item:152000401;ver4;;;;]. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2013.11.08 17:43:18 : You are gathering Aria. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2013.11.08 17:43:25 : Your Collection skill has been upgraded to 3 points. ");
	logFile.appendFile("2013.11.08 17:43:26 : You have acquired [item:152000401;ver4;;;;]. ");
	logFile.appendFile("2013.11.08 17:43:26 : You have gained 80 XP. ");
	logFile.appendFile("2013.11.08 17:43:26 : You have gathered successfully. ");
	logFileUtility.parseLogFile();

	EXPECT_EQ(2, professionModule.gathers.getResult().getNumSuccess());
	EXPECT_EQ(0, professionModule.gathers.getResult().getNumFailure());
	EXPECT_EQ(0, professionModule.gathers.getResult().getNumCancel());
	EXPECT_EQ(0, professionModule.gathers.getResult().getNumProcs());
	EXPECT_EQ(2, professionModule.gathers.getResult().getTotalAttempts());

	EXPECT_EQ(2, professionModule.gathers.getIndividualItemGatherCrafts().getEntry("Aria").getNumSuccess());
	EXPECT_EQ(0, professionModule.gathers.getIndividualItemGatherCrafts().getEntry("Aria").getNumFailure());
	EXPECT_EQ(0, professionModule.gathers.getIndividualItemGatherCrafts().getEntry("Aria").getNumCancel());
	EXPECT_EQ(0, professionModule.gathers.getIndividualItemGatherCrafts().getEntry("Aria").getNumProcs());
	EXPECT_EQ(2, professionModule.gathers.getIndividualItemGatherCrafts().getEntry("Aria").getTotalAttempts());
	EXPECT_FALSE(professionModule.gathers.getIndividualItemGatherCrafts().getEntry("Aria").isProcable());

	EXPECT_EQ("Collection", professionModule.gatherLeveling.getCurrentProfession());
	EXPECT_EQ(3, professionModule.gatherLeveling.getCurrentLevel());		
	EXPECT_EQ(2, professionModule.gatherLeveling.getNumLevelUps());	
	EXPECT_EQ(0, professionModule.gatherLeveling.getNumGatheredOrCraftedSinceLevelUp());
	EXPECT_EQ(1, professionModule.gatherLeveling.getNumGatheredOrCraftedForLastLevelUp());
	EXPECT_FLOAT_EQ(0, professionModule.gatherLeveling.getProgressBarValue());		
	
	EXPECT_EQ(3, professionModule.gatherLeveling.getProfessionLevelingHistory("Collection").getCurrentLevel());
	EXPECT_EQ(2, professionModule.gatherLeveling.getProfessionLevelingHistory("Collection").getNumLevelUps());
	EXPECT_EQ(1, professionModule.gatherLeveling.getProfessionLevelingHistory("Collection").getNumGatheredOrCraftedForLastLevelUp());

}

TEST_F(GatheringTest, essencetapping){
	logFile.appendFile("2013.11.03 19:27:09 : You have started gathering Hintera. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2013.11.03 19:27:14 : Japanese Dolls has conquered Heart of Fissure. ");	
	logFile.appendFile("2013.11.03 19:27:19 : You have acquired [item:152000419;ver4;;;;]. ");
	logFile.appendFile("2013.11.03 19:27:19 : You have gained 9,684 XP (Energy of Salvation 2,075). ");
	logFile.appendFile("2013.11.03 19:27:19 : You have gained experience from gathering. ");

	logFileUtility.parseLogFile();
	
	logFile.appendFile("2013.11.03 19:19:33 : You have started gathering Fresh Hintera. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2013.11.03 19:19:43 : Your Essencetapping skill has been upgraded to 485 points. ");
	logFile.appendFile("2013.11.03 19:19:43 : You have acquired [item:152000420;ver4;;;;]. ");
	logFile.appendFile("2013.11.03 19:19:43 : You have gained 9,684 XP (Energy of Salvation 2,075). ");
	logFile.appendFile("2013.11.03 19:19:43 : You have gained experience from gathering. ");

	logFileUtility.parseLogFile();

	logFile.appendFile("2013.11.03 19:27:09 : You have started gathering Hintera. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2013.11.03 19:27:14 : Japanese Dolls has conquered Heart of Fissure. ");	
	logFile.appendFile("2013.11.03 19:27:19 : You have acquired [item:152000419;ver4;;;;]. ");
	logFile.appendFile("2013.11.03 19:27:19 : You have gained 9,684 XP (Energy of Salvation 2,075). ");
	logFile.appendFile("2013.11.03 19:27:19 : You have gained experience from gathering. ");

	logFileUtility.parseLogFile();

	logFile.appendFile("2013.11.03 18:46:41 : You have started gathering Anevra.");
	logFileUtility.parseLogFile();
	logFile.appendFile("2013.11.03 18:46:56 : You have failed to gather Anevra.");
	logFileUtility.parseLogFile();

	logFile.appendFile("2013.11.03 18:50:25 : You have started gathering Anevra. ");
	logFile.appendFile("2013.11.03 18:50:25 : You have stopped gathering. ");
	logFileUtility.parseLogFile();

	logFile.appendFile("2013.11.03 19:27:09 : You have started gathering Hintera. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2013.11.03 19:27:14 : Japanese Dolls has conquered Heart of Fissure. ");	
	logFile.appendFile("2013.11.03 19:27:14 : You must level up to raise your skill level.");
	logFile.appendFile("2013.11.03 19:27:19 : You have acquired [item:152000419;ver4;;;;]. ");
	logFile.appendFile("2013.11.03 19:27:19 : You have gained 9,684 XP (Energy of Salvation 2,075). ");
	logFile.appendFile("2013.11.03 19:27:19 : You have gained experience from gathering. ");

	logFileUtility.parseLogFile();

	logFile.appendFile("2013.11.05 15:08:51 : You have started gathering Magical Aether. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2013.11.05 15:08:53 : The skill level for the Aethertapping skill does not increase as the difficulty is too low. ");
	logFile.appendFile("2013.11.05 15:08:53 : You have acquired [item:152000911;ver4;;;;]. ");

	logFileUtility.parseLogFile();


	EXPECT_EQ(5, professionModule.gathers.getResult().getNumSuccess());
	EXPECT_EQ(1, professionModule.gathers.getResult().getNumFailure());
	EXPECT_EQ(1, professionModule.gathers.getResult().getNumCancel());
	EXPECT_EQ(0, professionModule.gathers.getResult().getNumProcs());
	EXPECT_EQ(7, professionModule.gathers.getResult().getTotalAttempts());

	EXPECT_EQ(3, professionModule.gathers.getIndividualItemGatherCrafts().getEntry("Hintera").getNumSuccess());
	EXPECT_EQ(0, professionModule.gathers.getIndividualItemGatherCrafts().getEntry("Hintera").getNumFailure());
	EXPECT_EQ(0, professionModule.gathers.getIndividualItemGatherCrafts().getEntry("Hintera").getNumCancel());
	EXPECT_EQ(0, professionModule.gathers.getIndividualItemGatherCrafts().getEntry("Hintera").getNumProcs());
	EXPECT_EQ(3, professionModule.gathers.getIndividualItemGatherCrafts().getEntry("Hintera").getTotalAttempts());
	EXPECT_FALSE(professionModule.gathers.getIndividualItemGatherCrafts().getEntry("Hintera").isProcable());

	EXPECT_EQ(1, professionModule.gathers.getIndividualItemGatherCrafts().getEntry("Fresh Hintera").getNumSuccess());
	EXPECT_EQ(0, professionModule.gathers.getIndividualItemGatherCrafts().getEntry("Fresh Hintera").getNumFailure());
	EXPECT_EQ(0, professionModule.gathers.getIndividualItemGatherCrafts().getEntry("Fresh Hintera").getNumCancel());
	EXPECT_EQ(0, professionModule.gathers.getIndividualItemGatherCrafts().getEntry("Fresh Hintera").getNumProcs());
	EXPECT_EQ(1, professionModule.gathers.getIndividualItemGatherCrafts().getEntry("Fresh Hintera").getTotalAttempts());
	EXPECT_FALSE(professionModule.gathers.getIndividualItemGatherCrafts().getEntry("Fresh Hintera").isProcable());

	EXPECT_EQ(0, professionModule.gathers.getIndividualItemGatherCrafts().getEntry("Anevra").getNumSuccess());
	EXPECT_EQ(1, professionModule.gathers.getIndividualItemGatherCrafts().getEntry("Anevra").getNumFailure());
	EXPECT_EQ(1, professionModule.gathers.getIndividualItemGatherCrafts().getEntry("Anevra").getNumCancel());
	EXPECT_EQ(0, professionModule.gathers.getIndividualItemGatherCrafts().getEntry("Anevra").getNumProcs());
	EXPECT_EQ(2, professionModule.gathers.getIndividualItemGatherCrafts().getEntry("Anevra").getTotalAttempts());
	EXPECT_FALSE(professionModule.gathers.getIndividualItemGatherCrafts().getEntry("Anevra").isProcable());
	
	EXPECT_EQ(1, professionModule.gathers.getIndividualItemGatherCrafts().getEntry("Magical Aether").getNumSuccess());
	EXPECT_EQ(0, professionModule.gathers.getIndividualItemGatherCrafts().getEntry("Magical Aether").getNumFailure());
	EXPECT_EQ(0, professionModule.gathers.getIndividualItemGatherCrafts().getEntry("Magical Aether").getNumCancel());
	EXPECT_EQ(0, professionModule.gathers.getIndividualItemGatherCrafts().getEntry("Magical Aether").getNumProcs());
	EXPECT_EQ(1, professionModule.gathers.getIndividualItemGatherCrafts().getEntry("Magical Aether").getTotalAttempts());
	EXPECT_FALSE(professionModule.gathers.getIndividualItemGatherCrafts().getEntry("Magical Aether").isProcable());

	EXPECT_EQ("Essencetapping", professionModule.gatherLeveling.getCurrentProfession());
	EXPECT_EQ(485, professionModule.gatherLeveling.getCurrentLevel());		
	EXPECT_EQ(1, professionModule.gatherLeveling.getNumLevelUps());	
	EXPECT_EQ(1, professionModule.gatherLeveling.getNumGatheredOrCraftedSinceLevelUp());
	EXPECT_EQ(-1, professionModule.gatherLeveling.getNumGatheredOrCraftedForLastLevelUp());
	EXPECT_FLOAT_EQ(0, professionModule.gatherLeveling.getProgressBarValue());	

	EXPECT_EQ(485, professionModule.gatherLeveling.getProfessionLevelingHistory("Essencetapping").getCurrentLevel());
	EXPECT_EQ(1, professionModule.gatherLeveling.getProfessionLevelingHistory("Essencetapping").getNumLevelUps());
	EXPECT_EQ(-1, professionModule.gatherLeveling.getProfessionLevelingHistory("Essencetapping").getNumGatheredOrCraftedForLastLevelUp());

}

TEST_F(GatheringTest, crafting1){
	logFile.appendFile("2013.11.05 18:04:10 : Quest acquired: Gritty Conide Supplies");
	logFile.appendFile("2013.11.05 18:04:10 : You have acquired 4 [item:182291205;ver4;;;;]s and stored them in your special cube. ");
	logFile.appendFile("2013.11.05 18:04:37 : You are crafting Gritty Conide. ");	
	logFileUtility.parseLogFile();
	logFile.appendFile("2013.11.05 18:04:47 : Your Cooking skill has been upgraded to 2 points. ");
	logFile.appendFile("2013.11.05 18:04:47 : You have gained 1,146 XP (Energy of Repose 327). ");
	logFile.appendFile("2013.11.05 18:04:47 : You have crafted successfully. ");
	logFile.appendFile("2013.11.05 18:04:47 : You have crafted [item:182291522;ver4;;;;]. ");
	logFile.appendFile("2013.11.05 18:04:47 : Quest updated: Gritty Conide Supplies ");
	logFile.appendFile("2013.11.05 18:04:49 : You are crafting Gritty Conide. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2013.11.05 18:04:58 : Your Cooking skill has been upgraded to 3 points. ");
	logFile.appendFile("2013.11.05 18:04:59 : You have crafted [item:182291522;ver4;;;;]. ");
	logFile.appendFile("2013.11.05 18:04:59 : You have gained 1,146 XP (Energy of Repose 327). ");
	logFile.appendFile("2013.11.05 18:04:59 : You have crafted successfully. ");
	logFile.appendFile("2013.11.05 18:04:59 : Quest updated: Gritty Conide Supplies ");
	logFile.appendFile("2013.11.05 18:05:01 : You are crafting Gritty Conide. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2013.11.05 18:05:04 : [3.LFG] [charname:Lieli;1.0000 0.6941 0.6941]: wtb [item:101301035;ver4;;;;] my pass, also buying [item:188950013;ver4;;s1a5spLXkRt+gYzaPXKeBd4A58W0H7ZP1LsHWSKEc2XLgHfTXkjFkATB1c8mejKmH0qUYnk1U7Kcwvu29yr3DA==;;] [item:186000237;ver4;;;;] (2100) pst ] ");
	logFile.appendFile("2013.11.05 18:05:10 : Your Cooking skill has been upgraded to 4 points. ");
	logFile.appendFile("2013.11.05 18:05:10 : You have crafted [item:182291522;ver4;;;;]. ");
	logFile.appendFile("2013.11.05 18:05:10 : You have gained 1,146 XP (Energy of Repose 327). ");
	logFile.appendFile("2013.11.05 18:05:10 : You have crafted successfully. ");
	logFile.appendFile("2013.11.05 18:05:10 : Quest updated: Gritty Conide Supplies ");
	logFile.appendFile("2013.11.05 18:05:12 : You are crafting Gritty Conide. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2013.11.05 18:05:27 : You have failed to craft Gritty Conide. ");
	logFileUtility.parseLogFile();

	EXPECT_EQ(3, professionModule.crafts.getResult().getNumSuccess());
	EXPECT_EQ(1, professionModule.crafts.getResult().getNumFailure());
	EXPECT_EQ(0, professionModule.crafts.getResult().getNumCancel());
	EXPECT_EQ(0, professionModule.crafts.getResult().getNumProcs());
	EXPECT_EQ(4, professionModule.crafts.getResult().getTotalAttempts());

	EXPECT_EQ(3, professionModule.crafts.getIndividualItemGatherCrafts().getEntry("Gritty Conide").getNumSuccess());
	EXPECT_EQ(1, professionModule.crafts.getIndividualItemGatherCrafts().getEntry("Gritty Conide").getNumFailure());
	EXPECT_EQ(0, professionModule.crafts.getIndividualItemGatherCrafts().getEntry("Gritty Conide").getNumCancel());
	EXPECT_EQ(0, professionModule.crafts.getIndividualItemGatherCrafts().getEntry("Gritty Conide").getNumProcs());
	EXPECT_EQ(4, professionModule.crafts.getIndividualItemGatherCrafts().getEntry("Gritty Conide").getTotalAttempts());
	EXPECT_FALSE(professionModule.crafts.getIndividualItemGatherCrafts().getEntry("Gritty Conide").isProcable());

	EXPECT_EQ("Cooking", professionModule.craftLeveling.getCurrentProfession());
	EXPECT_EQ(4, professionModule.craftLeveling.getCurrentLevel());		
	EXPECT_EQ(3, professionModule.craftLeveling.getNumLevelUps());	
	EXPECT_EQ(0, professionModule.craftLeveling.getNumGatheredOrCraftedSinceLevelUp());
	EXPECT_EQ(1, professionModule.craftLeveling.getNumGatheredOrCraftedForLastLevelUp());
	EXPECT_FLOAT_EQ(0, professionModule.craftLeveling.getProgressBarValue());	

	EXPECT_EQ(4, professionModule.craftLeveling.getProfessionLevelingHistory("Cooking").getCurrentLevel());
	EXPECT_EQ(3, professionModule.craftLeveling.getProfessionLevelingHistory("Cooking").getNumLevelUps());
	EXPECT_EQ(1, professionModule.craftLeveling.getProfessionLevelingHistory("Cooking").getNumGatheredOrCraftedForLastLevelUp());


}

TEST_F(GatheringTest, crafting2){
	logFile.appendFile("2013.07.17 11:13:18 : You are crafting Poma Herb Bulgogi. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2013.07.17 11:13:31 : You are crafting Tasty Poma Herb Bulgogi. ");
	logFileUtility.parseLogFile();

	logFile.appendFile("2013.07.17 11:14:04 : You have gained 15,210 XP. ");
	logFile.appendFile("2013.07.17 11:14:04 : You have crafted successfully. ");
	logFile.appendFile("2013.07.17 11:14:04 : You have crafted 2 [item:160002347;ver4;;;;]s. ");
	logFile.appendFile("2013.07.17 11:14:07 : You are crafting Poma Herb Bulgogi. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2013.07.17 11:14:34 : You are crafting Tasty Poma Herb Bulgogi. ");
	logFileUtility.parseLogFile();	

	logFile.appendFile("2013.07.17 11:14:49 : You have crafted 2 [item:160002347;ver4;;;;]s. ");
	logFile.appendFile("2013.07.17 11:14:49 : You have gained 15,210 XP. ");
	logFile.appendFile("2013.07.17 11:14:49 : You have crafted successfully. ");
	logFile.appendFile("2013.07.17 11:14:49 : [3.LFG] [charname:Xnxx;1.0000 0.6941 0.6941]: [cmd:YN9dx6QUIAkfM1CUPjouv0VRg5mfKVnkcIKURP7j+0JFUYOZnylZ5HCClET+4/tCzzNQLIyOe3eXmGh3h+unUQ==]BT DUO NEED CLER CHANT!!!??? ");
	logFile.appendFile("2013.07.17 11:14:52 : You are crafting Poma Herb Bulgogi. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2013.07.17 11:15:14 : You have gained 15,210 XP. ");
	logFile.appendFile("2013.07.17 11:15:14 : You have crafted successfully. ");
	logFile.appendFile("2013.07.17 11:15:14 : You have crafted 2 [item:160002341;ver4;;;;]s. ");
	logFileUtility.parseLogFile();	

	logFile.appendFile("2013.07.17 11:14:52 : You are crafting Poma Herb Bulgogi. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2013.11.07 19:22:15 : You must level up to raise your skill level. ");
	logFile.appendFile("2013.07.17 11:15:14 : You have gained 15,210 XP. ");
	logFile.appendFile("2013.07.17 11:15:14 : You have crafted 2 [item:160002341;ver4;;;;]s. ");
	logFile.appendFile("2013.07.17 11:15:14 : You have crafted successfully. ");
	logFileUtility.parseLogFile();
			
	logFile.appendFile("2013.05.31 18:18:47 : You are crafting Poma Herb Bulgogi. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2013.05.31 18:18:57 : You are crafting Tasty Poma Herb Bulgogi.");
	logFileUtility.parseLogFile();
	logFile.appendFile("2013.05.31 18:19:20 : You failed to craft the combo, and crafted 2 [item:160002341;ver4;;;;]s instead. ");
	logFile.appendFile("2013.05.31 18:19:20 : You have gained 10,914 XP (Energy of Repose 3,118). ");
	logFile.appendFile("2013.05.31 18:19:20 : The Dresser of Concentration effect has been applied. ");
	logFile.appendFile("2013.05.31 18:19:20 : You have crafted successfully. ");
	logFileUtility.parseLogFile();

	logFile.appendFile("2013.11.08 16:31:42 : You are crafting Horned Dragon Emperor's Salad. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2013.11.08 16:31:54 : [3.LFG] [charname:Theredor;1.0000 0.6941 0.6941]: [cmd:cFkpTZP8yRXX/HbmhcbMokVRg5mfKVnkcIKURP7j+0JFUYOZnylZ5HCClET+4/tCtHO9gK1sD3F71HcBPyK5Bg==]lf2m sauro need sorc and sw ");
	logFile.appendFile("2013.11.08 16:31:57 : The skill level for the Cooking skill does not increase as the difficulty is too low. ");
	logFile.appendFile("2013.11.08 16:31:57 : You have crafted 2 [item:160002385;ver4;;;;]s. ");
	logFileUtility.parseLogFile();

	EXPECT_EQ(6, professionModule.crafts.getResult().getNumSuccess());
	EXPECT_EQ(0, professionModule.crafts.getResult().getNumFailure());
	EXPECT_EQ(0, professionModule.crafts.getResult().getNumCancel());
	EXPECT_EQ(2, professionModule.crafts.getResult().getNumProcs());
	EXPECT_EQ(6, professionModule.crafts.getResult().getTotalAttempts());
		
	EXPECT_EQ(3, professionModule.crafts.getIndividualItemGatherCrafts().getEntry("Poma Herb Bulgogi").getNumSuccess());
	EXPECT_EQ(0, professionModule.crafts.getIndividualItemGatherCrafts().getEntry("Poma Herb Bulgogi").getNumFailure());
	EXPECT_EQ(0, professionModule.crafts.getIndividualItemGatherCrafts().getEntry("Poma Herb Bulgogi").getNumCancel());
	EXPECT_EQ(2, professionModule.crafts.getIndividualItemGatherCrafts().getEntry("Poma Herb Bulgogi").getNumProcs());
	EXPECT_EQ(5, professionModule.crafts.getIndividualItemGatherCrafts().getEntry("Poma Herb Bulgogi").getTotalAttempts());
	EXPECT_TRUE(professionModule.crafts.getIndividualItemGatherCrafts().getEntry("Poma Herb Bulgogi").isProcable());

	EXPECT_EQ(2, professionModule.crafts.getIndividualItemGatherCrafts().getEntry("Tasty Poma Herb Bulgogi").getNumSuccess());
	EXPECT_EQ(1, professionModule.crafts.getIndividualItemGatherCrafts().getEntry("Tasty Poma Herb Bulgogi").getNumFailure());
	EXPECT_EQ(0, professionModule.crafts.getIndividualItemGatherCrafts().getEntry("Tasty Poma Herb Bulgogi").getNumCancel());
	EXPECT_EQ(0, professionModule.crafts.getIndividualItemGatherCrafts().getEntry("Tasty Poma Herb Bulgogi").getNumProcs());
	EXPECT_EQ(3, professionModule.crafts.getIndividualItemGatherCrafts().getEntry("Tasty Poma Herb Bulgogi").getTotalAttempts());
	EXPECT_FALSE(professionModule.crafts.getIndividualItemGatherCrafts().getEntry("Tasty Poma Herb Bulgogi").isProcable());


}

	
TEST_F(GatheringTest, highCraft1){

	logFile.appendFile("2016.12.03 23:18:00 : Your Aetherforging skill has been upgraded to 2 points. ");
	logFile.appendFile("2016.12.03 23:18:00 : You have gained 15,461 XP. (Energy of Repose 4,417) ");
	logFile.appendFile("2016.12.03 23:18:00 : You have crafted successfully. ");
	logFile.appendFile("2016.12.03 23:18:00 : You’ve completed 10 [item:152012728;ver7;;;;](s). ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2016.12.03 23:18:09 : You’ve completed 10 [item:152012728;ver7;;;;](s). ");
	logFile.appendFile("2016.12.03 23:18:09 : You have gained 15,409 XP. (Energy of Repose 4,402) ");
	logFile.appendFile("2016.12.03 23:18:09 : You have crafted successfully. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2016.12.03 23:18:13 : You’ve completed 10 [item:152012728;ver7;;;;](s). ");
	logFile.appendFile("2016.12.03 23:18:13 : You have gained 15,409 XP. (Energy of Repose 4,402) ");
	logFile.appendFile("2016.12.03 23:18:13 : You have crafted successfully. ");
	logFileUtility.parseLogFile();

	EXPECT_EQ(3, professionModule.crafts.getResult().getNumSuccess());
	EXPECT_EQ(0, professionModule.crafts.getResult().getNumFailure());
	EXPECT_EQ(0, professionModule.crafts.getResult().getNumCancel());
	EXPECT_EQ(0, professionModule.crafts.getResult().getNumProcs());
	EXPECT_EQ(3, professionModule.crafts.getResult().getTotalAttempts());

	EXPECT_EQ(3, professionModule.crafts.getIndividualItemGatherCrafts().getEntry("[item:152012728;ver7;;;;]").getNumSuccess());
	EXPECT_EQ(0, professionModule.crafts.getIndividualItemGatherCrafts().getEntry("[item:152012728;ver7;;;;]").getNumFailure());
	EXPECT_EQ(0, professionModule.crafts.getIndividualItemGatherCrafts().getEntry("[item:152012728;ver7;;;;]").getNumCancel());
	EXPECT_EQ(0, professionModule.crafts.getIndividualItemGatherCrafts().getEntry("[item:152012728;ver7;;;;]").getNumProcs());
	EXPECT_EQ(3, professionModule.crafts.getIndividualItemGatherCrafts().getEntry("[item:152012728;ver7;;;;]").getTotalAttempts());
}	

	
	