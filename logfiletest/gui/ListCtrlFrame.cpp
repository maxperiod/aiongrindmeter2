#include "ListCtrlFrame.h"
#include "../stringFunctions.h"

wxBEGIN_EVENT_TABLE(ListCtrlFrame, wxFrame)    
    EVT_SIZE(ListCtrlFrame::OnSize)
	EVT_CLOSE(ListCtrlFrame::OnClose)
wxEND_EVENT_TABLE()

#define SCROLLBAR_PIXELS 25

ListCtrlFrame::ListCtrlFrame(wxWindow* parent, const wxPoint& pos) :
	 wxFrame(parent, wxID_ANY, "ffffff", pos, wxDefaultSize, (wxDEFAULT_FRAME_STYLE | wxSTAY_ON_TOP) & ~(wxMINIMIZE_BOX | wxMAXIMIZE_BOX)), 
		 nameColumnForVariableWidth(-1), totalFixedColumnsWidth(0)

{
	
	panel = new wxPanel(this);//, wxID_ANY, wxDefaultPosition, this->GetSize());
	
	parentSizer = new wxBoxSizer(wxVERTICAL);



	//parentSizer->Add(panel, 0, wxEXPAND, 0); //wxALL | wxALIGN_CENTER);
	
	//parentSizer->Add(new wxStaticText(this, -1, wxT("Craft Lvl Ups"))); 
	//parentSizer->Add(new wxButton(this, wxID_ANY, "sdlkfjsdf")) ; 
	
	listCtrl = new wxListCtrl(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
	/*
	listCtrl->AppendColumn("Item name", wxLIST_FORMAT_LEFT, 170);
	listCtrl->AppendColumn("S", wxLIST_FORMAT_RIGHT, 40);
	listCtrl->AppendColumn("F", wxLIST_FORMAT_RIGHT, 40);
	listCtrl->AppendColumn("C", wxLIST_FORMAT_RIGHT, 40);
	
	if (type == CRAFT) listCtrl->AppendColumn("Proc", wxLIST_FORMAT_RIGHT, 40);

	listCtrl->AppendColumn("Per Hour", wxLIST_FORMAT_RIGHT, 70);

	parentSizer->Add(listCtrl, 0, wxEXPAND | wxALL, 0);
	*/
	/*
	if (type == GATHER){
		this->SetSize(375, 150);
		panel->SetSize(375, 150);
		listCtrl->SetSize(375, 150);
	}
	else {
		this->SetSize(415, 150);
		panel->SetSize(415, 150);
		listCtrl->SetSize(415, 150);
	}
	*/
	
	//panel->Show();
	//this->SetSizer(parentSizer);
	panel->SetSizer(parentSizer);
	//panel->Layout();
		
	//panel->SetSizerAndFit(parentSizer);
	//this->Layout();
	
}

void ListCtrlFrame::addColumn(const wxString& columnName, int width, wxListColumnFormat format){
	listCtrl->AppendColumn(columnName, wxLIST_FORMAT_LEFT, width);
	totalFixedColumnsWidth += width;
}

void ListCtrlFrame::setNameColumnForVariableWidth(int columnNumber){
	if (columnNumber < nameColumnForVariableWidth < listCtrl->GetColumnCount()){
		nameColumnForVariableWidth = columnNumber;
		totalFixedColumnsWidth -= listCtrl->GetColumnWidth(nameColumnForVariableWidth);
	}
}

void ListCtrlFrame::OnSize(wxSizeEvent& event){
	
	//panel->SetSizerAndFit(parentSizer);
	//int deltaX = event.GetSize().GetX() - this->GetClientSize().GetX();

	panel->SetSize(this->GetClientSize());
	
	listCtrl->SetSize(this->GetClientSize());
	if (nameColumnForVariableWidth >= 0) {
		//int deltaX = panel->GetSize().GetX() - totalFixedColumnsWidth);
		listCtrl->SetColumnWidth(nameColumnForVariableWidth, panel->GetSize().GetX() - totalFixedColumnsWidth - SCROLLBAR_PIXELS);		
	}
	//	listCtrl->SetSize(wxSize(event.GetSize().GetX() - 20, event.GetSize().GetY() - 40));

	
	//this->Layout();
	
}