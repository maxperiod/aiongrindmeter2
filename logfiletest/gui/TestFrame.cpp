#include "TestFrame.h"

wxBEGIN_EVENT_TABLE(TestFrame, wxFrame)    
    EVT_SIZE(TestFrame::OnSize)
	EVT_CLOSE(TestFrame::OnClose)
wxEND_EVENT_TABLE()

TestFrame::TestFrame(wxWindow* parent, const wxPoint& pos): wxFrame(parent, wxID_ANY, "test", pos, wxDefaultSize, (wxDEFAULT_FRAME_STYLE | wxSTAY_ON_TOP) & ~(wxMINIMIZE_BOX | wxMAXIMIZE_BOX))
{
	panel = new wxPanel(this);
	
	parentSizer = new wxBoxSizer(wxVERTICAL);
		
	textCtrl = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY | wxTE_RICH2);

	panel->SetSizer(parentSizer);
	
	
}

void TestFrame::refresh(){

}


void TestFrame::OnSize(wxSizeEvent& event){
	
	panel->SetSize(this->GetClientSize());
	
	textCtrl->SetSize(this->GetClientSize());
	
}

