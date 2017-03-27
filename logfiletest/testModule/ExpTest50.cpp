#include "gtest/gtest.h"
//#include "../parser/MaxPeriodParser.h"
//#include "../lookups/RuleStringsHardCodedNA.h"
#include "../modules/SoulHealerModule.h"

#include "../parser/LogFileUtility.h"
#include "testLog/TemporaryLogFile.h"

#include "../lookups/ExpChartKR51.h"

/*
This test set CANNOT be run at the same time as ExpTest.cpp
*/

class ExpTest: public ::testing::Test{
protected:
	//MaxPeriodParser parser;
	//RuleStringsHardCodedNA rules;
	shared_ptr<ExpChart> expChart;
	
	ExpModule expModule;
	//ApModule apModule;
	//KinahModule kinahModule;
	//SoulHealerModule soulHealerModule;
	
	TemporaryLogFile logFile;
	
	LogFileUtility logFileUtility;
	

	ExpTest(): logFile("testModule/testLog/tests.log", "testModule/testLog/Chat.log"),  expChart(new ExpChartKR51()), expModule(expChart)//,

	{
	}

	
	virtual void SetUp(){
		logFile.makeFileCopy();

		logFileUtility.registerModule(expModule);

		string aionDirectory = "testModule/testLog/";
		
		ASSERT_TRUE(logFileUtility.setAionDirectory(aionDirectory));

	}


	virtual void TearDown(){		
		logFile.deleteFileCopy();
	}
};


TEST_F(ExpTest, PercentLevelUpWithCP1){
	//lvl 71: 31,229,819,120
	expModule.levelUpChecker.initializePercent(71, 99.99);
	

	logFile.appendFile("2016.07.28 20:45:18 : Critical Hit!You inflicted 2,510 damage on Icewing by using Booming Strike. ");
	logFile.appendFile("2016.07.28 20:45:18 : Critical Hit!Moomoomooo has weakened Icewing's Physical Def by using Booming Strike. ");
	logFile.appendFile("2016.07.28 20:45:18 : You recovered 128 HP by using Word of Revival. ");
	logFile.appendFile("2016.07.28 20:45:18 : You have gained 2,771,853 XP from Icewing. (Energy of Repose 583,548, Growth Energy 729,435) ");
	logFile.appendFile("2016.07.28 20:45:18 : Quest updated: [Group] Protect the Ruins of Roah ");
	logFile.appendFile("2016.07.28 20:45:18 : Icewing restored its attack speed. ");
	logFile.appendFile("2016.07.28 20:45:18 : You have gained 201 Abyss Points. ");
	//logFile.appendFile("2016.07.28 20:45:18 : Essence has increased by 1. ");
	logFile.appendFile("2016.11.10 23:03:36 : You’ve obtained 6 Essence. ");
	logFile.appendFile("2016.07.28 20:45:18 : A survey has arrived. Click the icon to open the survey window. ");
	logFileUtility.parseLogFile();	
	logFile.appendFile("2016.07.28 20:45:19 : Growth Aura filled to 48.49%. ");
	logFileUtility.parseLogFile();	

	EXPECT_EQ(72, expModule.levelUpChecker.getCurrentLevel());
	EXPECT_EQ(0, expModule.levelUpChecker.getPercent());
	EXPECT_EQ(2771853, expModule.expGainMeter.getNetGained());
}

