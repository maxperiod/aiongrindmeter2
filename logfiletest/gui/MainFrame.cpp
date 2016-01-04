#include <string>
using namespace std;

#include "MainFrame.h"
#include "../stringFunctions.h"

//#include "elements/ValuePerHourLine.h"

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_TIMER(TIMER_ID, MainFrame::OnTimer)
END_EVENT_TABLE()


MainFrame::MainFrame(const wxPoint& pos):
	wxFrame(NULL, wxID_ANY, string(APP_TITLE) + " " + string(APP_VERSION), pos, wxSize(MAINFRAME_WIDTH, MAINFRAME_HEIGHT), 
			(wxDEFAULT_FRAME_STYLE | wxSTAY_ON_TOP) & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)),
		timer(this, TIMER_ID),
		soulHealerModule(expModule, apModule, kinahModule),
		ticksPerRefresh(2), 
		tickCounter(0)
{
	parentSizer = new wxBoxSizer(wxVERTICAL);
	panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(MAINFRAME_WIDTH, MAINFRAME_HEIGHT));

	/*
	expFrame = new ExpFrame("XP", wxPoint(-1, -1), wxSize(FRAME_WIDTH, FRAME_HEIGHT), 
		expModule, 
		soulHealerModule,
		huntingModule,
		itemAcquisitionModule,
		"file.txt"
	);
	expFrame->Show(true);
	*/
	moduleWindowSelectionFrame = new ModuleWindowSelectionFrame(5, 3);
	moduleWindowSelectionFrame->Show();

	expFrame = new ExpFrame(expModule, soulHealerModule, wxDefaultPosition);
	expFrame->Show();
	moduleWindowSelectionFrame->addModuleWindow(expFrame, "XP", 0, 0);

	apFrame = new ApFrame(apModule, soulHealerModule, wxDefaultPosition);
	apFrame->Show();
	moduleWindowSelectionFrame->addModuleWindow(apFrame, "AP", 1, 0);

	professionLevelingFrame = new ProfessionLevelingFrame(professionModule, wxDefaultPosition);
	//professionLevelingFrame->Show();
	moduleWindowSelectionFrame->addModuleWindow(professionLevelingFrame, "Prof Leveling", 0, 1);

	gatherFrame = new ProfessionFrame(professionModule, GATHER, wxDefaultPosition);
	//gatherFrame->Show();
	moduleWindowSelectionFrame->addModuleWindow(gatherFrame, "Gathering", 1, 1);

	craftFrame = new ProfessionFrame(professionModule, CRAFT, wxDefaultPosition);
	//craftFrame->Show();
	moduleWindowSelectionFrame->addModuleWindow(craftFrame, "Crafting", 2, 1);

	itemAcquisitionFrame = new ItemAcquisitionFrame(itemAcquisitionModule, wxDefaultPosition);
	//itemAcquisitionFrame->Show();
	moduleWindowSelectionFrame->addModuleWindow(itemAcquisitionFrame, "Items Acquired", 0, 2);

	itemBundleFrame = new ItemBundleFrame(itemAcquisitionModule, wxDefaultPosition);
	//itemBundleFrame->Show();
	moduleWindowSelectionFrame->addModuleWindow(itemBundleFrame, "Bundles Opened", 1, 2);

	itemRollsFrame = new ItemRollsFrame(itemAcquisitionModule, wxDefaultPosition);
	//itemRollsFrame->Show();
	moduleWindowSelectionFrame->addModuleWindow(itemRollsFrame, "Item Rolls", 2, 2);

	mobKillsFrame = new MobKillsFrame(huntingModule, wxDefaultPosition);
	//mobKillsFrame->Show();
	moduleWindowSelectionFrame->addModuleWindow(mobKillsFrame, "Mob Kills", 3, 2);

	
	/*
	wxFrame* crapFrame = new wxFrame("sdkljf", wxPoint(-1, -1), wxSize(FRAME_WIDTH, FRAME_HEIGHT);
	crapFrame->SetSizer(new wxBoxSizer(wxVERTICAL));
	crapFrame->GetSizer()->Add(new ValuePerHourLine(this, wxID_ANY));
	*/
	logFileUtility.setAionDirectory("d:/Aion/");

	logFileUtility.registerModule(soulHealerModule);
	logFileUtility.registerModule(expModule);
	logFileUtility.registerModule(apModule);
	logFileUtility.registerModule(kinahModule);	
	logFileUtility.registerModule(gpModule);

	logFileUtility.registerModule(huntingModule);
	logFileUtility.registerModule(itemAcquisitionModule);
	
	logFileUtility.registerModule(professionModule);

	timer.Start(500);

}

void MainFrame::OnTimer(wxTimerEvent& event){
	timer.Start(500);
	logFileUtility.parseLogFile();

	if (tickCounter >= ticksPerRefresh){
		expFrame->refresh();
		apFrame->refresh();
		itemAcquisitionFrame->refresh();
		professionLevelingFrame->refresh();
		itemBundleFrame->refresh();
		gatherFrame->refresh();
		craftFrame->refresh();
		mobKillsFrame->refresh();
		itemRollsFrame->refresh();
		this->SetTitle(formatElapsedTime(itemAcquisitionModule.timer.getElapsedTime()));
		tickCounter = 0;
	}
	tickCounter ++;
	
}