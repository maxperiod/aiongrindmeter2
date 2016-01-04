#include "gtest/gtest.h"

#include "../parser/LogFileUtility.h"
#include "../language/EnglishNA.h"

#include "../modules/ItemAcquisitionModule.h"

#include "testLog/TemporaryLogFile.h"

class ItemAcquisitionModuleTest: public ::testing::Test{
protected:
	MaxPeriodParser parser;
	EnglishNA language;
	
	ItemAcquisitionModule itemAcquisitionModule;	
	TemporaryLogFile logFile;

	LogFileUtility logFileUtility;
	
	ItemAcquisitionModuleTest(): 
			logFile("testModule/testLog/tests.log", "testModule/testLog/Chat.log"){//,
			//logFileUtility(language){
	}

	virtual void SetUp(){
		logFile.makeFileCopy();

		logFileUtility.registerModule(itemAcquisitionModule);

		string aionDirectory = "testModule/testLog/";
		
		ASSERT_TRUE(logFileUtility.setAionDirectory(aionDirectory));

	}

	virtual void TearDown(){		
		logFile.deleteFileCopy();
	}
};

TEST_F(ItemAcquisitionModuleTest, getItem){
	logFile.appendFile("2014.09.10 22:45:16 : You have acquired [item:188051605;ver6;;;;]. ");
	logFileUtility.parseLogFile();
	logFileUtility.parseLogFile();

	EXPECT_EQ(1, itemAcquisitionModule.itemsAcquired.getTotalCount());

	EXPECT_EQ(188051605, itemAcquisitionModule.itemsAcquired.getLastUpdated()->first);
	EXPECT_EQ(1, itemAcquisitionModule.itemsAcquired.getLastUpdated()->second.numGained);
	EXPECT_EQ(1, itemAcquisitionModule.itemsAcquired.getLastUpdated()->second.numPackets);
}

TEST_F(ItemAcquisitionModuleTest, getItemMulti){
	logFile.appendFile("2014.09.10 22:45:16 : You have acquired 7 [item:164000156;ver6;;;;](s). ");
	logFileUtility.parseLogFile();
	logFileUtility.parseLogFile();

	EXPECT_EQ(7, itemAcquisitionModule.itemsAcquired.getTotalCount());

	EXPECT_EQ(164000156, itemAcquisitionModule.itemsAcquired.getLastUpdated()->first);
	EXPECT_EQ(7, itemAcquisitionModule.itemsAcquired.getLastUpdated()->second.numGained);
	EXPECT_EQ(1, itemAcquisitionModule.itemsAcquired.getLastUpdated()->second.numPackets);
}

TEST_F(ItemAcquisitionModuleTest, getItemSpecial){
	
	logFile.appendFile("2014.09.11 21:24:34 : You have acquired [item:186000135;ver6;;;;] and stored it in your special cube. ");
	logFile.appendFile("2014.09.11 21:24:34 : You have acquired [item:186000184;ver6;;;;] and stored it in your special cube. ");
	logFileUtility.parseLogFile();
	logFileUtility.parseLogFile();

	EXPECT_EQ(2, itemAcquisitionModule.itemsAcquired.getTotalCount());

	EXPECT_EQ(186000184, itemAcquisitionModule.itemsAcquired.getLastUpdated()->first);
	EXPECT_EQ(1, itemAcquisitionModule.itemsAcquired.getLastUpdated()->second.numGained);
	EXPECT_EQ(1, itemAcquisitionModule.itemsAcquired.getLastUpdated()->second.numPackets);
}

TEST_F(ItemAcquisitionModuleTest, getItemMultiSpecial){
	logFile.appendFile("2014.08.25 23:43:09 : Quest updated: [Coin] From The Cold Dead Klaws ");
	logFile.appendFile("2014.08.25 23:43:10 : You have acquired 10 [item:186000237;ver6;;;;]s and stored them in your special cube. ");
	logFile.appendFile("2014.08.25 23:43:10 : You have acquired [item:188052315;ver6;;;;]. ");
	logFile.appendFile("2014.08.25 23:43:10 : You have gained 4,825,175 XP from Nedzelinerk. ");
	logFile.appendFile("2014.08.25 23:43:10 : You can receive the daily quest again at 9 in the morning. ");
	logFile.appendFile("2014.08.25 23:43:10 : Quest complete: [Coin] From The Cold Dead Klaws ");	
	
	logFileUtility.parseLogFile();
	logFileUtility.parseLogFile();

	EXPECT_EQ(11, itemAcquisitionModule.itemsAcquired.getTotalCount());

	EXPECT_EQ(188052315, itemAcquisitionModule.itemsAcquired.getLastUpdated()->first);
	EXPECT_EQ(1, itemAcquisitionModule.itemsAcquired.getLastUpdated()->second.numGained);
	EXPECT_EQ(1, itemAcquisitionModule.itemsAcquired.getLastUpdated()->second.numPackets);

	EXPECT_EQ(10, itemAcquisitionModule.itemsAcquired.get(186000237).numGained);
	EXPECT_EQ(1, itemAcquisitionModule.itemsAcquired.get(186000237).numPackets);
	//EXPECT_EQ(10, itemAcquisitionModule.itemsAcquired.get(186000237)->second.numGained);
	//EXPECT_EQ(1, itemAcquisitionModule.itemsAcquired.get(186000237)->second.numPackets);
}

