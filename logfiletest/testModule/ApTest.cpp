#include "gtest/gtest.h"
//#include "../parser/MaxPeriodParser.h"
//#include "../lookups/RuleStringsHardCodedNA.h"
#include "../modules/SoulHealerModule.h"

#include "../parser/LogFileUtility.h"
#include "testLog/TemporaryLogFile.h"


class ApModuleTest: public ::testing::Test{
protected:
	//MaxPeriodParser parser;
	//RuleStringsHardCodedNA rules;
	
	//ExpModule expModule;
	ApModule apModule;
	//KinahModule kinahModule;
	//SoulHealerModule soulHealerModule;
	
	TemporaryLogFile logFile;
	
	LogFileUtility logFileUtility;
	

	ApModuleTest(): logFile("testModule/testLog/tests.log", "testModule/testLog/Chat.log")//,
		//soulHealerModule(expModule, apModule, kinahModule)
	{
	}

	
	virtual void SetUp(){
		logFile.makeFileCopy();

		//logFileUtility.registerModule(playerIdentificationModule);
		//logFileUtility.registerModule(expModule);
		logFileUtility.registerModule(apModule);
		//logFileUtility.registerModule(kinahModule);
		//logFileUtility.registerModule(soulHealerModule);

		string aionDirectory = "testModule/testLog/";
		
		ASSERT_TRUE(logFileUtility.setAionDirectory(aionDirectory));
		/*
		logFileUtility.registerMessageRuleCode(STR_MSG_COMBAT_MY_ABYSS_POINT_GAIN);
		logFileUtility.registerMessageRuleCode(STR_MSG_USE_ABYSSPOINT);
		logFileUtility.registerMessageRuleCode(STR_CANNOT_GET_AP_TARGET_LIMIT);
		logFileUtility.registerMessageRuleCode(STR_CANNOT_GET_AP_TIMEBASE_LIMIT);
		logFileUtility.registerMessageRuleCode(STR_MSG_COMBAT_HOSTILE_DEATH_TO_ME);
		logFileUtility.registerMessageRuleCode(STR_MSG_COMBAT_HOSTILE_DEATH_TO_B);
		logFileUtility.registerMessageRuleCode(STR_MSG_COMBAT_HOSTILE_DEATH);
		*/
	}


	virtual void TearDown(){		
		logFile.deleteFileCopy();
	}
};


TEST_F(ApModuleTest, pveAp){
	logFile.appendFile("2014.06.22 16:49:19 : Critical Hit!You inflicted 1,811 damage on Shaded Bloodwing by using Robust Blow VI. ");
	logFile.appendFile("2014.06.22 16:49:20 : Silence has been activated. ");	
	logFile.appendFile("2014.06.22 16:49:20 : You have gained 109,497 XP from Shaded Bloodwing. ");
	logFile.appendFile("2014.06.22 16:49:20 : Shaded Bloodwing is no longer silenced. ");
	logFile.appendFile("2014.06.22 16:49:20 : Shaded Bloodwing restored its attack speed. ");
	logFile.appendFile("2014.06.22 16:49:20 : You have gained 75 Abyss Points. ");
	
	logFileUtility.parseLogFile();

	EXPECT_EQ(75, apModule.apGainMeter.getNetGained());
	EXPECT_EQ(75, apModule.apGainMeter.getLastChange());
	EXPECT_EQ(0, apModule.apGainMeter.getPvpAp());
	
	EXPECT_EQ(-1, apModule.abyssRankChecker.getCurrentValue());
	EXPECT_EQ(-1, apModule.abyssRankChecker.getCumulativeCurrentValue());
	EXPECT_EQ(-1, apModule.abyssRankChecker.getCurrentLevelMaxValue());
	EXPECT_FLOAT_EQ(0, apModule.abyssRankChecker.getPercent());
	EXPECT_FLOAT_EQ(0, apModule.abyssRankChecker.getCumulativePercent());	
	EXPECT_EQ(0, apModule.abyssRankChecker.getLastChangePercent());
}

