#include "../model/MeterValue.h"
#include "gtest/gtest.h"

TEST(MeterValue, reset){
	MeterValue valueGained;

	EXPECT_EQ(0, valueGained.getTotalGained());
	EXPECT_EQ(0, valueGained.getTotalSpent());
	EXPECT_EQ(0, valueGained.getTotalLost());
	EXPECT_EQ(0, valueGained.getNetGained());
	EXPECT_EQ(0, valueGained.getLastChange());
	EXPECT_EQ(0, valueGained.getNumPacketsForLastChange());
	
}


TEST(MeterValue, gain1){
	MeterValue valueGained;

	valueGained.gain(100);

	EXPECT_EQ(0, valueGained.getTotalGained());
	EXPECT_EQ(0, valueGained.getTotalSpent());
	EXPECT_EQ(0, valueGained.getTotalLost());

	valueGained.applyFromBuffer();

	EXPECT_EQ(100, valueGained.getTotalGained());
	EXPECT_EQ(0, valueGained.getTotalSpent());
	EXPECT_EQ(0, valueGained.getTotalLost());
	EXPECT_EQ(100, valueGained.getNetGained());
	EXPECT_EQ(100, valueGained.getLastChange());
	EXPECT_EQ(1, valueGained.getNumPacketsForLastChange());
	
	valueGained.applyFromBuffer();
	
	EXPECT_EQ(100, valueGained.getTotalGained());
	EXPECT_EQ(0, valueGained.getTotalSpent());
	EXPECT_EQ(0, valueGained.getTotalLost());
	EXPECT_EQ(100, valueGained.getNetGained());
	EXPECT_EQ(100, valueGained.getLastChange());
	EXPECT_EQ(1, valueGained.getNumPacketsForLastChange());
	
}

TEST(MeterValue, spend1){
	MeterValue valueGained;

	valueGained.spend(100);

	EXPECT_EQ(0, valueGained.getTotalGained());
	EXPECT_EQ(0, valueGained.getTotalSpent());
	EXPECT_EQ(0, valueGained.getTotalLost());
	EXPECT_EQ(0, valueGained.getNetGained());
	
	valueGained.applyFromBuffer();

	EXPECT_EQ(0, valueGained.getTotalGained());
	EXPECT_EQ(100, valueGained.getTotalSpent());
	EXPECT_EQ(0, valueGained.getTotalLost());
	EXPECT_EQ(-100, valueGained.getNetGained());
	EXPECT_EQ(-100, valueGained.getLastChange());
	EXPECT_EQ(1, valueGained.getNumPacketsForLastChange());
	
		
	valueGained.applyFromBuffer();

	EXPECT_EQ(0, valueGained.getTotalGained());
	EXPECT_EQ(100, valueGained.getTotalSpent());
	EXPECT_EQ(0, valueGained.getTotalLost());
	EXPECT_EQ(-100, valueGained.getNetGained());
	EXPECT_EQ(-100, valueGained.getLastChange());
	EXPECT_EQ(1, valueGained.getNumPacketsForLastChange());
	

}

TEST(MeterValue, lose1){
	MeterValue valueGained;

	valueGained.lose(100);

	EXPECT_EQ(0, valueGained.getTotalGained());
	EXPECT_EQ(0, valueGained.getTotalSpent());
	EXPECT_EQ(0, valueGained.getTotalLost());
	EXPECT_EQ(0, valueGained.getNetGained());
	
	
	valueGained.applyFromBuffer();

	EXPECT_EQ(0, valueGained.getTotalGained());
	EXPECT_EQ(0, valueGained.getTotalSpent());
	EXPECT_EQ(100, valueGained.getTotalLost());
	EXPECT_EQ(-100, valueGained.getNetGained());
	EXPECT_EQ(-100, valueGained.getLastChange());
	EXPECT_EQ(1, valueGained.getNumPacketsForLastChange());
	
	valueGained.applyFromBuffer();

	EXPECT_EQ(0, valueGained.getTotalGained());
	EXPECT_EQ(0, valueGained.getTotalSpent());
	EXPECT_EQ(100, valueGained.getTotalLost());
	EXPECT_EQ(-100, valueGained.getNetGained());
	EXPECT_EQ(-100, valueGained.getLastChange());
	EXPECT_EQ(1, valueGained.getNumPacketsForLastChange());
	
}

