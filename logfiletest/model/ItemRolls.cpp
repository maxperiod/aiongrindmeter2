#include "ItemRolls.h"

ItemRolls::ItemRolls(): 
	numItemsRolled(0),
	numItemsPassed(0),
	numItemsWon(0),	
	sumOfMyRolls(0),
	sumOfWinningRolls(0)
{}

void ItemRolls::winItem(int item){

	if (itemRolls.size() > 0 
		&& itemRolls.back().item == -1 
		&& myLastRoll != -1
		&& itemRolls.back().winningRoll == myLastRoll
		&& itemRolls.back().winner == "")
	{
		itemRolls.back().item = item;
	}
	
		
	myLastRoll = -1;
}

void ItemRolls::didNotWinItem(int item,  const string& winner){
	if (itemRolls.size() > 0 
		&& itemRolls.back().item == -1 					
		&& itemRolls.back().winner == winner)
	{
		//vector<string> bracketValues;
		//BracketValueReader::readValues(params["%1"], bracketValues);					

		itemRolls.back().item = item;
	}
}

void ItemRolls::addItemRoll(int yourRoll, int winningRoll, const string& winner){
	currentRoll.item = -1;
	currentRoll.yourRoll = yourRoll;
	currentRoll.winningRoll = winningRoll;
	currentRoll.winner = winner;
	
	itemRolls.push_back(currentRoll);

	if (yourRoll > 0){
		numItemsRolled ++;
		sumOfMyRolls += yourRoll;
	}
	else {
		numItemsPassed ++;
	}
	sumOfWinningRolls += winningRoll;
}

void ItemRolls::addWinningItemRoll(){
	currentRoll.item = -1;
	currentRoll.yourRoll = myLastRoll;
	currentRoll.winningRoll = myLastRoll;
	currentRoll.winner = "";

	itemRolls.push_back(currentRoll);

	if (myLastRoll > 0){
		numItemsRolled ++;
		numItemsWon ++;
		sumOfMyRolls += myLastRoll;
		sumOfWinningRolls += myLastRoll;
	}
}

void ItemRolls::rollForItem(int value){
	myLastRoll = value;
}