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
	
private:
	bool checkSystemCFG(string aionPath);
	bool FileExists(string filename);
};

wxIMPLEMENT_APP(MyApp);


#define INI_FILE "aiongrindmeter.ini"
#define AION_BIN_32 "/bin32/AION.bin"
#define AION_BIN_64 "/bin64/AION.bin"

bool MyApp::OnInit()
{
	//Frame* frame = new Frame(string(APP_TITLE) + " " + string(APP_VERSION), wxPoint(-1, -1), wxSize(FRAME_WIDTH, FRAME_HEIGHT) );
	//frame->Show( true );
	
	MainFrame* mainFrame;

	string aionPath;

	wxFileConfig *config = new wxFileConfig(wxEmptyString, wxEmptyString, INI_FILE, wxEmptyString, wxCONFIG_USE_RELATIVE_PATH);
	wxConfigBase::Set(config);
	wxConfigBase *conf = wxConfigBase::Get(false);

	//Try to load from current directory
	aionPath = "../";
	if (FileExists(aionPath + LOG_FILE) || FileExists(aionPath + AION_BIN_32) || FileExists(aionPath + AION_BIN_64)){
		//Log file exists
		mainFrame = new MainFrame(aionPath, wxDefaultPosition);
		mainFrame->Show(true);
	}	
	else{
		//Try to load from ini's directory
		if(conf) {			
			aionPath = conf->Read( wxT("AionPath"));		      

		}
		if (/*FileExists(aionPath + LOG_FILE) || */FileExists(aionPath + AION_BIN_32) || FileExists(aionPath + AION_BIN_64)){
			
			if (checkSystemCFG(aionPath)){			
				mainFrame = new MainFrame(aionPath, wxDefaultPosition);
				mainFrame->Show(true);
			}
			else return false;
		}
		// Ask for user to browser for Aion's directory
		else{
			wxDirDialog dlg(NULL, "Locate your AION directory", "wxEmptyString", wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
			int success = dlg.ShowModal();
			aionPath = dlg.GetPath() + '/';
			if (success != wxID_OK){ // Cancel button
				//Close(true);
			}
			else if (!FileExists(aionPath + AION_BIN_32) &&  !FileExists(aionPath + AION_BIN_64)){
				wxMessageBox("This does not appear to be an Aion directory.", "Error", wxOK);
				return false;
			}
			else{ // Write directory choice to ini
				if (checkSystemCFG(aionPath)){		
					conf->Write(wxT("AionPath"), aionPath.c_str());
					mainFrame = new MainFrame(aionPath, wxDefaultPosition);
					mainFrame->Show(true);
				}
				else return false;
			}
			
		}

	}
	/*
	MainFrame* mainFrame = new MainFrame(wxDefaultPosition);
	mainFrame->Show(true);
	*/
	return true;
}

bool MyApp::checkSystemCFG(string aionPath){
	SystemCFG systemCFG;
	systemCFG.readCFG(aionPath + "system.cfg");
	if (!systemCFG.isReadSuccessful()){
		wxMessageBox("Unable to read Aion system.cfg file. Exiting.", "Error", wxOK);
		return false;
	}
	if (systemCFG.getProperty("g_chatlog") != "1"){
		
		wxMessageBox("Chat log disabled. Aion Grind Meter is trying to enable it now. You must restart your Aion client if it is already running.", "Notice", wxOK);
		systemCFG.setProperty("g_chatlog", "1");
				
		bool writeSuccess = systemCFG.writeCFG(aionPath + "system.cfg");
		if (!writeSuccess){
			wxMessageBox("Failed to enable Aion chatlog. If Aion was installed in Program Files folder, you must run Aion Grind Meter as an administrator.", "Error", wxOK);
			return false;
		}
	}
	return true;
}

bool MyApp::FileExists(string filename){
	bool fileExists;
	ifstream file;
	file.open(filename);	
	fileExists = !file.fail();		
	file.close();
	return fileExists;
}