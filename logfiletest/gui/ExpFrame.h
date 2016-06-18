#ifndef EXP_FRAME_H
#define EXP_FRAME_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/fileconf.h>
#include <wx/sizer.h>
#include <wx/gbsizer.h>


#include "../modules/ExpModule.h"
#include "../modules/SoulHealerModule.h"



enum{
	XP_BAR_ID,
	ID_Start,
	ID_Cumulative_XP,
	ID_ExpUpdate
};

#define LEVEL_INPUT_WIDTH 30
#define XP_AP_INPUT_WIDTH 85

class ExpFrame: public wxFrame
{

public:
	ExpFrame(wxWindow* parent, ExpModule& expModule, SoulHealerModule& soulHealerModule, const wxPoint& pos);
	void refresh();

	void OnOK(wxCommandEvent& event);
	void OnCumulativeXP(wxCommandEvent& event);
	void OnExpUpdate(wxCommandEvent& event);

	void OnClose(wxCloseEvent& event) {this->Hide();}

private:
	
	ExpModule* expModule;
	SoulHealerModule* soulHealerModule;

	wxBoxSizer *parentSizer;

	wxPanel* expPanel;

	wxGridBagSizer* expSizer;

	wxStaticText *label1;
	wxStaticText *label2;
	wxStaticText *label3;
	//wxStaticText *label4;
	
	wxStaticText *value1;
	wxStaticText *value2;
	wxStaticText *value3;

	wxStaticText *value1b;
	wxStaticText *value2b;
	wxStaticText *value3b;
	//wxStaticText *value4b;

	wxGauge *gauge;
	wxStaticText *gaugePercent;
	wxStaticText *expValueLabel;

	wxCheckBox *cumulativeToggle;

	// Initialization Panel
	wxGridBagSizer* initSizer;
	wxPanel *initPanel;

	wxStaticText *initLabel1;
	wxStaticText *initLabel2;	
	wxTextCtrl *initValue1;
	wxTextCtrl *initValue2;	
	wxButton *startButton;


	// Manual XP Update Panel
	wxGridBagSizer* expUpdateSizer;	
	wxPanel *manualExpUpdatePanel;
	
	wxStaticText *expInputMessage1;
	wxStaticText *expInputMessage2;
	wxStaticText *expInputLabel;
	wxTextCtrl *expInputValue;
	wxButton *expInputButton;

	wxDECLARE_EVENT_TABLE();
};

#endif