#include <cmath>
#include "stringFunctions.h"

string formatKiloMega(double number, int numSigDigits){
	ostringstream oss;

	/*
	12,345,678
	8 digits
	3 sig figs
	divisor is 100,000 or 10^5
	12.3 M
	*/
	double numericPart = abs(number);

	int numDigits = log10((double)numericPart) + 1; //numericPart > 0 ? log10((double)numericPart) + 1 : 1;

	//if (numDigits == 0) numDigits = 1;
	long long roundDownDivisor = pow(10.0, numDigits - numSigDigits);
	if (roundDownDivisor == 0) roundDownDivisor = 1;
	if (roundDownDivisor > 1) numericPart = (long long)numericPart / roundDownDivisor * roundDownDivisor;

	if (number < 0) oss << '-';

	if (abs(numericPart) >= 1000000000000){
		oss << setprecision(numSigDigits) << numericPart / 1000000000000 << " T";		
	}
	else if (abs(numericPart) >= 1000000000){
		oss << setprecision(numSigDigits) << numericPart / 1000000000 << " G";		
	}
	else if (abs(numericPart) >= 1000000){
		oss << setprecision(numSigDigits) << numericPart / 1000000 << " M";
	}
	else if (abs(numericPart) >= 1000 && numSigDigits < numDigits){
		oss << setprecision(numSigDigits) << numericPart / 1000 << " k";
	}
	else {
		oss << setprecision(numSigDigits) << numericPart;
	}
	return oss.str();
}

/*********************************************************************************************
Remove non-numeric characters from the string, intended for strip commas from a number
*********************************************************************************************/
string stripCommas(string& line){
	
	string newString;

	for (int i = 0; i < line.length(); i ++){
		if (line.at(i) >= 48 && line.at(i) <= 57){
			newString.push_back(line.at(i));
		}
	}
	return newString;
}

/*********************************************************************************************
Format a integer with comma separators. Optionally add plus sign on non-negative numbers
*********************************************************************************************/
string formatNumber(long long number, bool addPlusSign){
	ostringstream oss;
	oss.imbue(locale(""));
	if (addPlusSign && number >= 0) oss << "+";
	oss << fixed << number;
	return oss.str();
	
}

/*********************************************************************************************
Format a positive integer, or display question marks if negative
*********************************************************************************************/
string formatPositiveNumber(long long number){
	ostringstream oss;
	oss.imbue(locale(""));
	if (number >= 0) oss << fixed << number;
	else oss << "?";
	return oss.str();
	
}

/*********************************************************************************************
Format percentage with specified number of decimal spaces
*********************************************************************************************/
string formatPercent(float percentage, int numDecimals){
	ostringstream oss;
	oss.imbue(locale(""));
	oss << fixed << setprecision(numDecimals) << percentage << "%";
	return oss.str();
}

/*********************************************************************************************
Format decimal number with specified number of significant digits
*********************************************************************************************/
string formatDecimal(float decimalNumber, int numSigDigits){
	ostringstream oss;
	oss.imbue(locale(""));
	oss << setprecision(numSigDigits) << decimalNumber;
	return oss.str();
}

/*********************************************************************************************
Format percentage changes. 2 decimal spaces, 3 if below 0.1% Add plus sign if not negative
*********************************************************************************************/
string formatPercentChange(float value){
	ostringstream oss;
	oss.imbue(locale(""));
	
	if (value >= 0) oss << "+";
	oss << fixed;
	if (abs(value) < 0.00005) oss << setprecision(0);
	else if (abs(value) < 0.0001) oss << setprecision(6);
	else if (abs(value) < 0.001) oss << setprecision(5);
	else if (abs(value) < 0.01) oss << setprecision(4);
	else if (abs(value) < 0.1) oss << setprecision(3);
	else oss << setprecision(2);
	
	oss << value << "%";
	return oss.str();
}

/*********************************************************************************************
Format two values into (XXX,XXX,XXX / YYY,YYY,YYY)
*********************************************************************************************/
string formatCurrentAndNextValues(int current, int next){
	ostringstream oss;
	oss.imbue(locale(""));
	
	if (current >= 0) oss << current;
	else oss << "???";
	oss << " / ";
	if (next >= 0) oss << next;
	else oss << "???";
	return oss.str();
}

