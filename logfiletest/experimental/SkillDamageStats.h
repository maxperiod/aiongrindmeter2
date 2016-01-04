struct DamageStatEntry{
	DamageStatEntry():
			minDamage(0),
			maxDamage(0),
			totalDamage(0),
			numHits(0)
	{}

	int minDamage;
	int maxDamage;
	int totalDamage;
	int numHits;
};

struct SkillDamageStats{
	
	SkillDamageStats(): numUses(0), numResists(0)
	{}

	int numUses;

	DamageStatEntry normals;
	DamageStatEntry crits;
	DamageStatEntry blocks;
	DamageStatEntry parrys;
	DamageStatEntry critBlocks;
	DamageStatEntry critParrys;

	int numResists;
	/*
	int normalMinDamage;
	int normalMaxDamage;
	int critMinDamage;
	int critMaxDamage;
	int blockMinDamage;
	int blockMaxDamage;
	int parryMinDamage;
	int parryMaxDamage;

	int critBlockMinDamage;
	int critBlockMaxDamage;
	int critParryMinDamage;
	int critParryMaxDamage;

	int normalTotalDamage;
	int critTotalDamage;
	int blockTotalDamage;
	int parryTotalDamage;
	int critBlockTotalDamage;
	int critParryTotalDamage;

	int numNormals;
	int numCrits;
	int numBlocks;
	int numParrys;
	int numCritBlocks;
	int numCritParrys;	
	*/
};