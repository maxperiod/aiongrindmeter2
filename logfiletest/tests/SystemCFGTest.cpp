#include "gtest/gtest.h"
#include "../parser/SystemCFG.h"



TEST(SystemCFGTest, open0){
	
	SystemCFG systemCFG;

	systemCFG.readCFG("D:/Aion/system.cfg", true);
	
	EXPECT_TRUE(systemCFG.isReadSuccessful());

	EXPECT_EQ("1", systemCFG.getEntries().at("G_Chatlog"));
}


TEST(SystemCFGTest, open1){
	
	SystemCFG systemCFG;

	systemCFG.readCFG("testModule/testDirectoryChatLogDisabled/system.cfg", true);
	
	EXPECT_TRUE(systemCFG.isReadSuccessful());

	EXPECT_EQ("0", systemCFG.getEntries().at("G_Chatlog"));
}

TEST(SystemCFGTest, open2){
	
	SystemCFG systemCFG;

	systemCFG.readCFG("testModule/testDirectoryChatLogEnabled/system.cfg", true);
	
	EXPECT_TRUE(systemCFG.isReadSuccessful());

	EXPECT_EQ("1", systemCFG.getEntries().at("G_Chatlog"));
}