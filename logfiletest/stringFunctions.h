#ifndef STRING_FCTN_H
#define STRING_FCTN_H

#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

string formatKiloMega(double number, int numSigDigits = 3);
string stripCommas(string& line);
string formatCurrentAndNextValues(int current, int next);
string formatCurrentAndNextValuesWithKiloMega(long long current, long long next, int numSigDigits = 3);
string formatNumber(long long number, bool addPlusSign = false);
string formatPositiveNumber(long long number);
string formatPercent(float percentage, int numDecimals = 2);
string formatDecimal(float decimalNumber, int numSigDigits = 3);
string formatPercentChange(float value);
double calculateExpPercent(int currentExp, int nextLevel);
string formatAbyssRankName(int abyssRank);
string formatElapsedTime(long elapsedTime);

int stringToInt(string& input);
int verifyNumericInput(string& input);
double verifyPercentInput(const string& input, int maxDecimals = 2);


#endif