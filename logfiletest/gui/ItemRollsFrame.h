#ifndef ITEM_ROLLS_FRAME_H
#define ITEM_ROLLS_FRAME_H

#include "ListCtrlFrame.h"

#include "../modules/ItemAcquisitionModule.h"
#include "../parser/ItemIDFileReader.h"

class ItemRollsFrame: public ListCtrlFrame//wxFrame
{

public:
	ItemRollsFrame(wxWindow* parent, ItemAcquisitionModule& itemAcquisitionModule, const wxPoint& pos);
	void refresh();


private:
	
	ItemAcquisitionModule* itemAcquisitionModule;
	ItemIDFileReader itemIDReader;

};

#endif