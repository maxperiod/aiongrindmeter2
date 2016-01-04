#ifndef MOB_KILLS_FRAME_H
#define MOB_KILLS_FRAME_H

#include "../modules/HuntingModule.h"
#include "ListCtrlFrame.h"

class MobKillsFrame: public ListCtrlFrame
{

public:
	MobKillsFrame(HuntingModule& huntingModule, const wxPoint& pos);
		
	void refresh();


private:
	
	HuntingModule* huntingModule;
		
};

#endif