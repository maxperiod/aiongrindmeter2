#ifndef ITEMACQUISITIONMODULE_H
#define ITEMACQUISITIONMODULE_H

//#include "../AionAddon.h"
#include "../Module.h"

#include "../model/Counter.h"
#include "../model/ItemRolls.h"

#include "../Timer.h"

class ItemAcquisitionModule: public Module{
public:
	
	ItemAcquisitionModule();


	Timer timer;
	//Counter<int> itemsAcquired;
	Counter<int> itemsAcquired;
	Counter<string> itemsConsumed;	

	Counter<string> containersOpened;	
	map<string, Counter<int>> itemsFromContainers;

	//Counter<string> monstersKilled;
	ItemRolls itemRolls;

	void executeChatLogCommand(ChatLogCommand& command);

	void endOfTickAction();

private:
	int idleTicks;

		Counter<int> itemsBuffer;
	bool isContainerOpened;
	string openedContainerName;

	bool diceRollWin;


	void applyFromBuffer();
	void clearTemporaryStates();

	void acquireItem(const string& item, int quantity);	
	void otherPlayerWinsItem(const string& winner, const string& item);

};
#endif