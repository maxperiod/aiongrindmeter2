#ifndef ITEMROLLS_H
#define ITEMROLLS_H

#include <vector>
#include <string>
using namespace std;

struct ItemDiceRoll{
	int item;
	int yourRoll;
	int winningRoll;
	string winner;
};

class ItemRolls{
public:
	ItemRolls();

	void rollForItem(int value);

	void addItemRoll(int yourRoll, int winningRoll, const string& winner);
	void addWinningItemRoll();
	
	void winItem(int item);
	void didNotWinItem(int item, const string& winner);

	int getNumItemsRolled() {return numItemsRolled;}
	int getNumItemsPassed() {return numItemsPassed;}
	int getNumItemsWon() {return numItemsWon;}
	
	float getAverageOfMyRolls() {
		return (numItemsRolled > 0) ? (float)sumOfMyRolls / numItemsRolled : 0;
	}
	float getAverageOfWinningRolls() {
		int numRollsAndPasses = numItemsRolled + numItemsPassed;
		return (numRollsAndPasses > 0) ? (float)sumOfWinningRolls / numRollsAndPasses : 0;
	}

	const vector<ItemDiceRoll>& getItemRolls() {return itemRolls;}

private:
	int numItemsRolled;
	int numItemsPassed;
	int numItemsWon;
	
	int sumOfMyRolls;
	int sumOfWinningRolls;

	vector<ItemDiceRoll> itemRolls;
	
	ItemDiceRoll currentRoll;
	int myLastRoll;	
};
#endif