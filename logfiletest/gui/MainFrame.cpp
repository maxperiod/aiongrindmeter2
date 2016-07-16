#include <string>
using namespace std;

#include "MainFrame.h"
#include "../stringFunctions.h"

//#include "elements/ValuePerHourLine.h"

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_TIMER(TIMER_ID, MainFrame::OnTimer)
	EVT_BUTTON(WINDOW_MENU_BUTTON_ID, MainFrame::OnWindowMenuButton)
	EVT_CLOSE(MainFrame::OnClose)
END_EVENT_TABLE()


MainFrame::MainFrame(string& aionPath, const wxPoint& pos):
	wxFrame(NULL, wxID_ANY, string(APP_TITLE) + " " + string(APP_VERSION), pos, wxSize(MAINFRAME_WIDTH, MAINFRAME_HEIGHT), 
			(wxDEFAULT_FRAME_STYLE | wxSTAY_ON_TOP) & ~(wxRESIZE_BORDER | wxMINIMIZE_BOX | wxMAXIMIZE_BOX)),
		expModule(shared_ptr<ExpChart>(new ExpChartKR51())),
		apModule(shared_ptr<ApChart>(new ApChart())),
		timer(this, TIMER_ID),
		soulHealerModule(expModule, apModule, kinahModule),
		ticksPerRefresh(2), 
		tickCounter(0)		
{
	//LANGUAGE_MANAGER.setToEnglishEU();

	parentSizer = new wxBoxSizer(wxVERTICAL);
	panel = new wxPanel(this, wxID_ANY);

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
	moduleWindowSelectionFrame = new ModuleWindowSelectionFrame(this, 5, 3);
	//moduleWindowSelectionFrame->Show();

	expFrame = new ExpFrame(this, expModule, soulHealerModule, wxDefaultPosition);
	expFrame->Show();
	moduleWindowSelectionFrame->addModuleWindow(expFrame, "XP", 0, 0);

	apFrame = new ApFrame(this,apModule, soulHealerModule, wxDefaultPosition);
	apFrame->Show();
	moduleWindowSelectionFrame->addModuleWindow(apFrame, "AP", 1, 0);

	gpFrame = new GpFrame(this,gpModule, wxDefaultPosition);
	//gpFrame->Show();
	moduleWindowSelectionFrame->addModuleWindow(gpFrame, "GP", 2, 0);
	
	kinahFrame = new KinahFrame(this,kinahModule, wxDefaultPosition);
	moduleWindowSelectionFrame->addModuleWindow(kinahFrame, "Kinah", 3, 0);

	professionLevelingFrame = new ProfessionLevelingFrame(this,professionModule, wxDefaultPosition);
	//professionLevelingFrame->Show();
	moduleWindowSelectionFrame->addModuleWindow(professionLevelingFrame, "Gather/Craft Lvling", 0, 1);

	gatherFrame = new ProfessionFrame(this,professionModule, GATHER, wxDefaultPosition);
	//gatherFrame->Show();
	moduleWindowSelectionFrame->addModuleWindow(gatherFrame, "Gathering", 1, 1);

	craftFrame = new ProfessionFrame(this,professionModule, CRAFT, wxDefaultPosition);
	//craftFrame->Show();
	moduleWindowSelectionFrame->addModuleWindow(craftFrame, "Crafting", 2, 1);

	itemAcquisitionFrame = new ItemAcquisitionFrame(this,itemAcquisitionModule, wxDefaultPosition);
	//itemAcquisitionFrame->Show();
	moduleWindowSelectionFrame->addModuleWindow(itemAcquisitionFrame, "Items Acquired", 0, 2);

	itemBundleFrame = new ItemBundleFrame(this,itemAcquisitionModule, wxDefaultPosition);
	//itemBundleFrame->Show();
	moduleWindowSelectionFrame->addModuleWindow(itemBundleFrame, "Bundles Opened", 1, 2);

	itemRollsFrame = new ItemRollsFrame(this,itemAcquisitionModule, wxDefaultPosition);
	//itemRollsFrame->Show();
	moduleWindowSelectionFrame->addModuleWindow(itemRollsFrame, "Item Rolls", 2, 2);

	mobKillsFrame = new MobKillsFrame(this,huntingModule, wxDefaultPosition);
	//mobKillsFrame->Show();
	moduleWindowSelectionFrame->addModuleWindow(mobKillsFrame, "Mob Kills", 3, 2);

	playerKillsFrame = new PlayerKillsFrame(this,huntingModule, soulHealerModule, wxDefaultPosition);
	//mobKillsFrame->Show();
	moduleWindowSelectionFrame->addModuleWindow(playerKillsFrame, "Player Kills", 4, 2);

	moduleWindowSelectionFrame->finishAddingButtons();
	//mobKillsFrame->Show();

	testFrame = new TestFrame(this, wxDefaultPosition);
	//testFrame->Show();
	
	windowMenuButton = new wxButton(panel, WINDOW_MENU_BUTTON_ID, "Open Window");
	/*
	wxFrame* crapFrame = new wxFrame("sdkljf", wxPoint(-1, -1), wxSize(FRAME_WIDTH, FRAME_HEIGHT);
	crapFrame->SetSizer(new wxBoxSizer(wxVERTICAL));
	crapFrame->GetSizer()->Add(new ValuePerHourLine(this, wxID_ANY));
	*/
	logFileUtility.setAionDirectory(aionPath);

	logFileUtility.registerModule(soulHealerModule);
	logFileUtility.registerModule(expModule);
	logFileUtility.registerModule(apModule);
	logFileUtility.registerModule(kinahModule);	
	logFileUtility.registerModule(gpModule);

	logFileUtility.registerModule(huntingModule);
	logFileUtility.registerModule(itemAcquisitionModule);
	
	logFileUtility.registerModule(professionModule);

	timer.Start(500);

	panel->Fit();
	this->Fit();
}

void MainFrame::OnTimer(wxTimerEvent& event){
	timer.Start(500);
	logFileUtility.parseLogFile();

	if (tickCounter >= ticksPerRefresh){
		expFrame->refresh();
		apFrame->refresh();
		gpFrame->refresh();
		kinahFrame->refresh();
		itemAcquisitionFrame->refresh();
		professionLevelingFrame->refresh();
		itemBundleFrame->refresh();
		gatherFrame->refresh();
		craftFrame->refresh();
		mobKillsFrame->refresh();
		playerKillsFrame->refresh();
		itemRollsFrame->refresh();
		this->SetTitle(formatElapsedTime(itemAcquisitionModule.timer.getElapsedTime()));
		tickCounter = 0;
	}
	tickCounter ++;
	
}

void MainFrame::OnClose(wxCloseEvent& event){
	tickCounter = -99999;
	this->DestroyChildren();
	this->Destroy();
	
}