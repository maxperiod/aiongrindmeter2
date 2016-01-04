#include "../parser/decipher.h"
#include "gtest/gtest.h"

TEST(decipher, readParameterMark1){
	char* percent = "%0";
	EXPECT_EQ(2, readParameterMark(percent));
}

TEST(decipher, readParameterMark2){
	char* percent = "%num1";
	EXPECT_EQ(5, readParameterMark(percent));
}

TEST(decipher, readParameterMark3){
	char* percent = "%0d";
	EXPECT_EQ(3, readParameterMark(percent));
}

TEST(decipher, readParameterMark4){
	char* percent = "[%SkillCaster]";
	EXPECT_EQ(14, readParameterMark(percent));
}

TEST(decipher, readParameterMark5){
	char* percent = "[%SkillName]";
	EXPECT_EQ(12, readParameterMark(percent));
}

TEST(decipher, readParameterMark6){
	char* percent = "%.";
	EXPECT_EQ(0, readParameterMark(percent));
}

TEST(decipher, readParameterMark7){
	char* percent = "%DURATIONTIME0";
	EXPECT_EQ(14, readParameterMark(percent));
}

TEST(decipher, readParameterMark8){
	char* percent = "%2%";
	EXPECT_EQ(3, readParameterMark(percent));
}

//===============================================================

TEST(decipher, matchesUntilNextParameterMark1){
	char* a = "You have died.";
	char* b = "You have died.";
	EXPECT_EQ(14, matchesUntilNextParameterMark(a, b));
}

TEST(decipher, matchesUntilNextParameterMark2){
	char* a = "Haswell.";
	char* b = "You have died.";	
	EXPECT_EQ(-1, matchesUntilNextParameterMark(a, b));
}

TEST(decipher, matchesUntilNextParameterMark3){
	char* a = "You have gained 127 Abyss Points. ";
	char* b = "You have gained %num0 Abyss Points.";	
	EXPECT_EQ(16, matchesUntilNextParameterMark(a, b));
	
	char* a2 = a + 19;
	char* b2 = b + 21;
	EXPECT_EQ(14, matchesUntilNextParameterMark(a2, b2));
}

TEST(decipher, matchesUntilNextParameterMark4){
	char* a = "[Service/Weekly/Group] Legionary's Ring ";
	char* b = "%0";
	EXPECT_EQ(0, matchesUntilNextParameterMark(a, b));
}

//===============================================================

TEST(decipher, isNumericOnly1){
	char* rule = "%num0 Abyss Points.";
	EXPECT_TRUE(isParameterNumericOnly(rule, 5));
}

TEST(decipher, isNumericOnly2){
	char* rule = "%0 blah blah";
	EXPECT_FALSE(isParameterNumericOnly(rule, 2));
}

//===============================================================


TEST(decipher, readParameter2){
	
	char* a = "127 Abyss Points. ";
	char* b = " Abyss Points." 	;	
	EXPECT_EQ(3, readParameterValue(a, b));
}

TEST(decipher, readParameter3){
	
	char* a = "Blind Klaw Worker (Energy of Repose 11,494). ";
	char* b = " (Energy of Repose %num2)." ;		
	EXPECT_EQ(17, readParameterValue(a, b));	
}

TEST(decipher, readParameter4){
	
	char* a = "Blind Klaw Worker (Energy of Salvation 11,494). ";
	char* b = " (Energy of Repose %num2)." ;		
	EXPECT_EQ(-1, readParameterValue(a, b));	
}


//===============================================================

TEST(decipher, resemble1){
	map<string, string> params;
	EXPECT_TRUE(resembles(
		"2014.05.26 14:29:57 : You have died. ",
		"You have died.",
		params));
	EXPECT_TRUE(params.empty());
}

TEST(decipher, resemble2){
	map<string, string> params;
	EXPECT_TRUE(resembles(
		"2014.05.25 09:48:29 : You have gained 127 Abyss Points. ",
		"You have gained %num0 Abyss Points.",		
		params));
	EXPECT_EQ(1, params.size());
	EXPECT_EQ("127", params.at("%num0"));
}

TEST(decipher, resemble2a){
	map<string, string> params;
	EXPECT_TRUE(resembles(
		"2014.05.25 09:48:29 : You have gained 12 345 Abyss Points. ",
		"You have gained %num0 Abyss Points.",		
		params));
	EXPECT_EQ(1, params.size());
	EXPECT_EQ("12 345", params.at("%num0"));
}