TEST_F(ExpTest, CPNonLevelUp){
	//lvl 67: 1,639,578,224
	expModule.levelUpChecker.initializePercent(67, 88.88);
	

	logFile.appendFile("2016.07.26 00:12:52 : You have acquired 4 [item:186000236;ver6;;;;]s and stored them in your special cube. ");
	logFile.appendFile("2016.07.26 00:12:52 : You have acquired [item:186000414;ver6;;;;] and stored it in your special cube. ");
	logFile.appendFile("2016.07.26 00:12:52 : You have gained 3,618,881 XP from Dupor. ");
	logFile.appendFile("2016.07.26 00:12:52 : Completed quest has contributed 60 points to the Landing. ");
	logFile.appendFile("2016.07.26 00:12:52 : You can receive the weekly quest again at 9 in the morning on Monday. ");
	logFile.appendFile("2016.07.26 00:12:52 : Quest complete: [Weekly] Shield Stokebellow Outpost ");
	logFileUtility.parseLogFile();
	logFileUtility.parseLogFile();
	logFile.appendFile("2016.07.26 00:12:54 : [3.LFG] [charname:rhachel;1.0000 0.6941 0.6941]: WTS[item:167010277;ver6;;;;]42M [pos:Location;0 210070000 2916.8 829.0 0.0 0]  ");
	logFile.appendFile("2016.07.26 00:12:54 : You have acquired 6 [item:186000236;ver6;;;;]s and stored them in your special cube. ");
	logFile.appendFile("2016.07.26 00:12:54 : You have acquired [item:186000414;ver6;;;;] and stored it in your special cube. ");
	logFile.appendFile("2016.07.26 00:12:54 : You have gained 3,618,881 XP from Dupor. ");
	//logFile.appendFile("2016.07.26 00:12:54 : Essence has increased by 1. ");
	logFile.appendFile("2016.11.10 23:03:36 : You’ve obtained 6 Essence. ");
	logFile.appendFile("2016.07.26 00:12:54 : Completed quest has contributed 60 points to the Landing. ");
	logFile.appendFile("2016.07.26 00:12:54 : You can receive the weekly quest again at 9 in the morning on Monday. ");
	logFile.appendFile("2016.07.26 00:12:54 : Quest complete: [Weekly] Protect Stokebellow Outpost ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2016.07.26 00:12:55 : Growth Aura filled to 37.10%. ");
	logFileUtility.parseLogFile();

	EXPECT_EQ(67, expModule.levelUpChecker.getCurrentLevel());
	EXPECT_NEAR((1639578224 * 0.8888 + 3618881 * 2) / 1639578224 * 100 , expModule.levelUpChecker.getPercent(), 0.01);
	EXPECT_EQ(3618881 * 2, expModule.expGainMeter.getNetGained());
}

TEST_F(ExpTest, CPNonLevelUp2){
	//lvl 68: 3,752,976,718
	//5th essence: 1,705,898,509 (45.45%)
	expModule.levelUpChecker.initializePercent(68, 45.4);
	
	logFile.appendFile("2016.08.08 22:52:08 : You have gained 5,384,534 XP from Lucina.  ");
	logFile.appendFile("2016.08.08 22:52:08 : Quest complete: Most Extreme Elimination  ");
	logFile.appendFile("2016.08.08 22:52:08 : This quest can be re-attempted in 1 h.  ");
	logFile.appendFile("2016.08.08 22:52:08 : You have acquired [item:188054912;ver6;;;;].  ");
	logFileUtility.parseLogFile();

	logFile.appendFile("2016.08.08 22:52:12 : You have earned 1,861,920 Kinah.  ");
	logFile.appendFile("2016.08.08 22:52:12 : You have gained 26,524,800 XP from Lucina.  ");
	logFile.appendFile("2016.08.08 22:52:12 : Essence has increased by 1.  ");
	logFile.appendFile("2016.08.08 22:52:12 : Quest complete: Archon Trap Disposal  ");
	logFile.appendFile("2016.08.08 22:52:12 : This quest can be re-attempted in 1 d 16 h.  ");
	logFile.appendFile("2016.08.08 22:52:12 : You recovered 72 MP by using Invincibility Mantra Effect.  ");
	logFile.appendFile("2016.08.08 22:52:13 : Growth Aura filled to 74.90%.  ");
	logFileUtility.parseLogFile();

	logFile.appendFile("2016.08.08 22:52:23 : You have acquired [item:188054912;ver6;;;;].  ");
	logFile.appendFile("2016.08.08 22:52:23 : You have gained 5,384,534 XP from Akuaris.  ");
	logFile.appendFile("2016.08.08 22:52:23 : Quest complete: Singing the Tunes of Splendor  ");
	logFile.appendFile("2016.08.08 22:52:23 : This quest can be re-attempted in 1 h.  ");
	logFileUtility.parseLogFile();

	EXPECT_EQ(68, expModule.levelUpChecker.getCurrentLevel());
	EXPECT_NEAR((3752976718 * 0.454 + 5384534 + 26524800 + 5384534) / 3752976718 * 100, expModule.levelUpChecker.getPercent(), 0.01);
}

