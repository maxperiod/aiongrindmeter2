#include "RelicAp48.h"

/*
	Lesser Icon 186000066: 315 / 300
	Normal Icon 186000065: 630 / 600
	Greater Icon 186000064
	Major Icon 186000063
	Lesser Seal 186000062
	Normal Seal 186000061
	Greater Seal 186000060
	Major Seal 186000059
	Lesser Goblet 186000058
	Normal Goblet 186000057
	Greater Goblet 186000056
	Major Goblet 186000055
	Lesser Crown 186000054
	Normal Crown 186000053
	Greater Crown 186000052
	Major Crown 186000051
	Lesser Danuar 186000250
	Normal Danuar 186000249
	Greater Danuar 186000248
	Major Danuar 186000247
	Blood Mark 186000236
	*/

RelicAp48::RelicAp48(){
	relicApValues[186000066] = 300;
	relicApValues[186000065] = 600;
	relicApValues[186000064] = 900;
	relicApValues[186000063] = 1200;

	relicApValues[186000062] = 600;
	relicApValues[186000061] = 1200;
	relicApValues[186000060] = 1800;
	relicApValues[186000059] = 2400;

	relicApValues[186000058] = 800;
	relicApValues[186000057] = 1600;
	relicApValues[186000056] = 2400;
	relicApValues[186000055] = 3200;

	relicApValues[186000054] = 1600;
	relicApValues[186000053] = 3200;
	relicApValues[186000052] = 4800;
	relicApValues[186000051] = 6400;

	relicApValues[186000250] = 1700;
	relicApValues[186000249] = 3400;
	relicApValues[186000248] = 5100;
	relicApValues[186000247] = 6800;

	bestTurnInMultipliers[186000066] = 1.0f;
	bestTurnInMultipliers[186000065] = 1.0f;
	bestTurnInMultipliers[186000064] = 1.0f;
	bestTurnInMultipliers[186000063] = 1.0f;

	bestTurnInMultipliers[186000062] = 1.0f;
	bestTurnInMultipliers[186000061] = 1.0f;
	bestTurnInMultipliers[186000060] = 1.0f;
	bestTurnInMultipliers[186000059] = 1.0f;

	bestTurnInMultipliers[186000058] = 1.5f;
	bestTurnInMultipliers[186000057] = 1.5f;
	bestTurnInMultipliers[186000056] = 1.5f;
	bestTurnInMultipliers[186000055] = 1.5f;

	bestTurnInMultipliers[186000054] = 1.5f;
	bestTurnInMultipliers[186000053] = 1.5f;
	bestTurnInMultipliers[186000052] = 1.5f;
	bestTurnInMultipliers[186000051] = 1.5f;

	bestTurnInMultipliers[186000250] = 1.5f;
	bestTurnInMultipliers[186000249] = 1.5f;
	bestTurnInMultipliers[186000248] = 1.5f;
	bestTurnInMultipliers[186000247] = 1.5f;

}