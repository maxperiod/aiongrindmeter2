#include "pvpKillsCounter.h"
#include "gtest/gtest.h"

TEST(counter, insert1){
	PvpKillsCounter<string> itamz;

	map<string, PlayerKill>::iterator tada;	

	itamz.addKill("One");
	EXPECT_EQ(1, itamz.getTotalKills());
	
	tada = itamz.begin();	
	EXPECT_EQ("One", tada->first);
	EXPECT_EQ(1, tada->second.kills);
	EXPECT_EQ(0, tada->second.assists);
	tada ++;
	EXPECT_EQ(tada, itamz.end());
	
	itamz.addAssist("One");	
	itamz.addKill("Two");
	itamz.addAssist("Three");
	EXPECT_EQ(2, itamz.getTotalKills());
	EXPECT_EQ(2, itamz.getTotalAssists());

	
	tada = itamz.begin();
	EXPECT_EQ("One", tada->first);
	EXPECT_EQ(1, tada->second.kills);
	EXPECT_EQ(1, tada->second.assists);
	tada ++;
	EXPECT_EQ("Three", tada->first);
	EXPECT_EQ(0, tada->second.kills);
	EXPECT_EQ(1, tada->second.assists);
	tada ++;		
	EXPECT_EQ("Two", tada->first);
	EXPECT_EQ(1, tada->second.kills);
	EXPECT_EQ(0, tada->second.assists);
	tada ++; 
	EXPECT_EQ(tada, itamz.end());
	/*
	itamz.add("Sleeping", 3);
	EXPECT_EQ(9, itamz.getTotalCount());

	tada = itamz.begin();
	tada ++;
	EXPECT_EQ("Sleeping", tada->first);
	EXPECT_EQ(4, tada->second);
	
	itamz.erase("QQing");
	EXPECT_EQ(6, itamz.getTotalCount());
	tada = itamz.begin();
	EXPECT_EQ("Sleeping", tada->first);
	EXPECT_EQ(4, tada->second);
	*/
}


int main(int argc, char** argv){
	testing::InitGoogleTest(&argc, argv); 
	RUN_ALL_TESTS();
	getchar();
	return 0;
}