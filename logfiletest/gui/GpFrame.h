#ifndef GP_FRAME_H
#define GP_FRAME_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/fileconf.h>
#include <wx/sizer.h>
#include <wx/gbsizer.h>

#include "../modules/GpModule.h"

class GpFrame: public wxFrame
{

public:
	GpFrame(wxWindow* parent, GpModule& gpModule, const wxPoint& pos);
	void refresh();
	

	void OnClose(wxCloseEvent& event) {this->Hide();}

private:
	GpModule* gpModule;

	wxBoxSizer *parentSizer;

	wxPanel* gpPanel;

	wxGridBagSizer* gpSizer;

	wxStaticText *label1;
	wxStaticText *label2;
	wxStaticText *label3;
	
	
	wxStaticText *value1;
	wxStaticText *value2;
	wxStaticText *value3;
	


	wxDECLARE_EVENT_TABLE();
};



#endif