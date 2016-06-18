#include "ItemRollsFrame.h"
#include "../stringFunctions.h"

ItemRollsFrame::ItemRollsFrame(wxWindow* parent, ItemAcquisitionModule& itemAcquisitionModule, const wxPoint& pos)
	: ListCtrlFrame(parent, pos), itemIDReader("itemnames.txt")
{
	this->itemAcquisitionModule = &itemAcquisitionModule;

	addColumn("Item ID", 70, wxLIST_FORMAT_LEFT);
	addColumn("Item Name", 500, wxLIST_FORMAT_LEFT);
	addColumn("Your roll", 60, wxLIST_FORMAT_RIGHT);
	addColumn("Winning roll", 80, wxLIST_FORMAT_RIGHT);
	addColumn("Winner", 100, wxLIST_FORMAT_RIGHT);
	setNameColumnForVariableWidth(1);
}

void ItemRollsFrame::refresh(){
	wxString title;
	title << "Items rolls [" 
			<< itemAcquisitionModule->itemRolls.getNumItemsRolled() << " rolls / "
			<< itemAcquisitionModule->itemRolls.getNumItemsWon() << " wins / "
			<< itemAcquisitionModule->itemRolls.getNumItemsPassed() << " passes / "			
			<< itemAcquisitionModule->itemRolls.getAverageOfMyRolls() << " Avg Roll]";

	this->SetTitle(title);
			
	int rowNum = 0;
	for (int i = 0; i < itemAcquisitionModule->itemRolls.getItemRolls().size(); i ++){			
		
		ItemDiceRoll entry = itemAcquisitionModule->itemRolls.getItemRolls()[i];
		
		if (rowNum >= listCtrl->GetItemCount())
			listCtrl->InsertItem(rowNum, wxString() << entry.item);
		else 
			listCtrl->SetItem(rowNum, 0, wxString() << entry.item);

		listCtrl->SetItem(rowNum, 1, itemIDReader.getItemName(entry.item));
		
		if (entry.yourRoll > 0)
			listCtrl->SetItem(rowNum, 2, formatNumber(entry.yourRoll));
		else 
			listCtrl->SetItem(rowNum, 2, "Pass");

		if (entry.winningRoll > 0)
			listCtrl->SetItem(rowNum, 3, formatNumber(entry.winningRoll));
		else 
			listCtrl->SetItem(rowNum, 3, "Pass");
		
		listCtrl->SetItem(rowNum, 4, entry.winner);
		
		rowNum ++;
	}
		
}