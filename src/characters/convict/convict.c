#include "convict.h"

#include "../../psx/mem.h"
#include "../../psx/archive.h"
#include "../../scenes/stage/stage.h"
#include "../../main.h"

//Convict character structure
enum
{
	Convict_ArcMain_idle0,
	Convict_ArcMain_idle1,
	Convict_ArcMain_idle2,
	Convict_ArcMain_idle3,
	Convict_ArcMain_idle4,
	Convict_ArcMain_idle5,
	Convict_ArcMain_idle6,
	Convict_ArcMain_idle7,
	Convict_ArcMain_idle8,
	Convict_ArcMain_idle9,
	Convict_ArcMain_idle10,
	Convict_ArcMain_left0,
	Convict_ArcMain_left1,
	Convict_ArcMain_left2,
	Convict_ArcMain_left3,
	Convict_ArcMain_left4,
	Convict_ArcMain_left5,
	Convict_ArcMain_down0,
	Convict_ArcMain_down1,
	Convict_ArcMain_down2,
	Convict_ArcMain_down3,
	Convict_ArcMain_down4,
	Convict_ArcMain_down5,
	Convict_ArcMain_up0,
	Convict_ArcMain_up1,
	Convict_ArcMain_up2,
	Convict_ArcMain_up3,
	Convict_ArcMain_up4,
	Convict_ArcMain_up5,
	Convict_ArcMain_right0,
	Convict_ArcMain_right1,
	Convict_ArcMain_right2,
	Convict_ArcMain_right3,
	Convict_ArcMain_right4,
	Convict_ArcMain_right5,
	Convict_ArcMain_laugh0,
	Convict_ArcMain_laugh1,
	Convict_ArcMain_laugh2,
	Convict_ArcMain_laugh3,
	Convict_ArcMain_laugh4,

	Convict_Arc_Max,
};

typedef struct
{
	//Character base structure
	Character character;
	
	//Render data and state
	IO_Data arc_main;
	IO_Data arc_ptr[Convict_Arc_Max];
	
	Gfx_Tex tex;
	u8 frame, tex_id;
} Char_Convict;

//Convict character definitions
static const u16 char_convict_icons[2][4] = {
	{0,0,41,25},
	{42,0,41,27}
};

