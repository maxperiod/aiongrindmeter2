#include "../model/PlayerClassManager.h"
#include "gtest/gtest.h"

TEST(PlayerClassManagerTest, testClasses){	
	EXPECT_TRUE(PlayerClassManager::isSuperClass("WA")); 
	EXPECT_TRUE(PlayerClassManager::isSuperClass("SC")); 
	EXPECT_TRUE(PlayerClassManager::isSuperClass("MA")); 
	EXPECT_TRUE(PlayerClassManager::isSuperClass("CL"));
	EXPECT_TRUE(PlayerClassManager::isSuperClass("EN")); 
	EXPECT_TRUE(PlayerClassManager::isSuperClass("AR")); 

	EXPECT_FALSE(PlayerClassManager::isSuperClass("FI")); 
	EXPECT_FALSE(PlayerClassManager::isSuperClass("KN")); 
	EXPECT_FALSE(PlayerClassManager::isSuperClass("RA")); 
	EXPECT_FALSE(PlayerClassManager::isSuperClass("AS")); 
	EXPECT_FALSE(PlayerClassManager::isSuperClass("WI")); 
	EXPECT_FALSE(PlayerClassManager::isSuperClass("EL")); 
	EXPECT_FALSE(PlayerClassManager::isSuperClass("PR")); 
	EXPECT_FALSE(PlayerClassManager::isSuperClass("CH")); 
	EXPECT_FALSE(PlayerClassManager::isSuperClass("GU")); 
	EXPECT_FALSE(PlayerClassManager::isSuperClass("RI")); 
	EXPECT_FALSE(PlayerClassManager::isSuperClass("BA")); 

	EXPECT_FALSE(PlayerClassManager::isSuperClass("NP")); 
}