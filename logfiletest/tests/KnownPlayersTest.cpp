#include "../model/KnownPlayers.h"
#include "gtest/gtest.h"

TEST(KnownPlayers, addPlayer1){
	KnownPlayers players;

	EXPECT_FALSE(players.isPlayer("PublicLightBus"));
	players.addPlayer("PublicLightBus");
	EXPECT_TRUE(players.isPlayer("PublicLightBus"));
	EXPECT_EQ("", players.getPlayerClass("PublicLightBus"));
	
	players.setPlayerClass("PublicLightBus", "MA");
	EXPECT_TRUE(players.isPlayer("PublicLightBus"));
	EXPECT_EQ("MA", players.getPlayerClass("PublicLightBus"));
	
}

TEST(KnownPlayers, playerCannotBeDetermined){
	KnownPlayers players;
	
	players.setPlayerClass("PublicLightBus", "pcnpc");
	EXPECT_FALSE(players.isPlayer("PublicLightBus"));
	EXPECT_EQ("", players.getPlayerClass("PublicLightBus"));	
}

TEST(KnownPlayers, playerButClassNotKnown){
	KnownPlayers players;
	
	players.setPlayerClass("PublicLightBus", "multi");
	EXPECT_TRUE(players.isPlayer("PublicLightBus"));
	EXPECT_EQ("", players.getPlayerClass("PublicLightBus"));	
}


TEST(KnownPlayers, setPlayerSubclass){
	KnownPlayers players;
	
	players.setPlayerClass("PublicLightBus", "WI");
	EXPECT_TRUE(players.isPlayer("PublicLightBus"));
	EXPECT_EQ("WI", players.getPlayerClass("PublicLightBus"));
	
	players.setPlayerClass("PublicLightBus", "MA");
	EXPECT_TRUE(players.isPlayer("PublicLightBus"));
	EXPECT_EQ("WI", players.getPlayerClass("PublicLightBus"));
	
}


TEST(KnownPlayers, notAPlayer){
	KnownPlayers players;
	

	EXPECT_EQ("", players.getPlayerClass("Talon Laborer"));
	
}

