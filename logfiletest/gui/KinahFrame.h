#ifndef KINAH_FRAME_H
#define KINAH_FRAME_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/fileconf.h>
#include <wx/sizer.h>
#include <wx/gbsizer.h>

#include "../modules/KinahModule.h"

class KinahFrame: public wxFrame
{

public:
	KinahFrame(KinahModule& kinahModule, const wxPoint& pos);
	void refresh();
	

	void OnClose(wxCloseEvent& event) {this->Hide();}

private:
	KinahModule* kinahModule;

	wxBoxSizer *parentSizer;

	wxPanel* kinahPanel;

	wxGridBagSizer* kinahSizer;

	wxStaticText *label1;
	wxStaticText *label2;
	wxStaticText *label3;
	wxStaticText *label4;
	wxStaticText *label5;
	
	
	wxStaticText *value1;
	wxStaticText *value2;
	wxStaticText *value3;
	wxStaticText *value4;
	wxStaticText *value5;
	


	wxDECLARE_EVENT_TABLE();
};



#endif