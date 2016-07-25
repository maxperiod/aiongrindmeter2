#include "ItemConsumptionFrame.h"
#include "../stringFunctions.h"



ItemConsumptionFrame::ItemConsumptionFrame(wxWindow* parent, ItemAcquisitionModule& itemAcquisitionModule, const wxPoint& pos) :
	 ListCtrlFrame(parent, pos)
{
	this->itemAcquisitionModule = &itemAcquisitionModule;
	
	addColumn("Item Name", 500, wxLIST_FORMAT_LEFT);
	addColumn("Used", 50, wxLIST_FORMAT_RIGHT);
	addColumn("Per Hour", 70, wxLIST_FORMAT_RIGHT);

	setNameColumnForVariableWidth(0);

	SetTitle("Items Consumed");
}


	 
void ItemConsumptionFrame::refresh() {
	
	//ItemIDFileReader itemIDReader("file.txt");

	int rowNum = 0;
	for (map<string, CounterEntry>::iterator iter = itemAcquisitionModule->itemsConsumed.begin(); 
		iter != itemAcquisitionModule->itemsConsumed.end(); iter ++)
	{
		
		if (rowNum >= listCtrl->GetItemCount())
			listCtrl->InsertItem(rowNum, wxString() << iter->first);
		else 
			listCtrl->SetItem(rowNum, 0, wxString() << iter->first);
			
		//listCtrl->SetItem(rowNum, 1, iter->second.numGained);
		listCtrl->SetItem(rowNum, 1, formatNumber(iter->second.numGained));

		if (iter->second.numPackets >= 3) 
			listCtrl->SetItem(rowNum, 2, formatKiloMega(itemAcquisitionModule->timer.calculatePerHourRate(iter->second.numGained)) + " / h");
		else 
			listCtrl->SetItem(rowNum, 2, "");

		rowNum ++;
	}

			
		
}