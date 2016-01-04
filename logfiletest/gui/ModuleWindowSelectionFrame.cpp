#include "ModuleWindowSelectionFrame.h"


wxBEGIN_EVENT_TABLE(ModuleWindowSelectionFrame, wxFrame)    
	EVT_BUTTON(MODULE_WINDOW_BUTTON_0, ModuleWindowSelectionFrame::OnModuleWindowButton0)
    EVT_BUTTON(MODULE_WINDOW_BUTTON_1, ModuleWindowSelectionFrame::OnModuleWindowButton1)
	EVT_BUTTON(MODULE_WINDOW_BUTTON_2, ModuleWindowSelectionFrame::OnModuleWindowButton2)
	EVT_BUTTON(MODULE_WINDOW_BUTTON_3, ModuleWindowSelectionFrame::OnModuleWindowButton3)
	EVT_BUTTON(MODULE_WINDOW_BUTTON_4, ModuleWindowSelectionFrame::OnModuleWindowButton4)
	EVT_BUTTON(MODULE_WINDOW_BUTTON_5, ModuleWindowSelectionFrame::OnModuleWindowButton5)
	EVT_BUTTON(MODULE_WINDOW_BUTTON_6, ModuleWindowSelectionFrame::OnModuleWindowButton6)
	EVT_BUTTON(MODULE_WINDOW_BUTTON_7, ModuleWindowSelectionFrame::OnModuleWindowButton7)
	EVT_BUTTON(MODULE_WINDOW_BUTTON_8, ModuleWindowSelectionFrame::OnModuleWindowButton8)
	EVT_BUTTON(MODULE_WINDOW_BUTTON_9, ModuleWindowSelectionFrame::OnModuleWindowButton9)
	EVT_BUTTON(MODULE_WINDOW_BUTTON_10, ModuleWindowSelectionFrame::OnModuleWindowButton10)
	EVT_BUTTON(MODULE_WINDOW_BUTTON_11, ModuleWindowSelectionFrame::OnModuleWindowButton11)
	EVT_BUTTON(MODULE_WINDOW_BUTTON_12, ModuleWindowSelectionFrame::OnModuleWindowButton12)
	EVT_BUTTON(MODULE_WINDOW_BUTTON_13, ModuleWindowSelectionFrame::OnModuleWindowButton13)
	EVT_BUTTON(MODULE_WINDOW_BUTTON_14, ModuleWindowSelectionFrame::OnModuleWindowButton14)
	EVT_BUTTON(MODULE_WINDOW_BUTTON_15, ModuleWindowSelectionFrame::OnModuleWindowButton15)
	EVT_BUTTON(MODULE_WINDOW_BUTTON_16, ModuleWindowSelectionFrame::OnModuleWindowButton16)
	EVT_BUTTON(MODULE_WINDOW_BUTTON_17, ModuleWindowSelectionFrame::OnModuleWindowButton17)
	EVT_BUTTON(MODULE_WINDOW_BUTTON_18, ModuleWindowSelectionFrame::OnModuleWindowButton18)
	EVT_BUTTON(MODULE_WINDOW_BUTTON_19, ModuleWindowSelectionFrame::OnModuleWindowButton19)
	EVT_BUTTON(MODULE_WINDOW_BUTTON_20, ModuleWindowSelectionFrame::OnModuleWindowButton20)
	EVT_BUTTON(MODULE_WINDOW_BUTTON_21, ModuleWindowSelectionFrame::OnModuleWindowButton21)
	EVT_BUTTON(MODULE_WINDOW_BUTTON_22, ModuleWindowSelectionFrame::OnModuleWindowButton22)
	EVT_BUTTON(MODULE_WINDOW_BUTTON_23, ModuleWindowSelectionFrame::OnModuleWindowButton23)
	EVT_BUTTON(MODULE_WINDOW_BUTTON_24, ModuleWindowSelectionFrame::OnModuleWindowButton24)
	
	

	EVT_CLOSE(ModuleWindowSelectionFrame::OnClose)
wxEND_EVENT_TABLE()


ModuleWindowSelectionFrame::ModuleWindowSelectionFrame(int numRows, int numColumns): 
	wxFrame(NULL, wxID_ANY, "Open Window", wxDefaultPosition, wxDefaultSize, (wxDEFAULT_FRAME_STYLE | wxSTAY_ON_TOP) & ~(wxRESIZE_BORDER | wxMINIMIZE_BOX | wxMAXIMIZE_BOX)),
	moduleWindowButtons(numRows * numColumns, nullptr),
	moduleWindows(numRows * numColumns, nullptr)
{
	
	panel = new wxPanel(this);
	sizer = new wxGridSizer(numRows, numColumns, wxSize(1, 1));	
		
	panel->SetSizer(sizer);
	//panel->Show();

	//sizer->Add(new wxStaticText(this, -1, "testsetset"), wxEXPAND);
	//sizer->Add(new wxButton(this, -1, "sdfsdffsd"), wxEXPAND);
	
	
	//moduleWindowButtons = new wxButton*(numRows * numColumns); 
}

void ModuleWindowSelectionFrame::addModuleWindow(wxFrame* window, const wxString& name, int row, int column){

	wxButton* newButton = new wxButton(panel, row * sizer->GetCols() + column, name);
	//newButton->Show();
	sizer->Add(newButton, wxEXPAND);
	moduleWindowButtons[row * sizer->GetCols() + column] = newButton;
	moduleWindows[row * sizer->GetCols() + column] = window;
	//unique_ptr<wxButton>
	//sizer-
	
	//this->Layout();
	//panel->SetSize(this->GetClientSize());
	panel->Fit();
	this->Fit();
	
}

void ModuleWindowSelectionFrame::clickModuleWindowButton(int buttonNum){
	//wxMessageBox(moduleWindowButtons[buttonNum]->GetLabelText(), "test", wxOK);
	if (moduleWindows[buttonNum]->IsShown())
		moduleWindows[buttonNum]->Hide();
	else 
		moduleWindows[buttonNum]->Show();
}