TEST_F(ItemAcquisitionModuleTest, rollDice){
	logFile.appendFile("2014.06.18 17:45:44 : You rolled the dice and got 94 (max. 100). ");
	logFile.appendFile("2014.06.18 17:45:44 : You recovered 4,797 HP by using Prayer of Resilience VII. ");
	logFile.appendFile("2014.06.18 17:45:45 : Vandiem gave up rolling the dice. ");
	logFile.appendFile("2014.06.18 17:45:45 : You rolled the highest. ");
	logFile.appendFile("2014.06.18 17:45:45 : You have acquired [item:167000559;ver6;;;;]. ");

	logFileUtility.parseLogFile();
	logFileUtility.parseLogFile();
		
	//EXPECT_EQ(1, itemAcquisitionModule.itemsAcquired.get(167000559)->second.numGained);
	EXPECT_EQ(1, itemAcquisitionModule.itemsAcquired.get(167000559).numGained);

	EXPECT_EQ(167000559, itemAcquisitionModule.itemRolls.getItemRolls()[0].item);
	EXPECT_EQ(94, itemAcquisitionModule.itemRolls.getItemRolls()[0].yourRoll);
	EXPECT_EQ(94, itemAcquisitionModule.itemRolls.getItemRolls()[0].winningRoll);
	EXPECT_EQ("", itemAcquisitionModule.itemRolls.getItemRolls()[0].winner);

	logFile.appendFile("2014.06.19 10:13:26 : You rolled the dice and got 99 (max. 100). ");
	logFile.appendFile("2014.06.19 10:13:26 : Kamihana gave up rolling the dice. ");
	logFile.appendFile("2014.06.19 10:13:27 : selmor rolled the dice and got 100 (max. 100). ");
	logFile.appendFile("2014.06.19 10:13:27 : Healerofgood rolled the dice and got 55 (max. 100). ");
	logFile.appendFile("2014.06.19 10:13:29 : [3.LFG] [charname:WatchOutiHavegun;1.0000 0.6941 0.6941]: [cmd:bALJZwIJYYXl3+8qK8JnmIsK2du/wgyik+5GCzUGq6hFUYOZnylZ5HCClET+4/tC7/jlqn70jmbxtLCSkF3oRv+QkIX5X4xzhAqJOP8CJFA=]? Forest ? Manor  ");
	logFile.appendFile("2014.06.19 10:13:30 : Fitrios rolled the dice and got 97 (max. 100). ");
	logFile.appendFile("2014.06.19 10:13:30 : selmor rolled the highest (selmor rolled 100, while you rolled 99). ");
	logFile.appendFile("2014.06.19 10:13:30 : selmor has acquired [item:111601301]. ");

	logFileUtility.parseLogFile();
	logFileUtility.parseLogFile();

	EXPECT_EQ(111601301, itemAcquisitionModule.itemRolls.getItemRolls()[1].item);
	EXPECT_EQ(99, itemAcquisitionModule.itemRolls.getItemRolls()[1].yourRoll);
	EXPECT_EQ(100, itemAcquisitionModule.itemRolls.getItemRolls()[1].winningRoll);
	EXPECT_EQ("selmor", itemAcquisitionModule.itemRolls.getItemRolls()[1].winner);

	logFile.appendFile("2014.08.27 00:08:24 : You gave up rolling the dice. ");
	logFile.appendFile("2014.08.27 00:08:24 : Vyncentt rolled the dice and got 81 (max. 100). ");
	logFile.appendFile("2014.08.27 00:08:25 : Greyskie gave up rolling the dice. ");
	logFile.appendFile("2014.08.27 00:08:25 : VVlasta rolled the dice and got 93 (max. 100). ");
	logFile.appendFile("2014.08.27 00:08:25 : LightGunz gave up rolling the dice. ");
	logFile.appendFile("2014.08.27 00:08:25 : VVlasta recovered 240 MP due to the effect of Resonating Melody V. ");
	logFile.appendFile("2014.08.27 00:08:25 : [3.LFG] [charname:Eireena;1.0000 0.6941 0.6941]: she wants the D ");
	logFile.appendFile("2014.08.27 00:08:26 : Kenruk gave up rolling the dice. ");
	logFile.appendFile("2014.08.27 00:08:26 : VVlasta rolled the highest (VVlasta rolled 93, while you passed). ");
	logFile.appendFile("2014.08.27 00:08:26 : VVlasta has acquired [item:152013038]. ");

	logFileUtility.parseLogFile();
	logFileUtility.parseLogFile();

	EXPECT_EQ(3, itemAcquisitionModule.itemRolls.getItemRolls().size());
	
	EXPECT_EQ(152013038, itemAcquisitionModule.itemRolls.getItemRolls()[2].item);
	EXPECT_EQ(-1, itemAcquisitionModule.itemRolls.getItemRolls()[2].yourRoll);
	EXPECT_EQ(93, itemAcquisitionModule.itemRolls.getItemRolls()[2].winningRoll);
	EXPECT_EQ("VVlasta", itemAcquisitionModule.itemRolls.getItemRolls()[2].winner);

	logFile.appendFile("2014.08.27 00:11:32 : LightGunz has acquired [item:188053450]. ");
	logFile.appendFile("2014.08.27 00:11:33 : Vyncentt has acquired [item:188053450]. ");

	logFileUtility.parseLogFile();
	logFileUtility.parseLogFile();

	EXPECT_EQ(3, itemAcquisitionModule.itemRolls.getItemRolls().size());

	EXPECT_EQ(2, itemAcquisitionModule.itemRolls.getNumItemsRolled());
	EXPECT_EQ(1, itemAcquisitionModule.itemRolls.getNumItemsPassed());
	EXPECT_EQ(1, itemAcquisitionModule.itemRolls.getNumItemsWon());
	EXPECT_FLOAT_EQ((float)(94+99)/2, itemAcquisitionModule.itemRolls.getAverageOfMyRolls());
	EXPECT_FLOAT_EQ((float)(94+100+93)/3, itemAcquisitionModule.itemRolls.getAverageOfWinningRolls());
}