TEST_F(ApModuleTest, apPurchase){
	apModule.abyssRankChecker.initialize(95000);

	logFile.appendFile("2013.07.03 18:15:39 : Your Abyss Rank has changed to Soldier, Rank 7. ");
	logFile.appendFile("2013.07.03 18:15:39 : You used 89,775 Abyss Points. ");
	logFile.appendFile("2013.07.03 18:15:40 : [3.LFG] [charname:Vladarina;1.0000 0.6941 0.6941]: Asmos, we expect a LOT of elyos to attack [pos:Pradeth;600060000 2676.0 2720.2 0.0 0] tonight. I need everybody (even level 50s) I can get inside of that fort EARLY, before 11 pm est vuln (5 hours). Bind  ");
	logFile.appendFile("2013.07.03 18:15:40 : You have purchased [item:140000816;ver4;;;;]. ");
	
	logFileUtility.parseLogFile();

	EXPECT_EQ(89775, apModule.apGainMeter.getTotalSpent());
	EXPECT_EQ(-89775, apModule.apGainMeter.getNetGained());
	EXPECT_EQ(3, apModule.abyssRankChecker.getCurrentLevel());
	EXPECT_NEAR(-455.62863, apModule.abyssRankChecker.getLastChangePercent(), 0.0001);

	EXPECT_EQ(95000-89775, apModule.abyssRankChecker.getCurrentValue());
	EXPECT_EQ(95000-89775, apModule.abyssRankChecker.getCumulativeCurrentValue());
}

