#include "bffake.h"

#include "../../psx/mem.h"
#include "../../psx/archive.h"
#include "../../scenes/stage/stage.h"
#include "../../main.h"

//BFFake character structure
enum
{
	BFFake_ArcMain_idle0,
	BFFake_ArcMain_idle1,
	BFFake_ArcMain_idle2,
	BFFake_ArcMain_idle3,
	BFFake_ArcMain_idle4,
	BFFake_ArcMain_left0,
	BFFake_ArcMain_left1,
	BFFake_ArcMain_down0,
	BFFake_ArcMain_down1,
	BFFake_ArcMain_up0,
	BFFake_ArcMain_up1,
	BFFake_ArcMain_right0,
	BFFake_ArcMain_right1,
	BFFake_ArcMain_leftalt0,
	BFFake_ArcMain_leftalt1,
	BFFake_ArcMain_leftalt2,
	BFFake_ArcMain_leftalt3,
	BFFake_ArcMain_leftalt4,
	BFFake_ArcMain_downalt0,
	BFFake_ArcMain_downalt1,
	BFFake_ArcMain_downalt2,
	BFFake_ArcMain_downalt3,
	BFFake_ArcMain_downalt4,
	BFFake_ArcMain_upalt0,
	BFFake_ArcMain_upalt1,
	BFFake_ArcMain_upalt2,
	BFFake_ArcMain_upalt3,
	BFFake_ArcMain_upalt4,
	BFFake_ArcMain_rightalt0,
	BFFake_ArcMain_rightalt1,
	BFFake_ArcMain_rightalt2,
	BFFake_ArcMain_rightalt3,

	BFFake_Arc_Max,
};

typedef struct
{
	//Character base structure
	Character character;
	
	//Render data and state
	IO_Data arc_main;
	IO_Data arc_ptr[BFFake_Arc_Max];
	
	Gfx_Tex tex;
	u8 frame, tex_id;
} Char_BFFake;

//BFFake character definitions
static const u16 char_bffake_icons[2][4] = {
	{0,0,41,25},
	{42,0,41,27}
};

static const CharFrame char_bffake_frame[] = {
	{BFFake_ArcMain_idle0,{0,0,97,105},{47,91}}, //0 Idle
	{BFFake_ArcMain_idle1,{0,0,97,105},{47,91}}, //1 Idle
	{BFFake_ArcMain_idle2,{0,0,97,106},{47,92}}, //2 Idle
	{BFFake_ArcMain_idle3,{0,0,94,107},{48,93}}, //3 Idle
	{BFFake_ArcMain_idle4,{0,0,94,107},{48,93}}, //4 Idle
	
	{BFFake_ArcMain_left0,{0,0,100,105},{54,91}}, //5 Left
	{BFFake_ArcMain_left1,{0,0,97,105},{51,91}}, //6 Left
	
	{BFFake_ArcMain_down0,{0,0,115,86},{46,72}}, //7 Down
	{BFFake_ArcMain_down1,{0,0,112,88},{43,74}}, //8 Down
	
	{BFFake_ArcMain_up0,{0,0,94,116},{49,102}}, //9 Up
	{BFFake_ArcMain_up1,{0,0,95,115},{50,101}}, //10 Up
	
	{BFFake_ArcMain_right0,{0,0,94,106},{46,92}}, //11 Right
	{BFFake_ArcMain_right1,{0,0,96,106},{48,92}}, //12 Right
	
	{BFFake_ArcMain_leftalt0,{0,0,98,104},{52,90}}, //13 Left-alt
	{BFFake_ArcMain_leftalt1,{0,0,132,144},{86,129}}, //14 Left-alt
	{BFFake_ArcMain_leftalt2,{0,0,124,149},{78,134}}, //15 Left-alt
	{BFFake_ArcMain_leftalt3,{0,0,123,150},{77,135}}, //16 Left-alt
	{BFFake_ArcMain_leftalt4,{0,0,122,150},{76,135}}, //17 Left-alt
	
	{BFFake_ArcMain_downalt0,{0,0,99,85},{46,72}}, //18 Down-alt
	{BFFake_ArcMain_downalt1,{0,0,165,150},{84,137}}, //19 Down-alt
	{BFFake_ArcMain_downalt2,{0,0,172,140},{83,127}}, //20 Down-alt
	{BFFake_ArcMain_downalt3,{0,0,172,139},{83,126}}, //21 Down-alt
	{BFFake_ArcMain_downalt4,{0,0,171,139},{82,126}}, //22 Down-alt
	
	{BFFake_ArcMain_upalt0,{0,0,90,136},{46,121}}, //23 Up-alt
	{BFFake_ArcMain_upalt1,{0,0,135,160},{88,145}}, //24 Up-alt
	{BFFake_ArcMain_upalt2,{0,0,134,155},{86,140}}, //25 Up-alt
	{BFFake_ArcMain_upalt3,{0,0,134,152},{87,137}}, //26 Up-alt
	{BFFake_ArcMain_upalt4,{0,0,134,151},{87,136}}, //27 Up-alt
	
	{BFFake_ArcMain_rightalt0,{0,0,96,103},{42,91}}, //28 Right-alt
	{BFFake_ArcMain_rightalt1,{0,0,148,108},{59,96}}, //29 Right-alt
	{BFFake_ArcMain_rightalt2,{0,0,131,112},{54,100}}, //30 Right-alt
	{BFFake_ArcMain_rightalt3,{0,0,126,112},{53,100}}, //31 Right-alt
	

};