TEST_F(ItemAcquisitionModuleTest, rollDice2){
	logFile.appendFile("2014.09.18 12:12:52 : You rolled the dice and got 55 (max. 100). ");
	logFile.appendFile("2014.09.18 12:12:52 : Lyndsai has acquired [item:186000238]. ");
	logFileUtility.parseLogFile();

	logFile.appendFile("2014.09.18 12:12:53 : RinoaFFVIII gave up rolling the dice. ");
	logFile.appendFile("2014.09.18 12:12:55 : [charname:Bretonn;0.0196 0.7843 0.8431]: ty all seee ya ");
	logFileUtility.parseLogFile();
	logFileUtility.parseLogFile();

	logFile.appendFile("2014.09.18 12:12:58 : RinoaFFVIII has become the new group leader. ");
	logFile.appendFile("2014.09.18 12:12:58 : Bretonn has left your group. ");
	logFile.appendFile("2014.09.18 12:13:00 : KicsiAni rolled the dice and got 90 (max. 100). ");
	logFile.appendFile("2014.09.18 12:13:00 : Momomomoo: damnit rinoaffviii won two composite bundles this run ");
	logFileUtility.parseLogFile();
	logFileUtility.parseLogFile();
	
	logFile.appendFile("2014.09.18 12:13:04 : Lyndsai gave up rolling the dice. ");
	logFile.appendFile("2014.09.18 12:13:04 : KicsiAni rolled the highest (KicsiAni rolled 90, while you rolled 55). ");
	logFileUtility.parseLogFile();
	logFileUtility.parseLogFile();

	logFile.appendFile("2014.09.18 12:13:17 : There is 1 minute left to trade with Sauro Guard's Tunic. ");
	logFile.appendFile("2014.09.18 12:13:22 : KicsiAni has left your group. ");
	logFile.appendFile("2014.09.18 12:13:25 : [charname:xlllllllllllllx;0.5961 0.9294 0.0667]: asmo ");
	logFile.appendFile("2014.09.18 12:13:29 : You left the group. ");	
	logFileUtility.parseLogFile();
	logFileUtility.parseLogFile();

	logFile.appendFile("2014.09.18 12:14:12 : You have acquired [item:186000238;ver6;;;;] and stored it in your special cube. ");
	logFile.appendFile("2014.09.18 12:14:13 : You have acquired [item:188053023;ver6;;;;]. ");
	logFile.appendFile("2014.09.18 12:14:13 : Momomomoo has acquired [item:188053023]. ");
	logFileUtility.parseLogFile();
	logFileUtility.parseLogFile();

	EXPECT_EQ(-1, itemAcquisitionModule.itemRolls.getItemRolls()[0].item);
	EXPECT_EQ(55, itemAcquisitionModule.itemRolls.getItemRolls()[0].yourRoll);
	EXPECT_EQ(90, itemAcquisitionModule.itemRolls.getItemRolls()[0].winningRoll);
	EXPECT_EQ("KicsiAni", itemAcquisitionModule.itemRolls.getItemRolls()[0].winner);

	EXPECT_EQ(1, itemAcquisitionModule.itemRolls.getItemRolls().size());

}

