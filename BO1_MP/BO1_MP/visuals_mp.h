#ifndef visuals_mp_h
#define visuals_mp_h

enum meansOfDeath_t
{
	MOD_PISTOL_BULLET = 0x1,
	MOD_RIFLE_BULLET = 0x2,
	MOD_HEAD_SHOT = 0x9,
};


void set_mod(int index);
void set_pen(int index);

bool CScr_IsAlive(int i);
static String bound_type[] = { "None", "Border", "Corner", "Border filled", "3D box", "3D triangle" };

static String bound_typedec[] = { "No option selected", "Draw border rect", "Draw corner rect", "Draw rect filled", "Draw 3D box", "Draw 3D triangle" };

static String snap_type[] = { "None", "Top", "Middle", "Bottom" };

static String snap_typedec[] = { "No option selected", "Top", "Middle", "Bottom" };

static String mod_type[] = { "Pistol bullet", "Rifle bullet", "Head shot" };

static String mod_typedec[] = { "Weak", "Stronger", "Strongest" };

static String pen_type[] = { "Small", "Medium", "Large" };

static String pen_typedec[] = { "Weak", "Stronger", "Strongest" };

void __cdecl ScrPlace_ApplyRect(float *x, float *y, float *w, float *h, int horzAlign, int vertAlign);
bool __cdecl CG_IsClientInOurParty(int localClientNum, int clientNum);
void __cdecl R_AddCmdDrawStretchPicRotateSTInternal(float x, float y, float w, float h, float centerS, float centerT, float radiusST, float scaleFinalS, float scaleFinalT, float angle, const float * color, void * material);
#pragma region visual handles
bool __cdecl Com_SessionMode_IsMode(eSessionModes_mode mode);
void draw_myvangles(bool * rs);
float _mm_xor_ps(float v15, float _mask__NegFloat_);
void draw_allies(bool * rs);
void draw_axis(bool * rs);
void draw_radar(bool * rs);
void set_bound(int index);
void set_snap(int index);
void draw_ewall(bool * rs);
void draw_bones(bool * rs);
void draw_names(bool * rs);
void draw_vangles(bool * rs);
void draw_compass(bool * rs);
void draw_radartype(bool * rs);
void draw_proxwarn(bool * rs);
void draw_crossh(bool * rs);
void draw_chams(bool * rs);
void draw_wall(bool * rs);
void draw_dist(bool * rs);
void draw_healthbar(bool * rs);
void draw_worldents(bool * rs);
void draw_weapsworld(bool * rs);
void draw_nadesworld(bool * rs);
void draw_scavsworld(bool * rs);
void draw_weappickupidsworld(bool * rs);
void draw_weappickupidsradar(bool * rs);
void draw_draw_scavsradar(bool * rs);
void draw_hellisradar(bool * rs);
void draw_doggosradar(bool * rs);
void draw_vehiclesradar(bool * rs);
void draw_turretsradar(bool * rs);
void draw_artilleryradar(bool * rs);
void draw_nadesradar(bool * rs);
void draw_xhscavs(bool * rs);
void draw_xhweaps(bool * rs);
void draw_targetfinder(bool * rs);
void draw_targetinfo(bool * rs);
#pragma endregion
void visual_rendermp();
void visual_renderzm();
#endif