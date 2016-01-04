#include <string>
#include <map>
#include <ctime>
using namespace std;

struct TimedDamage{
	int damage;	
	long lastHitTime;
};

class AssistDamage{
public:
	AssistDamage(): expirySeconds(20){}
	
	AssistDamage(int expiry): expirySeconds(expiry){}
	
	void inflictDamage(string target, int damage){
		checkForExpiry(target);

		if (damageByTarget.count(target) == 0){
			TimedDamage timedDamage;
			timedDamage.damage = damage;
			timedDamage.lastHitTime = clock();
			damageByTarget[target] = timedDamage;
		}
		else {
			TimedDamage* entry = &damageByTarget[target];
			entry->damage += damage;
			entry->lastHitTime = clock();
		}
		
	}
	int getInflictedDamage(string target){
		checkForExpiry(target);
		if (damageByTarget.count(target) == 1){
			return damageByTarget[target].damage;
		}
		else return -1;
	}

private:	
	int expirySeconds;
	map<string, TimedDamage> damageByTarget;

	bool checkForExpiry(string target){
		if (damageByTarget.count(target) == 1){
			if (((clock() - damageByTarget[target].lastHitTime) / CLOCKS_PER_SEC) > expirySeconds){
				damageByTarget.erase(target);
				return true;
			}
			
		}		
		return false;
	}

};