#include "../lookups/SkillToClassHardCodedNA.h"
#include "gtest/gtest.h"

TEST(SkillToClass, NA1){
	SkillToClassHardCodedNA skillToClassMap;
	EXPECT_EQ("KN", skillToClassMap.getClass("Steel Wall Defense III"));

	EXPECT_EQ("", skillToClassMap.getClass("Ferocious Strike I"));
}

int main(int argc, char** argv){
	testing::InitGoogleTest(&argc, argv); 
	RUN_ALL_TESTS();
	getchar();
	return 0;
}