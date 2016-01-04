#include "../model/ExpChart.h"
#include "../model/ApChart.h"

#include "gtest/gtest.h"

TEST(ExpChart, ExpChart){
	ProgressBar* expChart = new ExpChart();
	
	EXPECT_EQ(-1, expChart->getMaxValue(-1));
	EXPECT_EQ(0, expChart->getMaxValue(0));
	EXPECT_EQ(400, expChart->getMaxValue(1));
	EXPECT_EQ(584561235, expChart->getMaxValue(65));
	EXPECT_EQ(-1, expChart->getMaxValue(66));
}

TEST(ExpBar, init){
	ProgressBar* expChart = new ExpChart();
	
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
}


TEST(ExpBar, getPercent1){
	ProgressBar* expChart = new ExpChart();

	expChart->initialize(1, 300);
	EXPECT_EQ(1, expChart->getCurrentLevel());
	EXPECT_FLOAT_EQ(0.75, expChart->getPercent());
	
	expChart->initialize(65, 0);
	EXPECT_EQ(65, expChart->getCurrentLevel());
	EXPECT_FLOAT_EQ(0, expChart->getPercent());
	
	expChart->initialize(65, 584561235);
	EXPECT_EQ(65, expChart->getCurrentLevel());
	EXPECT_FLOAT_EQ(1, expChart->getPercent());
	
}

TEST(ApBar, getPercent1){
	ProgressBar* apChart = new ApChart();

	apChart->initialize(0);
	EXPECT_EQ(1, apChart->getCurrentLevel());
	EXPECT_FLOAT_EQ(0, apChart->getPercent());

	apChart->initialize(900);
	EXPECT_EQ(1, apChart->getCurrentLevel());
	EXPECT_FLOAT_EQ(0.75, apChart->getPercent());

	apChart->initialize(1200);
	EXPECT_EQ(2, apChart->getCurrentLevel());
	EXPECT_FLOAT_EQ(0, apChart->getPercent());

	apChart->initialize(2710);
	EXPECT_EQ(2, apChart->getCurrentLevel());
	EXPECT_FLOAT_EQ(0.5, apChart->getPercent());

	apChart->initialize(105600);
	EXPECT_EQ(8, apChart->getCurrentLevel());
	EXPECT_FLOAT_EQ(0, apChart->getPercent());

	apChart->initialize(116900);
	EXPECT_EQ(8, apChart->getCurrentLevel());
	EXPECT_FLOAT_EQ(0.25, apChart->getPercent());
	
	apChart->initialize(150800);
	EXPECT_EQ(9, apChart->getCurrentLevel());
	EXPECT_FLOAT_EQ(1, apChart->getPercent());
	
	apChart->initialize(200000000);
	EXPECT_EQ(9, apChart->getCurrentLevel());
	EXPECT_FLOAT_EQ(1, apChart->getPercent());	
}


TEST(ApBar, getPercent2){
	ProgressBar* apChart = new ApChart();

	apChart->initialize(1, 0);
	EXPECT_EQ(1, apChart->getCurrentLevel());
	EXPECT_FLOAT_EQ(0, apChart->getPercent());

	apChart->initialize(1, 900);
	EXPECT_EQ(1, apChart->getCurrentLevel());
	EXPECT_FLOAT_EQ(0.75, apChart->getPercent());

	apChart->initialize(2, 1200);
	EXPECT_EQ(2, apChart->getCurrentLevel());
	EXPECT_FLOAT_EQ(0, apChart->getPercent());

	apChart->initialize(2, 2710);
	EXPECT_EQ(2, apChart->getCurrentLevel());
	EXPECT_FLOAT_EQ(0.5, apChart->getPercent());

	apChart->initialize(8, 105600);
	EXPECT_EQ(8, apChart->getCurrentLevel());
	EXPECT_FLOAT_EQ(0, apChart->getPercent());

	apChart->initialize(8, 116900);
	EXPECT_EQ(8, apChart->getCurrentLevel());
	EXPECT_FLOAT_EQ(0.25, apChart->getPercent());

	apChart->initialize(9, 150800);
	EXPECT_EQ(9, apChart->getCurrentLevel());
	EXPECT_FLOAT_EQ(1, apChart->getPercent());

	apChart->initialize(9, 200000000);
	EXPECT_EQ(9, apChart->getCurrentLevel());
	EXPECT_FLOAT_EQ(1, apChart->getPercent());	
}


int main(int argc, char** argv){
	testing::InitGoogleTest(&argc, argv); 
	RUN_ALL_TESTS();
	getchar();
	return 0;
}