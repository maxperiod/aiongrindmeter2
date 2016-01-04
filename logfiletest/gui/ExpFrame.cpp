#include "ExpFrame.h"	
#include "../stringFunctions.h"


wxBEGIN_EVENT_TABLE(ExpFrame, wxFrame)    
    EVT_BUTTON(ID_Start, ExpFrame::OnOK)
	EVT_CHECKBOX(ID_Cumulative_XP, ExpFrame::OnCumulativeXP)
	EVT_BUTTON(ID_ExpUpdate, ExpFrame::OnExpUpdate)
	EVT_CLOSE(ExpFrame::OnClose)
wxEND_EVENT_TABLE()

ExpFrame::ExpFrame(ExpModule& expModule, SoulHealerModule& soulHealerModule, const wxPoint& pos) :
	wxFrame(NULL, wxID_ANY, "XP", pos, wxDefaultSize, (wxDEFAULT_FRAME_STYLE | wxSTAY_ON_TOP) & ~(wxRESIZE_BORDER | wxMINIMIZE_BOX | wxMAXIMIZE_BOX))	
{
	this->expModule = &expModule;
	this->soulHealerModule = &soulHealerModule;

	expPanel = new wxPanel(this);//, wxID_ANY, wxDefaultPosition, wxSize(this->GetSize().GetX() - 10, -1));	

	expSizer = new wxGridBagSizer(2, 6);

	label1 = new wxStaticText(expPanel, -1, wxT("XP Gained"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE); 
	expSizer->Add(label1, wxGBPosition(0, 0));
	label2 = new wxStaticText(expPanel, -1, wxT("XP / hour"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE); 
	expSizer->Add(label2, wxGBPosition(1, 0));
	label3 = new wxStaticText(expPanel, -1, wxT("Last Gained"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE); 
	expSizer->Add(label3, wxGBPosition(2, 0));
	//label4 = new wxStaticText(expPanel, -1, wxT("Last level up")); 
	//expSizer->Add(label4, wxGBPosition(3, 0));

	value1 = new wxStaticText(expPanel, -1, wxT("X,XXX,XXX,XXX"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE | wxALIGN_RIGHT); 
	expSizer->Add(value1, wxGBPosition(0, 1), wxDefaultSpan, wxALIGN_RIGHT);
	value2 = new wxStaticText(expPanel, -1, wxT("-X.XX X / h"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE | wxALIGN_RIGHT); 
	expSizer->Add(value2, wxGBPosition(1, 1), wxDefaultSpan, wxALIGN_RIGHT);
	value3 = new wxStaticText(expPanel, -1, wxT("XX,XXX,XXX"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE | wxALIGN_RIGHT); 
	expSizer->Add(value3, wxGBPosition(2, 1), wxDefaultSpan, wxALIGN_RIGHT); 

	value1b = new wxStaticText(expPanel, -1, wxT("X.XX Lv"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE | wxALIGN_RIGHT); 
	expSizer->Add(value1b, wxGBPosition(0, 2), wxDefaultSpan, wxALIGN_RIGHT);
	value2b = new wxStaticText(expPanel, -1, wxT("X.XX Lv / h"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE | wxALIGN_RIGHT); 
	expSizer->Add(value2b, wxGBPosition(1, 2), wxDefaultSpan, wxALIGN_RIGHT);
	value3b = new wxStaticText(expPanel, -1, wxT("XX.XX %"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE | wxALIGN_RIGHT); 
	expSizer->Add(value3b, wxGBPosition(2, 2), wxDefaultSpan, wxALIGN_RIGHT);
	//value4 = new wxStaticText(expPanel, -1, wxT("xxxxxxxxx")); 
	//expSizer->Add(value4, wxGBPosition(3, 1), wxDefaultSpan, wxALIGN_RIGHT);

	gauge = new wxGauge(expPanel, XP_BAR_ID, 10000, wxDefaultPosition, wxSize(150, -1), wxGA_SMOOTH);	
	expSizer->Add(gauge, wxGBPosition(3, 0), wxGBSpan(1, 2), wxALIGN_CENTER);
	gaugePercent = new wxStaticText(expPanel, -1, wxT("XX.XX %")); 
	expSizer->Add(gaugePercent, wxGBPosition(3, 2), wxDefaultSpan, wxALIGN_RIGHT);

	//expSizer->Layout();

	//expSizer->SetDimension(wxDefaultPosition, wxSize(expPanel->GetSize().GetX() - 100, -1));
	expPanel->SetSizer(expSizer);	
	//expPanel->Layout();
	expValueLabel = new wxStaticText(expPanel, -1, wxT("XXX.X X / XXX.X X")); 
	expSizer->Add(expValueLabel, wxGBPosition(4, 0), wxGBSpan(1, 2), wxALIGN_CENTER);

	cumulativeToggle = new wxCheckBox(expPanel, ID_Cumulative_XP, wxT("Cumulative Lv 1-65 XP bar"));
	expSizer->Add(cumulativeToggle, wxGBPosition(5, 0), wxGBSpan(1, 2));
	//expSizer->GetC
	//parentSizer = new wxBoxSizer(wxVERTICAL);
	//parentSizer->Add(expPanel, 0, wxEXPAND | wxALL, 0);

	//parentSizer->Add(new wxStaticText(this, -1, wxT("Craft Lvl Ups"))); 
	//parentSizer->Add(new wxButton(this, wxID_ANY, "sdlkfjsdf")) ; 
	
	expPanel->Fit();
	expPanel->Show();
	//this->SetSize(this->DoGetBestClientSize());
	this->Fit();
	//this->Layout();

	expPanel->Hide();

	// ===========================================================================

	initSizer = new wxGridBagSizer(4, 4);
	
	initPanel = new wxPanel(this);

	initLabel1 = new wxStaticText(initPanel, -1, wxT("Char Level")); 
	initSizer->Add(initLabel1, wxGBPosition(0, 0));
	initLabel2 = new wxStaticText(initPanel, -1, wxT("Current XP")); 
	initSizer->Add(initLabel2, wxGBPosition(1, 0));
	
	initValue1 = new wxTextCtrl(initPanel, -1, wxEmptyString, wxDefaultPosition, wxSize(LEVEL_INPUT_WIDTH, -1)); 
	initValue1->SetMaxLength(2);
	initSizer->Add(initValue1, wxGBPosition(0, 1));
	initValue2 = new wxTextCtrl(initPanel, -1, wxEmptyString, wxDefaultPosition, wxSize(XP_AP_INPUT_WIDTH, -1)); 
	initSizer->Add(initValue2, wxGBPosition(1, 1));
	
	startButton = new wxButton(initPanel, ID_Start, wxT("OK"));
	initSizer->Add(startButton, wxGBPosition(3, 1));

	initPanel->SetSizer(initSizer);
	//initPanel->Fit();
	initPanel->SetSize(this->GetClientSize());
	//initSizer->SetDimension(0, 0, FRAME_WIDTH, PANEL_HEIGHT + NAV_HEIGHT);
	
	
	// ===========================================================================

	expUpdateSizer = new wxGridBagSizer(4, 4);

	manualExpUpdatePanel = new wxPanel(this);	

	expInputMessage1 = new wxStaticText(manualExpUpdatePanel, -1, wxT("You have lost XP because you were killed by a monster."));
	expInputMessage1->Wrap(this->GetClientSize().GetX());
	expUpdateSizer->Add(expInputMessage1, wxGBPosition(0, 0), wxGBSpan(1, 3)); 
	expInputMessage2 = new wxStaticText(manualExpUpdatePanel, -1, wxT("Visit a Soul Healer to automatically update your XP. Alternatively you can update XP manually."));
	expInputMessage2->Wrap(this->GetClientSize().GetX());
	expUpdateSizer->Add(expInputMessage2, wxGBPosition(1, 0), wxGBSpan(1, 3)); 
	expInputLabel = new wxStaticText(manualExpUpdatePanel, -1, wxT("Current XP")); 
	expUpdateSizer->Add(expInputLabel, wxGBPosition(2, 0));
	expInputValue = new wxTextCtrl(manualExpUpdatePanel, -1, wxEmptyString, wxDefaultPosition, wxSize(XP_AP_INPUT_WIDTH, -1), wxALIGN_RIGHT); 
	expUpdateSizer->Add(expInputValue, wxGBPosition(2, 1));
	expInputButton = new wxButton(manualExpUpdatePanel, ID_ExpUpdate, wxT("Manual update XP"));
	expUpdateSizer->Add(expInputButton, wxGBPosition(2, 2));

	
	manualExpUpdatePanel->SetSizer(expUpdateSizer);
	manualExpUpdatePanel->SetSize(this->GetClientSize());

	manualExpUpdatePanel->Hide();

	initPanel->Show();
}

void ExpFrame::refresh(){
	if (soulHealerModule != nullptr && !initPanel->IsShown()){
		if (soulHealerModule->soulHealer.isExpUpdateNeeded() && !manualExpUpdatePanel->IsShown()){
			expPanel->Hide();
			manualExpUpdatePanel->Show();
		}
		else if (!soulHealerModule->soulHealer.isExpUpdateNeeded() && !expPanel->IsShown()){
			manualExpUpdatePanel->Hide();
			expPanel->Show();
		}
	}

	value1->SetLabel(formatNumber(expModule->expGainMeter.getNetGained()));
	value2->SetLabel(formatKiloMega(expModule->timer.calculatePerHourRate(expModule->expGainMeter.getNetGained())) + " / h");
	value3->SetLabel(formatNumber(expModule->expGainMeter.getLastChange(), true));

	if (expModule->levelUpChecker.isInitialized()){
		
		wxString expBarValueLabel;
		float expBarValue;
		
		if (cumulativeToggle->GetValue()){
			expBarValueLabel << formatKiloMega(expModule->levelUpChecker.getCumulativeCurrentValue(), 4) << " / " << formatKiloMega(expModule->expChart.getLevelCapValue(), 4);
			//expBarValueLabel << formatCurrentAndNextValuesWithKiloMega(expModule->levelUpChecker.getCumulativeCurrentValue(), expModule->expChart.getLevelCapValue(), 4);
			expBarValue = expModule->levelUpChecker.getCumulativePercent() * 100;
			
		}
		else {
			//expBarValueLabel << formatKiloMega(expModule->levelUpChecker.getCurrentValue()) << " / " << formatKiloMega(expModule->levelUpChecker.getCurrentLevelMaxValue());
			expBarValueLabel << formatCurrentAndNextValuesWithKiloMega(expModule->levelUpChecker.getCurrentValue(), expModule->levelUpChecker.getCurrentLevelMaxValue(), 4);
			expBarValue = expModule->levelUpChecker.getPercent() * 100;
			
		}
		expValueLabel->SetLabel(expBarValueLabel); //SetLabel(formatPercent(expBarPercent / 100));
		gauge->SetValue(expBarValue);
		gaugePercent->SetLabel(formatPercent(expBarValue / 100));//, cumulativeToggle->GetValue() + 1));

		wxString title;
		title << "XP - Lv. " << expModule->levelUpChecker.getCurrentLevel();
		this->SetTitle(title);

		float numLevelsGained = expModule->levelUpChecker.getNumLevelsGained();
		if (numLevelsGained >= 1) 
			value1b->SetLabel(wxString() << formatDecimal(numLevelsGained) + " Lv");
		else
			value1b->SetLabel(wxString() << formatPercent(numLevelsGained * 100) + " %");
		
		float levelsPerHour = expModule->getWeightedLevelUpsPerHour();
		if (levelsPerHour < 1) 
			value2b->SetLabel(wxString() << formatDecimal(levelsPerHour * 100) << " % / h");
		else 
			value2b->SetLabel(wxString() << formatDecimal(levelsPerHour) << " Lv / h");

		value3b->SetLabel(formatPercentChange(expModule->levelUpChecker.getLastChangePercent()));
		
		
	}
	/*
	if (expModule->expGainMeter.isLastTickChanged()){
		initValue2->SetValue("");
		expInputValue->SetValue("");
	}
	*/
	expPanel->Layout();
}

void ExpFrame::OnOK(wxCommandEvent& event){
	// For verifyNumericInput function, -2 is blank input, -1 is invalid input
	int level = verifyNumericInput(initValue1->GetValue().ToStdString());
	//int currentExp = verifyNumericInput(initValue2->GetValue().ToStdString());
	double currentExpPercent = 0;
	initValue2->GetValue().ToDouble(&currentExpPercent);
	/*
	if (level == -2 || currentExp == -2){
	}
	else if (expModule->levelUpChecker.initialize(level, currentExp)){
		initPanel->Hide();
		expPanel->Show();
	}
	else{
		wxMessageBox( "One or more of your entered values are invalid.", "Error", wxOK);
	
	}
	*/
	if (expModule->levelUpChecker.initializePercent(level, currentExpPercent)){
		initPanel->Hide();
		expPanel->Show();
		soulHealerModule->soulHealer.expUpdateNotNeeded();
	}

	refresh();
}

void ExpFrame::OnCumulativeXP(wxCommandEvent& event){
	refresh();
}

void ExpFrame::OnExpUpdate(wxCommandEvent& event){
	int currentExp = verifyNumericInput(expInputValue->GetValue().ToStdString());
	if (soulHealerModule->soulHealer.manualExpUpdate(currentExp)){

	}
}