static const CharFrame char_convict_frame[] = {
	{Convict_ArcMain_idle0,{0,0,141,189},{63,182}}, //0 Idle
	{Convict_ArcMain_idle1,{0,0,140,188},{62,182}}, //1 Idle
	{Convict_ArcMain_idle2,{0,0,134,189},{62,182}}, //2 Idle
	{Convict_ArcMain_idle3,{0,0,139,190},{61,184}}, //3 Idle
	{Convict_ArcMain_idle4,{0,0,141,193},{60,186}}, //4 Idle
	{Convict_ArcMain_idle5,{0,0,135,193},{60,186}}, //5 Idle
	{Convict_ArcMain_idle6,{0,0,131,194},{60,186}}, //6 Idle
	{Convict_ArcMain_idle7,{0,0,139,194},{60,186}}, //7 Idle
	{Convict_ArcMain_idle8,{0,0,145,194},{60,186}}, //8 Idle
	{Convict_ArcMain_idle9,{0,0,146,194},{60,186}}, //9 Idle
	{Convict_ArcMain_idle10,{0,0,152,194},{60,186}}, //10 Idle
	{Convict_ArcMain_idle7,{0,0,139,194},{60,186}}, //11 Idle
	{Convict_ArcMain_idle8,{0,0,145,194},{60,186}}, //12 Idle
	{Convict_ArcMain_idle9,{0,0,146,194},{60,186}}, //13 Idle
	{Convict_ArcMain_idle10,{0,0,152,194},{60,186}}, //14 Idle
	
	{Convict_ArcMain_left0,{0,0,207,185},{145,171}}, //15 Left
	{Convict_ArcMain_left1,{0,0,203,186},{141,172}}, //16 Left
	{Convict_ArcMain_left2,{0,0,200,185},{140,171}}, //17 Left
	{Convict_ArcMain_left3,{0,0,196,186},{135,172}}, //18 Left
	{Convict_ArcMain_left4,{0,0,195,185},{133,171}}, //19 Left
	{Convict_ArcMain_left5,{0,0,194,186},{133,172}}, //20 Left
	
	{Convict_ArcMain_down0,{0,0,161,178},{115,170}}, //21 Down
	{Convict_ArcMain_down1,{0,0,162,183},{117,175}}, //22 Down
	{Convict_ArcMain_down2,{0,0,160,186},{116,178}}, //23 Down
	{Convict_ArcMain_down3,{0,0,160,186},{116,178}}, //24 Down
	{Convict_ArcMain_down4,{0,0,160,186},{116,178}}, //25 Down
	{Convict_ArcMain_down5,{0,0,160,186},{116,178}}, //26 Down
	
	{Convict_ArcMain_up0,{0,0,186,256},{127,245}}, //27 Up
	{Convict_ArcMain_up1,{0,0,179,250},{122,238}}, //28 Up
	{Convict_ArcMain_up2,{0,0,175,236},{117,224}}, //29 Up
	{Convict_ArcMain_up3,{0,0,176,233},{118,220}}, //30 Up
	{Convict_ArcMain_up4,{0,0,179,231},{120,218}}, //31 Up
	{Convict_ArcMain_up5,{0,0,179,231},{119,218}}, //32 Up
	
	{Convict_ArcMain_right0,{0,0,200,198},{35,193}}, //33 Right
	{Convict_ArcMain_right1,{0,0,195,187},{36,182}}, //34 Right
	{Convict_ArcMain_right2,{0,0,190,183},{37,178}}, //35 Right
	{Convict_ArcMain_right3,{0,0,188,183},{37,178}}, //36 Right
	{Convict_ArcMain_right4,{0,0,187,183},{37,178}}, //37 Right
	{Convict_ArcMain_right5,{0,0,188,183},{38,178}}, //38 Right
	
	{Convict_ArcMain_laugh0,{0,0,131,206},{59,198}}, //39 Laugh
	{Convict_ArcMain_laugh1,{0,0,138,203},{60,195}}, //40 Laugh
	{Convict_ArcMain_laugh2,{0,0,144,198},{62,190}}, //41 Laugh
	{Convict_ArcMain_laugh3,{0,0,154,197},{62,189}}, //42 Laugh
	{Convict_ArcMain_laugh4,{0,0,153,197},{62,189}}, //43 Laugh
	

};

static const Animation char_convict_anim[CharAnim_Max] = {
	{12, (const u8[]){ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,  ASCR_BACK, 1}},		//CharAnim_Idle
	{18, (const u8[]){ 15, 16, 17, 18, 19, 20,  ASCR_BACK, 1}},		//CharAnim_Left
	{0, (const u8[]){ASCR_CHGANI, CharAnim_Idle}},		//CharAnim_LeftAlt
	{18, (const u8[]){ 21, 22, 23, 24, 25, 26,  ASCR_BACK, 1}},		//CharAnim_Down
	{0, (const u8[]){ASCR_CHGANI, CharAnim_Idle}},		//CharAnim_DownAlt
	{18, (const u8[]){ 27, 28, 29, 30, 31, 32,  ASCR_BACK, 1}},		//CharAnim_Up
	{0, (const u8[]){ASCR_CHGANI, CharAnim_Idle}},		//CharAnim_UpAlt
	{18, (const u8[]){ 33, 34, 35, 36, 37, 38,  ASCR_BACK, 1}},		//CharAnim_Right
	{0, (const u8[]){ASCR_CHGANI, CharAnim_Idle}},		//CharAnim_RightAlt
	{18, (const u8[]){ 39, 40, 41, 42, 43,  ASCR_BACK, 1}},		//CharAnim_Special1
	{0, (const u8[]){ASCR_CHGANI, CharAnim_Idle}},		//CharAnim_Special2
	{0, (const u8[]){ASCR_CHGANI, CharAnim_Idle}},		//CharAnim_Special3

};

