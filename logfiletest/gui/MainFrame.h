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

#include "ProfessionLevelingFrame.h"
#include "ProfessionFrame.h"

#include "ItemAcquisitionFrame.h"
#include "ItemBundleFrame.h"
#include "ItemRollsFrame.h"

#include "MobKillsFrame.h"


#define APP_TITLE "Aion Grind Meter"
#define APP_VERSION "2.0.0"

#define MAINFRAME_WIDTH 230
#define MAINFRAME_HEIGHT 100
#define MAINPANEL_HEIGHT 40

#define LOG_FILE "Chat.log"

#define AION_BIN_32 "/bin32/AION.bin"
#define AION_BIN_64 "/bin64/AION.bin"

#define INI_FILE "aiongrindmeter.ini"

enum
{
    TIMER_ID
};


class MainFrame: public wxFrame
{

public:
	MainFrame(const wxPoint& pos);
	//MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);	
	
	wxDECLARE_EVENT_TABLE();
private:
	ExpModule expModule;
	ApModule apModule;
	KinahModule kinahModule;
	SoulHealerModule soulHealerModule;
	GpModule gpModule;

	HuntingModule huntingModule;
	ItemAcquisitionModule itemAcquisitionModule;
	
	ProfessionModule professionModule;

	LogFileUtility logFileUtility;

	wxTimer timer;

	ModuleWindowSelectionFrame* moduleWindowSelectionFrame;

	ExpFrame* expFrame;
	ApFrame* apFrame;

	ProfessionLevelingFrame* professionLevelingFrame;
	ProfessionFrame* gatherFrame;
	ProfessionFrame* craftFrame;
	
	ItemAcquisitionFrame* itemAcquisitionFrame;
	ItemBundleFrame* itemBundleFrame;
	ItemRollsFrame* itemRollsFrame;

	MobKillsFrame* mobKillsFrame;

	
	/*
	Frame* expFrame;
	Frame* apFrame;
	*/


	wxBoxSizer* parentSizer;
	wxPanel* panel;

	void OnTimer(wxTimerEvent& event);
	
	int ticksPerRefresh;
	int tickCounter;
};
