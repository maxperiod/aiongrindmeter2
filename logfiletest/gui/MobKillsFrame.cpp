#include "MobKillsFrame.h"
#include "../stringFunctions.h"

MobKillsFrame::MobKillsFrame(HuntingModule& huntingModule, const wxPoint& pos):
	ListCtrlFrame(pos) {
	this->huntingModule = &huntingModule;
			
	addColumn("Monster Name", 500, wxLIST_FORMAT_LEFT);
	addColumn("Kills", 50, wxLIST_FORMAT_RIGHT);
	addColumn("Per Hour", 70, wxLIST_FORMAT_RIGHT);

	setNameColumnForVariableWidth(0);
}
		
void MobKillsFrame::refresh(){
	
	int totalMobsKilled = huntingModule->monstersKilled.getTotalCount();

	int rowNum = 0;
	for (map<string, CounterEntry>::iterator iter = huntingModule->monstersKilled.begin(); 
		iter != huntingModule->monstersKilled.end(); iter ++)
	{
		
		if (rowNum >= listCtrl->GetItemCount())
			listCtrl->InsertItem(rowNum, iter->first);
		else 
			listCtrl->SetItem(rowNum, 0, iter->first);
			
		
		listCtrl->SetItem(rowNum, 1, formatNumber(iter->second.numGained));

		if (iter->second.numPackets >= 3) 
			listCtrl->SetItem(rowNum, 2, formatKiloMega(huntingModule->timer.calculatePerHourRate(iter->second.numGained)) + " / h");
		else 
			listCtrl->SetItem(rowNum, 2, "");
		

		/*
		cout << "Monsters killed (" << totalMobsKilled << ")";
		if (totalMobsKilled >= 3)
			cout << " (" << formatKiloMega(huntingModule.timer.calculatePerHourRate(totalMobsKilled)) << " / h)";
		cout << endl;
		*/
		/*
		cout << iter->first << " " << itemIDReader.getItemName(iter->first) << " x" << iter->second.numGained;
			if (iter->second.numPackets >= 3) 
				cout <<"\t(" << formatKiloMega(itemAcquisitionModule->timer.calculatePerHourRate(iter->second.numGained)) << " / h)";
		cout << endl;
		*/
		rowNum ++;
	}

	if (totalMobsKilled >= 3)
		this->SetTitle(wxString("Monsters kills: ") << totalMobsKilled << " (" << formatKiloMega(huntingModule->timer.calculatePerHourRate(totalMobsKilled)) << " / h)");
	else
		this->SetTitle(wxString("Monsters kills: ") << totalMobsKilled);
		
}