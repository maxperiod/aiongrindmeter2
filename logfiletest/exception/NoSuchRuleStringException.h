#include <exception>
using namespace std;

class NoSuchRuleStringException: public exception
{
public:
	NoSuchRuleStringException(const char* ruleString){
		this->ruleString = ruleString;
	}

	virtual const char* what() const throw(){
		return ruleString;
	}
private:
	const char* ruleString;
};