TEST_F(ApModuleTest, pvpAp){

	apModule.abyssRankChecker.initialize(100000);

	logFile.appendFile("2014.06.18 22:53:24 : You have gained 522 Abyss Points. ");
	logFile.appendFile("2014.06.18 22:53:24 : You have gained 17,530 XP from CalamiityJane. ");
	logFile.appendFile("2014.06.18 22:53:24 : Quest updated: [Urgent Order] Kurius' Request ");
	logFile.appendFile("2014.06.18 22:53:24 : CalamiityJane is no longer poisoned. ");
	logFile.appendFile("2014.06.18 22:53:24 : CalamiityJane restored its attack speed. ");
	logFile.appendFile("2014.06.18 22:53:24 : You have defeated CalamiityJane. ");
	logFile.appendFile("2014.06.18 22:53:24 : Invalid target. ");

	logFileUtility.parseLogFile();

	EXPECT_EQ(522, apModule.apGainMeter.getTotalGained());
	EXPECT_EQ(522, apModule.apGainMeter.getNetGained());
	EXPECT_EQ(522, apModule.apGainMeter.getLastChange());
	EXPECT_EQ(522, apModule.apGainMeter.getPvpAp());

	EXPECT_EQ(100522, apModule.abyssRankChecker.getCurrentValue());
	EXPECT_EQ(100522, apModule.abyssRankChecker.getCumulativeCurrentValue());

	logFile.appendFile("2014.07.13 09:34:14 : You have gained 518 Abyss Points. ");
	logFile.appendFile("2014.07.13 09:34:14 : You cannot get any PvP XP from the current target for a while. ");
	logFile.appendFile("2014.07.13 09:34:14 : Zwenl is no longer silenced. ");
	logFile.appendFile("2014.07.13 09:34:14 : Zwenl restored its attack speed. ");
	logFile.appendFile("2014.07.13 09:34:14 : FinaIDash has defeated Zwenl. ");
	
	logFileUtility.parseLogFile();

	EXPECT_EQ(1040, apModule.apGainMeter.getTotalGained());
	EXPECT_EQ(1040, apModule.apGainMeter.getNetGained());
	EXPECT_EQ(518, apModule.apGainMeter.getLastChange());
	EXPECT_EQ(1040, apModule.apGainMeter.getPvpAp());

	EXPECT_EQ(101040, apModule.abyssRankChecker.getCurrentValue());
	EXPECT_EQ(101040, apModule.abyssRankChecker.getCumulativeCurrentValue());

	logFile.appendFile("2014.07.13 09:34:02 : You cannot get any Abyss Point from the current target for a while. ");
	logFile.appendFile("2014.07.13 09:34:02 : You cannot get any PvP XP from the current target for a while. ");
	logFile.appendFile("2014.07.13 09:34:02 : Kidnt is no longer shocked. ");
	logFile.appendFile("2014.07.13 09:34:02 : Kidnt restored its movement speed. ");
	logFile.appendFile("2014.07.13 09:34:02 : Kidnt restored its attack speed. ");
	logFile.appendFile("2014.07.13 09:34:02 : You have defeated Kidnt. ");
	
	logFileUtility.parseLogFile();

	EXPECT_EQ(1040, apModule.apGainMeter.getTotalGained());
	EXPECT_EQ(1040, apModule.apGainMeter.getNetGained());
	EXPECT_EQ(0, apModule.apGainMeter.getLastChange());
	EXPECT_EQ(1040, apModule.apGainMeter.getPvpAp());

	logFile.appendFile("2014.06.22 16:44:24 : IDizzyI inflicted 512 damage on Dalbert by using Trunk Shot V. ");
	logFile.appendFile("2014.06.22 16:44:24 : Dalbert was knocked back from shock because IDizzyI used Trunk Shot V. ");
	logFile.appendFile("2014.06.22 16:44:25 : Dalbert restored its movement speed. ");
	logFile.appendFile("2014.06.22 16:44:25 : Dalbert is in the teleport state as it used Graspbreaker I. ");
	logFile.appendFile("2014.06.22 16:44:25 : Dalbert used Graspbreaker I to dispel magic effects. ");
	logFile.appendFile("2014.06.22 16:44:26 : Noble Energy inflicted 692 damage on Dalbert by using Noble Energy VI. ");
	logFile.appendFile("2014.06.22 16:44:26 : Shaded Bloodwing inflicted 764 damage on Valanya. ");
	logFile.appendFile("2014.06.22 16:44:26 : Dalbert is no longer staggering. ");
	logFile.appendFile("2014.06.22 16:44:26 : Dalbert restored its attack speed. ");
	logFile.appendFile("2014.06.22 16:44:26 : Shaimy has defeated Dalbert. ");
	
	logFileUtility.parseLogFile();

	logFile.appendFile("2014.06.22 16:49:19 : Critical Hit!You inflicted 1,811 damage on Shaded Bloodwing by using Robust Blow VI. ");
	logFile.appendFile("2014.06.22 16:49:20 : Silence has been activated. ");	
	logFile.appendFile("2014.06.22 16:49:20 : You have gained 109,497 XP from Shaded Bloodwing. ");
	logFile.appendFile("2014.06.22 16:49:20 : Shaded Bloodwing is no longer silenced. ");
	logFile.appendFile("2014.06.22 16:49:20 : Shaded Bloodwing restored its attack speed. ");
	logFile.appendFile("2014.06.22 16:49:20 : You have gained 75 Abyss Points. ");

	logFileUtility.parseLogFile();

	EXPECT_EQ(1115, apModule.apGainMeter.getTotalGained());
	EXPECT_EQ(1115, apModule.apGainMeter.getNetGained());
	EXPECT_EQ(75, apModule.apGainMeter.getLastChange());
	EXPECT_EQ(1040, apModule.apGainMeter.getPvpAp());

}

TEST_F(ApModuleTest, DoNotCountDisciplineKOAsPvpKill){
	logFile.appendFile("2014.10.24 23:27:19 : You have gained 1,833 Abyss Points. ");
	logFile.appendFile("2014.10.24 23:27:19 : You have acquired 1,085 [item:186000130;ver6;;;;]s and stored them in your special cube. ");
	logFile.appendFile("2014.10.24 23:27:19 : You have acquired 79 [item:186000137;ver6;;;;]s and stored them in your special cube. ");
	logFile.appendFile("2014.10.24 23:27:19 : You have gained 200 points from Liudviken-TM. ");
	logFile.appendFile("2014.10.24 23:27:19 : You have defeated Liudviken-TM. ");
	logFile.appendFile("2014.10.24 23:27:19 : Quest updated: After the Warm-Up ");
	logFile.appendFile("2014.10.24 23:27:19 : You have gained 52 Glory Points. ");

	logFileUtility.parseLogFile();

	EXPECT_EQ(1833, apModule.apGainMeter.getTotalGained());
	EXPECT_EQ(1833, apModule.apGainMeter.getNetGained());
	EXPECT_EQ(1833, apModule.apGainMeter.getLastChange());
	EXPECT_EQ(0, apModule.apGainMeter.getPvpAp());

}

