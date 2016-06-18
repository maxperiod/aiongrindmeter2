#ifndef PLAYER_KILLS_FRAME_H
#define PLAYER_KILLS_FRAME_H

#include "../modules/HuntingModule.h"
#include "../modules/SoulHealerModule.h"
#include "ListCtrlFrame.h"

class PlayerKillsFrame: public ListCtrlFrame
{

public:
	PlayerKillsFrame(wxWindow* parent, HuntingModule& huntingModule, SoulHealerModule& soulHealerModule, const wxPoint& pos);
		
	void refresh();


private:
	
	HuntingModule* huntingModule;
	SoulHealerModule* soulHealerModule;
};

#endif