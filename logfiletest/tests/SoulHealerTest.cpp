#include "gtest/gtest.h"
#include "../parser/RuleStrings.h"

#include "../lookups/ExpChartNA40.h"
#include "../lookups/ApChart.h"

#include "../model/ServerState.h"
#include "../model/ExpGainMeter.h"
#include "../model/ApGainMeter.h"

#include "../model/KinahGainMeter.h"
#include "../model/SoulHealer.h"

class mockRuleStrings: public RuleStrings{
public:
	mockRuleStrings(){
		rules["STR_INTERSERVER_ORIGINAL_NAME"] = "Standard Server";
		rules["STR_INTERSERVER_NOVICE_NAME"] = "Fast-Track Server";
		rules["STR_INSTANCE_DUNGEON_INTER_SERVER"] = "Instance Server";
	}
};

class SoulHealerTest: public ::testing::Test{
protected:
	ServerState serverState;
	
	ExpChartNA40 expChart;
	ApChart apChart;

	LevelUpChecker levelUpChecker;
	LevelUpChecker abyssRankUpChecker;

	ExpGainMeter expGainMeter;	
	ApGainMeter apGainMeter;	
	KinahGainMeter kinahMeter;
	
	SoulHealer soulHealer;

	SoulHealerTest():
		expGainMeter(levelUpChecker), 					
		apGainMeter(abyssRankUpChecker),
		soulHealer(expGainMeter, levelUpChecker, abyssRankUpChecker, 
			kinahMeter, serverState)
	{
		levelUpChecker.setExpChart(expChart);
		abyssRankUpChecker.setExpChart(apChart);
	}

	virtual void SetUp(){
		RULE_STRINGS = new mockRuleStrings();
	}

	virtual void TearDown(){		
		delete(RULE_STRINGS);
	}
};

TEST_F(SoulHealerTest, pveDeath1){

	levelUpChecker.initialize(13, 61851);
	
	soulHealer.PvEDeath();

	EXPECT_TRUE(soulHealer.isExpUpdateNeeded());
	EXPECT_FALSE(soulHealer.isApUpdateNeeded());
	
	kinahMeter.spend(551);
	expGainMeter.gain(2171);
	soulHealer.soulHeal();

	EXPECT_EQ(-1085,expGainMeter.getNetGained());
	EXPECT_EQ(-1085, expGainMeter.getLastChange());
	EXPECT_EQ(-551, kinahMeter.getNetGained());
	EXPECT_EQ(-551, kinahMeter.getLastChange());
}

TEST_F(SoulHealerTest, pveDeath2){

	levelUpChecker.initialize(43, 21016061);
	
	soulHealer.PvEDeath();
	kinahMeter.spend(18022);
	expGainMeter.gain(244780);
	soulHealer.soulHeal();

	EXPECT_EQ(-122390, expGainMeter.getNetGained());
	EXPECT_EQ(-122390, expGainMeter.getLastChange());
	EXPECT_EQ(20893671, levelUpChecker.getCurrentValue());
	EXPECT_EQ(-18022, kinahMeter.getNetGained());
	EXPECT_EQ(-18022, kinahMeter.getLastChange());
	
	soulHealer.PvEDeath();
	kinahMeter.spend(18022);
	expGainMeter.gain(244780);
	soulHealer.soulHeal();

	EXPECT_EQ(-244780, expGainMeter.getNetGained());
	EXPECT_EQ(-122390, expGainMeter.getLastChange());
	EXPECT_EQ(20771281, levelUpChecker.getCurrentValue());
	EXPECT_EQ(-36044, kinahMeter.getNetGained());
	EXPECT_EQ(-18022, kinahMeter.getLastChange());
	
}

TEST_F(SoulHealerTest, oneKinahSoulHealing){

	levelUpChecker.initialize(43, 21016061);	
	abyssRankUpChecker.initialize(10000);

	soulHealer.PvEDeath();
	kinahMeter.spend(1);	
	soulHealer.soulHeal();

	EXPECT_EQ(0, expGainMeter.getNetGained());
	EXPECT_EQ(0, expGainMeter.getLastChange());
	EXPECT_EQ(21016061, levelUpChecker.getCurrentValue());
	EXPECT_EQ(-1, kinahMeter.getNetGained());
	EXPECT_EQ(-1, kinahMeter.getLastChange());
	
	EXPECT_FALSE(soulHealer.isExpUpdateNeeded());
	EXPECT_TRUE(soulHealer.isApUpdateNeeded());	
	
}


TEST_F(SoulHealerTest, oneKinahSoulHealingNoInit){

	levelUpChecker.initialize(43, 21016061);	

	soulHealer.PvEDeath();
	kinahMeter.spend(1);	
	soulHealer.soulHeal();

	EXPECT_EQ(0, expGainMeter.getNetGained());
	EXPECT_EQ(0, expGainMeter.getLastChange());
	EXPECT_EQ(21016061, levelUpChecker.getCurrentValue());
	EXPECT_EQ(-1, kinahMeter.getNetGained());
	EXPECT_EQ(-1, kinahMeter.getLastChange());
	
	EXPECT_FALSE(soulHealer.isExpUpdateNeeded());
	EXPECT_FALSE(soulHealer.isApUpdateNeeded());	
	
}

TEST_F(SoulHealerTest, pvpDeath){

	levelUpChecker.initialize(43, 21016061);	
	abyssRankUpChecker.initialize(10000);

	soulHealer.PvPDeath();
		
	EXPECT_TRUE(soulHealer.isApUpdateNeeded());	
	
}

TEST_F(SoulHealerTest, pvpDeathNoInit){
	soulHealer.PvPDeath();
		
	EXPECT_FALSE(soulHealer.isApUpdateNeeded());		
}

