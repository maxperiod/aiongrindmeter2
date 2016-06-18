#include "GpFrame.h"
#include "../stringFunctions.h"

wxBEGIN_EVENT_TABLE(GpFrame, wxFrame)        
	EVT_CLOSE(GpFrame::OnClose)
wxEND_EVENT_TABLE()



GpFrame::GpFrame(wxWindow* parent, GpModule& gpModule, const wxPoint& pos) :
	wxFrame(parent, wxID_ANY, "GP", pos, wxDefaultSize, (wxDEFAULT_FRAME_STYLE | wxSTAY_ON_TOP) & ~(wxRESIZE_BORDER | wxMINIMIZE_BOX | wxMAXIMIZE_BOX))	
{
	this->gpModule = &gpModule;
	

	gpPanel = new wxPanel(this);//, wxID_ANY, wxDefaultPosition, wxSize(this->GetSize().GetX() - 10, -1));	

	gpSizer = new wxGridBagSizer(2, 6);

	label1 = new wxStaticText(gpPanel, -1, wxT("GP Gained"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE); 
	gpSizer->Add(label1, wxGBPosition(0, 0));
	label2 = new wxStaticText(gpPanel, -1, wxT("GP / hour"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE); 
	gpSizer->Add(label2, wxGBPosition(1, 0));
	label3 = new wxStaticText(gpPanel, -1, wxT("Last Change"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE); 
	gpSizer->Add(label3, wxGBPosition(2, 0));
	

	value1 = new wxStaticText(gpPanel, -1, wxT("XXX,XXX"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE | wxALIGN_RIGHT); 
	gpSizer->Add(value1, wxGBPosition(0, 1), wxDefaultSpan, wxALIGN_RIGHT);
	value2 = new wxStaticText(gpPanel, -1, wxT("-X.XX X / h"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE | wxALIGN_RIGHT); 
	gpSizer->Add(value2, wxGBPosition(1, 1), wxDefaultSpan, wxALIGN_RIGHT);
	value3 = new wxStaticText(gpPanel, -1, wxT("XXX,XXX"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE | wxALIGN_RIGHT); 
	gpSizer->Add(value3, wxGBPosition(2, 1), wxDefaultSpan, wxALIGN_RIGHT);

	//gpSizer->SetDimension(wxDefaultPosition, wxSize(gpPanel->GetSize().GetX() - 100, -1));
	gpPanel->SetSizer(gpSizer);	
	//gpPanel->Layout();
	//gpSizer->GetC
	//parentSizer = new wxBoxSizer(wxVERTICAL);
	//parentSizer->Add(gpPanel, 0, wxEXPAND | wxALL, 0);

	//parentSizer->Add(new wxStaticText(this, -1, wxT("Craft Lvl Ups"))); 
	//parentSizer->Add(new wxButton(this, wxID_ANY, "sdlkfjsdf")) ; 
	
	gpPanel->Fit();
	gpPanel->Show();
	//this->SetSize(this->DoGetBestClientSize());
	this->Fit();
	//this->Layout();
	
}

void GpFrame::refresh(){
	

	value1->SetLabel(formatNumber(gpModule->gpGainMeter.getNetGained()));
	value2->SetLabel(formatKiloMega(gpModule->timer.calculatePerHourRate(gpModule->gpGainMeter.getNetGained())) + " / h");
	
	value3->SetLabel(formatNumber(gpModule->gpGainMeter.getLastChange(), true));
		
		
		
	
	/*
	if (expModule->expGainMeter.isLastTickChanged()){
		initValue2->SetValue("");
		expInputValue->SetValue("");
	}
	*/
	//gpPanel->Layout();
}