TEST(MeterValue, gainMultiple1){
	MeterValue valueGained;

	valueGained.gain(200);
	valueGained.gain(200);
	valueGained.gain(200);

	EXPECT_EQ(0, valueGained.getTotalGained());
	EXPECT_EQ(0, valueGained.getTotalSpent());
	EXPECT_EQ(0, valueGained.getTotalLost());
	EXPECT_EQ(0, valueGained.getNetGained());
	
	valueGained.applyFromBuffer();

	EXPECT_EQ(600, valueGained.getTotalGained());
	EXPECT_EQ(0, valueGained.getTotalSpent());
	EXPECT_EQ(0, valueGained.getTotalLost());
	EXPECT_EQ(600, valueGained.getNetGained());
	EXPECT_EQ(600, valueGained.getLastChange());
	EXPECT_EQ(200, valueGained.getLastSingleChange());
	EXPECT_EQ(3, valueGained.getNumPacketsForLastChange());

	valueGained.gain(300);
	valueGained.gain(100);


	valueGained.applyFromBuffer();
	EXPECT_EQ(1000, valueGained.getTotalGained());
	EXPECT_EQ(0, valueGained.getTotalSpent());
	EXPECT_EQ(0, valueGained.getTotalLost());
	EXPECT_EQ(1000, valueGained.getNetGained());
	EXPECT_EQ(400, valueGained.getLastChange());
	EXPECT_EQ(2, valueGained.getNumPacketsForLastChange());
	
	
	valueGained.applyFromBuffer();
	EXPECT_EQ(1000, valueGained.getTotalGained());
	EXPECT_EQ(0, valueGained.getTotalSpent());
	EXPECT_EQ(0, valueGained.getTotalLost());
	EXPECT_EQ(1000, valueGained.getNetGained());
	EXPECT_EQ(400, valueGained.getLastChange());
	EXPECT_EQ(2, valueGained.getNumPacketsForLastChange());
	
}

TEST(MeterValue, sendMultiple1){
	MeterValue valueGained;

	valueGained.spend(200);
	valueGained.spend(200);
	valueGained.spend(200);

	EXPECT_EQ(0, valueGained.getTotalGained());
	EXPECT_EQ(0, valueGained.getTotalSpent());
	EXPECT_EQ(0, valueGained.getTotalLost());

	valueGained.applyFromBuffer();

	EXPECT_EQ(0, valueGained.getTotalGained());
	EXPECT_EQ(600, valueGained.getTotalSpent());
	EXPECT_EQ(0, valueGained.getTotalLost());
	EXPECT_EQ(-600, valueGained.getNetGained());
	EXPECT_EQ(-600, valueGained.getLastChange());
	EXPECT_EQ(3, valueGained.getNumPacketsForLastChange());

	valueGained.spend(300);
	valueGained.spend(100);

	valueGained.applyFromBuffer();
	EXPECT_EQ(0, valueGained.getTotalGained());
	EXPECT_EQ(1000, valueGained.getTotalSpent());
	EXPECT_EQ(0, valueGained.getTotalLost());
	EXPECT_EQ(-1000, valueGained.getNetGained());
	EXPECT_EQ(-400, valueGained.getLastChange());
	EXPECT_EQ(2, valueGained.getNumPacketsForLastChange());
}

TEST(MeterValue, loseMultiple1){
	MeterValue valueGained;

	valueGained.gain(200);
	valueGained.gain(200);
	valueGained.lose(310);

	EXPECT_EQ(0, valueGained.getTotalGained());
	EXPECT_EQ(0, valueGained.getTotalSpent());
	EXPECT_EQ(0, valueGained.getTotalLost());

	valueGained.applyFromBuffer();

	EXPECT_EQ(400, valueGained.getTotalGained());
	EXPECT_EQ(0, valueGained.getTotalSpent());
	EXPECT_EQ(310, valueGained.getTotalLost());
	EXPECT_EQ(90, valueGained.getNetGained());
	EXPECT_EQ(90, valueGained.getLastChange());
	EXPECT_EQ(3, valueGained.getNumPacketsForLastChange());

	valueGained.spend(300);
	valueGained.lose(200);

	valueGained.applyFromBuffer();
	EXPECT_EQ(400, valueGained.getTotalGained());
	EXPECT_EQ(300, valueGained.getTotalSpent());
	EXPECT_EQ(510, valueGained.getTotalLost());
	EXPECT_EQ(-410, valueGained.getNetGained());
	EXPECT_EQ(-500, valueGained.getLastChange());
	EXPECT_EQ(2, valueGained.getNumPacketsForLastChange());
	
}




int main(int argc, char** argv){
	testing::InitGoogleTest(&argc, argv); 
	RUN_ALL_TESTS();
	getchar();
	return 0;
}