TEST_F(ExpTest, CPTransformIsNotLevelUp){
	//lvl 68: 3,752,976,718
	//5th essence: 1,705,898,509 (45.45%)
	expModule.levelUpChecker.initializePercent(68, 45.4);
	
	logFile.appendFile("2016.08.08 22:29:56 : You learned Windfall (Level 1). ");
	logFile.appendFile("2016.08.08 22:29:56 : You learned Mercurial Blast (Level 1). ");
	logFileUtility.parseLogFile();

	logFile.appendFile("2016.08.08 22:52:08 : You have gained 5,384,534 XP from Lucina.  ");
	logFile.appendFile("2016.08.08 22:52:08 : Quest complete: Most Extreme Elimination  ");
	logFile.appendFile("2016.08.08 22:52:08 : This quest can be re-attempted in 1 h.  ");
	logFile.appendFile("2016.08.08 22:52:08 : You have acquired [item:188054912;ver6;;;;].  ");
	logFileUtility.parseLogFile();

	EXPECT_EQ(68, expModule.levelUpChecker.getCurrentLevel());
	

}

TEST_F(ExpTest, updateExpFromDeathNoExpLoss){
	//lvl 68: 3,752,976,718
	//before kill: 37,529,768
	//after kill: 118,000,639 (3.144%)

	expModule.levelUpChecker.initializePercent(68, 1);
	
	logFile.appendFile("2016.11.27 10:10:40 : Magical Water Damage Effect has been activated. ");
	logFile.appendFile("2016.11.27 10:10:40 : You have gained 80,470,871 XP from Special Forces Commander Gegares. (Growth Energy 16,894,767) ");
	logFile.appendFile("2016.11.27 10:10:40 : Indratu Legion Drakan Ambusher inflicted 1 damage on Atreia Protector. ");
	logFile.appendFile("2016.11.27 10:10:40 : Indratu Legion Drakan Ambusher inflicted 1 damage on Atreia Protector. ");
	logFile.appendFile("2016.11.27 10:10:40 : Indratu Legion Drakan Elite Combatant inflicted 945 damage on Atreia Protector. ");
	logFile.appendFile("2016.11.27 10:10:40 : Atreia Protector inflicted 1 damage on Indratu Legion Drakan Elite Combatant. ");
	logFile.appendFile("2016.11.27 10:10:40 : Indratu Legion Drakan Searcher inflicted 198 damage on Atreia Protector. ");
	logFileUtility.parseLogFile();

	logFile.appendFile("2016.12.03 09:46:21 : Shadow of Oblivion has inflicted 20,342 damage on you by using Oblivion Wave. ");
	logFile.appendFile("2016.12.03 09:46:21 : MooMOOMoomooOOo has been dismissed. ");
	logFile.appendFile("2016.12.03 09:46:21 : You have died. ");
	logFile.appendFile("2016.12.03 09:46:21 : You cannot do that while you are dead. ");
	logFileUtility.parseLogFile();

	EXPECT_EQ(68, expModule.levelUpChecker.getCurrentLevel());
		
	EXPECT_TRUE(expModule.levelUpChecker.setCurrentPercent(3.145));

	EXPECT_EQ(80470871, expModule.expGainMeter.getTotalGained());
	EXPECT_EQ(80470871, expModule.expGainMeter.getNetGained());
	EXPECT_NEAR(0.02145, expModule.levelUpChecker.getNumLevelsGained(), 0.01);
	EXPECT_EQ(0, expModule.expGainMeter.getTotalLost());

	EXPECT_NEAR(3.145, expModule.levelUpChecker.getPercent(), 0.01);
	

}


TEST_F(ExpTest, largeExpGained){
	//lvl 71: 31,229,819,120
	expModule.levelUpChecker.initializePercent(74, 0);
	

	
	logFile.appendFile("2016.01.28 20:45:18 : You have gained 1,000,000,000 XP from Luke Skywalker. ");
	logFileUtility.parseLogFile();	
	logFile.appendFile("2016.01.28 20:45:18 : You have gained 1,000,000,000 XP from Luke Skywalker. ");
	logFileUtility.parseLogFile();	
	logFile.appendFile("2016.01.28 20:45:18 : You have gained 1,000,000,000 XP from Luke Skywalker. ");
	logFileUtility.parseLogFile();	
	
	
	EXPECT_EQ(3000000000, expModule.expGainMeter.getNetGained());

	logFile.appendFile("2016.01.28 20:45:18 : You have gained 3,000,000,000 XP from Luke Skywalker. ");
	logFileUtility.parseLogFile();	

	EXPECT_EQ(6000000000, expModule.expGainMeter.getNetGained());
}