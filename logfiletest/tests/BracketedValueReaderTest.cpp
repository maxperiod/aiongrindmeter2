#include "../parser/BracketValueReader.h"
#include "gtest/gtest.h"


TEST(BracketValueReaderTest, test1){
	vector<string> result;
	BracketValueReader::readValues("[item:186000184;ver6;;;;]", result);
	EXPECT_EQ("item", result[0]);
	EXPECT_EQ("186000184", result[1]);
	EXPECT_EQ("ver6", result[2]);
	EXPECT_EQ("", result[3]);
	EXPECT_EQ("", result[4]);
	EXPECT_EQ("", result[5]);
	EXPECT_EQ("", result[6]);
}

TEST(BracketValueReaderTest, test2){
	vector<string> result;
	BracketValueReader::readValues("[charname:Worwick;1.0000 0.6941 0.6941]", result);
	EXPECT_EQ("charname", result[0]);
	EXPECT_EQ("Worwick", result[1]);
	EXPECT_EQ("1.0000 0.6941 0.6941", result[2]);	
}

TEST(BracketValueReaderTest, testInvalid1){
	vector<string> result;
	BracketValueReader::readValues("[charname:Worwick;1.0000 0.6941 0.6941", result);
	EXPECT_TRUE(result.empty());	
}

