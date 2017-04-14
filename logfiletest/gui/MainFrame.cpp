#include <string>
#include <ctime>
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
	wxFrame(NULL, 
		wxID_ANY, 
		string(APP_TITLE) + " " + string(APP_VERSION), 
		pos, 
		wxSize(MAINFRAME_WIDTH, MAINFRAME_HEIGHT), 
		(wxDEFAULT_FRAME_STYLE | wxSTAY_ON_TOP) & ~(wxRESIZE_BORDER | wxMINIMIZE_BOX | wxMAXIMIZE_BOX)
	),
	started(false),
	aionPath(aionPath),
	expModule(shared_ptr<ExpChart>(new ExpChartKR51())),
	apModule(shared_ptr<ApChart>(new ApChart())),
	timer(this, TIMER_ID),
	soulHealerModule(expModule, apModule, kinahModule),
	ticksPerRefresh(2), 
	tickCounter(0)		
{
	//For NA builds, comment out following line. For EU builds, enable following line.
	//LANGUAGE_MANAGER.setToEnglishEU();

	parentSizer = new wxBoxSizer(wxVERTICAL);
	panel = new wxPanel(this, wxID_ANY);
	
	moduleWindowSelectionFrame = new ModuleWindowSelectionFrame(this, 6, 3);
	moduleWindowSelectionFrame->SetTitle("Open Window - " + string(APP_TITLE) + " " + string(APP_VERSION) + " " + LANGUAGE_MANAGER.getCurrentLanguage().getLanguageCode());
	//moduleWindowSelectionFrame->Show();

	expFrame = new ExpFrame(this, expModule, soulHealerModule, wxDefaultPosition);
	//expFrame->Show();
	moduleWindowSelectionFrame->addModuleWindow(expFrame, "XP", 0, 0);

	apFrame = new ApFrame(this,apModule, soulHealerModule, wxDefaultPosition);
	//apFrame->Show();
	moduleWindowSelectionFrame->addModuleWindow(apFrame, "AP", 0, 1);

	gpFrame = new GpFrame(this,gpModule, wxDefaultPosition);
	//gpFrame->Show();
	moduleWindowSelectionFrame->addModuleWindow(gpFrame, "GP", 0, 2);
	
	kinahFrame = new KinahFrame(this,kinahModule, wxDefaultPosition);
	moduleWindowSelectionFrame->addModuleWindow(kinahFrame, "Kinah", 1, 0);

	professionLevelingFrame = new ProfessionLevelingFrame(this,professionModule, wxDefaultPosition);
	//professionLevelingFrame->Show();
	moduleWindowSelectionFrame->addModuleWindow(professionLevelingFrame, "Gather/Craft Lvling", 1, 1);

	gatherFrame = new ProfessionFrame(this,professionModule, GATHER, wxDefaultPosition);
	//gatherFrame->Show();
	moduleWindowSelectionFrame->addModuleWindow(gatherFrame, "Gathering", 1, 2);

	craftFrame = new ProfessionFrame(this,professionModule, CRAFT, wxDefaultPosition);
	//craftFrame->Show();
	moduleWindowSelectionFrame->addModuleWindow(craftFrame, "Crafting", 2, 0);

	itemAcquisitionFrame = new ItemAcquisitionFrame(this,itemAcquisitionModule, wxDefaultPosition);
	//itemAcquisitionFrame->Show();
	moduleWindowSelectionFrame->addModuleWindow(itemAcquisitionFrame, "Items Acquired", 2, 1);

	itemConsumptionFrame = new ItemConsumptionFrame(this,itemAcquisitionModule, wxDefaultPosition);
	moduleWindowSelectionFrame->addModuleWindow(itemConsumptionFrame, "Items Consumed", 2, 2);

	itemBundleFrame = new ItemBundleFrame(this,itemAcquisitionModule, wxDefaultPosition);
	//itemBundleFrame->Show();
	moduleWindowSelectionFrame->addModuleWindow(itemBundleFrame, "Bundles Opened", 3, 0);

	itemRollsFrame = new ItemRollsFrame(this,itemAcquisitionModule, wxDefaultPosition);
	//itemRollsFrame->Show();
	moduleWindowSelectionFrame->addModuleWindow(itemRollsFrame, "Item Rolls", 3, 1);

	mobKillsFrame = new MobKillsFrame(this,huntingModule, wxDefaultPosition);
	//mobKillsFrame->Show();
	moduleWindowSelectionFrame->addModuleWindow(mobKillsFrame, "Mob Kills", 3, 2);

	playerKillsFrame = new PlayerKillsFrame(this,huntingModule, soulHealerModule, wxDefaultPosition);
	//mobKillsFrame->Show();
	moduleWindowSelectionFrame->addModuleWindow(playerKillsFrame, "Player Kills", 4, 0);

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


	float secondsSinceLastMessage = (clock() - logFileUtility.getTimestampOfLatestMessage()) / CLOCKS_PER_SEC;

	//Start timer if logFileUtility reads first new line from chat log
	if (!started && logFileUtility.getTimestampOfLatestMessage() != -1 && secondsSinceLastMessage <= 10){
		expFrame->Show();
		apFrame->Show();

		expModule.timer.start();
		apModule.timer.start();
		gpModule.timer.start();
		kinahModule.timer.start();
		huntingModule.timer.start();
		itemAcquisitionModule.timer.start();
		professionModule.timer.start();
		started = true;
	}

	/*
	int secondsBeforePause = 30;
	//Pause timer after 30 seconds of inactivity
	if (started && secondsSinceLastMessage > secondsBeforePause){
		expModule.timer.stopWithAdjustmentSeconds(-secondsBeforePause + 12);
		apModule.timer.stopWithAdjustmentSeconds(-secondsBeforePause + 12);
		gpModule.timer.stopWithAdjustmentSeconds(-secondsBeforePause + 12);
		kinahModule.timer.stopWithAdjustmentSeconds(-secondsBeforePause + 12);
		huntingModule.timer.stopWithAdjustmentSeconds(-secondsBeforePause + 12);
		itemAcquisitionModule.timer.stopWithAdjustmentSeconds(-secondsBeforePause + 12);
		professionModule.timer.stopWithAdjustmentSeconds(-secondsBeforePause + 12);
		started = false;
	}
	*/

	//Refresh windows every ticksPerRefresh ticks
	if (tickCounter >= ticksPerRefresh){
		expFrame->refresh();
		apFrame->refresh();
		gpFrame->refresh();
		kinahFrame->refresh();
		itemAcquisitionFrame->refresh();
		itemConsumptionFrame->refresh();
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

	//Automatic chatlog re-enablement
	systemCFG.readCFG(aionPath + "system.cfg");
	
	if (systemCFG.getProperty("g_chatlog") != "1"){
				
		systemCFG.setProperty("g_chatlog", "1");
				
		bool writeSuccess = systemCFG.writeCFG(aionPath + "system.cfg");
		if (writeSuccess){
			wxNotificationMessage systemCFGEnableSuccessMessage(APP_TITLE, "Chatlog re-enabled after it was just disabled by Aion client.", this);			
			systemCFGEnableSuccessMessage.Show();
		}
		else {
			wxNotificationMessage systemCFGEnableFailureMessage(APP_TITLE, "Chatlog disabled by Aion client. Aion Grind Meter was unable to re-enable it.", this);
			systemCFGEnableFailureMessage.Show();
			this->Close();
		}
		
	}
	
}

void MainFrame::OnClose(wxCloseEvent& event){

	wxMessageDialog exitDialog(this, "Exit Aion Grind Meter?\n", "Exit", wxOK | wxCANCEL | wxCANCEL_DEFAULT);
	if (exitDialog.ShowModal() == wxID_OK){
		tickCounter = -99999;
		this->DestroyChildren();
		this->Destroy();
	}
	
}