#include "PlayerKillsFrame.h"
#include "../stringFunctions.h"

PlayerKillsFrame::PlayerKillsFrame(wxWindow* parent, HuntingModule& huntingModule, SoulHealerModule& soulHealerModule, const wxPoint& pos):
	ListCtrlFrame(parent, pos) {
	this->huntingModule = &huntingModule;
	this->soulHealerModule = &soulHealerModule;
			
	addColumn("Player Name", 150, wxLIST_FORMAT_LEFT);
	addColumn("Kills", 50, wxLIST_FORMAT_RIGHT);
	addColumn("Assists", 50, wxLIST_FORMAT_RIGHT);
	//addColumn("Deaths", 50, wxLIST_FORMAT_RIGHT);

	setNameColumnForVariableWidth(0);
}
		

void PlayerKillsFrame::refresh(){
	
	int totalKills = huntingModule->playersKilled.getTotalKills();
	int totalAssists = huntingModule->playersKilled.getTotalAssists();
	int totalDeaths = soulHealerModule->soulHealer.getNumPvpDeaths();
	int uniqueKills = huntingModule->playersKilled.getUniqueKills();

	int rowNum = 0;
	for (PvPMap::iterator iter = huntingModule->playersKilled.begin(); 
		iter != huntingModule->playersKilled.end(); iter ++)
	{
		
		if (rowNum >= listCtrl->GetItemCount())
			listCtrl->InsertItem(rowNum, iter->first);
		else 
			listCtrl->SetItem(rowNum, 0, iter->first);
			
		
		listCtrl->SetItem(rowNum, 1, formatNumber(iter->second.kills));
		listCtrl->SetItem(rowNum, 2, formatNumber(iter->second.assists));
		/*
		if (iter->second.kills >= 3) 
			listCtrl->SetItem(rowNum, 2, formatKiloMega(huntingModule->timer.calculatePerHourRate(iter->second.numGained)) + " / h");
		else 
			listCtrl->SetItem(rowNum, 2, "");
		*/

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

	if (totalKills >= 3)
		this->SetTitle(wxString("PvP - K: ") << totalKills 
			<< " | D: " << totalDeaths  
			<< " | A: " << totalAssists
			<< " | " << formatKiloMega(huntingModule->timer.calculatePerHourRate(totalKills)) << " Kills / h"
			<< " | Unique Kills: " << uniqueKills
			);

	else
		this->SetTitle(wxString("PvP - K: ") << totalKills 
			<< " | D: " << totalDeaths
			<< " | A: " << totalAssists 			
			<< " | Unique Kills: " << uniqueKills
			);
		
}