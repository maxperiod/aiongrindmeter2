#include <string>
#include <fstream>
using namespace std;

class TemporaryLogFile{
public:
	TemporaryLogFile(string original, string copy);
	void makeFileCopy();
	void deleteFileCopy();
	void appendFile(string line);
private:
	string filename;
	string copy;
};