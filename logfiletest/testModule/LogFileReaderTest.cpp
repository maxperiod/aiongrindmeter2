#include <ctime>
#include "gtest/gtest.h"

#include "../parser/LogFileReader.h"
#include "testLog/TemporaryLogFile.h"


class LogFileReaderTest: public ::testing::Test{
protected:
	TemporaryLogFile logFile;
	LogFileReader* logFileReader;
	
	LogFileReaderTest(): 
		logFile("testModule/testLog/tests.log", "testModule/testLog/Chat.log")
	{
	}
	
	virtual void SetUp(){
		//logFile = new TemporaryLogFile("testModule/testLog/tests.log", "testModule/testLog/Chat.log");
		logFileReader = new LogFileReader();
		logFile.makeFileCopy();
		logFileReader->openChatLog("testModule/testLog/");
		
		//bool status = logFile.
		
		ASSERT_TRUE(logFileReader->isOK());
	}

	virtual void TearDown(){		
		delete(logFileReader);
		logFile.deleteFileCopy();
		//delete(logFile);
	}
};

TEST_F(LogFileReaderTest, test1){
	
	logFile.appendFile("2014.06.18 17:37:40 : Critical Hit!You stunned Fierce Worg by using Shield Counter VI. ");
	logFile.appendFile("2014.06.18 17:37:41 : You inflicted 823 damage on Fierce Worg by using Provoking Shield Counter V. ");
	logFile.appendFile("2014.06.18 17:37:41 : Momomomoo Increased Fierce Worg's enmity Increase by using Provoking Shield Counter V. ");
	logFile.appendFile("2014.06.18 17:37:42 : Critical Hit!You inflicted 1,809 damage on Fierce Worg by using Swinging Shield Counter II. ");
	logFile.appendFile("2014.06.18 17:37:42 : Critical Hit!You knocked Fierce Worg over by using Swinging Shield Counter II. ");
	logFile.appendFile("2014.06.18 17:37:42 : Fierce Worg is no longer stunned. ");
	logFile.appendFile("2014.06.18 17:37:42 : Pistolnicka inflicted 2,372 damage on Fierce Worg by using Gunshot VI. ");
	logFile.appendFile("2014.06.18 17:37:42 : Critical Hit!You inflicted 2,641 damage on Fierce Worg by using Shield Retribution II. ");
	logFile.appendFile("2014.06.18 17:37:43 : Blindness has been activated. ");
	logFile.appendFile("2014.06.18 17:37:43 : Pistolnicka inflicted 2,406 damage on Fierce Worg by using Rapidfire V. ");
	logFile.appendFile("2014.06.18 17:37:43 : You inflicted 357 damage on Fierce Worg. ");
	logFile.appendFile("2014.06.18 17:37:43 : You inflicted 35 damage on Fierce Worg. ");
	logFile.appendFile("2014.06.18 17:37:44 : The weapon has been changed. ");
	logFile.appendFile("2014.06.18 17:37:44 : Critical Hit!You inflicted 1,469 damage on Fierce Worg by using Dazing Severe Blow IV. ");
	logFile.appendFile("2014.06.18 17:37:44 : Critical Hit!Fierce Worg's attack speed has decreased because Momomomoo used Dazing Severe Blow IV. ");
	logFile.appendFile("2014.06.18 17:37:44 : Fierce Worg is no longer shocked. ");
	logFile.appendFile("2014.06.18 17:37:44 : Fierce Worg restored its attack speed. ");
	logFile.appendFile("2014.06.18 17:37:44 : Pistolnicka inflicted 2,183 damage on Fierce Worg by using Rapidfire V. ");
	logFile.appendFile("2014.06.18 17:37:44 : You inflicted 1,112 damage on Fierce Worg by using Divine Blow IV. ");
	logFile.appendFile("2014.06.18 17:37:45 : Pistolnicka inflicted 1,629 damage on Fierce Worg by using Automatic Fire IV. ");
	logFile.appendFile("2014.06.18 17:37:46 : You inflicted 751 damage on Fierce Worg. ");
	logFile.appendFile("2014.06.18 17:37:46 : You inflicted 75 damage on Fierce Worg. ");
	logFile.appendFile("2014.06.18 17:37:46 : You inflicted 1,029 damage on Fierce Worg by using Provoking Severe Blow V. ");
	logFile.appendFile("2014.06.18 17:37:46 : Momomomoo Increased Fierce Worg's enmity Increase by using Provoking Severe Blow V. ");
	logFile.appendFile("2014.06.18 17:37:46 : You interrupted the target's skill. ");
	logFile.appendFile("2014.06.18 17:37:46 : Fierce Worg inflicted 573 damage on Pistolnicka. ");
	logFile.appendFile("2014.06.18 17:37:46 : You evaded Fierce Worg's attack. ");
	logFile.appendFile("2014.06.18 17:37:46 : Pistolnicka inflicted 310 damage on Fierce Worg. ");
	logFile.appendFile("2014.06.18 17:37:46 : Pistolnicka inflicted 327 damage on Fierce Worg. ");
	logFile.appendFile("2014.06.18 17:37:47 : Pistolnicka inflicted 1,629 damage on Fierce Worg by using Automatic Fire IV. ");
	logFile.appendFile("2014.06.18 17:37:47 : Critical Hit! You inflicted 1,351 critical damage on Fierce Worg. ");
	logFile.appendFile("2014.06.18 17:37:47 : You inflicted 135 damage on Fierce Worg. ");
	logFile.appendFile("2014.06.18 17:37:47 : You inflicted 135 damage on Fierce Worg. ");
	logFile.appendFile("2014.06.18 17:37:48 : You inflicted 1,641 damage on Fierce Worg by using Inquisitor's Blow IV. ");
	logFile.appendFile("2014.06.18 17:37:48 : Critical Hit!Pistolnicka inflicted 4,240 damage on Fierce Worg by using Steel Shot I. ");
	logFile.appendFile("2014.06.18 17:37:48 : Fierce Worg inflicted 387 damage on Pistolnicka. ");
	logFile.appendFile("2014.06.18 17:37:49 : You inflicted 651 damage on Fierce Worg by using Shining Slash V. ");
	logFile.appendFile("2014.06.18 17:37:49 : Pistolnicka inflicted 306 damage on Fierce Worg. ");
	logFile.appendFile("2014.06.18 17:37:49 : Pistolnicka inflicted 320 damage on Fierce Worg. ");
	logFile.appendFile("2014.06.18 17:37:49 : You received 404 damage from Fierce Worg. ");
	logFile.appendFile("2014.06.18 17:37:50 : Critical Hit! You inflicted 1,320 critical damage on Fierce Worg. ");
	logFile.appendFile("2014.06.18 17:37:50 : Critical Hit!You inflicted 2,762 damage on Fierce Worg by using Blood Pact I. ");
	logFile.appendFile("2014.06.18 17:37:50 : Pistolnicka inflicted 1,961 damage on Fierce Worg by using Spinning Fire I. ");
	logFile.appendFile("2014.06.18 17:37:51 : Fierce Worg inflicted 433 damage on Pistolnicka. ");
	logFile.appendFile("2014.06.18 17:37:51 : You inflicted 1,516 damage on Fierce Worg by using Blood Pact I. ");
	logFile.appendFile("2014.06.18 17:37:51 : [3.LFG] [charname:Anabetth;1.0000 0.6941 0.6941]: [cmd:eG545+WHdiUsi4qQOw9w6EVRg5mfKVnkcIKURP7j+0JFUYOZnylZ5HCClET+4/tCGoeNUJdub09D9KM1hv5iX0VRg5mfKVnkcIKURP7j+0I=]?Forest ?Mannor Need Cleric ");
	logFile.appendFile("2014.06.18 17:37:51 : Fierce Worg is no longer blind. ");
	logFile.appendFile("2014.06.18 17:37:51 : You inflicted 732 damage on Fierce Worg. ");
	logFile.appendFile("2014.06.18 17:37:51 : You inflicted 73 damage on Fierce Worg. ");
	logFile.appendFile("2014.06.18 17:37:51 : You inflicted 73 damage on Fierce Worg. ");
	logFile.appendFile("2014.06.18 17:37:52 : Invalid target. ");
	logFile.appendFile("2014.06.18 17:37:52 : Pistolnicka inflicted 1,681 damage on Fierce Worg by using Power Grab IV. ");
	logFile.appendFile("2014.06.18 17:37:52 : [3.LFG] [charname:Kmiirru;1.0000 0.6941 0.6941]: [cmd:7T3jB2meuF3yoQBrtN7GLEVRg5mfKVnkcIKURP7j+0JFUYOZnylZ5HCClET+4/tCsA5ZaHVfEPAbP4d47m+s6XfRLQk4qCI1SlwtlvfDFzk=]DS need Cleric/Sorc ");
	logFile.appendFile("2014.06.18 17:37:52 : You received 431 damage from Fierce Worg. ");
	logFile.appendFile("2014.06.18 17:37:52 : Quest updated: [Coin] Settle the Road ");
	logFile.appendFile("2014.06.18 17:37:52 : You have gained 80,714 XP from Fierce Worg (Energy of Repose 23,061). ");
	logFile.appendFile("2014.06.18 17:37:52 : Fierce Worg restored its attack speed. ");
	logFile.appendFile("2014.06.18 17:37:52 : You have gained 29 Abyss Points. ");
	logFile.appendFile("2014.06.18 17:37:52 : Pistolnicka inflicted 1,927 damage on Fierce Worg by using Dazzling Fire II. ");
	logFile.appendFile("2014.06.18 17:37:52 : Fierce Worg became stunned because Pistolnicka used Dazzling Fire II. ");
	logFile.appendFile("2014.06.18 17:37:53 : Fierce Worg inflicted 567 damage on Pistolnicka. ");
	logFile.appendFile("2014.06.18 17:37:53 : You restored 1,681 of Pistolnicka's HP by using Power Grab IV. ");
	logFile.appendFile("2014.06.18 17:37:53 : Pistolnicka recovered 840 MP due to the effect of Power Grab IV. ");
	logFile.appendFile("2014.06.18 17:37:54 : Pistolnicka inflicted 312 damage on Fierce Worg. ");
	logFile.appendFile("2014.06.18 17:37:54 : Pistolnicka inflicted 211 damage on Fierce Worg. ");
	logFile.appendFile("2014.06.18 17:37:54 : You recovered 3,000 HP by using Restoration Sacrifice I. ");
	logFile.appendFile("2014.06.18 17:37:54 : [3.LFG] [charname:Bauthazar;1.0000 0.6941 0.6941]: WTS 65 Cleric ");
	logFile.appendFile("2014.06.18 17:37:55 : Pistolnicka inflicted 1,805 damage on Fierce Worg by using Hot Shot III. ");
	logFile.appendFile("2014.06.18 17:37:55 : Fierce Worg is in the weaken Fire Resist state because Pistolnicka used Hot Shot III. ");
	logFile.appendFile("2014.06.18 17:37:55 : Fierce Worg's attack speed has decreased because Pistolnicka used Hot Shot III. ");
	logFile.appendFile("2014.06.18 17:37:59 : You recovered 818 HP by using Herb Treatment V. ");
	logFile.appendFile("2014.06.18 17:38:06 : [3.LFG] [charname:Elementstryker;1.0000 0.6941 0.6941]: WTS [item:187100016;ver6;????????????????????????????????????????????????????????????????????????????????????????????????;;;]PM Offer ");
	logFile.appendFile("2014.06.18 17:38:08 : [3.LFG] [charname:Rinnah;1.0000 0.6941 0.6941]: [cmd:QWMmS48xt8ojWC8jDBpg2UVRg5mfKVnkcIKURP7j+0JFUYOZnylZ5HCClET+4/tCjcUrpncUqic8VXTEMMpVgXl3L8ppPPBj3+semTb8lGg=]TAGATA NEED ALL !!! ");
	logFile.appendFile("2014.06.18 17:38:10 : [3.LFG] [charname:Lanoo;1.0000 0.6941 0.6941]: [cmd:jr7+0dVH/qA10YM/ULST6EVRg5mfKVnkcIKURP7j+0JFUYOZnylZ5HCClET+4/tCZLTXaOXV46vAG+r0aTWU0yBIjV+KrG1p9u4LJyG5euI=]TAGATA NEED ALL !!! ");
	logFile.appendFile("2014.06.18 17:38:24 : Your Physical Def has been weakened by using Reroute Power I. ");
	logFile.appendFile("2014.06.18 17:38:24 : You received the effect by using Reroute Power I. ");
	logFile.appendFile("2014.06.18 17:38:25 : You inflicted 1,853 damage on Sprawling Agrint by using Inquisitor's Blow IV. ");
	logFile.appendFile("2014.06.18 17:38:25 : Reroute Power Effect has been activated. ");
	logFile.appendFile("2014.06.18 17:38:25 : Sprawling Agrint received 237 damage due to the effect of Reroute Power Effect. ");
	logFile.appendFile("2014.06.18 17:38:26 : Critical Hit! You inflicted 1,602 critical damage on Sprawling Agrint. ");
	logFile.appendFile("2014.06.18 17:38:26 : You inflicted 160 damage on Sprawling Agrint. ");
	logFile.appendFile("2014.06.18 17:38:26 : You received 474 damage from Sprawling Agrint. ");
	logFile.appendFile("2014.06.18 17:38:26 : [3.LFG] [charname:Verthimor;1.0000 0.6941 0.6941]: WTS [item:113601199;ver5;;;;T0dFz1Pu0NeKGAuLPkBLzw==;;] your passes/wraps (or make skin)!! pm ");
	logFile.appendFile("2014.06.18 17:38:26 : You inflicted 2,795 damage on Sprawling Agrint by using Shining Slash V. ");
	logFile.appendFile("2014.06.18 17:38:27 : Reroute Power Effect has been activated. ");
	logFile.appendFile("2014.06.18 17:38:27 : Sprawling Agrint received 237 damage due to the effect of Reroute Power Effect. ");
	logFile.appendFile("2014.06.18 17:38:27 : Reroute Power Effect has been activated. ");
	logFile.appendFile("2014.06.18 17:38:27 : Sprawling Agrint received 237 damage due to the effect of Reroute Power Effect. ");
	logFile.appendFile("2014.06.18 17:38:27 : You inflicted 1,715 damage on Sprawling Agrint by using Blood Pact I. ");
	logFile.appendFile("2014.06.18 17:38:27 : Reroute Power Effect has been activated. ");
	logFile.appendFile("2014.06.18 17:38:27 : Sprawling Agrint received 237 damage due to the effect of Reroute Power Effect. ");
	logFile.appendFile("2014.06.18 17:38:28 : You inflicted 798 damage on Sprawling Agrint. ");
	logFile.appendFile("2014.06.18 17:38:28 : You inflicted 79 damage on Sprawling Agrint. ");
	logFile.appendFile("2014.06.18 17:38:28 : You inflicted 79 damage on Sprawling Agrint. ");
	logFile.appendFile("2014.06.18 17:38:28 : You inflicted 1,574 damage on Sprawling Agrint by using Blood Pact I. ");
	logFile.appendFile("2014.06.18 17:38:28 : Reroute Power Effect has been activated. ");
	logFile.appendFile("2014.06.18 17:38:28 : Sprawling Agrint received 237 damage due to the effect of Reroute Power Effect. ");
	logFile.appendFile("2014.06.18 17:38:28 : Reroute Power Effect has been activated. ");
	logFile.appendFile("2014.06.18 17:38:28 : Sprawling Agrint received 237 damage due to the effect of Reroute Power Effect. ");
	logFile.appendFile("2014.06.18 17:38:29 : Critical Hit!You inflicted 2,833 damage on Sprawling Agrint by using Blood Pact I. ");
	logFile.appendFile("2014.06.18 17:38:29 : Sprawling Agrint is no longer shocked. ");
	 

	queue<string> lines;

	long start = clock();
	logFileReader->readLines(lines);
	long end = clock();
	cout << "Time in seconds: " << (float)(end - start) / CLOCKS_PER_SEC << endl;

	EXPECT_EQ(101, lines.size());
	EXPECT_EQ("2014.06.18 17:37:40 : Critical Hit!You stunned Fierce Worg by using Shield Counter VI. ", lines.front());
	EXPECT_EQ("2014.06.18 17:38:29 : Sprawling Agrint is no longer shocked. ", lines.back());

	logFile.appendFile("2014.06.18 17:38:29 : Reroute Power Effect has been activated. ");
	logFile.appendFile("2014.06.18 17:38:29 : Sprawling Agrint received 237 damage due to the effect of Reroute Power Effect. ");
	logFile.appendFile("2014.06.18 17:38:29 : You received 358 damage from Sprawling Agrint. ");
		
	logFileReader->readLines(lines);
	
	EXPECT_EQ(104, lines.size());
	EXPECT_EQ("2014.06.18 17:37:40 : Critical Hit!You stunned Fierce Worg by using Shield Counter VI. ", lines.front());
	EXPECT_EQ("2014.06.18 17:38:29 : You received 358 damage from Sprawling Agrint. ", lines.back());


	logFile.appendFile("2014.06.18 17:38:29 : Sprawling Agrint is no longer shocked. ");
	logFile.appendFile("2014.06.18 17:38:29 : Reroute Power Effect has been activated. ");
	logFile.appendFile("2014.06.18 17:38:29 : Sprawling Agrint received 237 damage due to the effect of Reroute Power Effect. ");
	logFile.appendFile("2014.06.18 17:38:29 : You received 358 damage from Sprawling Agrint. ");
	
	logFileReader->readLines(lines);
	
	EXPECT_EQ(108, lines.size());
	EXPECT_EQ("2014.06.18 17:37:40 : Critical Hit!You stunned Fierce Worg by using Shield Counter VI. ", lines.front());
	EXPECT_EQ("2014.06.18 17:38:29 : You received 358 damage from Sprawling Agrint. ", lines.back());

	logFileReader->readLines(lines);

	EXPECT_EQ(108, lines.size());
	EXPECT_EQ("2014.06.18 17:37:40 : Critical Hit!You stunned Fierce Worg by using Shield Counter VI. ", lines.front());
	EXPECT_EQ("2014.06.18 17:38:29 : You received 358 damage from Sprawling Agrint. ", lines.back());

}

TEST_F(LogFileReaderTest, testReadFromBeginning){
	queue<string> lines;
	
	
	long start = clock();
	logFileReader->readLines(lines, true);
	long end = clock();
	cout << "Time in seconds: " << (float)(end - start) / CLOCKS_PER_SEC << endl;

}