TEST(decipher, resemble2b){
	map<string, string> params;
	EXPECT_TRUE(resembles(
		"2014.05.25 09:48:29 : You have gained 1.234 Abyss Points. ",
		"You have gained %num0 Abyss Points.",		
		params));
	EXPECT_EQ(1, params.size());
	EXPECT_EQ("1.234", params.at("%num0"));
}


TEST(decipher, resemble3){
	map<string, string> params;
	EXPECT_TRUE(resembles(
		"2014.05.23 21:55:48 : You have gained 40,229 XP from Blind Klaw Worker (Energy of Salvation 11,494). ",
		"You have gained %num1 XP from %0 (Energy of Salvation %num2).",
		params));
	EXPECT_EQ(3, params.size());
	EXPECT_EQ("40,229", params.at("%num1"));
	EXPECT_EQ("Blind Klaw Worker", params.at("%0"));
	EXPECT_EQ("11,494", params.at("%num2"));
}


TEST(decipher, resemble3a){
	map<string, string> params;
	EXPECT_FALSE(resembles(
		"2014.05.23 21:55:48 : You have gained 40,229 XP from Blind Klaw Worker (Energy of Repose 11,494). ",
		"You have gained %num1 XP from %0 (Energy of Salvation %num2).", 		
		params));

	EXPECT_TRUE(params.empty());
}

/*
This test will fail due to impossibility to exact parameters correctly.
Since there are only one space separating the parameters %0-%1, and %1-%2, 
any space encountered in the input string are treated as end of parameter.
For the third parameter, it will keep reading characters and spaces until it encounters " has died in ".
*/
TEST(decipher, resemble5){
	map<string, string> params;
	EXPECT_TRUE(resembles(
		"2014.05.24 11:06:32 : Asmodian Asmodian Army General JustStorm has died in Silentera Canyon. ",
		"%0 %1 %2 has died in %3.",		 		
		params));
	EXPECT_EQ(4, params.size());
	EXPECT_EQ("Asmodian", params.at("%0"));
	EXPECT_EQ("Asmodian Army General", params.at("%1"));	//Actual: "Asmodian"
	EXPECT_EQ("JustStorm", params.at("%2"));	//Actual: "Army General JustStorm"
	EXPECT_EQ("Silentera Canyon", params.at("%3"));
}


TEST(decipher, resemble6){
	map<string, string> params;
	EXPECT_TRUE(resembles(
		"2014.05.24 11:06:31 : Critical Hit!You inflicted 1,874 damage on Protectorate Special Enforcer by using Parrying Strike III. ",
		"Critical Hit!You inflicted %num0 damage on [%SkillTarget] by using [%SkillName].",		 		
		params));
	EXPECT_EQ(3, params.size());
	EXPECT_EQ("1,874", params.at("%num0"));
	EXPECT_EQ("Protectorate Special Enforcer", params.at("[%SkillTarget]"));
	EXPECT_EQ("Parrying Strike III", params.at("[%SkillName]"));
	
}


TEST(decipher, resemble7){
	map<string, string> params;
	EXPECT_TRUE(resembles(
		"2014.05.24 11:06:01 : Quest updated: [Service/Weekly/Group] Legionary's Ring ",
		"Quest updated: %0",
		params));
	EXPECT_EQ(1, params.size());
	EXPECT_EQ("[Service/Weekly/Group] Legionary's Ring", params.at("%0"));

}

TEST(decipher, resemble8){
	map<string, string> params;
	EXPECT_TRUE(resembles(
		"2014.05.24 21:19:20 : Enos Destroyer received 414 damage due to the effect of Reroute Power Effect. ",
		"[%SkillTarget] received %num0 damage due to the effect of [%SkillName].",
		params));
	EXPECT_EQ(3, params.size());
	EXPECT_EQ("Enos Destroyer", params.at("[%SkillTarget]"));
	EXPECT_EQ("414", params.at("%num0"));
	EXPECT_EQ("Reroute Power Effect", params.at("[%SkillName]"));

}

TEST(decipher, resemble9){
	map<string, string> params;
	EXPECT_TRUE(resembles(
		"2014.05.23 21:56:05 : You have acquired [item:152010326;ver5;;;;;;]. ",
		"You have acquired %0.",
		params));
	EXPECT_EQ(1, params.size());
	EXPECT_EQ("[item:152010326;ver5;;;;;;]", params.at("%0"));
}

