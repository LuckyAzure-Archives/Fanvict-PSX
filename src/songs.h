	{ //StageId_1_1 (Bopeebo)
		//Characters
		{Char_BF_New,    FIXED_DEC(85,1),  FIXED_DEC(90,1),  FIXED_DEC(75,100)},
		{Char_BFFake_New, FIXED_DEC(-105,1),  FIXED_DEC(90,1),  FIXED_DEC(75,100)},
		{NULL, NULL, NULL, NULL},
		
		//Stage background
		Back_Fake_New,
		
		//Camera Offset (X, Y, Scale)
		FIXED_DEC(0,1), FIXED_DEC(20,1), FIXED_DEC(125,100),
		
		//Song info
		1, 1,
		XA_Bopeebo, 0,
		"Bopeebo - Kawai Sprite",
		
		StageId_1_2, STAGE_LOAD_FLAG
	},
	{ //StageId_1_2 (Fresh)
		//Characters
		{Char_BF_New,    FIXED_DEC(85,1),  FIXED_DEC(90,1),  FIXED_DEC(75,100)},
		{Char_Convict_New, FIXED_DEC(-105,1),  FIXED_DEC(90,1),  FIXED_DEC(100,100)},
		{NULL, NULL, NULL, NULL},
		
		//Stage background
		Back_Fake_New,
		
		//Camera Offset (X, Y, Scale)
		FIXED_DEC(0,1), FIXED_DEC(0,1), FIXED_DEC(100,100),
		
		//Song info
		1, 2,
		XA_Fresh, 2,
		"Fresh - Kawai Sprite",
		
		StageId_1_3, STAGE_LOAD_FLAG
	},
	{ //StageId_1_3 (Dadbattle)
		//Characters
		{Char_BF_New,    FIXED_DEC(60,1),  FIXED_DEC(100,1),  FIXED_DEC(1,1)},
		{Char_Dad_New, FIXED_DEC(-120,1),  FIXED_DEC(100,1),  FIXED_DEC(1,1)},
		{NULL, NULL, NULL, NULL},
		
		//Stage background
		Back_Default_New,
		
		//Camera Offset (X, Y, Scale)
		FIXED_DEC(0,1), FIXED_DEC(0,1), FIXED_DEC(1,1),
		
		//Song info
		1, 3,
		XA_Dadbattle, 0,
		"Dadbattle - Kawai Sprite",
		
		StageId_1_3, 0
	},
	{ //StageId_1_4 (Tutorial)
		//Characters
		{Char_BF_New, FIXED_DEC(60,1),  FIXED_DEC(100,1),  FIXED_DEC(1,1)},
		{Char_GF_New,  FIXED_DEC(0,1),  FIXED_DEC(-15,1),  FIXED_DEC(1,1)}, //TODO
		{NULL, NULL, NULL, NULL},
		
		//Stage background
		Back_Default_New,
		
		//Camera Offset (X, Y, Scale)
		FIXED_DEC(0,1), FIXED_DEC(0,1), FIXED_DEC(1,1),
		
		//Song info
		1, 4,
		XA_Tutorial, 2,
		"Tutorial - Kawai Sprite",
		
		StageId_1_4, 0
	}