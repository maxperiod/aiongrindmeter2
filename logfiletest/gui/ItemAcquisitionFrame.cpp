#include "ItemAcquisitionFrame.h"
#include "../stringFunctions.h"

#include "../language/LanguageManager.h"

ItemAcquisitionFrame::ItemAcquisitionFrame(wxWindow* parent, ItemAcquisitionModule& itemAcquisitionModule, const wxPoint& pos) :
	 ListCtrlFrame(parent, pos)/*, itemIDReader("itemnames.txt")*/
{
	this->itemAcquisitionModule = &itemAcquisitionModule;
	
	addColumn("Item ID", 70, wxLIST_FORMAT_LEFT);
	addColumn("Item Name", 500, wxLIST_FORMAT_LEFT);
	addColumn("Gained", 50, wxLIST_FORMAT_RIGHT);
	addColumn("Per Hour", 70, wxLIST_FORMAT_RIGHT);

	setNameColumnForVariableWidth(1);

	SetTitle("Items Acquired");
}


void ItemAcquisitionFrame::refresh() {
	
	//ItemIDFileReader itemIDReader("file.txt");

	int rowNum = 0;
	for (map<int, CounterEntry>::iterator iter = itemAcquisitionModule->itemsAcquired.begin(); 
		iter != itemAcquisitionModule->itemsAcquired.end(); iter ++)
	{
		
		if (rowNum >= listCtrl->GetItemCount())
			listCtrl->InsertItem(rowNum, wxString() << iter->first);
		else 
			listCtrl->SetItem(rowNum, 0, wxString() << iter->first);
			
		listCtrl->SetItem(rowNum, 1, LANGUAGE_MANAGER.getCurrentLanguage().getItemIDFileReader().getItemName(iter->first));
		listCtrl->SetItem(rowNum, 2, formatNumber(iter->second.numGained));

		if (iter->second.numPackets >= 3) 
			listCtrl->SetItem(rowNum, 3, formatKiloMega(itemAcquisitionModule->timer.calculatePerHourRate(iter->second.numGained)) + " / h");
		else 
			listCtrl->SetItem(rowNum, 3, "");
		/*
		cout << iter->first << " " << itemIDReader.getItemName(iter->first) << " x" << iter->second.numGained;
			if (iter->second.numPackets >= 3) 
				cout <<"\t(" << formatKiloMega(itemAcquisitionModule->timer.calculatePerHourRate(iter->second.numGained)) << " / h)";
		cout << endl;
		*/
		rowNum ++;
	}
	/*
	IndividualItemGatherCrafts* gathersByItem;
	if (type == GATHER) gathersByItem = &professionModule->gathers.getIndividualItemGatherCrafts();
	else if (type == CRAFT) gathersByItem = &professionModule->crafts.getIndividualItemGatherCrafts();


	int rowNum = 0;
	for (map<string, GatherCraftRecord>::iterator iter = gathersByItem->begin(); iter != gathersByItem->end(); iter ++){
		

		if (rowNum >= listCtrl->GetItemCount())
			listCtrl->InsertItem(rowNum, iter->first);
		else 
			listCtrl->SetItem(rowNum, 0, iter->first);
		
		listCtrl->SetItem(rowNum, 1, formatNumber(iter->second.getNumSuccess()));
		listCtrl->SetItem(rowNum, 2, formatNumber(iter->second.getNumFailure()));
		listCtrl->SetItem(rowNum, 3, formatNumber(iter->second.getNumCancel()));
		if (type == CRAFT){
			listCtrl->SetItem(rowNum, 4, formatNumber(iter->second.getNumProcs()));
			listCtrl->SetItem(rowNum, 5, formatKiloMega(professionModule->timer.calculatePerHourRate(iter->second.getNumSuccess())) + " / h");
		}
		else {
			listCtrl->SetItem(rowNum, 4, formatKiloMega(professionModule->timer.calculatePerHourRate(iter->second.getNumSuccess())) + " / h");
		}
		
		rowNum ++;
	}

	GatherCraftRecord* gathers;
	if (type == GATHER){
		gathers = &professionModule->gathers.getResult();
		this->SetTitle(
			"Gathering - S: " + formatNumber(gathers->getNumSuccess()) 
			+ " | F: " + formatNumber(gathers->getNumFailure()) 
			+ " | C: " + formatNumber(gathers->getNumCancel()) 
			+ " | " + formatKiloMega(professionModule->timer.calculatePerHourRate(gathers->getNumSuccess())) + " / h)");
	}
	else if (type == CRAFT){
		gathers = &professionModule->crafts.getResult();
		this->SetTitle(
			"Crafting - S: " + formatNumber(gathers->getNumSuccess()) 
			+ " | F: " + formatNumber(gathers->getNumFailure()) 
			+ " | C: " + formatNumber(gathers->getNumCancel()) 
			+ " | Proc: " + formatNumber(gathers->getNumProcs()) 
			+ " | " + formatKiloMega(professionModule->timer.calculatePerHourRate(gathers->getNumSuccess())) + " / h)");
	}
			
	
		*/	
			
			
		
}

