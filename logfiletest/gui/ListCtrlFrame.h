#ifndef LISTCTRL_FRAME_H
#define LISTCTRL_FRAME_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/fileconf.h>
#include <wx/sizer.h>
#include <wx/listctrl.h>

#include <vector>
using namespace std;

class ListCtrlFrame: public wxFrame
{

public:
	ListCtrlFrame(const wxPoint& pos);
		
	virtual void refresh() = 0;


protected:
	void addColumn(const wxString& columnName, int width, wxListColumnFormat format);
	
	void setNameColumnForVariableWidth(int columnNumber); 
	
	wxBoxSizer *parentSizer;
	
	wxPanel* panel;
	
	wxListCtrl* listCtrl;

	void OnSize(wxSizeEvent& event);

	wxDECLARE_EVENT_TABLE();

private:
	int nameColumnForVariableWidth;
	int totalFixedColumnsWidth;

	void OnClose(wxCloseEvent& event) {this->Hide();}
};

#endif