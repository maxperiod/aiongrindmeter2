#ifndef AP_FRAME_H
#define AP_FRAME_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/fileconf.h>
#include <wx/sizer.h>
#include <wx/gbsizer.h>


#include "../modules/ApModule.h"
#include "../modules/SoulHealerModule.h"




enum{
	AP_BAR_ID,
	ID_AP_Start,
	//ID_Cumulative_AP,
	ID_ApUpdate
};


#define XP_AP_INPUT_WIDTH 85

class ApFrame: public wxFrame
{

public:
	ApFrame(wxWindow* parent, ApModule& apModule, SoulHealerModule& soulHealerModule, const wxPoint& pos);
	void refresh();

	void OnOK(wxCommandEvent& event);
	void OnCumulativap(wxCommandEvent& event);
	void OnApUpdate(wxCommandEvent& event);

	void OnClose(wxCloseEvent& event) {this->Hide();}

private:
	
	ApModule* apModule;
	SoulHealerModule* soulHealerModule;

	wxBoxSizer *parentSizer;

	wxPanel* apPanel;

	wxGridBagSizer* apSizer;

	wxStaticText *label1;
	wxStaticText *label2;
	wxStaticText *label3;
	wxStaticText *label4;
	wxStaticText *label5;
	wxStaticText *label6;
	
	wxStaticText *value1;
	wxStaticText *value2;
	wxStaticText *value3;
	wxStaticText *value4;
	wxStaticText *value5;
	wxStaticText *value6;

	wxStaticText *value1b;
	wxStaticText *value2b;
	wxStaticText *value3b;
	wxStaticText *value4b;
	wxStaticText *value5b;
	wxStaticText *value6b;

	wxStaticText *currentApLabel;
	wxStaticText *currentApValue;

	wxStaticText *lastChangeLabel;
	wxStaticText *lastChangeValue;

	wxStaticText *pvpApLabel;
	wxStaticText *pvpApValue;

	wxStaticText *netPvpApLabel;
	wxStaticText *netPvpApValue;

	wxGauge *gauge;
	wxStaticText *gaugePercent;
	wxStaticText *apValueLabel;

	wxCheckBox *cumulativeToggle;

	// Initialization Panel
	wxGridBagSizer* initSizer;
	wxPanel *initPanel;

	wxStaticText *initLabel1;
	wxStaticText *initLabel2;	
	wxTextCtrl *initValue1;
	wxTextCtrl *initValue2;	
	wxButton *startButton;


	// Manual AP Update Panel
	wxGridBagSizer* apUpdateSizer;	
	wxPanel *manualApUpdatePanel;
	
	wxStaticText *apInputMessage1;
	wxStaticText *apInputMessage2;
	wxStaticText *apInputLabel;
	wxTextCtrl *apInputValue;
	wxButton *apInputButton;

	wxDECLARE_EVENT_TABLE();
};

#endif