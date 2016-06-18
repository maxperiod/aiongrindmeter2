#include "KinahFrame.h"
#include "../stringFunctions.h"

wxBEGIN_EVENT_TABLE(KinahFrame, wxFrame)        
	EVT_CLOSE(KinahFrame::OnClose)
wxEND_EVENT_TABLE()



KinahFrame::KinahFrame(wxWindow* parent, KinahModule& kinahModule, const wxPoint& pos) :
	wxFrame(parent, wxID_ANY, "Kinah", pos, wxDefaultSize, (wxDEFAULT_FRAME_STYLE | wxSTAY_ON_TOP) & ~(wxRESIZE_BORDER | wxMINIMIZE_BOX | wxMAXIMIZE_BOX))	
{
	this->kinahModule = &kinahModule;
	

	kinahPanel = new wxPanel(this);//, wxID_ANY, wxDefaultPosition, wxSize(this->GetSize().GetX() - 10, -1));	

	kinahSizer = new wxGridBagSizer(2, 6);

	label1 = new wxStaticText(kinahPanel, -1, wxT("Kinah Revenue"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE); 
	kinahSizer->Add(label1, wxGBPosition(0, 0));
	label2 = new wxStaticText(kinahPanel, -1, wxT("Kinah Expenses"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE); 
	kinahSizer->Add(label2, wxGBPosition(1, 0));
	label3 = new wxStaticText(kinahPanel, -1, wxT("Net Income"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE); 
	kinahSizer->Add(label3, wxGBPosition(2, 0));
	label4 = new wxStaticText(kinahPanel, -1, wxT("Last Change"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE); 
	kinahSizer->Add(label4, wxGBPosition(3, 0));
	label5 = new wxStaticText(kinahPanel, -1, wxT("NPC Sales"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE); 
	kinahSizer->Add(label5, wxGBPosition(4, 0));
	

	value1 = new wxStaticText(kinahPanel, -1, wxT("-XX,XXX,XXX,XXX"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE | wxALIGN_RIGHT); 
	kinahSizer->Add(value1, wxGBPosition(0, 1), wxDefaultSpan, wxALIGN_RIGHT);
	value2 = new wxStaticText(kinahPanel, -1, wxT("-XX,XXX,XXX,XXX"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE | wxALIGN_RIGHT); 
	kinahSizer->Add(value2, wxGBPosition(1, 1), wxDefaultSpan, wxALIGN_RIGHT);
	value3 = new wxStaticText(kinahPanel, -1, wxT("-XX,XXX,XXX,XXX"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE | wxALIGN_RIGHT); 
	kinahSizer->Add(value3, wxGBPosition(2, 1), wxDefaultSpan, wxALIGN_RIGHT);
	value4 = new wxStaticText(kinahPanel, -1, wxT("-XX,XXX,XXX,XXX"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE | wxALIGN_RIGHT); 
	kinahSizer->Add(value4, wxGBPosition(3, 1), wxDefaultSpan, wxALIGN_RIGHT);
	value5 = new wxStaticText(kinahPanel, -1, wxT("-XX,XXX,XXX,XXX"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE | wxALIGN_RIGHT); 
	kinahSizer->Add(value5, wxGBPosition(4, 1), wxDefaultSpan, wxALIGN_RIGHT);

	//kinahSizer->SetDimension(wxDefaultPosition, wxSize(kinahPanel->GetSize().GetX() - 100, -1));
	kinahPanel->SetSizer(kinahSizer);	
	//kinahPanel->Layout();
	//kinahSizer->GetC
	//parentSizer = new wxBoxSizer(wxVERTICAL);
	//parentSizer->Add(kinahPanel, 0, wxEXPAND | wxALL, 0);

	//parentSizer->Add(new wxStaticText(this, -1, wxT("Craft Lvl Ups"))); 
	//parentSizer->Add(new wxButton(this, wxID_ANY, "sdlkfjsdf")) ; 
	
	kinahPanel->Fit();
	kinahPanel->Show();
	//this->SetSize(this->DoGetBestClientSize());
	this->Fit();
	//this->Layout();
	
}

void KinahFrame::refresh(){
	

	value1->SetLabel(formatNumber(kinahModule->kinahGainMeter.getTotalGained()));
	value2->SetLabel(formatNumber(kinahModule->kinahGainMeter.getTotalSpent()));
	value3->SetLabel(formatNumber(kinahModule->kinahGainMeter.getNetGained()));
	value4->SetLabel(formatNumber(kinahModule->kinahGainMeter.getLastChange(), true));
	value5->SetLabel(formatNumber(kinahModule->kinahGainMeter.getNpcSales()));
		
	//kinahPanel->Layout();
}