TEST_F(ItemAcquisitionModuleTest, openContainer1){
	logFile.appendFile("2014.06.29 01:05:33 : You have acquired 2 [item:186000243;ver6;;;;]s and stored them in your special cube. ");
	logFile.appendFile("2014.06.29 01:05:33 : You have opened the Cuperine Ceramium Piece Case. ");
	logFile.appendFile("2014.06.29 01:05:33 : You have used Cuperine Ceramium Piece Case. ");

	logFileUtility.parseLogFile();
	logFileUtility.parseLogFile();

	EXPECT_EQ(0, itemAcquisitionModule.itemsAcquired.getTotalCount());

	EXPECT_EQ(1, itemAcquisitionModule.containersOpened.get("Cuperine Ceramium Piece Case").numGained);
	EXPECT_EQ(2, itemAcquisitionModule.itemsFromContainers.at("Cuperine Ceramium Piece Case").get(186000243).numGained);
}


TEST_F(ItemAcquisitionModuleTest, openContainer2){
	logFile.appendFile("2014.08.07 12:44:56 : You have acquired 3 [item:152000113;ver6;;;;](s). ");
	logFile.appendFile("2014.08.07 12:44:56 : You have opened the Greater Malevite Ore. ");
	logFile.appendFile("2014.08.07 12:44:56 : You have used Greater Malevite Ore. ");

	logFileUtility.parseLogFile();
	logFileUtility.parseLogFile();

	EXPECT_EQ(0, itemAcquisitionModule.itemsAcquired.getTotalCount());

	EXPECT_EQ(1, itemAcquisitionModule.containersOpened.get("Greater Malevite Ore").numGained);
	EXPECT_EQ(3, itemAcquisitionModule.itemsFromContainers.at("Greater Malevite Ore").get(152000113).numGained);
}

TEST_F(ItemAcquisitionModuleTest, openTwoDifferentContainers){

	logFile.appendFile("2014.06.21 16:05:38 : You have acquired [item:186000242;ver6;;;;] and stored it in your special cube. ");
	logFile.appendFile("2014.06.21 16:05:38 : You have opened the Fancy Medal Chest. ");
	logFile.appendFile("2014.06.21 16:05:38 : You have used Fancy Medal Chest. ");

	logFileUtility.parseLogFile();
	logFileUtility.parseLogFile();

	logFile.appendFile("2014.06.21 16:05:11 : You have opened the Veteran's Composite Manastone Bundle. ");
	logFile.appendFile("2014.06.21 16:05:11 : You have used Veteran's Composite Manastone Bundle. ");
	logFile.appendFile("2014.06.21 16:05:11 : You have acquired [item:167000676;ver6;;;;]. ");

	logFileUtility.parseLogFile();
	logFileUtility.parseLogFile();

	EXPECT_EQ(0, itemAcquisitionModule.itemsAcquired.getTotalCount());

	EXPECT_EQ(1, itemAcquisitionModule.containersOpened.get("Fancy Medal Chest").numGained);
	EXPECT_EQ(1, itemAcquisitionModule.containersOpened.get("Veteran's Composite Manastone Bundle").numGained);
	EXPECT_EQ(1, itemAcquisitionModule.itemsFromContainers.at("Fancy Medal Chest").get(186000242).numGained);
	EXPECT_EQ(1, itemAcquisitionModule.itemsFromContainers.at("Veteran's Composite Manastone Bundle").get(167000676).numGained);
}

