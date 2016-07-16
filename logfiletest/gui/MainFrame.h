#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/fileconf.h>
#include <wx/gbsizer.h>


#include "../parser/LogFileUtility.h"

#include "../modules/ExpModule.h"
#include "../modules/ApModule.h"
#include "../modules/KinahModule.h"
#include "../modules/SoulHealerModule.h"
#include "../modules/GpModule.h"

#include "../modules/HuntingModule.h"
#include "../modules/ItemAcquisitionModule.h"

#include "../modules/ProfessionModule.h"

#include "ModuleWindowSelectionFrame.h"

#include "ExpFrame.h"
#include "ApFrame.h"
#include "GpFrame.h"
#include "KinahFrame.h"

#include "ProfessionLevelingFrame.h"
#include "ProfessionFrame.h"

#include "ItemAcquisitionFrame.h"
#include "ItemBundleFrame.h"
#include "ItemRollsFrame.h"

#include "MobKillsFrame.h"
#include "PlayerKillsFrame.h"

#include "../lookups/ExpChartKR51.h"
#include "../lookups/ExpChartNA40.h"
#include "../lookups/ExpChartEU49.h"

#include "TestFrame.h"

#define APP_TITLE "Aion Grind Meter"
#define APP_VERSION "2.0.1-alpha"

#define MAINFRAME_WIDTH 230
#define MAINFRAME_HEIGHT 100
#define MAINPANEL_HEIGHT 40

#define LOG_FILE "Chat.log"

#define AION_BIN_32 "/bin32/AION.bin"
#define AION_BIN_64 "/bin64/AION.bin"

#define INI_FILE "aiongrindmeter.ini"

enum
{
    TIMER_ID,
	WINDOW_MENU_BUTTON_ID
};


class MainFrame: public wxFrame
{

public:
	MainFrame(string& aionPath, const wxPoint& pos);
	//MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);	
	
	wxDECLARE_EVENT_TABLE();
private:
	ExpModule expModule;
	ApModule apModule;
	GpModule gpModule;
	KinahModule kinahModule;
	SoulHealerModule soulHealerModule;

	HuntingModule huntingModule;
	ItemAcquisitionModule itemAcquisitionModule;
	
	ProfessionModule professionModule;

	LogFileUtility logFileUtility;

	ApChart apChart;

	wxTimer timer;

	ModuleWindowSelectionFrame* moduleWindowSelectionFrame;

	ExpFrame* expFrame;
	ApFrame* apFrame;
	GpFrame* gpFrame;
	KinahFrame* kinahFrame;

	ProfessionLevelingFrame* professionLevelingFrame;
	ProfessionFrame* gatherFrame;
	ProfessionFrame* craftFrame;
	
	ItemAcquisitionFrame* itemAcquisitionFrame;
	ItemBundleFrame* itemBundleFrame;
	ItemRollsFrame* itemRollsFrame;

	MobKillsFrame* mobKillsFrame;
	PlayerKillsFrame* playerKillsFrame;

	TestFrame* testFrame;
	/*
	Frame* expFrame;
	Frame* apFrame;
	*/


	wxBoxSizer* parentSizer;
	wxPanel* panel;

	wxButton* windowMenuButton;

	void OnTimer(wxTimerEvent& event);
	void OnWindowMenuButton(wxCommandEvent& event) {moduleWindowSelectionFrame->Show();}

	void OnClose(wxCloseEvent& event);

	int ticksPerRefresh;
	int tickCounter;
};

