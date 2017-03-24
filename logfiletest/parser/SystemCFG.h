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

	bool writeCFG(const string& filename, bool encrypted = true);
	void readCFG(const string& filename, bool encrypted = true);

	const CFGmap getEntries() const {return entries;}
	
	string getProperty(const string& attribute) const;
	void setProperty(const string& attribute, const string& value);
	void removeProperty(const string& attribute);

private:
	bool CFGReadSuccess;

	CFGmap entries;
};
