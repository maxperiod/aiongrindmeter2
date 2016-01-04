#include "../model/ExpGainMeter.h"
#include "../lookups/ExpChartNA40.h"
#include "gtest/gtest.h"

TEST(ExpBar, init){
	ExpChartNA40 expChart;
	LevelUpChecker levelUpChecker;
	levelUpChecker.setExpChart(expChart);
	ExpGainMeter meter(levelUpChecker);

	EXPECT_FALSE(levelUpChecker.initialize(0, 0));

	EXPECT_TRUE(levelUpChecker.initialize(1, 0));
	EXPECT_TRUE(levelUpChecker.initialize(1, 400));
	EXPECT_FALSE(levelUpChecker.initialize(1, -1));
	EXPECT_FALSE(levelUpChecker.initialize(1, 401));

	EXPECT_TRUE(levelUpChecker.initialize(65, 0));
	EXPECT_TRUE(levelUpChecker.initialize(65, 584561235));
	EXPECT_FALSE(levelUpChecker.initialize(65, -1));
	EXPECT_FALSE(levelUpChecker.initialize(65, 584561236));
	
	EXPECT_FALSE(levelUpChecker.initialize(66, 0));

	EXPECT_FLOAT_EQ(0, levelUpChecker.getNumLevelsGained());
}

TEST(ExpBar, getPercent1){
	ExpChartNA40 expChart;
	LevelUpChecker levelUpChecker;
	levelUpChecker.setExpChart(expChart);
	ExpGainMeter meter(levelUpChecker);

	levelUpChecker.initialize(1, 300);
	EXPECT_FLOAT_EQ(75, levelUpChecker.getPercent());
	levelUpChecker.initialize(65, 0);
	EXPECT_FLOAT_EQ(0, levelUpChecker.getPercent());
	levelUpChecker.initialize(65, 584561235);
	EXPECT_FLOAT_EQ(100, levelUpChecker.getPercent());

}


TEST(ExpBar, cumulative1){
	ExpChartNA40 expChart;
	LevelUpChecker levelUpChecker;
	levelUpChecker.setExpChart(expChart);
	ExpGainMeter meter(levelUpChecker);

	levelUpChecker.initialize(1, 0);	
	EXPECT_EQ(0, levelUpChecker.getCumulativeCurrentValue());
	levelUpChecker.initialize(2, 0);	
	EXPECT_EQ(400, levelUpChecker.getCumulativeCurrentValue());
	levelUpChecker.initialize(3, 0);	
	EXPECT_EQ(1433, levelUpChecker.getCumulativeCurrentValue());
	levelUpChecker.initialize(3, 200);	
	EXPECT_EQ(1633, levelUpChecker.getCumulativeCurrentValue());
	levelUpChecker.initialize(64, 0);	
	EXPECT_EQ(2700930959l, levelUpChecker.getCumulativeCurrentValue());
	levelUpChecker.initialize(65, 100000000);	
	EXPECT_EQ(3309499233l, levelUpChecker.getCumulativeCurrentValue());

}

TEST(ExpBar, getLevelCap){
	ExpChartNA40 expChart;
	
	EXPECT_EQ(3209499233l, expChart.getLevelCapValue());

}

TEST(ExpBar, levelCapExpWaste){
	ExpChartNA40 expChart;
	LevelUpChecker levelUpChecker;
	levelUpChecker.setExpChart(expChart);
	ExpGainMeter meter(levelUpChecker);

	levelUpChecker.initialize(65, 584000000);
	meter.gain(1000000);
	meter.applyFromBuffer();

	EXPECT_EQ(65, levelUpChecker.getCurrentLevel());
	EXPECT_EQ(584561235, levelUpChecker.getCurrentValue());	
	EXPECT_EQ(561235, meter.getNetGained());
	EXPECT_EQ(438765, meter.getTotalLost());

}

TEST(ExpBar, getCumulativePercent){
	ExpChartNA40 expChart;
	LevelUpChecker levelUpChecker;
	levelUpChecker.setExpChart(expChart);	

	levelUpChecker.initialize(59, 3209499233l / 2 - 1484090156l);
	EXPECT_FLOAT_EQ(50, levelUpChecker.getCumulativePercent());

}

TEST(ExpMeter, ExpRepose1){
	ExpChartNA40 expChart;
	LevelUpChecker levelUpChecker;
	levelUpChecker.setExpChart(expChart);
	ExpGainMeter meter(levelUpChecker);

	meter.gain(20052999);
	meter.useRepose(10405);

	meter.applyFromBuffer();

	EXPECT_EQ(20052999, meter.getTotalGained());
	EXPECT_EQ(20052999, meter.getNetGained());
	EXPECT_EQ(10405, meter.getReposeUsed());		
	EXPECT_EQ(-1, levelUpChecker.getCurrentValue());
	EXPECT_EQ(-1, levelUpChecker.getCurrentLevelMaxValue());
}

TEST(ExpMeter, ExpWithInit){
	ExpChartNA40 expChart;
	LevelUpChecker levelUpChecker;
	levelUpChecker.setExpChart(expChart);
	ExpGainMeter meter(levelUpChecker);

	levelUpChecker.initialize(20, 12000);
	meter.gain(7580);
	meter.applyFromBuffer();

	EXPECT_EQ(20, levelUpChecker.getCurrentLevel());
	EXPECT_EQ(19580, levelUpChecker.getCurrentValue());
	EXPECT_FLOAT_EQ(627122, levelUpChecker.getCurrentLevelMaxValue());
	
	EXPECT_EQ(7580, meter.getNetGained());
}

