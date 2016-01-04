#include "../model/ApGainMeter.h"
#include "../lookups/ApChart.h"
#include "gtest/gtest.h"

TEST(ApGainMeter, GainAp1){
	ApChart apChart;
	LevelUpChecker rankUpChecker;
	rankUpChecker.setExpChart(apChart);
	ApGainMeter meter(rankUpChecker);
	meter.gain(1008);	

	meter.applyFromBuffer();

	EXPECT_EQ(1008, meter.getTotalGained());
	EXPECT_EQ(1008, meter.getNetGained());	
	EXPECT_EQ(-1, rankUpChecker.getCurrentValue());
	EXPECT_EQ(-1, rankUpChecker.getCurrentLevelMaxValue());
}

TEST(ApGainMeter, SpendAp1){
	ApChart apChart;
	LevelUpChecker rankUpChecker;
	rankUpChecker.setExpChart(apChart);
	ApGainMeter meter(rankUpChecker);

	rankUpChecker.initialize(95000);
	meter.spend(89775);

	meter.applyFromBuffer();

	EXPECT_EQ(0, meter.getTotalGained());
	EXPECT_EQ(89775, meter.getTotalSpent());
	EXPECT_EQ(0, meter.getTotalLost());
	EXPECT_EQ(-89775, meter.getNetGained());	
	EXPECT_EQ(5225, rankUpChecker.getCurrentValue());
	EXPECT_EQ(10990, rankUpChecker.getCurrentLevelMaxValue());
}


TEST(ApGainMeter, LoseAp1){
	ApChart apChart;
	LevelUpChecker rankUpChecker;
	rankUpChecker.setExpChart(apChart);
	ApGainMeter meter(rankUpChecker);
	
	rankUpChecker.initialize(95000);

	rankUpChecker.setCurrentValue(94500);

	

	EXPECT_EQ(0, meter.getTotalGained());
	EXPECT_EQ(0, meter.getTotalSpent());
	EXPECT_EQ(500, meter.getTotalLost());
	EXPECT_EQ(-500, meter.getNetGained());	
	EXPECT_EQ(94500, rankUpChecker.getCurrentValue());
	EXPECT_EQ(105600, rankUpChecker.getCurrentLevelMaxValue());
}

TEST(ApGainMeter, invalidUpdate){
	ApChart apChart;
	LevelUpChecker rankUpChecker;
	rankUpChecker.setExpChart(apChart);
	ApGainMeter meter(rankUpChecker);
	
	rankUpChecker.initialize(95000);
	rankUpChecker.setCurrentValue(95001);

	EXPECT_EQ(0, meter.getTotalGained());
	EXPECT_EQ(0, meter.getTotalSpent());
	EXPECT_EQ(0, meter.getTotalLost());
	EXPECT_EQ(0, meter.getNetGained());	
	EXPECT_EQ(95000, rankUpChecker.getCurrentValue());
	EXPECT_EQ(105600, rankUpChecker.getCurrentLevelMaxValue());
}


TEST(ApBar, getPercent1){
	ApChart apChart;
	LevelUpChecker rankUpChecker;
	rankUpChecker.setExpChart(apChart);
	ApGainMeter meter(rankUpChecker);
	
	

	rankUpChecker.initialize(0);
	EXPECT_FLOAT_EQ(0, rankUpChecker.getPercent());
	rankUpChecker.initialize(900);
	EXPECT_FLOAT_EQ(75, rankUpChecker.getPercent());
	rankUpChecker.initialize(1200);
	EXPECT_FLOAT_EQ(0, rankUpChecker.getPercent());
	rankUpChecker.initialize(2710);
	EXPECT_FLOAT_EQ(50, rankUpChecker.getPercent());
	rankUpChecker.initialize(105600);
	EXPECT_FLOAT_EQ(0, rankUpChecker.getPercent());
	rankUpChecker.initialize(116900);
	EXPECT_FLOAT_EQ(25, rankUpChecker.getPercent());
	rankUpChecker.initialize(150800);
	EXPECT_FLOAT_EQ(100, rankUpChecker.getPercent());
	rankUpChecker.initialize(200000000);
	EXPECT_FLOAT_EQ(100, rankUpChecker.getPercent());	

}


TEST(ApBar, getPercent2){
	ApChart apChart;
	LevelUpChecker rankUpChecker;
	rankUpChecker.setExpChart(apChart);
	ApGainMeter meter(rankUpChecker);
	
	
	rankUpChecker.initialize(1, 0);
	EXPECT_FLOAT_EQ(0, rankUpChecker.getPercent());
	rankUpChecker.initialize(1, 900);
	EXPECT_FLOAT_EQ(75, rankUpChecker.getPercent());
	rankUpChecker.initialize(2, 1200);
	EXPECT_FLOAT_EQ(0, rankUpChecker.getPercent());
	rankUpChecker.initialize(2, 2710);
	EXPECT_FLOAT_EQ(50, rankUpChecker.getPercent());
	rankUpChecker.initialize(8, 105600);
	EXPECT_FLOAT_EQ(0, rankUpChecker.getPercent());
	rankUpChecker.initialize(8, 116900);
	EXPECT_FLOAT_EQ(25, rankUpChecker.getPercent());
	rankUpChecker.initialize(9, 150800);
	EXPECT_FLOAT_EQ(100, rankUpChecker.getPercent());
	rankUpChecker.initialize(9, 200000000);
	EXPECT_FLOAT_EQ(100, rankUpChecker.getPercent());	

}

