#include <iostream>

#include "../model/AssistDamage.h"
#include "gtest/gtest.h"


TEST(KnownPlayers, addPlayer1){
	int damageExpiry = 1;
	AssistDamage damageInflicted(damageExpiry);

	damageInflicted.inflictDamage("Darth Vader", 1640);
	//cout << "Hit any key to continue. Damage expiry is " << damageExpiry << " seconds" << endl;
	//getchar();
	EXPECT_EQ(1640, damageInflicted.getInflictedDamage("Darth Vader"));
	//EXPECT_TRUE(damageInflicted.hasDealtDamageRecently("Darth Vader"));
	
	damageInflicted.inflictDamage("Darth Vader", 2000);
	EXPECT_EQ(3640, damageInflicted.getInflictedDamage("Darth Vader"));
	//EXPECT_TRUE(damageInflicted.hasDealtDamageRecently("Darth Vader"));
	
	cout << "Wait 1 second, then hit ENTER..." << endl;
	getchar();
	EXPECT_EQ(-1, damageInflicted.getInflictedDamage("Darth Vader"));
}

int main(int argc, char** argv){
	testing::InitGoogleTest(&argc, argv); 
	RUN_ALL_TESTS();
	getchar();
	return 0;
}