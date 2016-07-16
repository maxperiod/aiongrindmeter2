#include "ProfessionLevelingFrame.h"
#include "../stringFunctions.h"

wxBEGIN_EVENT_TABLE(ProfessionLevelingFrame, wxFrame)    
	EVT_CLOSE(ProfessionLevelingFrame::OnClose)
wxEND_EVENT_TABLE()

ProfessionLevelingFrame::ProfessionLevelingFrame(wxWindow* parent, ProfessionModule& professionModule, const wxPoint& pos) :
	 wxFrame(parent, wxID_ANY, "sdfsdgsd", pos, wxDefaultSize, (wxDEFAULT_FRAME_STYLE | wxSTAY_ON_TOP) & ~(wxRESIZE_BORDER | wxMINIMIZE_BOX | wxMAXIMIZE_BOX))
{
	this->professionModule = &professionModule;
	professionLevelingPanel = new wxPanel(this);//, wxID_ANY, wxDefaultPosition, wxSize(this->GetSize().GetX() - 10, -1));
	

	gatherLevelSizer = new wxGridBagSizer(2, 6);
	
	label1 = new wxStaticText(professionLevelingPanel, -1, wxT("Profession level ups"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE); 
	gatherLevelSizer->Add(label1, wxGBPosition(0, 0));
	label2 = new wxStaticText(professionLevelingPanel, -1, wxT("Level ups / hour"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE); 
	gatherLevelSizer->Add(label2, wxGBPosition(1, 0));
	label3 = new wxStaticText(professionLevelingPanel, -1, wxT("Gather/Crafts this level"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE); 
	gatherLevelSizer->Add(label3, wxGBPosition(2, 0));
	label4 = new wxStaticText(professionLevelingPanel, -1, wxT("Last level up"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE); 
	gatherLevelSizer->Add(label4, wxGBPosition(3, 0));

	value1 = new wxStaticText(professionLevelingPanel, -1, wxT("XX,XXX"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE | wxALIGN_RIGHT); 
	gatherLevelSizer->Add(value1, wxGBPosition(0, 1), wxDefaultSpan, wxALIGN_RIGHT);
	value2 = new wxStaticText(professionLevelingPanel, -1, wxT("X.XX X / h"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE | wxALIGN_RIGHT); 
	gatherLevelSizer->Add(value2, wxGBPosition(1, 1), wxDefaultSpan, wxALIGN_RIGHT);
	value3 = new wxStaticText(professionLevelingPanel, -1, wxT("XXX"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE | wxALIGN_RIGHT); 
	gatherLevelSizer->Add(value3, wxGBPosition(2, 1), wxDefaultSpan, wxALIGN_RIGHT);
	value4 = new wxStaticText(professionLevelingPanel, -1, wxT("XXX"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE | wxALIGN_RIGHT); 
	gatherLevelSizer->Add(value4, wxGBPosition(3, 1), wxDefaultSpan, wxALIGN_RIGHT);

	gauge = new wxGauge(professionLevelingPanel, PROF_XP_BAR_ID, 10000, wxDefaultPosition, wxSize(150, -1), wxGA_SMOOTH);	
	gatherLevelSizer->Add(gauge, wxGBPosition(4, 0), wxGBSpan(1, 2), wxALIGN_CENTER);

	//gatherLevelSizer->SetDimension(wxDefaultPosition, wxSize(professionLevelingPanel->GetSize().GetX() - 100, -1));
	professionLevelingPanel->SetSizer(gatherLevelSizer);	
	professionLevelingPanel->Layout();

	//parentSizer = new wxBoxSizer(wxVERTICAL);
	//parentSizer->Add(professionLevelingPanel, 0, wxEXPAND | wxALL, 0);

	//parentSizer->Add(new wxStaticText(this, -1, wxT("Craft Lvl Ups"))); 
	//parentSizer->Add(new wxButton(this, wxID_ANY, "sdlkfjsdf")) ; 
	
	professionLevelingPanel->Show();
	//this->SetSizer(parentSizer);
		
	professionLevelingPanel->Fit();
	this->Fit();
	//this->Layout();
	
}


void ProfessionLevelingFrame::refresh() {
	//professionModule->craftLeveling.getCurrentProfession();
	ProfessionLeveling* professionLeveling; 
	if (professionModule->professionMode == ProfessionModule::GATHER) professionLeveling = &professionModule->gatherLeveling;
	else professionLeveling = &professionModule->craftLeveling;
	
	wxString title;
	title << professionLeveling->getCurrentProfession() << ": " << formatNumber(professionLeveling->getCurrentLevel()) << 'p';
	this->SetTitle(title);
	value1->SetLabel(formatNumber(professionLeveling->getNumLevelUps()));
	value2->SetLabel(formatKiloMega(professionModule->timer.calculatePerHourRate(
		professionLeveling->getNumLevelUps() + professionLeveling->getProgressBarValue() / 100)) + " / h");
	value3->SetLabel(formatNumber(professionLeveling->getNumGatheredOrCraftedSinceLevelUp()));
	value4->SetLabel(formatNumber(professionLeveling->getNumGatheredOrCraftedForLastLevelUp()));
	
	professionLevelingPanel->Layout();
	gauge->SetValue(professionLeveling->getProgressBarValue() * 100);
	
}