TEST_F(ItemAcquisitionModuleTest, openContainer4){
	logFile.appendFile("2014.06.30 17:19:59 : You have acquired [item:167000772;ver6;;;;]. ");
	logFile.appendFile("2014.06.30 17:20:00 : You have acquired [item:167000775;ver6;;;;]. ");
	logFile.appendFile("2014.06.30 17:20:00 : You have opened the Worn Yellow Sack. ");
	logFile.appendFile("2014.06.30 17:20:00 : You have used Worn Yellow Sack. ");
	logFile.appendFile("2014.06.30 17:20:00 : You have acquired [item:167000769;ver6;;;;]. ");

	logFileUtility.parseLogFile();
	logFileUtility.parseLogFile();

	EXPECT_EQ(0, itemAcquisitionModule.itemsAcquired.getTotalCount());

	EXPECT_EQ(1, itemAcquisitionModule.containersOpened.get("Worn Yellow Sack").numGained);
	EXPECT_EQ(1, itemAcquisitionModule.itemsFromContainers.at("Worn Yellow Sack").get(167000772).numGained);
	EXPECT_EQ(1, itemAcquisitionModule.itemsFromContainers.at("Worn Yellow Sack").get(167000775).numGained);
	EXPECT_EQ(1, itemAcquisitionModule.itemsFromContainers.at("Worn Yellow Sack").get(167000769).numGained);
}



TEST_F(ItemAcquisitionModuleTest, openContainerMultiple){
	logFile.appendFile("2014.07.11 23:37:54 : You have acquired 3 [item:152000912;ver6;;;;](s). ");
	logFile.appendFile("2014.07.11 23:37:54 : You have opened the Pure Magical Aether. ");
	logFile.appendFile("2014.07.11 23:37:54 : You have used Pure Magical Aether. ");
	logFile.appendFile("2014.07.11 23:37:54 : Macro complete. ");
	logFileUtility.parseLogFile();
	logFileUtility.parseLogFile();
	logFile.appendFile("2014.07.11 23:37:57 : You have acquired 3 [item:152000912;ver6;;;;](s). ");
	logFile.appendFile("2014.07.11 23:37:57 : You have opened the Pure Magical Aether. ");
	logFile.appendFile("2014.07.11 23:37:57 : You have used Pure Magical Aether. ");
	logFileUtility.parseLogFile();
	logFileUtility.parseLogFile();
	logFile.appendFile("2014.07.11 23:38:01 : You have acquired 3 [item:152000912;ver6;;;;](s). ");
	logFile.appendFile("2014.07.11 23:38:01 : You have opened the Pure Magical Aether. ");
	logFile.appendFile("2014.07.11 23:38:01 : You have used Pure Magical Aether. ");
	logFileUtility.parseLogFile();
	logFileUtility.parseLogFile();

	EXPECT_EQ(0, itemAcquisitionModule.itemsAcquired.getTotalCount());

	EXPECT_EQ(3, itemAcquisitionModule.containersOpened.get("Pure Magical Aether").numGained);
	EXPECT_EQ(9, itemAcquisitionModule.itemsFromContainers.at("Pure Magical Aether").get(152000912).numGained);	

}

TEST_F(ItemAcquisitionModuleTest, openContainerBeforeWinningRoll){
	logFile.appendFile("2014.07.14 11:45:16 : You rolled the dice and got 93 (max. 100). ");
	logFileUtility.parseLogFile();
	logFileUtility.parseLogFile();
	logFile.appendFile("2014.07.14 11:45:18 : You have acquired 300 [item:186000237;ver6;;;;]s and stored them in your special cube. ");
	logFile.appendFile("2014.07.14 11:45:18 : You have opened the Bloody Ancient Coin Chest. ");
	logFile.appendFile("2014.07.14 11:45:18 : You have used Bloody Ancient Coin Chest. ");
	logFileUtility.parseLogFile();
	//logFileUtility.parseLogFile();
	logFile.appendFile("2014.07.14 11:45:19 : You rolled the highest. ");
	logFile.appendFile("2014.07.14 11:45:19 : You have acquired [item:186000235;ver6;;;;]. ");
	logFileUtility.parseLogFile();
	logFileUtility.parseLogFile();

	EXPECT_EQ(1, itemAcquisitionModule.itemsAcquired.getTotalCount());

	EXPECT_EQ(186000235, itemAcquisitionModule.itemsAcquired.getLastUpdated()->first);
	EXPECT_EQ(1, itemAcquisitionModule.itemsAcquired.getLastUpdated()->second.numGained);
	EXPECT_EQ(1, itemAcquisitionModule.itemsAcquired.getLastUpdated()->second.numPackets);

	EXPECT_EQ(186000235, itemAcquisitionModule.itemRolls.getItemRolls()[0].item);
	EXPECT_EQ(93, itemAcquisitionModule.itemRolls.getItemRolls()[0].yourRoll);
	EXPECT_EQ(93, itemAcquisitionModule.itemRolls.getItemRolls()[0].winningRoll);
	EXPECT_EQ("", itemAcquisitionModule.itemRolls.getItemRolls()[0].winner);


	EXPECT_EQ(1, itemAcquisitionModule.containersOpened.get("Bloody Ancient Coin Chest").numGained);
	EXPECT_EQ(300, itemAcquisitionModule.itemsFromContainers.at("Bloody Ancient Coin Chest").get(186000237).numGained);	
}

