#include "ProfessionFrame.h"
#include "../stringFunctions.h"
/*
wxBEGIN_EVENT_TABLE(ProfessionFrame, wxFrame)    
    EVT_SIZE(ProfessionFrame::OnSize)
wxEND_EVENT_TABLE()
*/

ProfessionFrame::ProfessionFrame(wxWindow* parent, ProfessionModule& professionModule, GatherType type, const wxPoint& pos) :
	 //wxFrame(NULL, wxID_ANY, "ffffff", pos, wxDefaultSize, (wxDEFAULT_FRAME_STYLE | wxSTAY_ON_TOP) & ~(wxMAXIMIZE_BOX)), type(type)
	ListCtrlFrame(parent, pos), type(type)
{
	this->professionModule = &professionModule;
	/*
	professionPanel = new wxPanel(this);//, wxID_ANY, wxDefaultPosition, this->GetSize());
	
	parentSizer = new wxBoxSizer(wxVERTICAL);



	listCtrl = new wxListCtrl(professionPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxALWAYS_SHOW_SB);

	listCtrl->AppendColumn("Item name", wxLIST_FORMAT_LEFT, 170);
	listCtrl->AppendColumn("S", wxLIST_FORMAT_RIGHT, 40);
	listCtrl->AppendColumn("F", wxLIST_FORMAT_RIGHT, 40);
	listCtrl->AppendColumn("C", wxLIST_FORMAT_RIGHT, 40);
	
	if (type == CRAFT) listCtrl->AppendColumn("Proc", wxLIST_FORMAT_RIGHT, 40);

	listCtrl->AppendColumn("Per Hour", wxLIST_FORMAT_RIGHT, 70);

	parentSizer->Add(listCtrl, 0, wxEXPAND | wxALL, 0);
	
	professionPanel->SetSizer(parentSizer);
	*/
	

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
			
	
			
			
			
		
}

/*
void ProfessionFrame::OnSize(wxSizeEvent& event){
	
	//professionPanel->SetSizerAndFit(parentSizer);
	
	professionPanel->SetSize(this->GetClientSize());
	
	listCtrl->SetSize(this->GetClientSize());
	//listCtrl->SetSize(wxSize(event.GetSize().GetX() - 20, event.GetSize().GetY() - 40));
	
	if (type == GATHER) listCtrl->SetColumnWidth(0, event.GetSize().GetWidth() - 225);
	else if (type == CRAFT) listCtrl->SetColumnWidth(0, event.GetSize().GetWidth() - 265);
	//this->Layout();
	
}
*/