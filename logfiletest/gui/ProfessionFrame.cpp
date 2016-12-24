#include "ProfessionFrame.h"
#include "../stringFunctions.h"
#include "../parser/BracketValueReader.h"
#include "../language/LanguageManager.h"

ProfessionFrame::ProfessionFrame(wxWindow* parent, ProfessionModule& professionModule, GatherType type, const wxPoint& pos) :
	ListCtrlFrame(parent, pos), type(type)
{
	this->professionModule = &professionModule;

	addColumn("Item name", 300, wxLIST_FORMAT_LEFT);
	addColumn("S", 40, wxLIST_FORMAT_RIGHT);
	addColumn("F", 40, wxLIST_FORMAT_RIGHT);
	addColumn("C", 40, wxLIST_FORMAT_RIGHT);
	
	if (type == CRAFT) addColumn("Proc", 40, wxLIST_FORMAT_RIGHT);

	addColumn("Per Hour", 70, wxLIST_FORMAT_RIGHT);

	setNameColumnForVariableWidth(0);
}


void ProfessionFrame::refresh() {
	 

	IndividualItemGatherCrafts* gathersByItem;
	if (type == GATHER) gathersByItem = &professionModule->gathers.getIndividualItemGatherCrafts();
	else if (type == CRAFT) gathersByItem = &professionModule->crafts.getIndividualItemGatherCrafts();


	int rowNum = 0;
	for (map<string, GatherCraftRecord>::iterator iter = gathersByItem->begin(); iter != gathersByItem->end(); iter ++){
		
		const string& item = iter->first;
		
		string displayName;
		string itemName = LANGUAGE_MANAGER.getCurrentLanguage().getItemIDFileReader().getItemName(iter->first);
		if (itemName != "0") //(item.find("[item:") == 0 && item.at(item.length() - 1) == ']'){
			displayName = itemName;
		else 
			displayName = iter->first;

		if (rowNum >= listCtrl->GetItemCount())
			listCtrl->InsertItem(rowNum, displayName);
		else 
			listCtrl->SetItem(rowNum, 0, displayName);
		
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
			
	
			
			
			
		
}

