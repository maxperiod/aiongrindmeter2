#include <iostream>
#include <map>
using namespace std;


class caseInsensitiveStringCompare{
public:
	bool operator() (const string& lhs, const string& rhs) const;
};

typedef map<string, string, caseInsensitiveStringCompare> CFGmap;

class SystemCFG{
public:
	SystemCFG(): CFGReadSuccess(false){}

	bool isReadSuccessful() {return CFGReadSuccess;}

	void writeCFG(const string& filename, bool encrypted = false);
	void readCFG(const string& filename, bool encrypted = false);

	const CFGmap& getEntries() {return entries;}
	
	void setProperty(const string& attribute, const string& value);

private:
	bool CFGReadSuccess;

	CFGmap entries;
};
