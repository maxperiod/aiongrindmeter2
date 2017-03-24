
using namespace std;

#include "gtest/gtest.h"

#include "../Module.h"
#include "../parser/LogFileUtility.h"
#include "../language/EnglishNA.h"
#include "../parser/ChatLogCommand.h"

#include "testLog/TemporaryLogFile.h"

class Module1: public Module{
public:
	int x;
	int m;
	Module1(): x(0), m(0){
		DECLARE_MESSAGE_RULE(STR_WORLDMAP_INFO);
		DECLARE_MESSAGE_RULE(STR_MSG_GET_ITEM);
	}

	void executeChatLogCommand(ChatLogCommand& command){
		if (command.getMessageRuleCode() == STR_WORLDMAP_INFO) x++;
		else if (command.getMessageRuleCode() == STR_MSG_GET_ITEM) m += 100;
	}

	void endOfTickAction(){
	}

};

class Module2: public Module{
public:
	int y;
	int n;
	Module2(): y(6), n(0){
		DECLARE_MESSAGE_RULE(STR_WORLDMAP_UNDER_CONSTRUCTION);
		DECLARE_MESSAGE_RULE(STR_MSG_GET_ITEM);
	}

	void executeChatLogCommand(ChatLogCommand& command){
		if (command.getMessageRuleCode() == STR_WORLDMAP_UNDER_CONSTRUCTION) y *= 2;
		else if (command.getMessageRuleCode() == STR_MSG_GET_ITEM) n += 200;
	}

	void endOfTickAction(){
		y -= 1;
	}
};

class LogFileUtilityTest: public ::testing::Test{
protected:
	TemporaryLogFile logFile;

	EnglishNA language;

	LogFileUtility logFileUtility;
	Module1 module1;
	Module2 module2;
	
	LogFileUtilityTest(): 
		logFile("testModule/testLog/tests.log", "testModule/testLog/Chat.log")//,
		//logFileUtility(language)
	{
		logFile.makeFileCopy();
	}

	virtual void SetUp(){
		
		bool status = logFileUtility.setAionDirectory("testModule/testLog/");
		ASSERT_TRUE(status);

		logFileUtility.registerModule(module1);
		logFileUtility.registerModule(module2);
		/*
		logFileUtility.registerMessageRuleCode(STR_WHISPER_REFUSE);
		logFileUtility.registerMessageRuleCode(STR_WORLDMAP_INFO);
		logFileUtility.registerMessageRuleCode(STR_WORLDMAP_UNDER_CONSTRUCTION);
		logFileUtility.registerMessageRuleCode(STR_YOU_EXCLUDED);
		*/
	}
};

TEST_F(LogFileUtilityTest, test1){
	logFileUtility.parseLogFile();
	EXPECT_EQ(-1, logFileUtility.getTimestampOfLatestMessage());

	logFile.appendFile("2014.06.18 17:37:06 : [3.LFG] [charname:RoboNublet;1.0000 0.6941 0.6941]: [cmd:mj7/5TZfrJ2pXvZb+rtkB5YNnze4s0GemRKuJ7Dm4clFUYOZnylZ5HCClET+4/tCxcsuVhhDO9yuNqQAm2su0z1PcaoWddhrHx3o2lBYvN0=]EC 350 plse ");
	logFile.appendFile("2014.06.18 17:37:22 : The map is now loading. ");

	logFileUtility.parseLogFile();

	EXPECT_GT(logFileUtility.getTimestampOfLatestMessage(), 0);

	EXPECT_EQ(1, module1.x);
	EXPECT_EQ(4, module2.y);
}

TEST_F(LogFileUtilityTest, test2){
	logFile.appendFile("2014.06.18 17:37:06 : The World Map is currently being prepared. ");
	logFile.appendFile("2014.06.18 17:37:06 : Pistolnicka evaded Fierce Worg's attack. ");

	logFileUtility.parseLogFile();

	EXPECT_EQ(0, module1.x);
	EXPECT_EQ(11, module2.y);
}

TEST_F(LogFileUtilityTest, test3){
	logFile.appendFile("2014.06.26 21:16:18 : You have opened the Greater Contribution Bundle. ");
	logFile.appendFile("2014.06.26 21:16:18 : You have used Greater Contribution Bundle. ");
	logFile.appendFile("2014.06.26 21:16:19 : You have acquired [item:186000058;ver6;;;;]. ");
	logFile.appendFile("2014.06.26 21:16:21 : [charname:DrFLytOx;1.0000 1.0000 1.0000]: hey ");

	logFileUtility.parseLogFile();

	EXPECT_EQ(100, module1.m);
	EXPECT_EQ(200, module2.n);
}

TEST(TestDirectory, testDirectoryChatLogDisabled){
	LogFileUtility logFileUtility;
	EXPECT_FALSE(logFileUtility.setAionDirectory("testModule/testDirectoryChatLogDisabled/"));
	EXPECT_TRUE(logFileUtility.isValidAionDirectory());
	EXPECT_FALSE(logFileUtility.isChatLogEnabled());
}

TEST(TestDirectory, testDirectoryChatLogEnabled){
	LogFileUtility logFileUtility;
	EXPECT_FALSE(logFileUtility.setAionDirectory("testModule/testDirectoryChatLogEnabled/"));
	EXPECT_TRUE(logFileUtility.isValidAionDirectory());
	EXPECT_TRUE(logFileUtility.isChatLogEnabled());
}

TEST(TestDirectory, testDirectoryLogfileExistsChatLogDisabled){
	LogFileUtility logFileUtility;
	EXPECT_TRUE(logFileUtility.setAionDirectory("testModule/testDirectoryLogfileExistsChatLogDisabled/"));
	EXPECT_TRUE(logFileUtility.isValidAionDirectory());
	EXPECT_FALSE(logFileUtility.isChatLogEnabled());
}

TEST(TestDirectory, testDirectoryLogfileExistsChatLogEnabled){
	LogFileUtility logFileUtility;
	EXPECT_TRUE(logFileUtility.setAionDirectory("testModule/testDirectoryLogfileExistsChatLogEnabled/"));
	EXPECT_TRUE(logFileUtility.isValidAionDirectory());
	EXPECT_TRUE(logFileUtility.isChatLogEnabled());
}

TEST(TestDirectory, invalidAionDirectory){
	LogFileUtility logFileUtility;
	EXPECT_FALSE(logFileUtility.setAionDirectory("./"));
	EXPECT_FALSE(logFileUtility.isValidAionDirectory());
	EXPECT_FALSE(logFileUtility.isChatLogEnabled());
}
