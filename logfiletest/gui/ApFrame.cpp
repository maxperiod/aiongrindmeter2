#include "ApFrame.h"
#include "../stringFunctions.h"

wxBEGIN_EVENT_TABLE(ApFrame, wxFrame)    
    EVT_BUTTON(ID_AP_Start, ApFrame::OnOK)
	//EVT_CHECKBOX(ID_Cumulative_XP, ExpFrame::OnCumulativeXP)
	EVT_BUTTON(ID_ApUpdate, ApFrame::OnApUpdate)
	EVT_CLOSE(ApFrame::OnClose)
wxEND_EVENT_TABLE()


ApFrame::ApFrame(wxWindow* parent, ApModule& apModule, SoulHealerModule& soulHealerModule, const wxPoint& pos):
	wxFrame(parent, wxID_ANY, "AP", pos, wxDefaultSize, (wxDEFAULT_FRAME_STYLE | wxSTAY_ON_TOP) & ~(wxRESIZE_BORDER | wxMINIMIZE_BOX | wxMAXIMIZE_BOX))	
	{
	this->apModule = &apModule;
	this->soulHealerModule = &soulHealerModule;

	apPanel = new wxPanel(this);//, wxID_ANY, wxDefaultPosition, wxSize(this->GetSize().GetX() - 10, -1));	

	apSizer = new wxGridBagSizer(2, 6);

	label1 = new wxStaticText(apPanel, -1, wxT("AP Revenue"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE); 
	apSizer->Add(label1, wxGBPosition(0, 0));
	label2 = new wxStaticText(apPanel, -1, wxT("AP Spent"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE); 
	apSizer->Add(label2, wxGBPosition(1, 0));
	label3 = new wxStaticText(apPanel, -1, wxT("AP Lost"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE); 
	apSizer->Add(label3, wxGBPosition(2, 0));
	label4 = new wxStaticText(apPanel, -1, wxT("Net Income"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE); 
	apSizer->Add(label4, wxGBPosition(3, 0));
	label5 = new wxStaticText(apPanel, -1, wxT("Relic AP"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE); 
	apSizer->Add(label5, wxGBPosition(4, 0));
	label6 = new wxStaticText(apPanel, -1, wxT("Income+Relics"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE); 
	apSizer->Add(label6, wxGBPosition(5, 0));

	value1 = new wxStaticText(apPanel, -1, wxT("XX,XXX,XXX"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE | wxALIGN_RIGHT); 
	apSizer->Add(value1, wxGBPosition(0, 1), wxDefaultSpan);
	value2 = new wxStaticText(apPanel, -1, wxT("XX,XXX,XXX"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE | wxALIGN_RIGHT); 
	apSizer->Add(value2, wxGBPosition(1, 1), wxDefaultSpan);
	value3 = new wxStaticText(apPanel, -1, wxT("XX,XXX,XXX"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE | wxALIGN_RIGHT); 
	apSizer->Add(value3, wxGBPosition(2, 1), wxDefaultSpan);
	value4 = new wxStaticText(apPanel, -1, wxT("XX,XXX,XXX"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE | wxALIGN_RIGHT); 
	apSizer->Add(value4, wxGBPosition(3, 1), wxDefaultSpan);
	value5 = new wxStaticText(apPanel, -1, wxT("XX,XXX,XXX"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE | wxALIGN_RIGHT); 
	apSizer->Add(value5, wxGBPosition(4, 1), wxDefaultSpan);
	value6 = new wxStaticText(apPanel, -1, wxT("XX,XXX,XXX"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE | wxALIGN_RIGHT); 
	apSizer->Add(value6, wxGBPosition(5, 1), wxDefaultSpan);

	value1b = new wxStaticText(apPanel, -1, wxT("-X.XX X / h"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE | wxALIGN_RIGHT); 
	apSizer->Add(value1b, wxGBPosition(0, 2), wxDefaultSpan);
	value2b = new wxStaticText(apPanel, -1, wxT("-X.XX X / h"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE | wxALIGN_RIGHT); 
	apSizer->Add(value2b, wxGBPosition(1, 2), wxDefaultSpan);
	value3b = new wxStaticText(apPanel, -1, wxT("-X.XX X / h"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE | wxALIGN_RIGHT); 
	apSizer->Add(value3b, wxGBPosition(2, 2), wxDefaultSpan);
	value4b = new wxStaticText(apPanel, -1, wxT("-X.XX X / h"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE | wxALIGN_RIGHT); 
	apSizer->Add(value4b, wxGBPosition(3, 2), wxDefaultSpan);
	value5b = new wxStaticText(apPanel, -1, wxT("-X.XX X / h"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE | wxALIGN_RIGHT); 
	apSizer->Add(value5b, wxGBPosition(4, 2), wxDefaultSpan);
	value6b = new wxStaticText(apPanel, -1, wxT("-X.XX X / h"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE | wxALIGN_RIGHT); 
	apSizer->Add(value6b, wxGBPosition(5, 2), wxDefaultSpan);


	currentApLabel = new wxStaticText(apPanel, -1, wxT("Current AP"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE); 
	apSizer->Add(currentApLabel, wxGBPosition(0, 3));
	lastChangeLabel = new wxStaticText(apPanel, -1, wxT("Last Change"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE); 
	apSizer->Add(lastChangeLabel, wxGBPosition(1, 3));
	
	pvpApLabel = new wxStaticText(apPanel, -1, wxT("Gross PvP AP"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE); 
	apSizer->Add(pvpApLabel, wxGBPosition(2, 3));
	netPvpApLabel = new wxStaticText(apPanel, -1, wxT("Net PvP AP"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE); 
	apSizer->Add(netPvpApLabel, wxGBPosition(3, 3));

	currentApValue = new wxStaticText(apPanel, -1, wxT("XXX,XXX,XXX"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE | wxALIGN_RIGHT); 
	apSizer->Add(currentApValue, wxGBPosition(0, 4));
	lastChangeValue = new wxStaticText(apPanel, -1, wxT("XXX,XXX,XXX"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE | wxALIGN_RIGHT); 
	apSizer->Add(lastChangeValue, wxGBPosition(1, 4));
	
	pvpApValue = new wxStaticText(apPanel, -1, wxT("XXX,XXX,XXX"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE | wxALIGN_RIGHT); 
	apSizer->Add(pvpApValue, wxGBPosition(2, 4));
	netPvpApValue = new wxStaticText(apPanel, -1, wxT("XXX,XXX,XXX"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE | wxALIGN_RIGHT); 
	apSizer->Add(netPvpApValue, wxGBPosition(3, 4));


	apPanel->SetSizer(apSizer);

	apPanel->Fit();
	apPanel->Show();


	this->Fit();

	apPanel->Hide();

	// ===========================================================================

	initSizer = new wxGridBagSizer(4, 4);
	
	initPanel = new wxPanel(this);

	initLabel1 = new wxStaticText(initPanel, -1, wxT("Current AP")); 
	initSizer->Add(initLabel1, wxGBPosition(0, 0));
	//initLabel2 = new wxStaticText(initPanel, -1, wxT("Current XP")); 
	//initSizer->Add(initLabel2, wxGBPosition(1, 0));
	
	//initValue1 = new wxTextCtrl(initPanel, -1, wxEmptyString, wxDefaultPosition, wxSize(LEVEL_INPUT_WIDTH, -1)); 
	//initValue1->SetMaxLength(2);
	//initSizer->Add(initValue1, wxGBPosition(0, 1));
	initValue1 = new wxTextCtrl(initPanel, -1, wxEmptyString, wxDefaultPosition, wxSize(XP_AP_INPUT_WIDTH, -1)); 
	initSizer->Add(initValue1, wxGBPosition(0, 1));
	
	startButton = new wxButton(initPanel, ID_AP_Start, wxT("OK"));
	initSizer->Add(startButton, wxGBPosition(1, 1));

	initPanel->SetSizer(initSizer);
	//initPanel->Fit();
	initPanel->SetSize(this->GetClientSize());
	//initSizer->SetDimension(0, 0, FRAME_WIDTH, PANEL_HEIGHT + NAV_HEIGHT);
	
	
	// ===========================================================================

	
	apUpdateSizer = new wxGridBagSizer(4, 4);

	manualApUpdatePanel = new wxPanel(this);
	//parentSizer->Add(manualApUpdatePanel, wxGROW);

	apInputMessage1 = new wxStaticText(manualApUpdatePanel, -1, wxT("You have lost AP because you were PKed by an opposing faction player."));
	apInputMessage1->Wrap(this->GetClientSize().GetX());
	apUpdateSizer->Add(apInputMessage1, wxGBPosition(0, 0), wxGBSpan(1, 3)); 
	apInputMessage2 = new wxStaticText(manualApUpdatePanel, -1, wxT("Since AP loss are not logged in Chat.log, manual AP update is required."));
	apInputMessage2->Wrap(this->GetClientSize().GetX());
	apUpdateSizer->Add(apInputMessage2, wxGBPosition(1, 0), wxGBSpan(1, 3)); 
	apInputLabel = new wxStaticText(manualApUpdatePanel, -1, wxT("Current AP")); 
	apUpdateSizer->Add(apInputLabel, wxGBPosition(2, 0));
	apInputValue = new wxTextCtrl(manualApUpdatePanel, -1, wxEmptyString, wxDefaultPosition, wxSize(XP_AP_INPUT_WIDTH, -1), wxALIGN_RIGHT); 
	apUpdateSizer->Add(apInputValue, wxGBPosition(2, 1));
	apInputButton = new wxButton(manualApUpdatePanel, ID_ApUpdate, wxT("update AP"));
	apUpdateSizer->Add(apInputButton, wxGBPosition(3, 2));

	manualApUpdatePanel->SetSizer(apUpdateSizer);
	manualApUpdatePanel->SetSize(this->GetClientSize());

	manualApUpdatePanel->Hide();
}

void ApFrame::refresh(){

	if (soulHealerModule != nullptr && !initPanel->IsShown()){
		if (soulHealerModule->soulHealer.isApUpdateNeeded() && !manualApUpdatePanel->IsShown()){
			apPanel->Hide();
			manualApUpdatePanel->Show();
			this->Show();
		}
		else if (!soulHealerModule->soulHealer.isApUpdateNeeded() && !apPanel->IsShown()){
			manualApUpdatePanel->Hide();
			apPanel->Show();
		}
	}

	value1->SetLabel(formatNumber(apModule->apGainMeter.getTotalGained()));
	value1b->SetLabel(wxString() << formatKiloMega(apModule->timer.calculatePerHourRate(apModule->apGainMeter.getTotalGained())) << " / h");

	value2->SetLabel(formatNumber(apModule->apGainMeter.getTotalSpent()));
	value2b->SetLabel(wxString() << formatKiloMega(apModule->timer.calculatePerHourRate(apModule->apGainMeter.getTotalSpent())) << " / h");

	value3->SetLabel(formatNumber(apModule->apGainMeter.getTotalLost()));
	value3b->SetLabel(wxString() << formatKiloMega(apModule->timer.calculatePerHourRate(apModule->apGainMeter.getTotalLost())) << " / h");

	value4->SetLabel(formatNumber(apModule->apGainMeter.getNetGained()));
	value4b->SetLabel(wxString() << formatKiloMega(apModule->timer.calculatePerHourRate(apModule->apGainMeter.getNetGained())) << " / h");
	
	value5->SetLabel(formatNumber(apModule->apGainMeter.getRelicAp()));
	value5b->SetLabel(wxString() << formatKiloMega(apModule->timer.calculatePerHourRate(apModule->apGainMeter.getRelicAp())) << " / h");

	value6->SetLabel(formatNumber(apModule->apGainMeter.getNetGained() + apModule->apGainMeter.getRelicAp()));
	value6b->SetLabel(wxString() << formatKiloMega(apModule->timer.calculatePerHourRate(apModule->apGainMeter.getNetGained() + apModule->apGainMeter.getRelicAp())) << " / h");

	currentApValue->SetLabel(formatNumber(apModule->abyssRankChecker.getCurrentValue()));
	lastChangeValue->SetLabel(formatNumber(apModule->apGainMeter.getLastChange(), true));

	pvpApValue->SetLabel(formatNumber(apModule->apGainMeter.getPvpAp()));
	netPvpApValue->SetLabel(formatNumber(apModule->apGainMeter.getPvpAp() - apModule->apGainMeter.getTotalLost()));

	/*
	if (apModule->apGainMeter.isLastTickChanged()){
		initValue1->SetValue("");
		apInputValue->SetValue("");
	}	
	*/
	apPanel->Layout();
}

void ApFrame::OnOK(wxCommandEvent& event){
	
	int currentAp = verifyNumericInput(initValue1->GetValue().ToStdString());
	
	if (currentAp == -2){
	}
	else if (apModule->abyssRankChecker.initialize(currentAp)){
		initPanel->Hide();
		apPanel->Show();
		soulHealerModule->soulHealer.apUpdateNotNeeded();
	}
	else{
		wxMessageBox( "Invalid current AP value.", "Error", wxOK);	
	}
}

void ApFrame::OnCumulativap(wxCommandEvent& event){
}

void ApFrame::OnApUpdate(wxCommandEvent& event){
	int currentAp = verifyNumericInput(apInputValue->GetValue().ToStdString());
	if (soulHealerModule->soulHealer.manualApUpdate(currentAp)){

	}
}
