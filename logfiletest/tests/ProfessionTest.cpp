#include "gtest/gtest.h"
#include "../model/GatherCraft.h"
#include "../model/IndividualItemGatherCrafts.h"
#include "../model/ProfessionLeveling.h"

TEST(GatherCraft, startupCheck){
	GatherCraft gatherCraft;
	
	GatherCraftRecord result = gatherCraft.getResult();
	EXPECT_EQ(0, result.getNumSuccess());
	EXPECT_EQ(0, result.getNumFailure());
	EXPECT_EQ(0, result.getNumCancel());
	EXPECT_EQ(0, result.getNumProcs());
	EXPECT_EQ(0, result.getTotalAttempts());
	/*
	GatherCraftRecord* result2 = gatherCraft.getResult(GatherCraft::MORPH);
	EXPECT_EQ(0, result2.getNumSuccess());
	EXPECT_EQ(0, result2.getNumFailure());
	EXPECT_EQ(0, result2.getNumCancel());
	EXPECT_EQ(0, result2.getNumProcs());
	EXPECT_EQ(0, result2.getTotalAttempts());

	GatherCraftRecord* result3 = gatherCraft.getResult(GatherCraft::MORPH);
	EXPECT_EQ(0, result3.getNumSuccess());
	EXPECT_EQ(0, result3.getNumFailure());
	EXPECT_EQ(0, result3.getNumCancel());
	EXPECT_EQ(0, result3.getNumProcs());
	EXPECT_EQ(0, result3.getTotalAttempts());
	*/
	EXPECT_FALSE(gatherCraft.isInProgress());
	
}

TEST(GatherCraft, gather1){
	GatherCraft gatherCraft;
	
	gatherCraft.begin("Aria");
	EXPECT_TRUE(gatherCraft.isInProgress());
	gatherCraft.success();
	EXPECT_FALSE(gatherCraft.isInProgress());

	gatherCraft.begin("Aria");
	gatherCraft.success();
	
	GatherCraftRecord result = gatherCraft.getResult();
	EXPECT_EQ(2, result.getNumSuccess());
	EXPECT_EQ(0, result.getNumFailure());
	EXPECT_EQ(0, result.getNumCancel());
	EXPECT_EQ(0, result.getNumProcs());
	EXPECT_EQ(2, result.getTotalAttempts());

	IndividualItemGatherCrafts gatheredItems = gatherCraft.getIndividualItemGatherCrafts();
	GatherCraftRecord item = gatheredItems.getEntry("Aria");

	EXPECT_EQ(2, item.getNumSuccess());
	EXPECT_EQ(0, item.getNumFailure());
	EXPECT_EQ(0, item.getNumCancel());
	EXPECT_EQ(0, item.getNumProcs());
	EXPECT_EQ(2, item.getTotalAttempts());
}

TEST(GatherCraft, gatherFail1){
	GatherCraft gatherCraft;
	
	gatherCraft.begin("Anevra");
	EXPECT_TRUE(gatherCraft.isInProgress());
	gatherCraft.fail();
	EXPECT_FALSE(gatherCraft.isInProgress());
	
	GatherCraftRecord result = gatherCraft.getResult();
	EXPECT_EQ(0, result.getNumSuccess());
	EXPECT_EQ(1, result.getNumFailure());
	EXPECT_EQ(0, result.getNumCancel());
	EXPECT_EQ(0, result.getNumProcs());
	EXPECT_EQ(1, result.getTotalAttempts());

	IndividualItemGatherCrafts gatheredItems = gatherCraft.getIndividualItemGatherCrafts();
	GatherCraftRecord item = gatheredItems.getEntry("Anevra");

	EXPECT_EQ(0, item.getNumSuccess());
	EXPECT_EQ(1, item.getNumFailure());
	EXPECT_EQ(0, item.getNumCancel());
	EXPECT_EQ(0, item.getNumProcs());
	EXPECT_EQ(1, item.getTotalAttempts());
	EXPECT_FALSE(item.isProcable());
}

