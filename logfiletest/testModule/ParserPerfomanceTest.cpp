#include <ctime>
#include <memory>
#include "gtest/gtest.h"

//#include "../lookups/RuleStringsHardCodedNA.h"
#include "../parser/LogFileReader.h"
#include "testLog/TemporaryLogFile.h"
#include "../parser/MaxPeriodParser.h"

#include "../parser/ChatLogCommandFactory.h"
#include "../lookups/CommandStringsNAEnglish.h"


class ParserPerformanceTest: public ::testing::Test{
protected:
	queue<string> lines;
	map<string, string> params;

	
	TemporaryLogFile logFile;
	LogFileReader* logFileReader;
	MaxPeriodParser parser;	

	// method 1
	
	//RuleStringsHardCodedNA rules;

	// method 2
	CommandStringsNAEnglish commandStrings;
	ChatLogCommandFactory commandFactory;
	
	// method 3
	//LogFileUtility logFileUtility;


	ParserPerformanceTest(): 
		logFile("testModule/testLog/tests.log", "testModule/testLog/Chat.log")
	{
	}
	
	virtual void SetUp(){
		//logFile = new TemporaryLogFile("testModule/testLog/tests.log", "testModule/testLog/Chat.log");
		logFileReader = new LogFileReader();
		logFile.makeFileCopy();
		logFileReader->setAionDirectory("testModule/testLog/");
		
		//RULE_STRINGS = &rules;
		//parser.setRuleStrings(*RULE_STRINGS);	

		COMMAND_RULES = &commandStrings;		
		
		//bool status = logFile.
		
		ASSERT_TRUE(logFileReader->isOK());

		setUpCommandFactory();
	}

	virtual void TearDown(){		
		delete(logFileReader);
		logFile.deleteFileCopy();
		//delete(logFile);
	}	

