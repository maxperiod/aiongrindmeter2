#ifndef ITEM_ACQUISITION_FRAME_H
#define ITEM_ACQUISITION_FRAME_H

#include "../modules/ItemAcquisitionModule.h"
#include "ListCtrlFrame.h"
#include "../parser/ItemIDFileReader.h"


class ItemAcquisitionFrame: public ListCtrlFrame
{

public:
	ItemAcquisitionFrame(ItemAcquisitionModule& itemAcquisitionModule, const wxPoint& pos);
		
	void refresh();


private:
	
	ItemAcquisitionModule* itemAcquisitionModule;
	
	ItemIDFileReader itemIDReader;
};

#endif