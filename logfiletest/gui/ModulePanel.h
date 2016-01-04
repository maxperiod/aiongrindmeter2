#ifndef PANEL_H
#define PANEL_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/fileconf.h>
#include <wx/gbsizer.h>


class ModulePanel: public wxPanel{
public:
	Panel(wxWindow *parent, wxWindowID id=wxID_ANY, const wxPoint &pos=wxDefaultPosition, 
		const wxSize &size=wxDefaultSize,  long style=wxTAB_TRAVERSAL, const wxString &name=wxPanelNameStr);	

private:
	wxBoxSizer* sizer;


};
#endif
