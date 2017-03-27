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
	MainFrame* mainFrame;
	string aionPath;

	wxFileConfig *config;
	wxConfigBase *conf;

	bool checkSystemCFG(string aionPath);
	bool FileExists(string filename);
	bool prepareToRun(string aionPath);
};

wxIMPLEMENT_APP(MyApp);


#define INI_FILE "aiongrindmeter.ini"
#define AION_BIN_32 "/bin32/AION.bin"
#define AION_BIN_64 "/bin64/AION.bin"

bool MyApp::OnInit()
{
	//Frame* frame = new Frame(string(APP_TITLE) + " " + string(APP_VERSION), wxPoint(-1, -1), wxSize(FRAME_WIDTH, FRAME_HEIGHT) );
	//frame->Show( true );
	
	

	//string aionPath;

	config = new wxFileConfig(wxEmptyString, wxEmptyString, INI_FILE, wxEmptyString, wxCONFIG_USE_RELATIVE_PATH);
	wxConfigBase::Set(config);
	conf = wxConfigBase::Get(false);

	//Try to load from current directory
	aionPath = "../";
	if (FileExists(aionPath + LOG_FILE) || FileExists(aionPath + AION_BIN_32) || FileExists(aionPath + AION_BIN_64)){
		return prepareToRun(aionPath);
	}	
	else{
		//Try to load from ini's directory
		if(conf) {			
			aionPath = conf->Read( wxT("AionPath"));		      			
		}
		if (/*FileExists(aionPath + LOG_FILE) || */FileExists(aionPath + AION_BIN_32) || FileExists(aionPath + AION_BIN_64)){
			
			return prepareToRun(aionPath);
		}
		// Ask for user to browser for Aion's directory
		else{
			wxDirDialog dlg(NULL, "Locate your AION directory.\n(It should contain bin32 and/or bin64 subdirectories in it.)", "wxEmptyString", wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
			int success = dlg.ShowModal();
			aionPath = dlg.GetPath() + '/';
			if (success != wxID_OK){ // Cancel button
				//Close(true);
				return false;
			}
			else if (!FileExists(aionPath + AION_BIN_32) &&  !FileExists(aionPath + AION_BIN_64)){
				wxMessageBox("This does not appear to be an Aion directory.\nThe correct Aion directory should contain bin32 and/or bin64 subdirectories in it.", "Error", wxOK);
				return false;
			}
			else{ // Write directory choice to ini
				conf->Write(wxT("AionPath"), aionPath.c_str());
				return prepareToRun(aionPath);
			}
			
		}

	}

	return true;
}

bool MyApp::prepareToRun(string aionPath){
	if (checkSystemCFG(aionPath)){		
		
		mainFrame = new MainFrame(aionPath, wxDefaultPosition);
		mainFrame->Show(true);
		return true;
	}
	else return false;
}

bool MyApp::checkSystemCFG(string aionPath){
	SystemCFG systemCFG;
	systemCFG.readCFG(aionPath + "system.cfg");
	if (!systemCFG.isReadSuccessful()){
		wxMessageBox("Unable to read Aion system.cfg file. Exiting.", "Error", wxOK);
		return false;
	}
	if (systemCFG.getProperty("g_chatlog") != "1"){
		
		wxMessageBox("Chat log disabled.\nAion Grind Meter is trying to enable it now.\nYou must restart your Aion client if it is already running.", "Notice", wxOK);
		systemCFG.setProperty("g_chatlog", "1");
				
		bool writeSuccess = systemCFG.writeCFG(aionPath + "system.cfg");
		if (!writeSuccess){
			wxMessageBox("Failed to enable Aion chatlog.\nIf Aion was installed in Program Files folder, you must run Aion Grind Meter as an administrator.", "Error", wxOK);
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