#include "gtest/gtest.h"
#include "../stringfunctions.h"


TEST(stringFunctions, formatKiloMega1){
	EXPECT_EQ("12.7 M", formatKiloMega(12790000, 3));

}

TEST(stringFunctions, formatKiloMega2){
	EXPECT_EQ("1.23", formatKiloMega(1.23, 3));

}

TEST(stringFunctions, formatKiloMega3){
	EXPECT_EQ("19.9", formatKiloMega(19.9, 3));

}

TEST(stringFunctions, formatKiloMega4){
	EXPECT_EQ("1.99 k", formatKiloMega(1999, 3));

}

TEST(stringFunctions, formatKiloMega5){
	EXPECT_EQ("0.0429", formatKiloMega(0.0429, 3));

}

TEST(stringFunctions, formatNumber1){
	int number = 123;
	EXPECT_EQ("123", formatNumber(number));

}

TEST(stringFunctions, formatNumber1a){
	int number = -123;
	EXPECT_EQ("-123", formatNumber(number));

}

TEST(stringFunctions, formatNumber1b){
	int number = 123;
	EXPECT_EQ("+123", formatNumber(number, true));

}

TEST(stringFunctions, formatNumber1c){
	int number = -123;
	EXPECT_EQ("-123", formatNumber(number, true));

}


TEST(stringFunctions, formatNumber2){
	int number = 4567;
	EXPECT_EQ("4,567", formatNumber(number));

}

TEST(stringFunctions, formatNumber2a){
	int number = -4567;
	EXPECT_EQ("-4,567", formatNumber(number));

}

TEST(stringFunctions, formatNumber2b){
	int number = 4567;
	EXPECT_EQ("+4,567", formatNumber(number, true));

}

TEST(stringFunctions, formatNumber2c){
	int number = -4567;
	EXPECT_EQ("-4,567", formatNumber(number, true));

}

TEST(stringFunctions, formatNumber3){
	long long number = 3000000000;
	EXPECT_EQ("3,000,000,000", formatNumber(number));

}


TEST(stringFunctions, formatCurrentAndNextValuesWithKiloMega1){
	EXPECT_EQ("12.7 M / 12.7 M", formatCurrentAndNextValuesWithKiloMega(12790000, 12790000, 3));

}

TEST(stringFunctions, formatCurrentAndNextValuesWithKiloMega2){
	EXPECT_EQ("1.2 M / 12.7 M", formatCurrentAndNextValuesWithKiloMega(1279000, 12790000, 3));

}

TEST(stringFunctions, formatCurrentAndNextValuesWithKiloMega3){
	EXPECT_EQ("0.1 M / 12.7 M", formatCurrentAndNextValuesWithKiloMega(127900, 12790000, 3));

}

TEST(stringFunctions, formatCurrentAndNextValuesWithKiloMega4){
	EXPECT_EQ("2.91 T / 29.18 T", formatCurrentAndNextValuesWithKiloMega(2918584335977, 29185843359773, 4));

}

TEST(stringFunctions, formatCurrentAndNextValuesWithKiloMega5){
	EXPECT_EQ("1 / 9,999", formatCurrentAndNextValuesWithKiloMega(1, 9999, 4));

}

TEST(stringFunctions, formatCurrentAndNextValuesWithKiloMega6){
	EXPECT_EQ("0.99 k / 11.11 k", formatCurrentAndNextValuesWithKiloMega(999, 11111, 4));

}

TEST(stringFunctions, verifyPercentInput1){
	EXPECT_NEAR(10, verifyPercentInput("10"), 0.001);
}

TEST(stringFunctions, verifyPercentInput2){
	EXPECT_NEAR(10.99, verifyPercentInput("10.99"), 0.001);
}

TEST(stringFunctions, verifyPercentInput3){
	EXPECT_NEAR(0.01, verifyPercentInput("0.01"), 0.001);
}

TEST(stringFunctions, verifyPercentInput5){
	EXPECT_NEAR(-1, verifyPercentInput("1.2.3"), 0.001);
}

TEST(stringFunctions, verifyPercentInput6){
	EXPECT_NEAR(99.99, verifyPercentInput("99,99"), 0.001);
}

TEST(stringFunctions, verifyPercentInput7){
	EXPECT_NEAR(-1, verifyPercentInput("A1.15"), 0.001);
}

TEST(stringFunctions, verifyPercentInput8){
	EXPECT_NEAR(0.67, verifyPercentInput(".67"), 0.001);
}

TEST(stringFunctions, verifyPercentInput9){
	EXPECT_NEAR(-1, verifyPercentInput("10.a1"), 0.001);
}

TEST(stringFunctions, verifyPercentInput10){
	EXPECT_NEAR(67, verifyPercentInput("67."), 0.001);
}

TEST(stringFunctions, verifyPercentInput11){
	EXPECT_NEAR(12.34, verifyPercentInput(" 12.34"), 0.001);
}

TEST(stringFunctions, verifyPercentInput12){
	EXPECT_NEAR(56.78, verifyPercentInput("56.78 "), 0.001);
}

TEST(stringFunctions, verifyPercentInput13){
	EXPECT_NEAR(100, verifyPercentInput(" 100 "), 0.001);
}

TEST(stringFunctions, verifyPercentInput14){
	EXPECT_NEAR(-1, verifyPercentInput("-0.01"), 0.001);
}

TEST(stringFunctions, stripCommas1){
	string input = "135,161";
	EXPECT_EQ(135161, stringToInt(stripCommas(input)));
}

TEST(stringFunctions, stripCommas2){
	string input = "74 510";
	EXPECT_EQ(74510, stringToInt(stripCommas(input)));
}

TEST(stringFunctions, stripCommas3){
	string input = "2'298";
	EXPECT_EQ(2298, stringToInt(stripCommas(input)));
}