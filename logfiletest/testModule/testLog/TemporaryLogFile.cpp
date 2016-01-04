#include "TemporaryLogFile.h"


TemporaryLogFile::TemporaryLogFile(string chatLogToBeCopied, string copy){
	filename = chatLogToBeCopied;
	this->copy = copy;
}

void TemporaryLogFile::makeFileCopy(){
	ifstream originalFile;
	ofstream tempFile;
	originalFile.open(filename);
	tempFile.open(copy, ios::trunc);
	while(originalFile.good()){
		string copyLine;
		std::getline (originalFile,copyLine);
		if (originalFile.good()) tempFile << copyLine << endl;
	}
	tempFile.close();
	originalFile.close();
	
	
}

void TemporaryLogFile::deleteFileCopy(){
	remove(copy.c_str());
}

void TemporaryLogFile::appendFile(string line){
	ofstream fileToAppend;
	fileToAppend.open(copy, ios::app);
	fileToAppend << line << endl;
	fileToAppend.close();
}