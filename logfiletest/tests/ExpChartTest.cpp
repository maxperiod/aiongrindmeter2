#include "../lookups/ExpChartNA40.h"
#include "../lookups/ApChart.h"

#include "gtest/gtest.h"

TEST(ExpChart, ExpChart){
	ExpChart* expChart = new ExpChartNA40();
	
	EXPECT_EQ(-1, expChart->getMaxValue(-1));
	EXPECT_EQ(0, expChart->getMaxValue(0));
	EXPECT_EQ(400, expChart->getMaxValue(1));
	EXPECT_EQ(584561235, expChart->getMaxValue(65));
	EXPECT_EQ(-1, expChart->getMaxValue(66));

	delete(expChart);
}

/*
TEST(ExpBar, init){
	ExpChart* expChart = new ExpChartNA40();
	
	EXPECT_FALSE(expChart->initialize(0, 0));

	EXPECT_TRUE(expChart->initialize(1, 0));
	EXPECT_TRUE(expChart->initialize(1, 400));
	EXPECT_FALSE(expChart->initialize(1, -1));
	EXPECT_FALSE(expChart->initialize(1, 401));

	EXPECT_TRUE(expChart->initialize(65, 0));
	EXPECT_TRUE(expChart->initialize(65, 584561235));
	EXPECT_FALSE(expChart->initialize(65, -1));
	EXPECT_FALSE(expChart->initialize(65, 584561236));
	
	EXPECT_FALSE(expChart->initialize(66, 0));

	delete(expChart);
}


TEST(ExpBar, getPercent1){
	ExpChart* expChart = new ExpChartNA40();

	expChart->initialize(1, 300);
	EXPECT_FLOAT_EQ(0.75, expChart->getPercent());
	expChart->initialize(65, 0);
	EXPECT_FLOAT_EQ(0, expChart->getPercent());
	expChart->initialize(65, 584561235);
	EXPECT_FLOAT_EQ(1, expChart->getPercent());
	
	delete(expChart);
}

TEST(ExpBar, cumulative1){
	ExpChart* expChart = new ExpChartNA40();
	expChart->initialize(1, 0);	
	EXPECT_EQ(0, expChart->getCumulativeCurrentValue());
	expChart->initialize(2, 0);	
	EXPECT_EQ(400, expChart->getCumulativeCurrentValue());
	expChart->initialize(3, 0);	
	EXPECT_EQ(1433, expChart->getCumulativeCurrentValue());
	expChart->initialize(3, 200);	
	EXPECT_EQ(1633, expChart->getCumulativeCurrentValue());
	expChart->initialize(64, 0);	
	EXPECT_EQ(2700930959, expChart->getCumulativeCurrentValue());
	expChart->initialize(65, 100000000);	
	EXPECT_EQ(3309499233, expChart->getCumulativeCurrentValue());

	delete(expChart);
}
*/
TEST(ExpBar, getLevelCap){
	ExpChartNA40 expChart;// = new ExpChartNA40();
	
	EXPECT_EQ(3209499233l, expChart.getLevelCapValue());

}
/*
TEST(ExpBar, getCumulativePercent){
		ExpChart* expChart = new ExpChartNA40();
	long l65exp = 3209499233;
	expChart->initialize(59, l65exp / 2 - 1484090156);
	EXPECT_FLOAT_EQ(0.5, expChart->getCumulativePercent());
	delete(expChart);
}

TEST(ApBar, getPercent1){
	ProgressBar* apChart = new ApChart();

	apChart->initialize(0);
	EXPECT_FLOAT_EQ(0, apChart->getPercent());
	apChart->initialize(900);
	EXPECT_FLOAT_EQ(0.75, apChart->getPercent());
	apChart->initialize(1200);
	EXPECT_FLOAT_EQ(0, apChart->getPercent());
	apChart->initialize(2710);
	EXPECT_FLOAT_EQ(0.5, apChart->getPercent());
	apChart->initialize(105600);
	EXPECT_FLOAT_EQ(0, apChart->getPercent());
	apChart->initialize(116900);
	EXPECT_FLOAT_EQ(0.25, apChart->getPercent());
	apChart->initialize(150800);
	EXPECT_FLOAT_EQ(1, apChart->getPercent());
	apChart->initialize(200000000);
	EXPECT_FLOAT_EQ(1, apChart->getPercent());	

	delete(apChart);
}


TEST(ApBar, getPercent2){
	ProgressBar* apChart = new ApChart();

	apChart->initialize(1, 0);
	EXPECT_FLOAT_EQ(0, apChart->getPercent());
	apChart->initialize(1, 900);
	EXPECT_FLOAT_EQ(0.75, apChart->getPercent());
	apChart->initialize(2, 1200);
	EXPECT_FLOAT_EQ(0, apChart->getPercent());
	apChart->initialize(2, 2710);
	EXPECT_FLOAT_EQ(0.5, apChart->getPercent());
	apChart->initialize(8, 105600);
	EXPECT_FLOAT_EQ(0, apChart->getPercent());
	apChart->initialize(8, 116900);
	EXPECT_FLOAT_EQ(0.25, apChart->getPercent());
	apChart->initialize(9, 150800);
	EXPECT_FLOAT_EQ(1, apChart->getPercent());
	apChart->initialize(9, 200000000);
	EXPECT_FLOAT_EQ(1, apChart->getPercent());	

	delete(apChart);
}

TEST(ApBar, cumulative1){
	ProgressBar* apChart = new ApChart();
	apChart->initialize(1, 100);	
	EXPECT_EQ(100, apChart->getCumulativeCurrentValue());
	apChart->initialize(9, 151800);
	EXPECT_EQ(151800, apChart->getCumulativeCurrentValue());

	delete(apChart);
}
*/
TEST(ApBar, getLevelCap){
	ApChart apChart;
	
	EXPECT_EQ(150800, apChart.getLevelCapValue());
}
/*
TEST(ApBar, getCumulativePercent){
	ProgressBar* apChart = new ApChart();
	apChart->initialize(7, 75400);
	EXPECT_FLOAT_EQ(0.5, apChart->getCumulativePercent());
	delete(apChart);
}
*/
/*
int main(int argc, char** argv){
	testing::InitGoogleTest(&argc, argv); 
	RUN_ALL_TESTS();
	getchar();
	return 0;
}
*/