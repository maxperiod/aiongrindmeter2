#ifndef ITEM_BUNDLE_FRAME_H
#define ITEM_BUNDLE_FRAME_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/fileconf.h>
#include <wx/sizer.h>
#include <wx/treectrl.h>

#include "../modules/ItemAcquisitionModule.h"
#include "../parser/ItemIDFileReader.h"
#include "../stringFunctions.h"

using namespace std;

class ItemBundleFrame: public wxFrame
{

public:
	ItemBundleFrame(wxWindow* parent, ItemAcquisitionModule& itemAcquisitionModule, const wxPoint& pos);
		
	void refresh();


protected:	 
	
	ItemAcquisitionModule* itemAcquisitionModule;
	
	ItemIDFileReader itemIDReader;

	wxBoxSizer *parentSizer;
	
	wxPanel* panel;
	
	wxTreeCtrl* treeCtrl;

	void OnSize(wxSizeEvent& event);

	wxDECLARE_EVENT_TABLE();

private:
	wxTreeItemId root;
	void OnClose(wxCloseEvent& event) {this->Hide();}
};

#endif