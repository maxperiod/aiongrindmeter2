#include <memory>
using namespace std;

#include "gtest/gtest.h"
#include "../parser/MaxPeriodParser.h"
#include "../parser/UserCommandFactory.h"

class CommandFactoryTest: public ::testing::Test{
protected:
	MaxPeriodParser parser;
	
	UserCommandFactory userCommandFactory;
	
	virtual void SetUp(){
		userCommandFactory.setParser(parser);		
	}
};

TEST_F(CommandFactoryTest, testNotCommand){
	vector<string> command = userCommandFactory.getUserCommand("2014.06.21 14:01:59 : Momomomoo: mooOOOOoooo.... ");
	EXPECT_EQ(0, command.size());
	//EXPECT_EQ("mooOOOOoooo....", command[0]);
}

TEST_F(CommandFactoryTest, testCommandNoParams){
	vector<string> command = userCommandFactory.getUserCommand("2014.06.21 14:01:59 : Momomomoo: .dps ");
	EXPECT_EQ(1, command.size());
	EXPECT_EQ("dps", command[0]);
}

TEST_F(CommandFactoryTest, testCommandWithParam){
	vector<string> command = userCommandFactory.getUserCommand("2014.06.21 14:01:59 : Momomomoo: .ap 1250000 ");
	EXPECT_EQ(2, command.size());
	EXPECT_EQ("ap", command[0]);
	EXPECT_EQ("1250000", command[1]);
}

TEST_F(CommandFactoryTest, testParamWithSpaces){
	vector<string> command = userCommandFactory.getUserCommand("2014.06.21 14:01:59 : Momomomoo: .kills Grimed Clodworm Swarm ");
	EXPECT_EQ(2, command.size());
	EXPECT_EQ("kills", command[0]);
	EXPECT_EQ("Grimed Clodworm Swarm", command[1]);
}

TEST_F(CommandFactoryTest, testParamWithMultipleSeparator){
	vector<string> command = userCommandFactory.getUserCommand("2014.06.21 14:01:59 : Momomomoo: .exp  13286478 ");
	EXPECT_EQ(2, command.size());
	EXPECT_EQ("exp", command[0]);
	EXPECT_EQ("13286478", command[1]);
}

TEST_F(CommandFactoryTest, testNotMe){
	vector<string> command = userCommandFactory.getUserCommand("2014.07.14 11:51:44 : [charname:Alexadnerus;0.0196 0.7843 0.8431]: .clear ");
	EXPECT_EQ(0, command.size());
	
}