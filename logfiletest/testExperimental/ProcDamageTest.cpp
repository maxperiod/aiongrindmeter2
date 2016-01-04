#include "../experimental/ProcDamageRegister.h"
#include "../experimental/CombatStats.h"
#include "gtest/gtest.h"

TEST(ProcDamageTest, proc1){
	ProcDamageRegister procDamageRegister;
	CombatStats cs;

	procDamageRegister.activateProc("Reroute Power Effect");
	procDamageRegister.applyDamage("Reroute Power Effect", 294);
	procDamageRegister.activateProc("Reroute Power Effect");
	procDamageRegister.applyDamage("Reroute Power Effect", 294);

	EXPECT_EQ(cs.totalDamageInflicted, 588);

	
/*
2014.06.18 17:37:22 : Reroute Power Effect has been activated. 
2014.06.18 17:37:22 : Fierce Worg received 294 damage due to the effect of Reroute Power Effect. 
2014.06.18 17:37:22 : Reroute Power Effect has been activated. 
2014.06.18 17:37:22 : Fierce Worg received 294 damage due to the effect of Reroute Power Effect. 
*/
}