string formatCurrentAndNextValuesWithKiloMega(long long current, long long next, int numSigDigits){
	ostringstream oss;
	oss.imbue(locale(""));
	/*
	if (current >= 0) oss << current;
	else oss << "???";
	oss << " / ";
	if (next >= 0) oss << next;
	else oss << "???";
	return oss.str();
	*/

	//ostringstream oss;
	
	//oss << fixed;	

	/*
	int divisor = 1;
	long long truncadedCurrent = current;
	long long numDigitsNext = log10((double)next) + 1;
	
	for (int i = numSigDigits; i < numDigitsNext; i ++){
		divisor *= 10;
	}
	*/

	double numericPartCurrent = abs(current);
	double numericPartNext = abs(next);

	int numDigitsNext = numericPartNext > 0 ? log10((double)numericPartNext) + 1 : 1;

	if (numDigitsNext == 0) numDigitsNext = 1;
	long long roundDownDivisor = pow(10.0, numDigitsNext - numSigDigits);
	if (roundDownDivisor == 0) roundDownDivisor = 1;
	
	numericPartCurrent = (long long)numericPartCurrent / roundDownDivisor * roundDownDivisor;
	numericPartNext = (long long)numericPartNext / roundDownDivisor * roundDownDivisor;
	
	if (abs(next) >= 1000000000000){		
		//oss << setprecision(numSigDigits) << (double)(current / divisor * divisor) / 1000000000000 << " T / " << formatKiloMega(next, numSigDigits);//(double)next / 1000000000 << " T";
		oss << setprecision(numSigDigits) << numericPartCurrent / 1000000000000 << " T / " << numericPartNext / 1000000000000 << " T";
	}
	else if (abs(next) >= 1000000000){		
		//oss << setprecision(numSigDigits) << (double)(current / divisor * divisor) / 1000000000 << " G / " << formatKiloMega(next, numSigDigits);//(double)next / 1000000000 << " G";
		oss << setprecision(numSigDigits) << numericPartCurrent / 1000000000 << " G / " << numericPartNext / 1000000000 << " G";
	}
	else if (abs(next) >= 1000000){
		//oss << setprecision(numSigDigits) << (double)(current / divisor * divisor) / 1000000 << " M / " << formatKiloMega(next, numSigDigits);//(double)next / 1000000 << " M";
		oss << setprecision(numSigDigits) << numericPartCurrent / 1000000 << " M / " << numericPartNext / 1000000 << " M";
	}
	else if (abs(next) >= 1000 && numSigDigits < numDigitsNext){
		//oss << setprecision(numSigDigits) << (double)(current / divisor * divisor) / 1000 << " k / " << formatKiloMega(next, numSigDigits);//(double)next / 1000 << " k ";
		oss << setprecision(numSigDigits) << numericPartCurrent / 1000 << " K / " << numericPartNext / 1000 << " K";
	}
	else {
		oss << setprecision(numSigDigits) << current << " / " << next;
	}
	
	

	return oss.str();
}


double calculateExpPercent(int currentExp, int nextLevel){
	
	return floor((double)currentExp / nextLevel * 10000) / 100;

	
}

/*********************************************************************************************
Get of Abyss Rank
*********************************************************************************************/
string formatAbyssRankName(int abyssRank){
	ostringstream oss;
	if (abyssRank > 1) oss << abyssRank << " kyu";
	else oss << "???";
	return oss.str();
}

/*********************************************************************************************
Format elasped time into HH : MM : SS format
*********************************************************************************************/
string formatElapsedTime(long elapsedTime){
	ostringstream oss;
	int hours = elapsedTime / 3600;
	int minutes = (elapsedTime % 3600) / 60;
	int seconds = elapsedTime % 60;
	
	if (hours < 10) oss << "0";
	oss << hours << " : ";
	if (minutes < 10) oss << "0";
	oss << minutes << " : ";
	if (seconds < 10) oss << "0";
	oss << seconds;

	return oss.str();

}

int stringToInt(string& input){
	return atoi(stripCommas(input).c_str());
}

/*********************************************************************************************
Verify a string to see whether it's a valid integer or not. Invalid inputs return -1
*********************************************************************************************/
int verifyNumericInput(string& input){
	bool hasComma = false;
	bool hasPeriod = false;

	//Strip spaces in front of input
	while(input[0] == ' ') input.erase(0, 1);

	//Strip trailing spaces from input
	while (input[input.length() - 1] == ' ') input.erase(input.length() - 1, 1);
	if (input.length() < 1) return -2;

	//Valid input characters are digits, comma, and periods
	for (int i = 0; i < input.length(); i ++){
		if (!((input[i] >= 48 && input[i] <= 57) || input[i] == ',' || input[i] == '.'))
			return -1;
	}
	
	for (int i = 0; i < input.length(); i ++){
		if (input[i] == ',') hasComma = true;
	}

	for (int i = 0; i < input.length(); i ++){
		if (input[i] == '.'){
			if (hasComma) return -1;
			else hasPeriod = true;
		}
	}
		
	if (hasComma || hasPeriod){
		for (int i = 0; i < input.length(); i ++){
			if (input[i] == ',' || input[i] == '.'){
				if (i == 0) return -1;
				if ((input.length() - i) % 4 != 0) return -1;
				
			}
			else if ((input.length() - i) % 4 == 0) return -1;
		}

	}

	return atoi(stripCommas(input).c_str());
}



double verifyPercentInput(const string& input, int maxDecimals){
	//bool hasComma = false;
	//bool hasPeriod = false;
	string input2 = input;
	int numDecimalPoints = 0;
	int numDecimalPlaces = 0;
	
	//Strip trailing percentage sign at the back
	if (input2[input2.length() - 1] == '%') input2.erase(input2.length() - 1, 1);

	//Strip spaces in front of input
	while(input2[0] == ' ') input2.erase(0, 1);

	//Strip trailing spaces from input
	while (input2[input2.length() - 1] == ' ') input2.erase(input2.length() - 1, 1);
	if (input2.length() < 1) return -2;

	//Valid input characters are digits, comma, and periods
	for (int i = 0; i < input2.length(); i ++){
		if (!((input2[i] >= 48 && input2[i] <= 57) || input2[i] == ',' || input2[i] == '.'))
			return -1;
	}
	
	for (int i = 0; i < input2.length(); i ++){
		if (input2[i] == ',') input2[i] = '.';
		if (input2[i] == '.') numDecimalPoints ++;
	}

	if (numDecimalPoints > 1) return -1;
	/*
	for (int i = 0; i < input2.length(); i ++){
		if (input2[i] == '.'){
			if (hasComma) return -1;
			else hasPeriod = true;
		}
	}
		
	if (hasComma || hasPeriod){
		for (int i = 0; i < input2.length(); i ++){
			if (input2[i] == ',' || input2[i] == '.'){
				if (i == 0) return -1;
				if ((input2.length() - i) % 4 != 0) return -1;
				
			}
			else if ((input2.length() - i) % 4 == 0) return -1;
		}

	}
	*/
	return atof(input2.c_str());
}