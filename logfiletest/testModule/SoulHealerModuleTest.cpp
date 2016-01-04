#include "gtest/gtest.h"

#include "../modules/SoulHealerModule.h"

#include "../parser/LogFileUtility.h"
#include "testLog/TemporaryLogFile.h"

class SoulHealerModuleTest: public ::testing::Test{
protected:

	ExpModule expModule;
	ApModule apModule;
	KinahModule kinahModule;
	SoulHealerModule soulHealerModule;
	
	TemporaryLogFile logFile;
	
	LogFileUtility logFileUtility;
	

	SoulHealerModuleTest(): logFile("testModule/testLog/tests.log", "testModule/testLog/Chat.log"),
		soulHealerModule(expModule, apModule, kinahModule)
	{
	}

	
	virtual void SetUp(){
		logFile.makeFileCopy();

		//logFileUtility.registerModule(playerIdentificationModule);
		logFileUtility.registerModule(expModule);
		logFileUtility.registerModule(apModule);
		logFileUtility.registerModule(kinahModule);
		logFileUtility.registerModule(soulHealerModule);

		string aionDirectory = "testModule/testLog/";
		
		ASSERT_TRUE(logFileUtility.setAionDirectory(aionDirectory));
		
	}


	virtual void TearDown(){		
		logFile.deleteFileCopy();
	}
};


TEST_F(SoulHealerModuleTest, PveDeath){
	expModule.levelUpChecker.initialize(13, 61851);
	apModule.abyssRankChecker.initialize(1000000);

	logFile.appendFile("2013.06.27 23:03:19 : You are no longer bleeding. ");
	logFile.appendFile("2013.06.27 23:03:19 : You have died. ");
	
	logFileUtility.parseLogFile();

	EXPECT_TRUE(soulHealerModule.soulHealer.isExpUpdateNeeded());
	EXPECT_FALSE(soulHealerModule.soulHealer.isApUpdateNeeded());

	logFile.appendFile("2013.07.04 18:15:04 : You spent 551 Kinah. ");
	logFile.appendFile("2013.07.04 18:15:04 : You have gained 2,171 XP. ");
	logFile.appendFile("2013.07.04 18:15:04 : You received Soul Healing. ");
	
	logFileUtility.parseLogFile();


	EXPECT_EQ(-1085, expModule.expGainMeter.getNetGained());
	EXPECT_EQ(-1085, expModule.expGainMeter.getLastChange());
	EXPECT_EQ(-551, kinahModule.kinahGainMeter.getNetGained());
	EXPECT_EQ(-551, kinahModule.kinahGainMeter.getLastChange());
	

}

TEST_F(SoulHealerModuleTest, PveDeath2){
	expModule.levelUpChecker.initialize(13, 61851);
	apModule.abyssRankChecker.initialize(1000000);

	logFile.appendFile("2014.06.22 10:15:39 : You received 10,179 damage from Company Bodyguard. ");
	logFile.appendFile("2014.06.22 10:15:41 : You received a delayed chain effect from Extended Mortal Wound used by Company Bodyguard. ");
	logFile.appendFile("2014.06.22 10:15:43 : Company Bodyguard gives up the pursuit. ");
	logFile.appendFile("2014.06.22 10:15:44 : You received 9,604 damage from Company Bodyguard. ");
	logFile.appendFile("2014.06.22 10:15:44 : You cannot use an item while in your current status. ");
	logFile.appendFile("2014.06.22 10:15:45 : You cannot use an item while in your current status. ");
	logFile.appendFile("2014.06.22 10:15:45 : You cannot use an item while in your current status. ");
	logFile.appendFile("2014.06.22 10:15:45 : You have died. ");
	logFile.appendFile("2014.06.22 10:15:52 : You have resurrected. ");

	logFileUtility.parseLogFile();

	EXPECT_TRUE(soulHealerModule.soulHealer.isExpUpdateNeeded());
	EXPECT_FALSE(soulHealerModule.soulHealer.isApUpdateNeeded());

	logFile.appendFile("2014.06.22 10:15:52 : You cannot attack the enemy faction in this region. ");
	logFile.appendFile("2014.06.22 10:15:56 : You spent 1 Kinah. ");
	logFile.appendFile("2014.06.22 10:15:56 : You received Soul Healing. ");

	logFileUtility.parseLogFile();

	EXPECT_FALSE(soulHealerModule.soulHealer.isExpUpdateNeeded());
	EXPECT_TRUE(soulHealerModule.soulHealer.isApUpdateNeeded());
}

