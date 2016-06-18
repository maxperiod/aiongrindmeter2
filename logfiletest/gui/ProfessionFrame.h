#ifndef PROFESSION_FRAME_H
#define PROFESSION_FRAME_H

#include "ListCtrlFrame.h"

#include "../modules/ProfessionModule.h"
/*
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/fileconf.h>
#include <wx/sizer.h>
#include <wx/listctrl.h>

#include <vector>
using namespace std;


*/
//#include "ProfessionLevelingPanel.h"

/*
#define FRAME_WIDTH 150
#define FRAME_HEIGHT 160
#define PANEL_HEIGHT 95
*/



enum GatherType{GATHER, CRAFT};

class ProfessionFrame: public ListCtrlFrame//wxFrame
{

public:
	ProfessionFrame(wxWindow* parent, ProfessionModule& professionModule, GatherType type, const wxPoint& pos);
		
	void refresh();


private:
	
	ProfessionModule* professionModule;
	GatherType type;
/*
	wxBoxSizer *parentSizer;

	
	wxPanel* professionPanel;
	
	wxListCtrl* listCtrl;



	void OnSize(wxSizeEvent& event);
	
	wxDECLARE_EVENT_TABLE();
	*/
};

#endif