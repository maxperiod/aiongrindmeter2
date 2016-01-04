#include <string>
using namespace std;

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif


#include "../gui/MainFrame.h"


class MyApp: public wxApp
{
public:
	virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
	//Frame* frame = new Frame(string(APP_TITLE) + " " + string(APP_VERSION), wxPoint(-1, -1), wxSize(FRAME_WIDTH, FRAME_HEIGHT) );
	//frame->Show( true );

	MainFrame* mainFrame = new MainFrame(wxDefaultPosition);
	mainFrame->Show(true);

	return true;
}