#ifndef MODULE_WINDOW_SELECTION_FRAME_H
#define MODULE_WINDOW_SELECTION_FRAME_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/fileconf.h>
#include <wx/sizer.h>
#include <wx/gbsizer.h>


#include <vector>
using namespace std;

enum{
	MODULE_WINDOW_BUTTON_0,
	MODULE_WINDOW_BUTTON_1,
	MODULE_WINDOW_BUTTON_2,
	MODULE_WINDOW_BUTTON_3,
	MODULE_WINDOW_BUTTON_4,
	MODULE_WINDOW_BUTTON_5,
	MODULE_WINDOW_BUTTON_6,
	MODULE_WINDOW_BUTTON_7,
	MODULE_WINDOW_BUTTON_8,
	MODULE_WINDOW_BUTTON_9,
	MODULE_WINDOW_BUTTON_10,
	MODULE_WINDOW_BUTTON_11,
	MODULE_WINDOW_BUTTON_12,
	MODULE_WINDOW_BUTTON_13,
	MODULE_WINDOW_BUTTON_14,
	MODULE_WINDOW_BUTTON_15,
	MODULE_WINDOW_BUTTON_16,
	MODULE_WINDOW_BUTTON_17,
	MODULE_WINDOW_BUTTON_18,
	MODULE_WINDOW_BUTTON_19,
	MODULE_WINDOW_BUTTON_20,
	MODULE_WINDOW_BUTTON_21,
	MODULE_WINDOW_BUTTON_22,
	MODULE_WINDOW_BUTTON_23,
	MODULE_WINDOW_BUTTON_24
	
};

class ModuleWindowSelectionFrame: public wxFrame {
public:
	ModuleWindowSelectionFrame(int numRows, int numColumns);
	void addModuleWindow(wxFrame* window, const wxString& name, int row, int column);

	void finishAddingButtons() {
		panel->SetSizer(sizer);
		panel->Fit();
		this->Fit();
	}

private:

	wxPanel* panel;
	wxFlexGridSizer* sizer;
	
	vector<wxButton*> moduleWindowButtons;
	vector<wxFrame*> moduleWindows;

	void clickModuleWindowButton(int buttonNum);
	
	void OnModuleWindowButton0(wxCommandEvent& event) {clickModuleWindowButton(0);}
	void OnModuleWindowButton1(wxCommandEvent& event) {clickModuleWindowButton(1);}
	void OnModuleWindowButton2(wxCommandEvent& event) {clickModuleWindowButton(2);}
	void OnModuleWindowButton3(wxCommandEvent& event) {clickModuleWindowButton(3);}
	void OnModuleWindowButton4(wxCommandEvent& event) {clickModuleWindowButton(4);}
	void OnModuleWindowButton5(wxCommandEvent& event) {clickModuleWindowButton(5);}
	void OnModuleWindowButton6(wxCommandEvent& event) {clickModuleWindowButton(6);}
	void OnModuleWindowButton7(wxCommandEvent& event) {clickModuleWindowButton(7);}
	void OnModuleWindowButton8(wxCommandEvent& event) {clickModuleWindowButton(8);}
	void OnModuleWindowButton9(wxCommandEvent& event) {clickModuleWindowButton(9);}
	void OnModuleWindowButton10(wxCommandEvent& event) {clickModuleWindowButton(10);}
	void OnModuleWindowButton11(wxCommandEvent& event) {clickModuleWindowButton(11);}
	void OnModuleWindowButton12(wxCommandEvent& event) {clickModuleWindowButton(12);}
	void OnModuleWindowButton13(wxCommandEvent& event) {clickModuleWindowButton(13);}
	void OnModuleWindowButton14(wxCommandEvent& event) {clickModuleWindowButton(14);}
	void OnModuleWindowButton15(wxCommandEvent& event) {clickModuleWindowButton(15);}
	void OnModuleWindowButton16(wxCommandEvent& event) {clickModuleWindowButton(16);}
	void OnModuleWindowButton17(wxCommandEvent& event) {clickModuleWindowButton(17);}
	void OnModuleWindowButton18(wxCommandEvent& event) {clickModuleWindowButton(18);}
	void OnModuleWindowButton19(wxCommandEvent& event) {clickModuleWindowButton(19);}
	void OnModuleWindowButton20(wxCommandEvent& event) {clickModuleWindowButton(20);}
	void OnModuleWindowButton21(wxCommandEvent& event) {clickModuleWindowButton(21);}
	void OnModuleWindowButton22(wxCommandEvent& event) {clickModuleWindowButton(22);}
	void OnModuleWindowButton23(wxCommandEvent& event) {clickModuleWindowButton(23);}
	void OnModuleWindowButton24(wxCommandEvent& event) {clickModuleWindowButton(24);}
	
	void OnClose(wxCloseEvent& event) {this->Hide();}

	wxDECLARE_EVENT_TABLE();
	
};

#endif