TEST_F(SoulHealerModuleTest, noExpToRecover){
	expModule.levelUpChecker.initialize(65, 584561235);

	logFile.appendFile("2014.08.30 14:55:21 : Megazero-TM has joined. ");
	logFile.appendFile("2014.08.30 14:55:25 : You have successfully entered the area, consuming one of your permitted entries. ");
	logFile.appendFile("2014.08.30 14:55:25 : You have joined Instance Server. ");
	logFile.appendFile("2014.08.30 14:55:26 : You can receive the daily quest. ");
	logFile.appendFile("2014.08.30 14:55:26 : You can receive the weekly quest. ");
	logFile.appendFile("2014.08.30 14:55:31 : You have joined the Arena of Discipline region channel. ");
	logFile.appendFile("2014.08.30 14:55:31 : You have joined the Arena of Discipline trade channel. ");
	logFile.appendFile("2014.08.30 14:55:31 : You have joined the LFG Channel. ");
	logFile.appendFile("2014.08.30 14:55:34 : You have joined the Templar Channel. ");

	logFileUtility.parseLogFile();

	EXPECT_EQ(soulHealerModule.serverState.INSTANCE_SERVER, soulHealerModule.serverState.getCurrentServer());

	logFile.appendFile("2014.08.30 15:01:30 : Ranked down to 2. ");
	logFile.appendFile("2014.08.30 15:01:30 : Your attack speed is restored to normal. ");
	logFile.appendFile("2014.08.30 15:01:30 : You were killed by Megazero-TM's attack. ");
	logFile.appendFile("2014.08.30 15:01:32 : Megazero-TM is no longer staggering. ");

	logFileUtility.parseLogFile();

	logFile.appendFile("2014.08.30 15:04:49 : You receive 10,537 damage due to Abyssal Distortion. ");
	logFile.appendFile("2014.08.30 15:04:49 : You have died. ");

	logFileUtility.parseLogFile();

	logFile.appendFile("2014.07.12 10:22:46 : You do not have any XP to recover. ");

	logFileUtility.parseLogFile();
	
	EXPECT_FALSE(soulHealerModule.soulHealer.isExpUpdateNeeded());
	EXPECT_FALSE(soulHealerModule.soulHealer.isApUpdateNeeded());	

}

TEST_F(SoulHealerModuleTest, pvpDeath){
	expModule.levelUpChecker.initialize(65, 584561235);
	apModule.abyssRankChecker.initialize(1000000);

	logFile.appendFile("2014.07.12 10:36:30 : You are no longer paralyzed. ");
	logFile.appendFile("2014.07.12 10:36:30 : You are no longer immobilized. ");
	logFile.appendFile("2014.07.12 10:36:30 : You are no longer silenced. ");
	logFile.appendFile("2014.07.12 10:36:30 : You were killed by Yuravica's attack. ");
	logFile.appendFile("2014.07.12 10:36:30 : You stopped using Steel Wall Defense I. ");

	logFileUtility.parseLogFile();
	
	EXPECT_FALSE(soulHealerModule.soulHealer.isExpUpdateNeeded());
	EXPECT_TRUE(soulHealerModule.soulHealer.isApUpdateNeeded());	

}