TEST(GatherCraft, gatherCancel1){
	GatherCraft gatherCraft;
	
	gatherCraft.begin("Anevra");
	EXPECT_TRUE(gatherCraft.isInProgress());
	gatherCraft.cancel();
	EXPECT_FALSE(gatherCraft.isInProgress());
	
	GatherCraftRecord result = gatherCraft.getResult();
	EXPECT_EQ(0, result.getNumSuccess());
	EXPECT_EQ(0, result.getNumFailure());
	EXPECT_EQ(1, result.getNumCancel());
	EXPECT_EQ(0, result.getNumProcs());
	EXPECT_EQ(1, result.getTotalAttempts());
}

TEST(GatherCraft, inventoryFull1){
	GatherCraft gatherCraft;
		
	gatherCraft.cancel();
	EXPECT_FALSE(gatherCraft.isInProgress());
	
	GatherCraftRecord result = gatherCraft.getResult();
	EXPECT_EQ(0, result.getNumSuccess());
	EXPECT_EQ(0, result.getNumFailure());
	EXPECT_EQ(0, result.getNumCancel());
	EXPECT_EQ(0, result.getNumProcs());
	EXPECT_EQ(0, result.getTotalAttempts());
}


TEST(GatherCraft, craft1){
	GatherCraft gatherCraft;
	gatherCraft.begin("Gritty Conide");
	gatherCraft.success();
	gatherCraft.begin("Gritty Conide");
	gatherCraft.success();
	gatherCraft.begin("Gritty Conide");
	gatherCraft.success();
	gatherCraft.begin("Gritty Conide");
	gatherCraft.fail();

	GatherCraftRecord result = gatherCraft.getResult();
	EXPECT_EQ(3, result.getNumSuccess());
	EXPECT_EQ(1, result.getNumFailure());
	EXPECT_EQ(0, result.getNumCancel());
	EXPECT_EQ(0, result.getNumProcs());
	EXPECT_EQ(4, result.getTotalAttempts());
	
}


TEST(GatherCraft, proc1){
	GatherCraft gatherCraft;
	gatherCraft.begin("Poma Herb Bulgogi");
	gatherCraft.begin("Tasty Poma Herb Bulgogi");
	gatherCraft.success();
	gatherCraft.begin("Poma Herb Bulgogi");
	gatherCraft.success();
	gatherCraft.begin("Poma Herb Bulgogi");
	gatherCraft.begin("Tasty Poma Herb Bulgogi");
	gatherCraft.fail();

	GatherCraftRecord result = gatherCraft.getResult();
	EXPECT_EQ(3, result.getNumSuccess());
	EXPECT_EQ(0, result.getNumFailure());
	EXPECT_EQ(0, result.getNumCancel());
	EXPECT_EQ(1, result.getNumProcs());
	EXPECT_EQ(3, result.getTotalAttempts());

	IndividualItemGatherCrafts gatheredItems = gatherCraft.getIndividualItemGatherCrafts();
	GatherCraftRecord item = gatheredItems.getEntry("Poma Herb Bulgogi");

	EXPECT_EQ(2, item.getNumSuccess());
	EXPECT_EQ(0, item.getNumFailure());
	EXPECT_EQ(0, item.getNumCancel());
	EXPECT_EQ(1, item.getNumProcs());
	EXPECT_EQ(3, item.getTotalAttempts());
	EXPECT_TRUE(item.isProcable());

	item = gatheredItems.getEntry("Tasty Poma Herb Bulgogi");

	EXPECT_EQ(1, item.getNumSuccess());
	EXPECT_EQ(1, item.getNumFailure());
	EXPECT_EQ(0, item.getNumCancel());
	EXPECT_EQ(0, item.getNumProcs());
	EXPECT_EQ(2, item.getTotalAttempts());
	EXPECT_FALSE(item.isProcable());
}