//Convict character functions
void Char_Convict_SetFrame(void *user, u8 frame)
{
	Char_Convict *this = (Char_Convict*)user;
	
	//Check if this is a new frame
	if (frame != this->frame)
	{
		//Check if new art shall be loaded
		const CharFrame *cframe = &char_convict_frame[this->frame = frame];
		if (cframe->tex != this->tex_id)
			Gfx_LoadTex(&this->tex, this->arc_ptr[this->tex_id = cframe->tex], 0);
	}
}

void Char_Convict_Tick(Character *character)
{
	Char_Convict *this = (Char_Convict*)character;
	
	//Perform idle dance
	if ((character->pad_held & (stage.prefs.control_keys[0] | stage.prefs.control_keys[1] | stage.prefs.control_keys[2] | stage.prefs.control_keys[3])) == 0)
		Character_PerformIdle(character);
	
	//Animate and draw
	Animatable_Animate(&character->animatable, (void*)this, Char_Convict_SetFrame);
	Character_Draw(character, &this->tex, &char_convict_frame[this->frame]);
}

void Char_Convict_SetAnim(Character *character, u8 anim)
{
	//Set animation
	Animatable_SetAnim(&character->animatable, anim);
	Character_CheckStartSing(character);
}

void Char_Convict_Free(Character *character)
{
	Char_Convict *this = (Char_Convict*)character;
	
	//Free art
	Mem_Free(this->arc_main);
}

Character *Char_Convict_New(fixed_t x, fixed_t y, fixed_t scale)
{
	//Allocate convict object
	Char_Convict *this = Mem_Alloc(sizeof(Char_Convict));
	if (this == NULL)
	{
		sprintf(error_msg, "[Char_Convict_New] Failed to allocate convict object");
		ErrorLock();
		return NULL;
	}
	
	//Initialize character
	this->character.tick = Char_Convict_Tick;
	this->character.set_anim = Char_Convict_SetAnim;
	this->character.free = Char_Convict_Free;
	
	Animatable_Init(&this->character.animatable, char_convict_anim);
	Character_Init((Character*)this, x, y);
	
	//Set character information
	this->character.spec = 0;
	
	memcpy(this->character.health_i, char_convict_icons, sizeof(char_convict_icons));
	
	//health bar color
	this->character.health_bar = 0xFF808080;
	
	this->character.focus_x = FIXED_DEC(30,1);
	this->character.focus_y = FIXED_DEC(-90,1);
	this->character.focus_zoom = FIXED_DEC(100,100);
	
	this->character.size = FIXED_MUL(FIXED_DEC(120,100),scale);
	
	//Load art
	this->arc_main = IO_Read("\\CHAR\\CONVICT.ARC;1");
	
	const char **pathp = (const char *[]){
		"idle0.tim",
		"idle1.tim",
		"idle2.tim",
		"idle3.tim",
		"idle4.tim",
		"idle5.tim",
		"idle6.tim",
		"idle7.tim",
		"idle8.tim",
		"idle9.tim",
		"idle10.tim",
		"left0.tim",
		"left1.tim",
		"left2.tim",
		"left3.tim",
		"left4.tim",
		"left5.tim",
		"down0.tim",
		"down1.tim",
		"down2.tim",
		"down3.tim",
		"down4.tim",
		"down5.tim",
		"up0.tim",
		"up1.tim",
		"up2.tim",
		"up3.tim",
		"up4.tim",
		"up5.tim",
		"right0.tim",
		"right1.tim",
		"right2.tim",
		"right3.tim",
		"right4.tim",
		"right5.tim",
		"laugh0.tim",
		"laugh1.tim",
		"laugh2.tim",
		"laugh3.tim",
		"laugh4.tim",

		NULL
	};
	IO_Data *arc_ptr = this->arc_ptr;
	for (; *pathp != NULL; pathp++)
		*arc_ptr++ = Archive_Find(this->arc_main, *pathp);
	
	//Initialize render state
	this->tex_id = this->frame = 0xFF;
	
	return (Character*)this;
}