TEST_F(SoulHealerModuleTest, pvpDeathButFinishedOffByMonster){
	expModule.levelUpChecker.initialize(65, 584561235);
	apModule.abyssRankChecker.initialize(1000000);

	logFile.appendFile("2013.06.27 18:54:59 : Ramthel has inflicted 4,146 damage on you by using Aetheric Spell V. ");
	logFile.appendFile("2013.06.27 18:55:00 : Trihorn Lapilima restored its attack speed. ");
	logFile.appendFile("2013.06.27 18:55:01 : Ramthel has inflicted 298 damage on you by using Flame Cage IV. ");
	logFile.appendFile("2013.06.27 18:55:01 : You received continuous damage because Ramthel used Flame Cage IV. ");
	logFile.appendFile("2013.06.27 18:55:01 : You inflicted 371 damage on Ramthel. ");
	logFile.appendFile("2013.06.27 18:55:02 : Critical Hit!You inflicted 927 damage on Ramthel by using Illusion Chains I. ");
	logFile.appendFile("2013.06.27 18:55:02 : Critical Hit!Ramthel's movement speed decreased as you used Illusion Chains I. ");
	logFile.appendFile("2013.06.27 18:55:02 : You receive 556 damage due to Bleeding. ");
	logFile.appendFile("2013.06.27 18:55:02 : Ramthel has immobilized you by using Root I. ");
	logFile.appendFile("2013.06.27 18:55:03 : Critical Hit!You inflicted 933 damage on Ramthel by using Punishing Wave III. ");
	logFile.appendFile("2013.06.27 18:55:03 : You inflicted 1,804 damage on Trihorn Lapilima by using Punishing Wave III. ");
	logFile.appendFile("2013.06.27 18:55:04 : You inflicted 404 damage on Ramthel by using Dazing Severe Blow III. ");
	logFile.appendFile("2013.06.27 18:55:04 : Ramthel's attack speed has decreased because Momomomoo used Dazing Severe Blow III. ");
	logFile.appendFile("2013.06.27 18:55:04 : You received 832 damage from Trihorn Lapilima. ");
	logFile.appendFile("2013.06.27 18:55:04 : You cannot do that while you are in combat. ");
	logFile.appendFile("2013.06.27 18:55:05 : You are no longer immobilized. ");
	logFile.appendFile("2013.06.27 18:55:05 : You are no longer silenced. ");
	logFile.appendFile("2013.06.27 18:55:05 : Your movement speed is restored to normal. ");
	logFile.appendFile("2013.06.27 18:55:05 : You have died. ");

	logFileUtility.parseLogFile();
		
	EXPECT_FALSE(soulHealerModule.soulHealer.isExpUpdateNeeded());
	EXPECT_TRUE(soulHealerModule.soulHealer.isApUpdateNeeded());	

}

TEST_F(SoulHealerModuleTest, pvpDeathButFinishedOffByMonster2){
	expModule.levelUpChecker.initialize(65, 584561235);
	apModule.abyssRankChecker.initialize(1000000);

	logFile.appendFile("2014.10.18 00:42:18 : Critical Hit!Xhargos inflicted 585 damage and the rune carve effect on you by using Fang Strike V. ");
	logFile.appendFile("2014.10.18 00:42:18 : [3.LFG] [charname:JackOkumura;1.0000 0.6941 0.6941]: [cmd:n1h5c27h506h0g6O1MsjIAdS+ffLdlryl3pvEFabceRFUYOZnylZ5HCClET+4/tC+Suc2zKclhIxV9MqhOlVjPCGPHpT7GfYH4Sgk56vZEM=] DEFEND UAS, DEFEND OUR DIVINE!! INCOMING DREDGE!!! ???????? FREE MEDALS???? ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2014.10.18 00:42:18 : Xhargos inflicted 228 damage and the rune carve effect on you by using Beast Kick IV. ");
	logFile.appendFile("2014.10.18 00:42:19 : Xhargos inflicted 283 damage and the rune carve effect on you by using Beast Swipe III. ");
	logFile.appendFile("2014.10.18 00:42:19 : You inflicted 352 damage on Xhargos. ");
	logFile.appendFile("2014.10.18 00:42:19 : You inflicted 35 damage on Xhargos. ");
	logFile.appendFile("2014.10.18 00:42:19 : You parried Shaded Bloodwing's attack. ");
	logFile.appendFile("2014.10.18 00:42:19 : You received 442 damage from Shaded Bloodwing. ");
	logFile.appendFile("2014.10.18 00:42:19 : Critical Hit!You inflicted 726 damage on Xhargos by using Robust Blow VI. ");
	logFile.appendFile("2014.10.18 00:42:19 : Xhargos has inflicted 1,094 damage on you by using Pain Rune V. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2014.10.18 00:42:20 : Xhargos is in the boost Attack state because Xhargos used Devotion I. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2014.10.18 00:42:21 : You received 531 damage from Shaded Bloodwing. ");
	logFile.appendFile("2014.10.18 00:42:21 : Critical Hit!Xhargos has inflicted 1,211 damage on you by using Shadowfall I. ");
	logFile.appendFile("2014.10.18 00:42:21 : Critical Hit!Xhargos has knocked you down by using Shadowfall I. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2014.10.18 00:42:22 : You are no longer stunned. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2014.10.18 00:42:23 : You received 43 poisoning damage due to the effect of Apply Poison III Effect. ");
	logFile.appendFile("2014.10.18 00:42:23 : You received 468 damage from Shaded Bloodwing. ");
	logFile.appendFile("2014.10.18 00:42:23 : [3.LFG] [charname:Mirelium;1.0000 0.6941 0.6941]: [cmd:aNmzbV9McTgGTUkMpEDDgUVRg5mfKVnkcIKURP7j+0JFUYOZnylZ5HCClET+4/tCyBvm0d1Nq/JHS36yUooDgYwjaM4uFPO/1LAKcq5ziRk=] ??DIVINE DEFENSE??  ");
	logFile.appendFile("2014.10.18 00:42:23 : Critical Hit!Xhargos has inflicted 704 damage on you by using Swift Edge VI. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2014.10.18 00:42:24 : Xhargos has inflicted 326 damage on you by using Soul Slash VI. ");
	logFile.appendFile("2014.10.18 00:42:24 : You are no longer shocked. ");
	logFile.appendFile("2014.10.18 00:42:24 : You cannot cast spells while silenced. ");
	logFile.appendFile("2014.10.18 00:42:24 : Xhargos inflicted 240 damage and the rune carve effect on you by using Rune Carve V. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2014.10.18 00:42:25 : Critical Hit!Xhargos inflicted 692 damage and the rune carve effect on you by using Fang Strike V. ");
	logFile.appendFile("2014.10.18 00:42:25 : You parried Shaded Bloodwing's attack. ");
	logFile.appendFile("2014.10.18 00:42:25 : You received 367 damage from Shaded Bloodwing. ");
	logFile.appendFile("2014.10.18 00:42:25 : Critical Hit!You inflicted 577 damage on Xhargos by using Doom Lure I. ");
	logFile.appendFile("2014.10.18 00:42:25 : Critical Hit!Xhargos's movement speed decreased as you used Doom Lure I. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2014.10.18 00:42:26 : You received 43 poisoning damage due to the effect of Apply Poison III Effect. ");
	logFile.appendFile("2014.10.18 00:42:26 : You are no longer poisoned. ");
	logFile.appendFile("2014.10.18 00:42:26 : You are no longer silenced. ");
	logFile.appendFile("2014.10.18 00:42:26 : You have died. ");
	logFile.appendFile("2014.10.18 00:42:26 : You have defeated Xhargos. ");

	logFileUtility.parseLogFile();

	EXPECT_FALSE(soulHealerModule.soulHealer.isExpUpdateNeeded());
	EXPECT_TRUE(soulHealerModule.soulHealer.isApUpdateNeeded());	

}