TEST_F(SoulHealerTest, pvpDeathArena){

	levelUpChecker.initialize(43, 21016061);	
	abyssRankUpChecker.initialize(10000);
	serverState.moveServer("Instance Server");

	soulHealer.PvPDeath();
		
	EXPECT_FALSE(soulHealer.isExpUpdateNeeded());
	EXPECT_FALSE(soulHealer.isApUpdateNeeded());

	serverState.moveServer("Standard Server");
	
	soulHealer.PvPDeath();

	EXPECT_FALSE(soulHealer.isExpUpdateNeeded());
	EXPECT_TRUE(soulHealer.isApUpdateNeeded());

		
}

TEST_F(SoulHealerTest, clearExpUpdate){
	levelUpChecker.initialize(44, 10000000);	
	soulHealer.PvEDeath();
	soulHealer.nothingToRecover();
		
	EXPECT_FALSE(soulHealer.isExpUpdateNeeded());
	EXPECT_FALSE(soulHealer.isApUpdateNeeded());	
	
}

TEST_F(SoulHealerTest, manualExpUpdate1){
	levelUpChecker.initialize(44, 10000000);	
	soulHealer.PvEDeath();
	EXPECT_TRUE(soulHealer.manualExpUpdate(10000000 - 380752));
	
	EXPECT_EQ(10000000 - 380752, levelUpChecker.getCurrentValue());
	EXPECT_EQ(267247400 + 10000000 - 380752, levelUpChecker.getCumulativeCurrentValue());
	EXPECT_EQ(380752, expGainMeter.getTotalLost());
	EXPECT_EQ(-380752, expGainMeter.getNetGained());

	EXPECT_FALSE(soulHealer.isExpUpdateNeeded());
	EXPECT_FALSE(soulHealer.isApUpdateNeeded());	
	
	kinahMeter.spend(20000);
	expGainMeter.gain(150000);
	soulHealer.soulHeal();

	EXPECT_EQ(10000000 - 380752 + 150000, levelUpChecker.getCurrentValue());

}

TEST_F(SoulHealerTest, manualExpUpdateInvalid){
	levelUpChecker.initialize(44, 10000000);	
	soulHealer.PvEDeath();
	EXPECT_FALSE(soulHealer.manualExpUpdate(10000001));
	
	EXPECT_EQ(10000000, levelUpChecker.getCurrentValue());
	EXPECT_EQ(267247400 + 10000000, levelUpChecker.getCumulativeCurrentValue());
	EXPECT_EQ(0, expGainMeter.getTotalLost());
	EXPECT_EQ(0, expGainMeter.getNetGained());

	EXPECT_TRUE(soulHealer.isExpUpdateNeeded());
	EXPECT_FALSE(soulHealer.isApUpdateNeeded());	
	
}

TEST_F(SoulHealerTest, manualExpUpdateZero){
	levelUpChecker.initialize(44, 10000000);	
	soulHealer.PvEDeath();
	EXPECT_TRUE(soulHealer.manualExpUpdate(10000000));
	
	EXPECT_EQ(10000000, levelUpChecker.getCurrentValue());
	EXPECT_EQ(267247400 + 10000000, levelUpChecker.getCumulativeCurrentValue());
	EXPECT_EQ(0, expGainMeter.getTotalLost());
	EXPECT_EQ(0, expGainMeter.getNetGained());

	EXPECT_FALSE(soulHealer.isExpUpdateNeeded());
	EXPECT_TRUE(soulHealer.isApUpdateNeeded());	
	
}

TEST_F(SoulHealerTest, manualApUpdate){
	abyssRankUpChecker.initialize(100000);	
	soulHealer.PvPDeath();
	
	EXPECT_EQ(serverState.STANDARD_SERVER, serverState.getCurrentServer());	

	EXPECT_FALSE(soulHealer.isExpUpdateNeeded());
	EXPECT_TRUE(soulHealer.isApUpdateNeeded());	
	
	EXPECT_TRUE(soulHealer.manualApUpdate(95000));

	EXPECT_EQ(95000, abyssRankUpChecker.getCurrentValue());
	EXPECT_EQ(95000, abyssRankUpChecker.getCurrentValue());
	EXPECT_EQ(5000, apGainMeter.getTotalLost());
	EXPECT_EQ(-5000, apGainMeter.getNetGained());	
	
	kinahMeter.spend(1);
	soulHealer.soulHeal();

	EXPECT_FALSE(soulHealer.isExpUpdateNeeded());
	EXPECT_FALSE(soulHealer.isApUpdateNeeded());	
	

}

TEST_F(SoulHealerTest, manualApUpdateInvalid){
	abyssRankUpChecker.initialize(100000);	
	soulHealer.PvPDeath();
	
	EXPECT_EQ(serverState.STANDARD_SERVER, serverState.getCurrentServer());	

	EXPECT_FALSE(soulHealer.isExpUpdateNeeded());
	EXPECT_TRUE(soulHealer.isApUpdateNeeded());	
	
	EXPECT_FALSE(soulHealer.manualApUpdate(100001));

	EXPECT_FALSE(soulHealer.isExpUpdateNeeded());
	EXPECT_TRUE(soulHealer.isApUpdateNeeded());	
	
	EXPECT_EQ(100000, abyssRankUpChecker.getCurrentValue());
	EXPECT_EQ(100000, abyssRankUpChecker.getCurrentValue());
	EXPECT_EQ(0, apGainMeter.getTotalLost());
	EXPECT_EQ(0, apGainMeter.getNetGained());	
	
}


int main(int argc, char** argv){
	testing::InitGoogleTest(&argc, argv); 
	RUN_ALL_TESTS();
	getchar();
	return 0;
}