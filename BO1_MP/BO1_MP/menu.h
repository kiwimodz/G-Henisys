#ifndef menu_h
#define menu_h
#include<hook.h>

#define max 100
void Wait(int timeout);
enum ids : int
{
	ID_MAIN,
	ID_AIMBOT,
	ID_ESP,
	ID_CHEATS,
	ID_ENTITY,
	ID_PLAYERS,
	ID_ACCOUNT,
	ID_SETTINGS,
	ID_PLAYERS_SUB,
	ID_ANTIAIM,
	ID_RADAR,
	ID_RADARENTS,
	ID_CROSSHAIR,
	ID_WORLDENTS,
	ID_THEME,
	ID_PRIMERY,
	ID_SECONDARY,
	ID_CUSTOMTHEME,
	ID_PLACEMENT,
	ID_CAMO,
	ID_DEBUG,
	ID_CHAMS,
	ID_HVH,
	ID_DEV,
	SERVER_INFO,
	ID_WEAPONIZED,
};
typedef void(*combo_func)(int data);

struct combodata_s
{
	bool opened;
	int tick, wait, scroll, maxscroll, size;
	float height;
	const char * * data;
	combo_func func;
};
static color dflash, dflash1;
struct menushit
{
	bool Mopened, active_option;
	int colori, id, tick, wait, scroll[max], prev[max], maxscroll[max], islide[max][max], barslide[max][max];
	char * ch;
};
struct menudata_s
{
	bool flshname, addname, checkresult[max][max], checkresult1[max][max][max], combo_active, smokec, nightmode, skyc, skyr, fade, mp, fps, res, serverinfo, host, map, game, ents, maxc, ping;
	int flagx, flagy;
	float frenderfovx;
	float dvis;
	float barslidevalue[max][max];
	float x, menusize, menufade, props, fmj, damage;
	float height, sypos1, sypos2, menux, menuy, Reflection, Layer3Scroll, Emissive_Amo, Layer1Scroll, Layer2Scroll, Gloss_Amount;
	color cflash, skin, skin2, esp[18], espzm[1200], colorslide, colorslide1;

	combodata_s combos[max][max];

	//handle_t handle;
};
extern menushit Mshit;
extern menudata_s menu;
extern String(*SL_ConvertToString_f)(short s);
static String Themecolor[] = { "Rain", /*"Red", "Yellow", "Orange", "Green", "Blue", "Purple", "Pink", "Aqua Green", "Sky Blue", "Cerulean", "Magenta", "Orchid", "Wisteria", "Lime Green", "Carnation Pink", "Golden Yellow", "Red Orange", "Gray", "Black", "White",*/ "Custom Theme", "Chams" };
void set_color(int index);
void RenderMenu();
void cheats_render();
void Menufade_scale(float value);
void Menusize_scale(float value);
void Damage_scale(float value);
void Fmj_scale(float value);
void combo_render_ui();
void Disconnect();
void HandleMenu();
void Cancel_Reload();

#endif