TEST(ExpMeter, LevelUp){
	ExpChartNA40 expChart;
	LevelUpChecker levelUpChecker;
	levelUpChecker.setExpChart(expChart);
	ExpGainMeter meter(levelUpChecker);

	levelUpChecker.initialize(5, 7000);
	meter.gain(2000);
	meter.applyFromBuffer();

	EXPECT_EQ(7000+2000-8601, levelUpChecker.getCurrentValue());
	EXPECT_EQ(2000, meter.getNetGained());
	EXPECT_EQ(6, levelUpChecker.getCurrentLevel());

	EXPECT_FLOAT_EQ(1-0.813859+0.0299482, levelUpChecker.getNumLevelsGained());
}

TEST(ExpMeter, LevelUpBlocked1){
	ExpChartNA40 expChart;
	LevelUpChecker levelUpChecker;
	levelUpChecker.setExpChart(expChart);
	ExpGainMeter meter(levelUpChecker);

	levelUpChecker.initialize(9, 10000);
	meter.gain(73200);
	levelUpChecker.prohibitLevelUp();
	meter.applyFromBuffer();


	EXPECT_EQ(43087, levelUpChecker.getCurrentValue());
	EXPECT_EQ(9, levelUpChecker.getCurrentLevel());
	EXPECT_EQ(33087, meter.getNetGained());
}

TEST(ExpMeter, ManualExpUpdate1){
	ExpChartNA40 expChart;
	LevelUpChecker levelUpChecker;
	levelUpChecker.setExpChart(expChart);
	ExpGainMeter meter(levelUpChecker);

	levelUpChecker.initialize(44, 10000000);
	EXPECT_TRUE(levelUpChecker.setCurrentValue(10000000 - 380752));
	EXPECT_EQ(10000000 - 380752, levelUpChecker.getCurrentValue());
	EXPECT_EQ(44, levelUpChecker.getCurrentLevel());
	EXPECT_EQ(-380752, meter.getNetGained());
}

TEST(ExpMeter, ManualExpUpdate2){
	ExpChartNA40 expChart;
	LevelUpChecker levelUpChecker;
	levelUpChecker.setExpChart(expChart);
	ExpGainMeter meter(levelUpChecker);

	levelUpChecker.initialize(44, 10000000);
	EXPECT_TRUE(levelUpChecker.setCurrentValue(10000000));
	EXPECT_EQ(10000000, levelUpChecker.getCurrentValue());
	EXPECT_EQ(44, levelUpChecker.getCurrentLevel());
	EXPECT_EQ(0, meter.getNetGained());
}

TEST(ExpMeter, ManualExpUpdate3){
	ExpChartNA40 expChart;
	LevelUpChecker levelUpChecker;
	levelUpChecker.setExpChart(expChart);
	ExpGainMeter meter(levelUpChecker);

	levelUpChecker.initialize(44, 10000000);
	EXPECT_FALSE(levelUpChecker.setCurrentValue(10000001));
	EXPECT_EQ(10000000, levelUpChecker.getCurrentValue());
	EXPECT_EQ(44, levelUpChecker.getCurrentLevel());
	EXPECT_EQ(0, meter.getNetGained());
}

TEST(ExpMeter, ManualExpUpdate4){
	ExpChartNA40 expChart;
	LevelUpChecker levelUpChecker;
	levelUpChecker.setExpChart(expChart);
	ExpGainMeter meter(levelUpChecker);

	levelUpChecker.initialize(44, 10000000);
	EXPECT_FALSE(levelUpChecker.setCurrentValue(-1));
	EXPECT_EQ(10000000, levelUpChecker.getCurrentValue());
	EXPECT_EQ(44, levelUpChecker.getCurrentLevel());
	EXPECT_EQ(0, meter.getNetGained());
}

TEST(ExpMeter, ManualExpUpdate5){
	ExpChartNA40 expChart;
	LevelUpChecker levelUpChecker;
	levelUpChecker.setExpChart(expChart);
	ExpGainMeter meter(levelUpChecker);

	levelUpChecker.initialize(44, 10000000);
	EXPECT_TRUE(levelUpChecker.setCurrentValue(990000));
	EXPECT_TRUE(levelUpChecker.setCurrentValue(9900000));
	EXPECT_EQ(9900000, levelUpChecker.getCurrentValue());
	EXPECT_EQ(44, levelUpChecker.getCurrentLevel());
	EXPECT_EQ(-100000, meter.getNetGained());
}


TEST(ExpMeter, ProjectedDecimalLevel1){
	ExpChartNA40 expChart;
	LevelUpChecker levelUpChecker;
	levelUpChecker.setExpChart(expChart);
	ExpGainMeter meter(levelUpChecker);

	levelUpChecker.initialize(2, 100);
	EXPECT_FLOAT_EQ(7.69047, levelUpChecker.getProjectedDecimalLevel(45000));
	//lv 7: 30978 total exp
}

TEST(ExpMeter, ProjectedDecimalLevel2){
	ExpChartNA40 expChart;
	LevelUpChecker levelUpChecker;
	levelUpChecker.setExpChart(expChart);
	ExpGainMeter meter(levelUpChecker);

	levelUpChecker.initialize(64, 400000000);
	EXPECT_FLOAT_EQ(65.15641, levelUpChecker.getProjectedDecimalLevel(200000000));
	
}

TEST(ExpMeter, ProjectedDecimalLevelNoInit){
	ExpChartNA40 expChart;
	LevelUpChecker levelUpChecker;
	levelUpChecker.setExpChart(expChart);
	ExpGainMeter meter(levelUpChecker);
	
	EXPECT_FLOAT_EQ(-1, levelUpChecker.getProjectedDecimalLevel(123456789));
	//lv 7: 30978 total exp
}