static const Animation char_bffake_anim[CharAnim_Max] = {
	{12, (const u8[]){ 0, 1, 2, 3, 4,  ASCR_BACK, 1}},		//CharAnim_Idle
	{12, (const u8[]){ 5, 6,  ASCR_BACK, 1}},		//CharAnim_Left
	{18, (const u8[]){ 13, 14, 15, 16, 17,  ASCR_BACK, 1}},		//CharAnim_LeftAlt
	{12, (const u8[]){ 7, 8,  ASCR_BACK, 1}},		//CharAnim_Down
	{18, (const u8[]){ 18, 19, 20, 21, 22,  ASCR_BACK, 1}},		//CharAnim_DownAlt
	{12, (const u8[]){ 9, 10,  ASCR_BACK, 1}},		//CharAnim_Up
	{18, (const u8[]){ 23, 24, 25, 26, 27,  ASCR_BACK, 1}},		//CharAnim_UpAlt
	{12, (const u8[]){ 11, 12,  ASCR_BACK, 1}},		//CharAnim_Right
	{18, (const u8[]){ 28, 29, 30, 31,  ASCR_BACK, 1}},		//CharAnim_RightAlt
	{0, (const u8[]){ASCR_CHGANI, CharAnim_Idle}},		//CharAnim_Special1
	{0, (const u8[]){ASCR_CHGANI, CharAnim_Idle}},		//CharAnim_Special2
	{0, (const u8[]){ASCR_CHGANI, CharAnim_Idle}},		//CharAnim_Special3

};

//BFFake character functions
void Char_BFFake_SetFrame(void *user, u8 frame)
{
	Char_BFFake *this = (Char_BFFake*)user;
	
	//Check if this is a new frame
	if (frame != this->frame)
	{
		//Check if new art shall be loaded
		const CharFrame *cframe = &char_bffake_frame[this->frame = frame];
		if (cframe->tex != this->tex_id)
			Gfx_LoadTex(&this->tex, this->arc_ptr[this->tex_id = cframe->tex], 0);
	}
}

void Char_BFFake_Tick(Character *character)
{
	Char_BFFake *this = (Char_BFFake*)character;
	
	//Perform idle dance
	if ((character->pad_held & (stage.prefs.control_keys[0] | stage.prefs.control_keys[1] | stage.prefs.control_keys[2] | stage.prefs.control_keys[3])) == 0)
		Character_PerformIdle(character);
	
	//Animate and draw
	Animatable_Animate(&character->animatable, (void*)this, Char_BFFake_SetFrame);
	Character_Draw(character, &this->tex, &char_bffake_frame[this->frame]);
}

void Char_BFFake_SetAnim(Character *character, u8 anim)
{
	//Set animation
	Animatable_SetAnim(&character->animatable, anim);
	Character_CheckStartSing(character);
}

void Char_BFFake_Free(Character *character)
{
	Char_BFFake *this = (Char_BFFake*)character;
	
	//Free art
	Mem_Free(this->arc_main);
}

Character *Char_BFFake_New(fixed_t x, fixed_t y, fixed_t scale)
{
	//Allocate bffake object
	Char_BFFake *this = Mem_Alloc(sizeof(Char_BFFake));
	if (this == NULL)
	{
		sprintf(error_msg, "[Char_BFFake_New] Failed to allocate bffake object");
		ErrorLock();
		return NULL;
	}
	
	//Initialize character
	this->character.tick = Char_BFFake_Tick;
	this->character.set_anim = Char_BFFake_SetAnim;
	this->character.free = Char_BFFake_Free;
	
	Animatable_Init(&this->character.animatable, char_bffake_anim);
	Character_Init((Character*)this, x, y);
	
	//Set character information
	this->character.spec = 0;
	
	memcpy(this->character.health_i, char_bffake_icons, sizeof(char_bffake_icons));
	
	//health bar color
	this->character.health_bar = 0xFF808080;
	
	this->character.focus_x = FIXED_DEC(30,1);
	this->character.focus_y = FIXED_DEC(-90,1);
	this->character.focus_zoom = FIXED_DEC(100,100);
	
	this->character.size = FIXED_MUL(FIXED_DEC(100,100),scale);
	
	//Load art
	this->arc_main = IO_Read("\\CHAR\\BFFAKE.ARC;1");
	
	const char **pathp = (const char *[]){
		"idle0.tim",
		"idle1.tim",
		"idle2.tim",
		"idle3.tim",
		"idle4.tim",
		"left0.tim",
		"left1.tim",
		"down0.tim",
		"down1.tim",
		"up0.tim",
		"up1.tim",
		"right0.tim",
		"right1.tim",
		"leftalt0.tim",
		"leftalt1.tim",
		"leftalt2.tim",
		"leftalt3.tim",
		"leftalt4.tim",
		"downalt0.tim",
		"downalt1.tim",
		"downalt2.tim",
		"downalt3.tim",
		"downalt4.tim",
		"upalt0.tim",
		"upalt1.tim",
		"upalt2.tim",
		"upalt3.tim",
		"upalt4.tim",
		"rightalt0.tim",
		"rightalt1.tim",
		"rightalt2.tim",
		"rightalt3.tim",

		NULL
	};
	IO_Data *arc_ptr = this->arc_ptr;
	for (; *pathp != NULL; pathp++)
		*arc_ptr++ = Archive_Find(this->arc_main, *pathp);
	
	//Initialize render state
	this->tex_id = this->frame = 0xFF;
	
	return (Character*)this;
}