TEST(ApBar, cumulative1){
	ApChart apChart;
	LevelUpChecker rankUpChecker;
	rankUpChecker.setExpChart(apChart);
	ApGainMeter meter(rankUpChecker);
	
	rankUpChecker.initialize(1, 100);	
	EXPECT_EQ(100, rankUpChecker.getCumulativeCurrentValue());
	rankUpChecker.initialize(9, 151800);
	EXPECT_EQ(151800, rankUpChecker.getCumulativeCurrentValue());
}

TEST(ApBar, getLevelCap){
	ApChart apChart;
	EXPECT_EQ(150800, apChart.getLevelCapValue());

}

TEST(ApBar, getCumulativePercent){
	ApChart apChart;
	LevelUpChecker rankUpChecker;
	rankUpChecker.setExpChart(apChart);
	ApGainMeter meter(rankUpChecker);
	
	rankUpChecker.initialize(7, 75400);
	EXPECT_FLOAT_EQ(0.5, rankUpChecker.getCumulativePercent());

}

TEST(ApBar, calculateDecimalLevel){
	ApChart apChart;
	LevelUpChecker rankUpChecker;
	rankUpChecker.setExpChart(apChart);
	ApGainMeter meter(rankUpChecker);
	
	rankUpChecker.initialize(95000);
	EXPECT_FLOAT_EQ(7.7047354, rankUpChecker.getCurrentDecimalLevel());

}

TEST(ApBar, calculateDecimalLevelNoInit){
	ApChart apChart;
	LevelUpChecker rankUpChecker;
	rankUpChecker.setExpChart(apChart);
	ApGainMeter meter(rankUpChecker);
		
	EXPECT_FLOAT_EQ(-1, rankUpChecker.getCurrentDecimalLevel());

}

TEST(ApGainMeter, GainRank1){
	ApChart apChart;
	LevelUpChecker rankUpChecker;
	rankUpChecker.setExpChart(apChart);
	ApGainMeter meter(rankUpChecker);
	rankUpChecker.initialize(600);

	meter.gain(2110);	

	meter.applyFromBuffer();

	EXPECT_EQ(2110, meter.getTotalGained());
	EXPECT_EQ(2110, meter.getNetGained());	
	EXPECT_EQ(2710, rankUpChecker.getCurrentValue());
	EXPECT_EQ(4220, rankUpChecker.getCurrentLevelMaxValue());
	EXPECT_FLOAT_EQ(50, rankUpChecker.getPercent());
	EXPECT_FLOAT_EQ(2.5, rankUpChecker.getCurrentDecimalLevel());
	EXPECT_NEAR(100, rankUpChecker.getLastChangePercent(), 0.0001);
	EXPECT_NEAR(1, rankUpChecker.getNumLevelsGained(), 0.0001);
}

TEST(ApGainMeter, GainRank1a){
	ApChart apChart;
	LevelUpChecker rankUpChecker;
	rankUpChecker.setExpChart(apChart);
	ApGainMeter meter(rankUpChecker);
	rankUpChecker.initialize(0);

	meter.gain(900);	

	meter.applyFromBuffer();

	EXPECT_EQ(900, meter.getTotalGained());
	EXPECT_EQ(900, meter.getNetGained());	
	EXPECT_EQ(900, rankUpChecker.getCurrentValue());
	EXPECT_EQ(1200, rankUpChecker.getCurrentLevelMaxValue());
	EXPECT_FLOAT_EQ(75, rankUpChecker.getPercent());
	EXPECT_FLOAT_EQ(1.75, rankUpChecker.getCurrentDecimalLevel());
	EXPECT_NEAR(75, rankUpChecker.getLastChangePercent(), 0.0001);
	EXPECT_NEAR(0.75, rankUpChecker.getNumLevelsGained(), 0.0001);
}


TEST(ApGainMeter, GainRank2){
	ApChart apChart;
	LevelUpChecker rankUpChecker;
	rankUpChecker.setExpChart(apChart);
	ApGainMeter meter(rankUpChecker);
	rankUpChecker.initialize(116900);

	meter.gain(10000000);	

	meter.applyFromBuffer();

	EXPECT_EQ(10000000, meter.getTotalGained());
	EXPECT_EQ(10000000, meter.getNetGained());	
	EXPECT_EQ(10116900, rankUpChecker.getCurrentValue());
	EXPECT_EQ(0, rankUpChecker.getCurrentLevelMaxValue());
	EXPECT_FLOAT_EQ(100, rankUpChecker.getPercent());
	EXPECT_EQ(9, rankUpChecker.getCurrentLevel());
	EXPECT_FLOAT_EQ(9, rankUpChecker.getCurrentDecimalLevel());
	EXPECT_NEAR(75, rankUpChecker.getLastChangePercent(), 0.0001);
	EXPECT_NEAR(0.75, rankUpChecker.getNumLevelsGained(), 0.0001);
}