TEST(GatherCraft, morph1){
	GatherCraft gatherCraft;
	gatherCraft.begin("Ralloc");
	gatherCraft.success();
	gatherCraft.begin("Ralloc");
	gatherCraft.success();
	gatherCraft.begin("Ralloc");
	gatherCraft.success();
	gatherCraft.begin("Ralloc");
	gatherCraft.success();
	gatherCraft.begin("Poma");
	gatherCraft.success();
	gatherCraft.begin("Poma");
	gatherCraft.success();

	GatherCraftRecord result3 = gatherCraft.getResult();
	EXPECT_EQ(6, result3.getNumSuccess());
	EXPECT_EQ(0, result3.getNumFailure());
	EXPECT_EQ(0, result3.getNumCancel());
	EXPECT_EQ(0, result3.getNumProcs());
	EXPECT_EQ(6, result3.getTotalAttempts());

	IndividualItemGatherCrafts gatheredItems = gatherCraft.getIndividualItemGatherCrafts();

	GatherCraftRecord item = gatheredItems.getEntry("Ralloc");
	EXPECT_EQ(4, item.getNumSuccess());
	EXPECT_EQ(0, item.getNumFailure());
	EXPECT_EQ(0, item.getNumCancel());
	EXPECT_EQ(0, item.getNumProcs());
	EXPECT_EQ(4, item.getTotalAttempts());

	GatherCraftRecord item2 = gatheredItems.getEntry("Poma");
	EXPECT_EQ(2, item2.getNumSuccess());
	EXPECT_EQ(0, item2.getNumFailure());
	EXPECT_EQ(0, item2.getNumCancel());
	EXPECT_EQ(0, item2.getNumProcs());
	EXPECT_EQ(2, item2.getTotalAttempts());
}

TEST(ProfessionLeveling, gatherLevelUp1){
	ProfessionLeveling leveler;
	leveler.gainProfessionExp();
	leveler.gainProfessionExp();
	leveler.levelUp("Essencetapping", 14);
	leveler.gainProfessionExp();
	leveler.gainProfessionExp();
	leveler.gainProfessionExp();
	EXPECT_EQ(-1, leveler.getProfessionLevelingHistory().getNumGatheredOrCraftedForLastLevelUp());

	leveler.levelUp("Essencetapping", 15);
	leveler.gainProfessionExp();
	leveler.gainProfessionExp();
	leveler.gainProfessionExp();
	leveler.levelUp("Essencetapping", 16);
	leveler.gainProfessionExp();
	leveler.gainProfessionExp();
	leveler.gainProfessionExp();

	EXPECT_EQ(2, leveler.getNumGatheredOrCraftedSinceLevelUp());
	EXPECT_EQ("Essencetapping", leveler.getCurrentProfession());

	EXPECT_EQ(16, leveler.getProfessionLevelingHistory().getCurrentLevel());
	EXPECT_EQ(3, leveler.getProfessionLevelingHistory().getNumLevelUps());
	EXPECT_EQ(3, leveler.getProfessionLevelingHistory().getNumGatheredOrCraftedForLastLevelUp());
	EXPECT_FLOAT_EQ(66.666667, leveler.getProgressBarValue());
}


TEST(ProfessionLeveling, gatherLevelCapped1){
	ProfessionLeveling leveler;
	leveler.levelUp("Essencetapping", 485);
	leveler.gainProfessionExp();
	leveler.levelCapped();	
	leveler.gainProfessionExp();
	
	EXPECT_EQ("Essencetapping", leveler.getCurrentProfession());
	EXPECT_EQ(0, leveler.getNumGatheredOrCraftedSinceLevelUp());
	
	EXPECT_EQ(485, leveler.getProfessionLevelingHistory().getCurrentLevel());
	EXPECT_EQ(1, leveler.getProfessionLevelingHistory().getNumLevelUps());
	EXPECT_EQ(-1, leveler.getProfessionLevelingHistory().getNumGatheredOrCraftedForLastLevelUp());
}

int main(int argc, char** argv){
	testing::InitGoogleTest(&argc, argv); 
	RUN_ALL_TESTS();
	getchar();
	return 0;
}