#ifndef PROFESSION_LEVELING_FRAME_H
#define PROFESSION_LEVELING_FRAME_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/fileconf.h>
#include <wx/sizer.h>
#include <wx/gbsizer.h>


#include <vector>
using namespace std;

#include "../modules/ProfessionModule.h"

#define FRAME_WIDTH 150
#define FRAME_HEIGHT 160
#define PANEL_HEIGHT 95


enum{
	PROF_XP_BAR_ID
};

class ProfessionLevelingFrame: public wxFrame
{

public:


	ProfessionLevelingFrame(wxWindow* parent, ProfessionModule& professionModule, const wxPoint& pos);

	void refresh();


private:
	
	ProfessionModule* professionModule;

	wxBoxSizer *parentSizer;

	wxPanel* professionLevelingPanel;

	wxGridBagSizer* gatherLevelSizer;

	wxStaticText *label1;
	wxStaticText *label2;
	wxStaticText *label3;
	wxStaticText *label4;

	wxStaticText *value1;
	wxStaticText *value2;
	wxStaticText *value3;
	wxStaticText *value4;

	wxGauge *gauge;	
	
	wxDECLARE_EVENT_TABLE();
	
	void OnClose(wxCloseEvent& event) {this->Hide();}

};

#endif