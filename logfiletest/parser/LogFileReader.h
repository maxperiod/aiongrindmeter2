#ifndef LOGFILEREADER_H
#define LOGFILEREADER_H

#include <string>
#include <iostream>
#include <fstream>
#include <queue>

using namespace std;


class LogFileReader{

public:	
	/*
	LogFileReader(): bufferSize(1024) {
		buffer = new char(bufferSize);
		buffer[bufferSize - 1] = 0;
	}*/
	//LogFileReader(string filename);
	bool openChatLog(string directory);
	bool closeChatLog();

	~LogFileReader();
	//queue<string> readLines();
	void readLines(queue<string>& lines, bool readFromBeginning = false);
	
	bool isOK() {return OK;}

private:
	ifstream file;
	bool OK;

	//int bufferSize;
	//char* buffer;
	//stack<string> lines;
	
};
#endif