	void setUpCommandFactory(){
				
		commandFactory.setParser(parser);
		commandFactory.setCommandRules(commandStrings);

		commandFactory.addParsableCommandCode(STR_MSG_COMBAT_OTHER_FRIENDLY_ATTACK);		
		commandFactory.addParsableCommandCode(STR_MSG_COMBAT_OTHER_HOSTILE_ATTACK);
		commandFactory.addParsableCommandCode(STR_MSG_COMBAT_OTHER_HOSTILE_BLOCK);
		commandFactory.addParsableCommandCode(STR_MSG_COMBAT_OTHER_HOSTILE_CRITICAL);
		commandFactory.addParsableCommandCode(STR_MSG_COMBAT_OTHER_HOSTILE_DODGE);
		commandFactory.addParsableCommandCode(STR_MSG_COMBAT_OTHER_HOSTILE_PARRY);
		commandFactory.addParsableCommandCode(STR_SKILL_SUCC_SpellATK_Instant_A_TO_B);
		commandFactory.addParsableCommandCode(STR_SKILL_SUCC_SpellATK_Instant_A_TO_ME);
		commandFactory.addParsableCommandCode(STR_SKILL_SUCC_SpellATK_Instant_A_TO_SELF);
		commandFactory.addParsableCommandCode(STR_SKILL_SUCC_AlwaysBlock_A_TO_B);

		//commandFactory.addParsableCommandCode(STR_SKILL_SUCC_Heal_INTERVAL_HEAL_TO_B);

		commandFactory.addParsableCommandCode(STR_GET_EXP_VITAL_MAKEUP_BONUS);
		commandFactory.addParsableCommandCode(STR_GET_EXP_VITAL_BONUS);
		commandFactory.addParsableCommandCode(STR_GET_EXP_MAKEUP_BONUS);
		commandFactory.addParsableCommandCode(STR_GET_EXP);

		commandFactory.addParsableCommandCode(STR_GET_EXP_VITAL_MAKEUP_BONUS);
		commandFactory.addParsableCommandCode(STR_GET_EXP2_VITAL_BONUS);
		commandFactory.addParsableCommandCode(STR_GET_EXP2_MAKEUP_BONUS);
		commandFactory.addParsableCommandCode(STR_GET_EXP2);

		commandFactory.addParsableCommandCode(STR_GET_EXP_PCBANG_VITAL_MAKEUP_BONUS);
		commandFactory.addParsableCommandCode(STR_GET_EXP_PCBANG_VITAL_BONUS);

		commandFactory.addParsableCommandCode(STR_GET_EXP2_PCBANG_VITAL_BONUS);
		commandFactory.addParsableCommandCode(STR_GET_EXP2_PCBANG_VITAL_MAKEUP_BONUS);

		commandFactory.addParsableCommandCode(STR_CANNOT_GET_PVP_EXP_TARGET_LIMIT);
		commandFactory.addParsableCommandCode(STR_CANNOT_GET_PVP_EXP_TIMEBASE_LIMIT);

		commandFactory.addParsableCommandCode(STR_MSG_ADDEXP_POINT_USE);
		commandFactory.addParsableCommandCode(STR_MSG_EXP_EXTRACTION_USE);

		commandFactory.addParsableCommandCode(STR_LEVEL_LIMIT_QUEST_NOT_FINISHED1);
		commandFactory.addParsableCommandCode(STR_MSG_CANT_NOVICE_SERVER_ALREADY_MAX_LEVEL);
	}
	/*
	int processLines(){
		int numLines = 0;
		int nonMatch = 0;

		logFileReader->readLines(lines, true);
		while(!lines.empty()){
			
			string line = lines.front();

			bool critical = parser.isCrit(line);

			
			
			if (parser.resemblesRule(line, "STR_MSG_COMBAT_OTHER_FRIENDLY_ATTACK", params)){
			}			
			else if (parser.resemblesRule(line, "STR_MSG_COMBAT_OTHER_HOSTILE_ATTACK", params)){
			}			
			else if (parser.resemblesRule(line, "STR_MSG_COMBAT_OTHER_HOSTILE_BLOCK", params)){
			}			
			else if (parser.resemblesRule(line, "STR_MSG_COMBAT_OTHER_HOSTILE_CRITICAL", params)){
			}			
			else if (parser.resemblesRule(line, "STR_MSG_COMBAT_OTHER_HOSTILE_DODGE", params)){
			}			
			else if (parser.resemblesRule(line, "STR_MSG_COMBAT_OTHER_HOSTILE_PARRY", params)){
			}			
			else if (parser.resemblesRule(line, "STR_SKILL_SUCC_SpellATK_Instant_A_TO_B", params)){
			}			
			else if (parser.resemblesRule(line, "STR_SKILL_SUCC_SpellATK_Instant_A_TO_ME", params)){
			}			
			else if (parser.resemblesRule(line, "STR_SKILL_SUCC_SpellATK_Instant_A_TO_SELF", params)){
			}			
			else if (parser.resemblesRule(line, "STR_SKILL_SUCC_AlwaysBlock_A_TO_B", params)){
			}			
			
			
			// EXP from a monster/player/NPC
			else if (parser.resemblesRule(line, "STR_GET_EXP_VITAL_MAKEUP_BONUS", params)){			
			}
			else if (parser.resemblesRule(line, "STR_GET_EXP_VITAL_BONUS", params)){				
			}
			else if (parser.resemblesRule(line, "STR_GET_EXP_MAKEUP_BONUS", params)){				
			}
			else if (parser.resemblesRule(line, "STR_GET_EXP", params)){								
			}	

			// EXP from no target (gathering/crafting)
			else if (parser.resemblesRule(line, "STR_GET_EXP_VITAL_MAKEUP_BONUS", params)){				
			}
			else if (parser.resemblesRule(line, "STR_GET_EXP2_VITAL_BONUS", params)){				
			}
			else if (parser.resemblesRule(line, "STR_GET_EXP2_MAKEUP_BONUS", params)){				
			}
			else if (parser.resemblesRule(line, "STR_GET_EXP2", params)){								
			}	
			
			// PC Cafe - from a target
			else if (parser.resemblesRule(line, "STR_GET_EXP_PCBANG_VITAL_MAKEUP_BONUS", params)){				
			}
			else if (parser.resemblesRule(line, "STR_GET_EXP_PCBANG_VITAL_BONUS", params)){				
			}

			// PC Cafe - gathering/crafting
			else if (parser.resemblesRule(line, "STR_GET_EXP2_PCBANG_VITAL_BONUS", params)){
			}
			else if (parser.resemblesRule(line, "STR_GET_EXP2_PCBANG_VITAL_MAKEUP_BONUS", params)){				
			}

			// PvP XP Cap
			else if (parser.resemblesRule(line, "STR_CANNOT_GET_PVP_EXP_TARGET_LIMIT", params)){				
			}
			else if (parser.resemblesRule(line, "STR_CANNOT_GET_PVP_EXP_TIMEBASE_LIMIT", params)){				
			}

			// Item Exp
			else if (parser.resemblesRule(line, "STR_MSG_ADDEXP_POINT_USE", params)){				
			}
			else if (parser.resemblesRule(line, "STR_MSG_EXP_EXTRACTION_USE", params)){				
			}

			// Level capped
			else if (parser.resemblesRule(line, "STR_LEVEL_LIMIT_QUEST_NOT_FINISHED1", params)){				
			}
			else if (parser.resemblesRule(line, "STR_MSG_CANT_NOVICE_SERVER_ALREADY_MAX_LEVEL", params)){				
			}
				
			
			else nonMatch ++;
			numLines ++;
			if (numLines % 10000 == 0) cout << numLines << endl;
			lines.pop();
		}
		return numLines - nonMatch;
	}
	*/

