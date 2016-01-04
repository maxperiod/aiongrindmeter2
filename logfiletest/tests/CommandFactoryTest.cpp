#include <memory>
using namespace std;

#include "gtest/gtest.h"
#include "../parser/MaxPeriodParser.h"

#include "../parser/CommandFactory.h"

#include "../lookups/CommandStringsNAEnglish.h"

//#include "../parser/RuleStrings.h"

#include "../exception/NoSuchRuleStringException.h"


/*
class MockCommandRules: public CommandRules{
public:
	MockCommandRules(){
		rules[STR_MSG_GET_SCORE] = "You have gained %num1 points from %0.";
		rules[STR_SKILL_EFFECT_MSG_CRITICAL] = "Critical Hit!";
		rules[STR_SKILL_SUCC_SkillATK_Instant_ME_TO_B] = "You inflicted %num0 damage on [%SkillTarget] by using [%SkillName].";
		rules[STR_SKILL_SUCC_CarveSignet_ME_TO_B] = "You inflicted %num0 damage and the rune carve effect on [%SkillTarget] by using [%SkillName].";
		rules[STR_SKILL_SUCC_DispelBuffCounterATK_ME_TO_B] = "You inflicted %num0 damage on [%SkillTarget] and dispelled some of its magical buffs by using [%SkillName].";
		rules[STR_MSG_COMBAT_MY_CRITICAL] = "Critical Hit! You inflicted %num1 critical damage on %0.";
		rules[STR_MSG_COMBAT_MY_ATTACK] = "You inflicted %num1 damage on %0.";
	}
};
*/
class CommandFactoryTest: public ::testing::Test{
protected:
	MaxPeriodParser parser;
	//MockCommandRules mockCommandRules;	
	CommandStringsNAEnglish commandStrings;
	CommandFactory commandFactory;
	
	virtual void SetUp(){
		commandFactory.setParser(parser);
		commandFactory.setCommandRules(commandStrings);		

		commandFactory.addParsableCommandCode(STR_MSG_GET_SCORE);
		//commandFactory.addParsableCommandCode(STR_SKILL_EFFECT_MSG_CRITICAL);
		commandFactory.addParsableCommandCode(STR_SKILL_SUCC_SkillATK_Instant_ME_TO_B, true);
		commandFactory.addParsableCommandCode(STR_SKILL_SUCC_CarveSignet_ME_TO_B, true);
		commandFactory.addParsableCommandCode(STR_SKILL_SUCC_DispelBuffCounterATK_ME_TO_B, true);
		commandFactory.addParsableCommandCode(STR_MSG_COMBAT_MY_CRITICAL);
		commandFactory.addParsableCommandCode(STR_MSG_COMBAT_MY_ATTACK);
		commandFactory.addParsableCommandCode(STR_GET_EXP_VITAL_MAKEUP_BONUS);
		commandFactory.addParsableCommandCode(STR_GET_EXP_VITAL_BONUS);
		commandFactory.addParsableCommandCode(STR_GET_EXP_MAKEUP_BONUS);
		commandFactory.addParsableCommandCode(STR_GET_EXP);

		COMMAND_RULES = &commandStrings;

		//parser.setCriticalString(commandStrings.getCriticalString());
		
		//parser.setRuleStrings(*RULE_STRINGS);

		//parser.setCriticalString("Critical Hit!");
	}
};


TEST_F(CommandFactoryTest, recognize1){
	//map<string, string> params;
	unique_ptr<Command> command = commandFactory.getCommand("2014.06.18 22:34:37 : You have gained 3,051 points from Sheban Intelligence Inspector. ");	
	
	ASSERT_TRUE(command);
	EXPECT_EQ(STR_MSG_GET_SCORE, command->getCommandCode());
	EXPECT_EQ("3,051", command->getParams().at("%num1"));
	EXPECT_EQ("Sheban Intelligence Inspector", command->getParams().at("%0"));
	EXPECT_FALSE(command->isCritical());
}

TEST_F(CommandFactoryTest, recognize2){
	//map<string, string> params;
	unique_ptr<Command> command = commandFactory.getCommand("2013.06.27 23:35:36 : You have gained 8,867 XP from Wori. ");	
	
	ASSERT_TRUE(command);
	EXPECT_EQ(STR_GET_EXP, command->getCommandCode());
	EXPECT_EQ("8,867", command->getParams().at("%num1"));
	EXPECT_EQ("Wori", command->getParams().at("%0"));
	EXPECT_FALSE(command->isCritical());
}

TEST_F(CommandFactoryTest, recognize3){
	//map<string, string> params;
	unique_ptr<Command> command = commandFactory.getCommand("2013.06.27 22:17:34 : You have gained 20,052,999 XP from Vard (Energy of Repose 10,405). ");	
		
	ASSERT_TRUE(command);
	EXPECT_EQ(STR_GET_EXP_VITAL_BONUS, command->getCommandCode());
	EXPECT_EQ("20,052,999", command->getParams().at("%num1"));
	EXPECT_EQ("Vard", command->getParams().at("%0"));
	EXPECT_EQ("10,405", command->getParams().at("%num2"));
	EXPECT_FALSE(command->isCritical());
}

TEST_F(CommandFactoryTest, critAutoAttack){
	//map<string, string> params;
	unique_ptr<Command> command = commandFactory.getCommand("2014.10.18 14:50:34 : Critical Hit! You inflicted 1,503 critical damage on Pashid Lab Unit Drone. ");	
	
	ASSERT_TRUE(command);
	EXPECT_EQ(STR_MSG_COMBAT_MY_CRITICAL, command->getCommandCode());
	EXPECT_EQ("1,503", command->getParams().at("%num1"));
	EXPECT_EQ("Pashid Lab Unit Drone", command->getParams().at("%0"));	
	EXPECT_FALSE(command->isCritical());
}

TEST_F(CommandFactoryTest, critSkill){
	unique_ptr<Command> command = commandFactory.getCommand("2014.08.25 22:19:38 : Critical Hit!You inflicted 3,863 damage on Baranath Dark Scout by using Ferocious Strike VI. ");
	ASSERT_TRUE(command);
	EXPECT_EQ(STR_SKILL_SUCC_SkillATK_Instant_ME_TO_B, command->getCommandCode());
	EXPECT_EQ("3,863", command->getParams().at("%num0"));
	EXPECT_EQ("Baranath Dark Scout", command->getParams().at("[%SkillTarget]"));	
	EXPECT_EQ("Ferocious Strike VI", command->getParams().at("[%SkillName]"));	
	EXPECT_TRUE(command->isCritical());
}

TEST_F(CommandFactoryTest, noRecognizedCommand){
	unique_ptr<Command> command = commandFactory.getCommand("2014.06.18 22:34:37 : You restored 932 of Youngzter's HP by using Recovery Spell III. ");
	EXPECT_FALSE(command);	
	
}
