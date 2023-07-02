#include "fake.h"

#include "../../psx/archive.h"
#include "../../psx/mem.h"
#include "../../scenes/stage/stage.h"

//Week 1 background structure
typedef struct
{
	//Stage background base structure
	StageBack back;
	
	//Textures
	Gfx_Tex tex_back0;
	Gfx_Tex tex_back1;
} Back_Fake;

//Week 1 background functions
void Back_Fake_DrawBG(StageBack *back)
{
	Back_Fake *this = (Back_Fake*)back;
	
	fixed_t fx, fy;
	
	fx = stage.camera.x;
	fy = stage.camera.y;
	
	RECT backl_src = {0, 0, 256, 256};
	RECT_FIXED backl_dst = {
		FIXED_DEC(-255,1) - fx,
		FIXED_DEC(-120,1) - fy,
		FIXED_DEC(256,1),
		FIXED_DEC(256,1)
	};
	RECT backr_src = {0, 0, 256, 256};
	RECT_FIXED backr_dst = {
		FIXED_DEC(-1,1) - fx,
		FIXED_DEC(-120,1) - fy,
		FIXED_DEC(256,1),
		FIXED_DEC(256,1)
	};
	
	Stage_DrawTex(&this->tex_back0, &backl_src, &backl_dst, stage.camera.bzoom, stage.camera.angle);
	Stage_DrawTex(&this->tex_back1, &backr_src, &backr_dst, stage.camera.bzoom, stage.camera.angle);
}

void Back_Fake_Free(StageBack *back)
{
	Back_Fake *this = (Back_Fake*)back;
	
	//Free structure
	Mem_Free(this);
}

StageBack *Back_Fake_New(void)
{
	//Allocate background structure
	Back_Fake *this = (Back_Fake*)Mem_Alloc(sizeof(Back_Fake));
	if (this == NULL)
		return NULL;
	
	//Set background functions
	this->back.draw_fg = NULL;
	this->back.draw_md = NULL;
	this->back.draw_bg = Back_Fake_DrawBG;
	this->back.free = Back_Fake_Free;
	
	//Load background textures
	IO_Data arc_back = IO_Read("\\STAGES\\FAKE.ARC;1");
	Gfx_LoadTex(&this->tex_back0, Archive_Find(arc_back, "0.tim"), 0);
	Gfx_LoadTex(&this->tex_back1, Archive_Find(arc_back, "1.tim"), 0);
	Mem_Free(arc_back);
	
	return (StageBack*)this;
}