TEST_F(ApModuleTest, gainRelic){
	logFile.appendFile("2014.07.19 17:14:47 : You have acquired [item:186000058;ver6;;;;]. ");

	logFileUtility.parseLogFile();

	EXPECT_EQ(0, apModule.apGainMeter.getTotalGained());
	EXPECT_EQ(0, apModule.apGainMeter.getNetGained());
	EXPECT_EQ(0, apModule.apGainMeter.getLastChange());
	EXPECT_EQ(1200, apModule.apGainMeter.getRelicAp());
	EXPECT_EQ(0, apModule.apGainMeter.getPvpAp());

	logFile.appendFile("2014.07.19 17:14:47 : You have acquired [item:186000066;ver6;;;;]. ");

	logFileUtility.parseLogFile();

	EXPECT_EQ(0, apModule.apGainMeter.getTotalGained());
	EXPECT_EQ(0, apModule.apGainMeter.getNetGained());
	EXPECT_EQ(0, apModule.apGainMeter.getLastChange());
	EXPECT_EQ(1515, apModule.apGainMeter.getRelicAp());
	EXPECT_EQ(0, apModule.apGainMeter.getPvpAp());

}

TEST_F(ApModuleTest, notRelicIItamz){
	logFile.appendFile("2014.12.06 14:39:47 : You have acquired [item:152012566;ver6;;;;]. ");

	logFileUtility.parseLogFile();

	EXPECT_EQ(0, apModule.apGainMeter.getTotalGained());
	EXPECT_EQ(0, apModule.apGainMeter.getNetGained());
	EXPECT_EQ(0, apModule.apGainMeter.getLastChange());
	EXPECT_EQ(0, apModule.apGainMeter.getRelicAp());
	EXPECT_EQ(0, apModule.apGainMeter.getPvpAp());

}

TEST_F(ApModuleTest, relics){
	apModule.abyssRankChecker.initialize(10000);
	EXPECT_EQ(10000, apModule.abyssRankChecker.getCurrentValue());

	logFile.appendFile("2013.07.23 12:32:19 : You have acquired [item:186000066;ver4;;;;]. ");
	logFile.appendFile("2013.07.23 12:32:19 : You have acquired 2 [item:162000120;ver4;;;;](s). ");
	logFileUtility.parseLogFile();

	EXPECT_EQ(apModule.relicAp.getRelicApValue(186000066), apModule.apGainMeter.getRelicAp());

	logFile.appendFile("2013.07.22 17:19:53 : Quest updated: [Daily] Sweeping Away the Elyos ");
	logFile.appendFile("2013.07.22 17:19:54 : You have acquired 12 [item:186000236;ver4;;;;]s and stored them in your special cube. ");
	logFile.appendFile("2013.07.22 17:19:54 : You have gained 3,446,516 XP from Hrund. ");
	logFile.appendFile("2013.07.22 17:19:54 : You can receive the weekly quest again at 9 in the morning on Wednesday. ");
	logFile.appendFile("2013.07.22 17:19:54 : Quest complete: [Daily] Sweeping Away the Elyos ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2013.11.07 03:15:58 : Sales complete.");
	logFile.appendFile("2013.11.07 03:15:58 : You have earned 288 Kinah.");	
	logFileUtility.parseLogFile();
	
	logFile.appendFile( "2013.09.03 22:39:32 : You sold the item. ");	
	logFile.appendFile( "2013.09.03 22:39:32 : You have gained 376,068 Abyss Points. ");	

	logFileUtility.parseLogFile();

	EXPECT_EQ(386068, apModule.abyssRankChecker.getCurrentValue());
	EXPECT_EQ(376068, apModule.apGainMeter.getTotalGained());
	EXPECT_EQ(376068, apModule.apGainMeter.getNetGained());
	EXPECT_EQ(apModule.relicAp.getRelicApValue(186000066) - 376068, apModule.apGainMeter.getRelicAp());

}