	int processLines2(){
		int numLines = 0;
		int nonMatch = 0;

		logFileReader->readLines(lines, true);
		while(!lines.empty()){
			
			string line = lines.front();
		
			unique_ptr<Command> command = commandFactory.getCommand(line);
			if (!command) nonMatch ++;
			numLines ++;
			if (numLines % 10000 == 0) cout << numLines << endl;
			lines.pop();
			
			if (command){
				if (command->getCommandCode() == STR_MSG_COMBAT_OTHER_FRIENDLY_ATTACK){
				}			
				else if (command->getCommandCode() == STR_MSG_COMBAT_OTHER_HOSTILE_ATTACK){
				}			
				else if (command->getCommandCode() == STR_MSG_COMBAT_OTHER_HOSTILE_BLOCK){
				}			
				else if (command->getCommandCode() == STR_MSG_COMBAT_OTHER_HOSTILE_CRITICAL){
				}			
				else if (command->getCommandCode() == STR_MSG_COMBAT_OTHER_HOSTILE_DODGE){
				}			
				else if (command->getCommandCode() == STR_MSG_COMBAT_OTHER_HOSTILE_PARRY){
				}			
				else if (command->getCommandCode() == STR_SKILL_SUCC_SpellATK_Instant_A_TO_B){
				}			
				else if (command->getCommandCode() == STR_SKILL_SUCC_SpellATK_Instant_A_TO_ME){
				}			
				else if (command->getCommandCode() == STR_SKILL_SUCC_SpellATK_Instant_A_TO_SELF){
				}			
				else if (command->getCommandCode() == STR_SKILL_SUCC_AlwaysBlock_A_TO_B){
				}			
			
			
				// EXP from a monster/player/NPC
				else if (command->getCommandCode() == STR_GET_EXP_VITAL_MAKEUP_BONUS){			
				}
				else if (command->getCommandCode() == STR_GET_EXP_VITAL_BONUS){				
				}
				else if (command->getCommandCode() == STR_GET_EXP_MAKEUP_BONUS){				
				}
				else if (command->getCommandCode() == STR_GET_EXP){								
				}	

				// EXP from no target (gathering/crafting)
				else if (command->getCommandCode() == STR_GET_EXP_VITAL_MAKEUP_BONUS){				
				}
				else if (command->getCommandCode() == STR_GET_EXP2_VITAL_BONUS){				
				}
				else if (command->getCommandCode() == STR_GET_EXP2_MAKEUP_BONUS){				
				}
				else if (command->getCommandCode() == STR_GET_EXP2){								
				}	
			
				// PC Cafe - from a target
				else if (command->getCommandCode() == STR_GET_EXP_PCBANG_VITAL_MAKEUP_BONUS){				
				}
				else if (command->getCommandCode() == STR_GET_EXP_PCBANG_VITAL_BONUS){				
				}

				// PC Cafe - gathering/crafting
				else if (command->getCommandCode() == STR_GET_EXP2_PCBANG_VITAL_BONUS){
				}
				else if (command->getCommandCode() == STR_GET_EXP2_PCBANG_VITAL_MAKEUP_BONUS){				
				}

				// PvP XP Cap
				else if (command->getCommandCode() == STR_CANNOT_GET_PVP_EXP_TARGET_LIMIT){				
				}
				else if (command->getCommandCode() == STR_CANNOT_GET_PVP_EXP_TIMEBASE_LIMIT){				
				}

				// Item Exp
				else if (command->getCommandCode() == STR_MSG_ADDEXP_POINT_USE){				
				}
				else if (command->getCommandCode() == STR_MSG_EXP_EXTRACTION_USE){				
				}

				// Level capped
				else if (command->getCommandCode() == STR_LEVEL_LIMIT_QUEST_NOT_FINISHED1){				
				}
				else if (command->getCommandCode() == STR_MSG_CANT_NOVICE_SERVER_ALREADY_MAX_LEVEL){				
				}
			}
		}
		return numLines - nonMatch;
	}

};

TEST_F(ParserPerformanceTest, warmup){
	
	//logFileReader->readLines(lines, true);
	
	long start = clock();
	EXPECT_LT(0, processLines2());
	long end = clock();
	cout << "Discarding first file runthrough"<< endl;
}
/*
TEST_F(ParserPerformanceTest, test1){
	
	//logFileReader->readLines(lines, true);
	
	long start = clock();
	EXPECT_LT(0, processLines());
	long end = clock();
	cout << "String command codes take 1 - Time in seconds: " << (float)(end - start) / CLOCKS_PER_SEC << endl;
}
*/
TEST_F(ParserPerformanceTest, test2){
	
	long start = clock();
	EXPECT_LT(0, processLines2());
	long end = clock();
	cout << "Enum command codes take 1 - Time in seconds: " << (float)(end - start) / CLOCKS_PER_SEC << endl;
}

/*
TEST_F(ParserPerformanceTest, test3){
	
	//logFileReader->readLines(lines, true);
	
	long start = clock();
	EXPECT_LT(0, processLines());
	long end = clock();
	cout << "String command codes take 2 - Time in seconds: " << (float)(end - start) / CLOCKS_PER_SEC << endl;
}
*/
TEST_F(ParserPerformanceTest, test4){
	
	long start = clock();
	EXPECT_LT(0, processLines2());
	long end = clock();
	cout << "Enum command codes take 2 - Time in seconds: " << (float)(end - start) / CLOCKS_PER_SEC << endl;
}