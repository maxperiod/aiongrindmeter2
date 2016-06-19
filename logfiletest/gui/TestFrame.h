#ifndef TEST_FRAME_H
#define TEST_FRAME_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/fileconf.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>


using namespace std;

class TestFrame: public wxFrame
{

public:
	TestFrame(wxWindow* parent, const wxPoint& pos);
		
	virtual void refresh();


protected:
	wxBoxSizer *parentSizer;
	
	
	wxPanel* panel;
	wxTextCtrl* textCtrl;

	void OnSize(wxSizeEvent& event);

	wxDECLARE_EVENT_TABLE();

private:

	void OnClose(wxCloseEvent& event) {this->Hide();}
};

#endif