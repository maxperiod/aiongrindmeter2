#include "gtest/gtest.h"
#include "../model/KinahGainMeter.h"

TEST(KinahGainMeter, npcSale1){
	KinahGainMeter meter;
	meter.gain(100);
	meter.applyFromBuffer();

	EXPECT_EQ(100, meter.getNetGained());
	EXPECT_EQ(100, meter.getLastChange());
	EXPECT_EQ(0, meter.getNpcSales());

	meter.setSaleMode();
	meter.gain(200);
	meter.applyFromBuffer();

	EXPECT_EQ(300, meter.getNetGained());
	EXPECT_EQ(200, meter.getLastChange());
	EXPECT_EQ(200, meter.getNpcSales());

	meter.gain(100);
	meter.applyFromBuffer();

	EXPECT_EQ(400, meter.getNetGained());
	EXPECT_EQ(100, meter.getLastChange());
	EXPECT_EQ(200, meter.getNpcSales());


}

int main(int argc, char** argv){
	testing::InitGoogleTest(&argc, argv); 
	RUN_ALL_TESTS();
	getchar();
	return 0;
}