TEST_F(ItemAcquisitionModuleTest, spamContainers){
	logFile.appendFile("2014.12.16 22:58:45 : You have opened the Heavy Hidden Bundle. ");
	logFile.appendFile("2014.12.16 22:58:45 : You have used Heavy Hidden Bundle. ");
	logFile.appendFile("2014.12.16 22:58:45 : You have acquired [item:152000316;ver6;;;;]. ");
	logFile.appendFile("2014.12.16 22:58:46 : You have acquired 10 [item:141000001;ver6;;;;](s). ");
	logFile.appendFile("2014.12.16 22:58:46 : You have opened the Heavy Hidden Bundle. ");
	logFile.appendFile("2014.12.16 22:58:46 : You have used Heavy Hidden Bundle. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2014.12.16 22:58:46 : You have acquired 10 [item:141000001;ver6;;;;](s). ");
	logFile.appendFile("2014.12.16 22:58:46 : You have opened the Heavy Hidden Bundle. ");
	logFile.appendFile("2014.12.16 22:58:46 : You have used Heavy Hidden Bundle. ");
	logFile.appendFile("2014.12.16 22:58:46 : You have acquired 10 [item:141000001;ver6;;;;](s). ");
	logFile.appendFile("2014.12.16 22:58:46 : You have opened the Heavy Hidden Bundle. ");
	logFile.appendFile("2014.12.16 22:58:46 : You have used Heavy Hidden Bundle. ");
	logFile.appendFile("2014.12.16 22:58:46 : You have acquired 10 [item:141000001;ver6;;;;](s). ");
	logFile.appendFile("2014.12.16 22:58:46 : You have opened the Heavy Hidden Bundle. ");
	logFile.appendFile("2014.12.16 22:58:46 : You have used Heavy Hidden Bundle. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2014.12.16 22:58:47 : You have acquired 10 [item:141000001;ver6;;;;](s). ");
	logFile.appendFile("2014.12.16 22:58:47 : You have opened the Heavy Hidden Bundle. ");
	logFile.appendFile("2014.12.16 22:58:47 : You have used Heavy Hidden Bundle. ");
	logFile.appendFile("2014.12.16 22:58:47 : You have opened the Heavy Hidden Bundle. ");
	logFile.appendFile("2014.12.16 22:58:47 : You have used Heavy Hidden Bundle. ");
	logFile.appendFile("2014.12.16 22:58:47 : You have acquired [item:152000907;ver6;;;;]. ");
	logFileUtility.parseLogFile();
	logFile.appendFile("2014.12.16 22:58:47 : You have acquired [item:152000907;ver6;;;;]. ");
	logFile.appendFile("2014.12.16 22:58:47 : You have opened the Heavy Hidden Bundle. ");
	logFile.appendFile("2014.12.16 22:58:47 : You have used Heavy Hidden Bundle. ");
	logFileUtility.parseLogFile();
	logFileUtility.parseLogFile();

	EXPECT_EQ(8, itemAcquisitionModule.containersOpened.get("Heavy Hidden Bundle").numGained);
	EXPECT_EQ(50, itemAcquisitionModule.itemsFromContainers.at("Heavy Hidden Bundle").get(141000001).numGained);	
	EXPECT_EQ(2, itemAcquisitionModule.itemsFromContainers.at("Heavy Hidden Bundle").get(152000907).numGained);	


}