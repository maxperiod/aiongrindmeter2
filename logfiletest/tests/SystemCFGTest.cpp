#include "gtest/gtest.h"
#include "../parser/SystemCFG.h"



TEST(SystemCFGTest, openNA){
	
	SystemCFG systemCFG;

	systemCFG.readCFG("D:/Aion/system.cfg", true);
	
	EXPECT_TRUE(systemCFG.isReadSuccessful());

	EXPECT_EQ("1", systemCFG.getEntries().at("g_chatlog"));
}

TEST(SystemCFGTest, openEU){
	
	SystemCFG systemCFG;

	systemCFG.readCFG("E:/GameforgeLive/Games/GBR_eng/AION/Download/system.cfg", true);
	
	EXPECT_TRUE(systemCFG.isReadSuccessful());

	EXPECT_EQ(0, systemCFG.getEntries().count("g_chatlog"));
	
}




TEST(SystemCFGTest, open1){
	
	
	SystemCFG systemCFG;
	systemCFG.readCFG("testModule/testDirectoryChatLogDisabled/system.cfg", true);
	
	EXPECT_TRUE(systemCFG.isReadSuccessful());
	EXPECT_EQ(0, systemCFG.getEntries().count("g_chatlog"));

	EXPECT_EQ(78, systemCFG.getEntries().size());

	systemCFG.setProperty("g_chatlog", "1");
	
	EXPECT_TRUE(systemCFG.writeCFG("testModule/testDirectoryChatLogDisabled/system2.cfg", true));	
	
	
	systemCFG.readCFG("testModule/testDirectoryChatLogDisabled/system2.cfg", true);
	
	EXPECT_TRUE(systemCFG.isReadSuccessful());

	EXPECT_EQ(79, systemCFG.getEntries().size());

	EXPECT_EQ("2048", systemCFG.getEntries().at("e_water_render_distance"));
	EXPECT_EQ("0.220000", systemCFG.getEntries().at("g_cam_rot_ratio"));
	EXPECT_EQ("7", systemCFG.getEntries().at("g_cfg_version"));
	EXPECT_EQ("4", systemCFG.getEntries().at("g_cfg_video_BACKGROUND"));
	EXPECT_EQ("4", systemCFG.getEntries().at("g_cfg_video_EFFECT"));
	EXPECT_EQ("4", systemCFG.getEntries().at("g_cfg_video_ENTITY_DIST"));
	EXPECT_EQ("3", systemCFG.getEntries().at("g_cfg_video_ENV_TEX"));
	EXPECT_EQ("6", systemCFG.getEntries().at("g_cfg_video_FSAA"));
	EXPECT_EQ("3", systemCFG.getEntries().at("g_cfg_video_GENERAL"));
	EXPECT_EQ("5", systemCFG.getEntries().at("g_cfg_video_GLARE"));
	EXPECT_EQ("5", systemCFG.getEntries().at("g_cfg_video_GLOW"));
	EXPECT_EQ("3", systemCFG.getEntries().at("g_cfg_video_MODEL_CACHE"));
	EXPECT_EQ("4", systemCFG.getEntries().at("g_cfg_video_MRT_BACKGROUND"));
	EXPECT_EQ("4", systemCFG.getEntries().at("g_cfg_video_MRT_BUMP"));
	EXPECT_EQ("3", systemCFG.getEntries().at("g_cfg_video_MRT_CAMERA"));
	EXPECT_EQ("5", systemCFG.getEntries().at("g_cfg_video_MRT_DOF"));
	EXPECT_EQ("4", systemCFG.getEntries().at("g_cfg_video_MRT_EFFECT"));
	EXPECT_EQ("4", systemCFG.getEntries().at("g_cfg_video_MRT_ENTITY_DIST"));
	EXPECT_EQ("3", systemCFG.getEntries().at("g_cfg_video_MRT_ENV_TEX"));
	EXPECT_EQ("2", systemCFG.getEntries().at("g_cfg_video_MRT_FSAA"));
	EXPECT_EQ("-2", systemCFG.getEntries().at("g_cfg_video_MRT_GENERAL"));
	EXPECT_EQ("5", systemCFG.getEntries().at("g_cfg_video_MRT_GLARE"));
	EXPECT_EQ("2", systemCFG.getEntries().at("g_cfg_video_MRT_GLOW"));
	EXPECT_EQ("2", systemCFG.getEntries().at("g_cfg_video_MRT_LOWEST"));
	EXPECT_EQ("3", systemCFG.getEntries().at("g_cfg_video_MRT_MODEL_CACHE"));
	EXPECT_EQ("4", systemCFG.getEntries().at("g_cfg_video_MRT_SHADER"));
	EXPECT_EQ("2", systemCFG.getEntries().at("g_cfg_video_MRT_SHADOW"));
	EXPECT_EQ("6", systemCFG.getEntries().at("g_cfg_video_MRT_SKILLFX"));
	EXPECT_EQ("6", systemCFG.getEntries().at("g_cfg_video_MRT_SUNSHAFT"));
	EXPECT_EQ("4", systemCFG.getEntries().at("g_cfg_video_MRT_TERRAIN_DIST"));
	EXPECT_EQ("4", systemCFG.getEntries().at("g_cfg_video_MRT_TEXTURE"));
	EXPECT_EQ("4", systemCFG.getEntries().at("g_cfg_video_MRT_WATER"));
	EXPECT_EQ("5", systemCFG.getEntries().at("g_cfg_video_MRT_WEATHERLAYER"));
	EXPECT_EQ("1", systemCFG.getEntries().at("g_cfg_video_screen_res"));
	EXPECT_EQ("4", systemCFG.getEntries().at("g_cfg_video_SHADER"));
	EXPECT_EQ("4", systemCFG.getEntries().at("g_cfg_video_SHADOW"));
	EXPECT_EQ("5", systemCFG.getEntries().at("g_cfg_video_SKILLFX"));
	EXPECT_EQ("4", systemCFG.getEntries().at("g_cfg_video_TERRAIN_DIST"));
	EXPECT_EQ("4", systemCFG.getEntries().at("g_cfg_video_TEXTURE"));
	EXPECT_EQ("4", systemCFG.getEntries().at("g_cfg_video_WATER"));
	EXPECT_EQ("1", systemCFG.getEntries().at("g_chatlog"));
	EXPECT_EQ("0", systemCFG.getEntries().at("g_client_var"));
	EXPECT_EQ("1", systemCFG.getEntries().at("g_muteMyPet"));
	EXPECT_EQ("0", systemCFG.getEntries().at("g_openSpecialServerList"));
	EXPECT_EQ("0.010000", systemCFG.getEntries().at("g_ThirdPersonRange"));
	EXPECT_EQ("0", systemCFG.getEntries().at("g_vendoradpopupToday"));
	EXPECT_EQ("16.000000", systemCFG.getEntries().at("r_DetailDistance"));
	EXPECT_EQ("1", systemCFG.getEntries().at("r_DetailTextures"));
	EXPECT_EQ("2", systemCFG.getEntries().at("r_EnvCMResolution"));
	EXPECT_EQ("0.001000", systemCFG.getEntries().at("r_EnvCMupdateInterval"));
	EXPECT_EQ("3", systemCFG.getEntries().at("r_EnvTexResolution"));
	EXPECT_EQ("0.001000", systemCFG.getEntries().at("r_EnvTexUpdateInterval"));
	EXPECT_EQ("0", systemCFG.getEntries().at("r_Fullscreen"));
	EXPECT_EQ("1137", systemCFG.getEntries().at("r_Height"));
	EXPECT_EQ("2", systemCFG.getEntries().at("r_MaximizeWindow"));
	EXPECT_EQ("1", systemCFG.getEntries().at("r_mrt_depthrender"));
	EXPECT_EQ("1", systemCFG.getEntries().at("r_mrt_initdetect"));
	EXPECT_EQ("560", systemCFG.getEntries().at("r_RestoreLeft"));
	EXPECT_EQ("311", systemCFG.getEntries().at("r_RestoreTop"));
	EXPECT_EQ("4", systemCFG.getEntries().at("r_ShaderModel"));
	EXPECT_EQ("3", systemCFG.getEntries().at("r_ShadowBlur"));
	EXPECT_EQ("0", systemCFG.getEntries().at("r_TexBumpResolution"));
	EXPECT_EQ("384.000000", systemCFG.getEntries().at("r_WaterReflections_MaxViewDist"));
	EXPECT_EQ("1", systemCFG.getEntries().at("r_WaterRefractions"));
	EXPECT_EQ("1920", systemCFG.getEntries().at("r_Width"));
	EXPECT_EQ("0", systemCFG.getEntries().at("s_HRTFEnable"));
	EXPECT_EQ("0.300885", systemCFG.getEntries().at("s_MasterVolume"));
	EXPECT_EQ("1", systemCFG.getEntries().at("s_MusicMute"));
	EXPECT_EQ("0.200000", systemCFG.getEntries().at("s_MusicVolume"));
	EXPECT_EQ("1.000000", systemCFG.getEntries().at("s_SFXVolume_COMMENT_GOSSIP"));
	EXPECT_EQ("0.800000", systemCFG.getEntries().at("s_SFXVolume_COMMENT_NPC"));
	EXPECT_EQ("1.000000", systemCFG.getEntries().at("s_SFXVolume_COMMENT_QUEST"));
	EXPECT_EQ("0.600000", systemCFG.getEntries().at("s_SFXVolume_COMMENT_SYSTEM"));
	EXPECT_EQ("0.350000", systemCFG.getEntries().at("s_SFXVolume_ENV"));
	EXPECT_EQ("0.500000", systemCFG.getEntries().at("s_SFXVolume_FX"));
	EXPECT_EQ("0.600000", systemCFG.getEntries().at("s_SFXVolume_UI"));
	EXPECT_EQ("1.000000", systemCFG.getEntries().at("s_SFXVolume_WEATHER"));
	EXPECT_EQ("1.000000", systemCFG.getEntries().at("sys_AdaptiveCharLOD"));
	EXPECT_EQ("0.000000", systemCFG.getEntries().at("sys_skiponlowspec"));
	/*
	CFGmap entries = systemCFG.getEntries();
	for (CFGmap::iterator iter = entries.begin(); iter != entries.end(); iter ++){
			
		cout << "EXPECT_EQ(\"" << iter->second << "\", systemCFG.getEntries().at(\"" << iter->first << "\"));" << endl;
	}
	
	*/

	systemCFG.removeProperty("g_chatlog");
	EXPECT_TRUE(systemCFG.writeCFG("testModule/testDirectoryChatLogDisabled/system2.cfg", true));

	//SystemCFG systemCFG;
	systemCFG.readCFG("testModule/testDirectoryChatLogDisabled/system2.cfg", true);
	
	EXPECT_TRUE(systemCFG.isReadSuccessful());
	EXPECT_EQ(0, systemCFG.getEntries().count("g_chatlog"));

	EXPECT_EQ(78, systemCFG.getEntries().size());
	
}

TEST(SystemCFGTest, open2){
	
	SystemCFG systemCFG;

	systemCFG.readCFG("testModule/testDirectoryChatLogEnabled/system.cfg", true);
	
	EXPECT_TRUE(systemCFG.isReadSuccessful());

	EXPECT_EQ("1", systemCFG.getEntries().at("g_chatlog"));
}