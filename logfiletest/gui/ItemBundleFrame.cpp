#include "ItemBundleFrame.h"

wxBEGIN_EVENT_TABLE(ItemBundleFrame, wxFrame)    
    EVT_SIZE(ItemBundleFrame::OnSize)
	EVT_CLOSE(ItemBundleFrame::OnClose)
wxEND_EVENT_TABLE()

ItemBundleFrame::ItemBundleFrame(ItemAcquisitionModule& itemAcquisitionModule, const wxPoint& pos) :
	 wxFrame(NULL, wxID_ANY, "Containers Opened", pos, wxDefaultSize, (wxDEFAULT_FRAME_STYLE | wxSTAY_ON_TOP) & ~(wxMAXIMIZE_BOX))  
		 , itemIDReader("itemnames.txt")
{
	this->itemAcquisitionModule = &itemAcquisitionModule;

	panel = new wxPanel(this);//, wxID_ANY, wxDefaultPosition, this->GetSize());
	
	parentSizer = new wxBoxSizer(wxVERTICAL);


	
	treeCtrl = new wxTreeCtrl(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, !wxTR_HAS_BUTTONS | wxTR_HIDE_ROOT);

	panel->SetSizer(parentSizer);
	root = treeCtrl->AddRoot("");
	/*
	wxTreeItemId id = treeCtrl->AppendItem(root, "Survivors x199 (800 / h)");
	treeCtrl->AppendItem(id, "123456789 Samsung Galaxy Tab 2 x2");
	treeCtrl->AppendItem(id, "987654321 Dark Luke x155");
	treeCtrl->ExpandAll();
	treeCtrl->DeleteChildren(root);
	
	id = treeCtrl->AppendItem(root, "Survivors x199 (800 / h)");
	treeCtrl->AppendItem(id, "123456789 Samsung Galaxy Tab 2 x2");
	treeCtrl->AppendItem(id, "987654321 Dark Luke x156");
	treeCtrl->ExpandAll();
	*/
}

void ItemBundleFrame::refresh(){
	
	treeCtrl->DeleteChildren(root);
	
	for (map<string, CounterEntry>::iterator iter = itemAcquisitionModule->containersOpened.begin();
				iter != itemAcquisitionModule->containersOpened.end(); iter ++)
	{
			
		wxString itemLine;
			
		itemLine << iter->first << " x" << iter->second.numGained;
		if (iter->second.numPackets >= 3) 
			itemLine <<"\t (" << formatKiloMega(itemAcquisitionModule->timer.calculatePerHourRate(iter->second.numGained)) << " / h)";
						
		wxTreeItemId id = treeCtrl->AppendItem(root, itemLine);

			
		Counter<int>& contentsMap = itemAcquisitionModule->itemsFromContainers[iter->first];
		for (map<int, CounterEntry>::iterator iter2 = contentsMap.begin(); 
				iter2 != contentsMap.end(); iter2 ++) {
			wxString itemAcquiredLine;
			itemAcquiredLine << "[" << iter2->first << "] " << itemIDReader.getItemName(iter2->first) << " x" << iter2->second.numGained;
			if (iter2->second.numPackets >= 3) 
				itemAcquiredLine <<"\t (" << formatKiloMega(itemAcquisitionModule->timer.calculatePerHourRate(iter2->second.numGained)) << " / h)";
				
			treeCtrl->AppendItem(id, itemAcquiredLine);
	
		}
		
	}
	
	treeCtrl->ExpandAll();
	
}

void ItemBundleFrame::OnSize(wxSizeEvent& event){
	

	panel->SetSize(this->GetClientSize());
	
	treeCtrl->SetSize(this->GetClientSize());

	
}