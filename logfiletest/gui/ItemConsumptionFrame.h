#ifndef ITEM_CONSUMPTION_FRAME_H
#define ITEM_CONSUMPTION_FRAME_H

#include "../modules/ItemAcquisitionModule.h"
#include "ListCtrlFrame.h"
#include "../parser/ItemIDFileReader.h"


class ItemConsumptionFrame: public ListCtrlFrame
{

public:
	ItemConsumptionFrame(wxWindow* parent, ItemAcquisitionModule& itemAcquisitionModule, const wxPoint& pos);
		
	void refresh();


private:
	
	ItemAcquisitionModule* itemAcquisitionModule;

};

#endif