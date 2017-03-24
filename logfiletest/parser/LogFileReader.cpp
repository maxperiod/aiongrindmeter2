#include "LogFileReader.h"
#include <iostream>

using namespace std;



/*********************************************************************************************
Constructor: Open Aion log file from filename, move file pointer to end of file
*********************************************************************************************/
//LogFileReader::LogFileReader(string filename){
bool LogFileReader::openChatLog(string directory){
	file.open(directory + "Chat.log");
	//file.seekg(0, ios::end);
	file.seekg(0, file.end);
	
	if (file.fail()) OK = false;
	else OK = true;
	return OK;
}

bool LogFileReader::closeChatLog(){
	file.close();	
	if (file.fail()) return false;
	else return true;
}

/*********************************************************************************************
Destructor: Close file
*********************************************************************************************/
LogFileReader::~LogFileReader(){
	file.close();	
	//delete(buffer);
}

/*********************************************************************************************
Read new lines that have been appended to the log file by the game Client, put them into a queue
*********************************************************************************************/
//queue<string> LogFileReader::readLines(){
void LogFileReader::readLines(queue<string>& lines, bool readFromBeginning){
	if (!OK) openChatLog(directory);

	if (readFromBeginning){
		file.seekg(0, file.beg);
	}

	string line;
	
	while(file.good()){
		std::getline (file,line);
		if (file.good()) lines.push(line);	
	}
	
	/*
	while(file.good()){
		
		string bufferOver = "";
		file.get(buffer, bufferSize);
		
		int startPos = 0;
		for (int i = 0; i < bufferSize - 1; i ++){
			if (i == '\n'){
				string line(buffer + startPos, i - startPos);
				lines.push(bufferOver + line);
				startPos = i;
				bufferOver = "";
			}
			
		}
		
		bufferOver += (buffer + startPos);
		
	}
	*/
	if (OK) file.clear();
	
}