TEST(decipher, resemble10){
	map<string, string> params;
	EXPECT_TRUE(resembles(
		"2014.05.23 21:52:52 : You have acquired 188 [item:169000010;ver5;;;;;;](s). ",
		"You have acquired %num1 %0(s).",
		params));
	EXPECT_EQ(2, params.size());
	EXPECT_EQ("188", params.at("%num1"));
	EXPECT_EQ("[item:169000010;ver5;;;;;;]", params.at("%0"));
}

TEST(decipher, resemble10a){
	map<string, string> params;
	EXPECT_TRUE(resembles(
		"2014.05.23 21:52:52 : You have acquired 1 188 [item:169000010;ver5;;;;;;](s). ",
		"You have acquired %num1 %0(s).",
		params));
	EXPECT_EQ(2, params.size());
	EXPECT_EQ("1 188", params.at("%num1"));
	EXPECT_EQ("[item:169000010;ver5;;;;;;]", params.at("%0"));
}

TEST(decipher, resemble11){
	map<string, string> params;
	EXPECT_TRUE(resembles(
		"2014.05.23 21:57:17 : You have acquired [item:182213512;ver5;;;;;;] and stored it in your special cube. ",
		"You have acquired %0 and stored it in your special cube.",
		params));
	EXPECT_EQ(1, params.size());
	EXPECT_EQ("[item:182213512;ver5;;;;;;]", params.at("%0"));
}

TEST(decipher, resemble12){
	map<string, string> params;
	EXPECT_TRUE(resembles(	
		"2014.04.29 20:37:30 : You restored your flight time by 60. ",
		"You restored your flight time by %num0.",
		params));	
	EXPECT_EQ(1, params.size());
	EXPECT_EQ("60", params.at("%num0"));
}

TEST(decipher, resemble13){
	map<string, string> params;
	EXPECT_FALSE(resembles(	
		"2014.05.23 21:52:52 : You have acquired [item:169000010;ver5;;;;;;](s). ",
		"You have acquired %num1 %0(s).",
		params));	
	EXPECT_EQ(0, params.size());
	
}

TEST(decipher, resemble14){
	map<string, string> params;
	EXPECT_TRUE(resembles(	
		"2014.05.23 21:52:52 : The Empyrean Lord Agent's HP has dropped below 50%.",
		"The Empyrean Lord Agent's HP has dropped below 50%%.",
		params));	
	EXPECT_EQ(0, params.size());
	
}

TEST(decipher, resemble15){
	map<string, string> params;
	EXPECT_TRUE(resembles(	
		"2014.05.24 10:07:52 : Momomomoo Increased Protectorate Special Enforcer's enmity Increase by using Provoking Severe Blow V. ",
		"[%SkillCaster] %0d [%SkillTarget]'s enmity %0 by using [%SkillName].",
		params));	
	EXPECT_EQ(5, params.size());
	EXPECT_EQ("Momomomoo", params.at("[%SkillCaster]"));
	EXPECT_EQ("Increased", params.at("%0d"));
	EXPECT_EQ("Protectorate Special Enforcer", params.at("[%SkillTarget]"));
	EXPECT_EQ("Increase", params.at("%0"));
	EXPECT_EQ("Provoking Severe Blow V", params.at("[%SkillName]"));
	
}
TEST(decipher, resemble16){
	map<string, string> params;
	EXPECT_TRUE(resembles(	
		"0000.00.00 00:00:00 : You are rested and brimming with energy. You gain 100% additional XP, and your item drop rate increases by 20%. You will reach a State of Repletion faster than with regular Energy of Repose. ",
		"You are rested and brimming with energy. You gain %0%% additional XP, and your item drop rate increases by %1%%. You will reach a State of Repletion faster than with regular Energy of Repose.",
		params));	
	EXPECT_EQ(2, params.size());
	EXPECT_EQ("100", params.at("%0"));
	EXPECT_EQ("20", params.at("%1"));
	
}
TEST(decipher, date){
	EXPECT_EQ("2014.05.24 10:07:52", getDate(	
		"2014.05.24 10:07:52 : Momomomoo Increased Protectorate Special Enforcer's enmity Increase by using Provoking Severe Blow V. "
		));
}


int main(int argc, char** argv){
	testing::InitGoogleTest(&argc, argv); 
	RUN_ALL_TESTS();
	getchar();
	return 0;
}