TEST_F(SoulHealerModuleTest, pvpDeathButAPNotInitialized1){
	

	logFile.appendFile("2014.06.28 11:42:08 : You were killed by Bladedchaos's attack. ");
	
	logFileUtility.parseLogFile();
		
	EXPECT_FALSE(soulHealerModule.soulHealer.isExpUpdateNeeded());
	EXPECT_FALSE(soulHealerModule.soulHealer.isApUpdateNeeded());	

}

TEST_F(SoulHealerModuleTest, pvpDeathFromDOTAndFinishedOffByMonster){
	expModule.levelUpChecker.initialize(65, 584561235);
	apModule.abyssRankChecker.initialize(1000000);

	logFile.appendFile("2013.07.02 01:17:44 : You receive 233 damage due to Magic Implosion VI. ");
	logFile.appendFile("2013.07.02 01:17:46 : You recovered from your fear. ");
	logFile.appendFile("2013.07.02 01:17:46 : Your movement speed is restored to normal. ");
	logFile.appendFile("2013.07.02 01:17:46 : You have died. ");

	logFileUtility.parseLogFile();
		
	EXPECT_FALSE(soulHealerModule.soulHealer.isExpUpdateNeeded());
	EXPECT_TRUE(soulHealerModule.soulHealer.isApUpdateNeeded());	
}


/*

TEST_F(SoulHealerModuleTest, manualExpPercentInput){
	//13, 61851 / 129506
	expModule.levelUpChecker.initializePercent(13, 47.76);
	apModule.abyssRankChecker.initialize(1000000);

	logFile.appendFile("2013.06.27 23:03:19 : You are no longer bleeding. ");
	logFile.appendFile("2013.06.27 23:03:19 : You have died. ");
	
	//exp lost 4342

	logFileUtility.parseLogFile();

	soulHealerModule.soulHealer.

	EXPECT_TRUE(soulHealerModule.soulHealer.isExpUpdateNeeded());
	EXPECT_FALSE(soulHealerModule.soulHealer.isApUpdateNeeded());




	EXPECT_FALSE(soulHealerModule.soulHealer.isExpUpdateNeeded());
	EXPECT_TRUE(soulHealerModule.soulHealer.isApUpdateNeeded());
}
*/