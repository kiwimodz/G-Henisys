#include <devstation\System.h>
#include <devstation\Math.h>
#include <devstation\Vector.h>
#include <cell\console\plugins\screen_shot.h>
#include <Structures.h>
#include<menu.h>
#include <Functions.h>
#include <visuals_mp.h>

int R_GetFontPathFromName_t[2] = { 0x75C104, 0xD67E98 };
String(*R_GetFontPathFromName)(String text) = (String(*)(String))R_GetFontPathFromName_t;

int CG_GameMessage_t[2] = { 0x0006AD98, 0xD67E98 };
void(*CG_GameMessage_f)(int r1, char * r2) = (void(*)(int, char *))CG_GameMessage_t;

//int zombiecheck_t[2] = { 0x31A080, 0xD67E98 };
//bool(*zombiecheck)() = (bool(*)())zombiecheck_t;


bool zombiecheck()
{
	return Com_SessionMode_IsMode(SESSIONMODE_ZOMBIES);
}

void CG_GameMessage(char * r2)
{
	CG_GameMessage_f(0, r2);
}

int Cbuf_AddText_t[2] = { 0x313C18, 0xD67E98 };
void(*Cbuf_AddText_f)(int r1, char * r2) = (void(*)(int, char *))Cbuf_AddText_t;

void Cbuf_AddText(char * r2)
{
	Cbuf_AddText_f(0, r2);
}

int BG_GetAmmoInClip_t[2] = { 0x0603694, 0xD67E98 };
int(*BG_GetAmmoInClip)(playerstate_s* ps, int weapon) = (int(*)(playerstate_s*, int))BG_GetAmmoInClip_t;

int WorldPosToScreenPos_t[2] = { 0x5A480, 0xD67E98 };
bool(*WorldPosToScreenPos_f)(int r1, Vector3 const & worldPos, Vector2 * screenPos) = (bool(*)(int, Vector3 const &, Vector2 *))WorldPosToScreenPos_t;

bool WorldPosToScreenPos(Vector3 worldPos, Vector2 *screenPos)
{
	return WorldPosToScreenPos_f(0, worldPos, screenPos);
}

int CG_LocationalTrace_t[2] = { 0x100018, 0xD67E98 };
void(*CG_LocationalTrace_f)(trace_ts* ptrace, Vector3* start, Vector3* end, int passEntityNum, int contentMask, bool checkRopes, col_context_t* context) = (void(*)(trace_ts *, Vector3*, Vector3*, int, int, bool, col_context_t *))CG_LocationalTrace_t;

void CG_LocationalTrace(trace_ts * ptrace, Vector3 *start, Vector3 *end, int passEntityNum, int contentMask, bool checkRopes, col_context_t * context)
{
	CG_LocationalTrace_f(ptrace, start, end, passEntityNum, contentMask, checkRopes, context);
}

int PlayerCmd_EnableInvulnerability_t[2] = { 0x1F9C9C, 0xD67E98 };
void(*PlayerCmd_EnableInvulnerability_f)(int *r1) = (void(*)(int*))PlayerCmd_EnableInvulnerability_t;


void PlayerCmd_EnableInvulnerability(int client) {
	int entref[] = { client, 0 };  // scr_entref_t entref = { client, CT_ENTITY };
	PlayerCmd_EnableInvulnerability_f(entref);
}

int PlayerCmd_disableinvulnerability_t[2] = { 0x001F9D38, 0xD67E98 };
void(*PlayerCmd_disableinvulnerability_f)(int *r1) = (void(*)(int*))PlayerCmd_disableinvulnerability_t;

void PlayerCmd_disableinvulnerability(int client) {
	int entref[] = { client, 0 };  // scr_entref_t entref = { client, CT_ENTITY };
	PlayerCmd_disableinvulnerability_f(entref);
}

int SV_GameSendServerCommand_t[2] = { 0x349F6C, 0xD67E98 };
void(*SV_GameSendServerCommand_f)(int r1, int r2, char* r3) = (void(*)(int, int, char*))SV_GameSendServerCommand_t;


void TeleportToPower()
{
	Vector3 Buried_Res = { 682.165, -552.677, 144.125 };
	*(Vector3*)(0x01780f50 + Mshit.scroll[ID_PLAYERS] * 0x5808) = Buried_Res;
	char boolBuff[100];
	snprintf(boolBuff, sizeof(boolBuff), "%c \"%s\"", 79, "Teleported to ^2Power");
	SV_GameSendServerCommand_f(Mshit.scroll[ID_PLAYERS], 0, boolBuff);//SV_GameSendServerCommand
}

void TeleportToPaP()
{
	Vector3 Buried_Res = { 6403.38, 779.031, -131.672 };
	*(Vector3*)(0x01780f50 + Mshit.scroll[ID_PLAYERS] * 0x5808) = Buried_Res;
	char boolBuff[100];
	snprintf(boolBuff, sizeof(boolBuff), "%c \"%s\"", 79, "Teleported to ^2PackaPunch");
	SV_GameSendServerCommand_f(Mshit.scroll[ID_PLAYERS], 0, boolBuff);//SV_GameSendServerCommand
}

int XShowKeyboardUI_t[2] = { 0x46710C, 0xD67E98 };
void(*XShowKeyboardUI_f)(int localClientNum, const wchar_t * title, const wchar_t * presetMsg, unsigned int length, void(*KB_COMPLETE)(int localClientNum, const wchar_t * wstring, unsigned int Length), unsigned int panel_mode) = (void(*)(int, const wchar_t *, const wchar_t *, unsigned int, void(*)(int, const wchar_t *, unsigned int), unsigned int))XShowKeyboardUI_t;


void XShowKeyboardUI(int localClientNum, const wchar_t * title, const wchar_t * presetMsg, unsigned int length, void(*KB_COMPLETE)(int localClientNum, const wchar_t * wstring, unsigned int Length), unsigned int panel_mode)
{
	*(char*)0xD82144 = 1;
	XShowKeyboardUI_f(localClientNum, title, presetMsg, length, KB_COMPLETE, panel_mode);
}

int Dvar_GetString_t[2] = { 0x3DAE50, 0xD67E98 };
String(*Dvar_GetString_f)(int dvarName) = (String(*)(int dvarName))Dvar_GetString_t;

int Dvar_t[2] = { 0x3DA628, 0xD67E98 };
int(*Dvar_f)(String dvarName) = (int(*)(String dvarName))Dvar_t;

String Dvar_GetString(String dvarName) {
	return Dvar_GetString_f(Dvar_f(dvarName));
}

void WideCharToMultibyte(const wchar_t * wchar, int length, char * buffer) {
	for (int i = 0; i < length; i++)
		buffer[i] = (char)wchar[i];
}

bool CScr_IsAlive(centity_s * cent) {
	if (!cent)
		return false;
	char nextstatetype = cent->Type;
	if (nextstatetype != 16 && nextstatetype != 1 && nextstatetype != 14 && nextstatetype != 12 && nextstatetype != 13 && nextstatetype != 15)
	{
		return false;
	}
	char v4 = cent->Type;
	if (v4 != 16 && v4 != 1 && v4 != 14 && v4 != 12 && v4 != 13 && v4 != 15 || cent->nextLerpeFlags & 0x40000)
		return false;
	else
		return true;
}

void PosPrediction(int i, Vector3 BonePos, int Scale, bool NotAllowZ)
{

}

void USleep(usecond_t time) {
	sys_timer_usleep(time * 1000);
}

bool AimTarget_IsTargetVisibleWithPrediction(int i, float fpredict)
{
	trace_ts ptrace;
	Vector3 targetbone;
	targetbone = local->player[i].vtag[bot.psztag[i]];
	PosPrediction(i, targetbone, fpredict, true);
	CG_LocationalTrace(&ptrace, &cg->refdef.ViewOrigin, &targetbone, cg->clientNum, 0x803003, 0, 0);
	return ptrace.fraction >= 0.98f;
}

int Dvar_GetBool_t[2] = { 0x3DA948, 0xD67E98 };
bool(*Dvar_GetBool_f)(pvoid dvarName) = (bool(*)(pvoid))Dvar_GetBool_t;

int Dvarv_t[2] = { 0x3DA628, 0xD67E98 };
pvoid(*Dvarv_f)(String dvarName) = (pvoid(*)(String))Dvarv_t;


bool Dvar_GetBool(String dvarName) {
	return Dvar_GetBool_f(Dvarv_f(dvarName));
}

int Dvar_GetFloat_t[2] = { 0x3DABB8, 0xD67E98 };
float(*Dvar_GetFloat_f)(pvoid dvarName) = (float(*)(pvoid))Dvar_GetFloat_t;


float Dvar_GetFloat(String dvarName) {
	return Dvar_GetFloat_f(Dvarv_f(dvarName));
}

int irand_t[2] = { 0x3CE988, 0xD67E98 };
int(*irand_f)(int r1, int r2) = (int(*)(int, int))irand_t;


int irand_(int min, int max_)
{
	return irand_f(min, max_);
}

bool cl_ingame()
{
	return Dvar_GetBool("cl_ingame") && (*(int*)(0xE22F18) > 0 && *(int*)(0xE22F1C) > 0 && *(int*)(0xE22F20) && *(int*)(0xD689D8) > 0) && (cg != NULL && centity != NULL) && !isHostMigrating();
}

int CG_IsEntityFriendlyNotEnemy_t[2] = { 0x049720, 0xD67E98 };
bool(*CG_IsEntityFriendlyNotEnemy_f)(int r1, centity_s *  r2) = (bool(*)(int, centity_s *))CG_IsEntityFriendlyNotEnemy_t;

#pragma region cg
bool CG_IsEntityFriendlyNotEnemy(centity_s * cent)
{
	return CG_IsEntityFriendlyNotEnemy_f(0, cent);
}

int AimTarget_GetTagPos_t[2] = { 0x015708, 0xD67E98 };
bool(*AimTarget_GetTagPos_f)(centity_s * cent, short tagname, Vector3* r4) = (bool(*)(centity_s *, short, Vector3*))AimTarget_GetTagPos_t;


void AimTarget_GetTagPos(centity_s * cent, short tagname, Vector3 *pos)
{
	*(int*)0x461FB4 = 0x4E800020;
	AimTarget_GetTagPos_f(cent, tagname, pos);
	*(int*)0x461FB4 = 0xF821FB71;

}
float VectorLength2D(Vector3* pV)
{
	return	sqrtf(pV->x * pV->x + pV->z * pV->z);
}


int VectoAngles_t[2] = { 0x3CAB90, 0xD67E98 };
void(*VectoAngles_f)(Vector3 *vec, Vector3* angles) = (void(*)(Vector3 *vec, Vector3* angles))VectoAngles_t;

void VectoAngles(Vector3 vec, Vector3* angles)
{
	VectoAngles_f(&vec, angles);
}

Vector3 AnglesToFoward(Vector3 Origin, Vector3 Angles, float diff)//1000.0f
{
	float angle, sr, sp, sy, cr, cp, cy, PiDiv;
	PiDiv = ((float)M_PI / 180);
	angle = Angles.y * PiDiv;
	sy = (float)sinf(angle);
	cy = (float)cosf(angle);
	angle = Angles.x * PiDiv;
	sp = sinf(angle);
	cp = (float)cosf(angle);
	angle = Angles.y * PiDiv;
	sr = (float)sinf(angle);
	cr = (float)cosf(angle);
	Vector3 Final((cp * cy * diff) + Origin.x, (cp * sy * diff) + Origin.y, (-sp * diff) + Origin.z);
	return Final;
}
#pragma endregion
#pragma region graphics

int R_RegisterFont_t[2] = { 0x75A2C0, 0xD67E98 };
int(*R_RegisterFont_f)(String font, int imageTrac) = (int(*)(String, int))R_RegisterFont_t;

int R_RegisterFont(String font, int imageTrac)
{
	return R_RegisterFont_f(font, imageTrac);
}

int R_TextWidth_t[2] = { 0x75A338, 0xD67E98 };
int(*R_TextWidth_f)(int localClientNum, const char *text, int maxChars, int font) = (int(*)(int, const char *, int, int))R_TextWidth_t;

int R_TextWidth(String text, const char * font, float scale)
{
	return R_TextWidth_f(0, text, 0x7FFFFFFF, R_RegisterFont(font, 0)) * scale;
}

int R_TextHeight_t[2] = { 0x75A5D0, 0xD67E98 };
int(*R_TextHeight_f)(int font) = (int(*)(int))R_TextHeight_t;

int R_TextHeight(String font, float scale)
{
	return R_TextHeight_f(R_RegisterFont(R_GetFontPathFromName(font), 0)) * scale;
}

void SmokeColor(bool * rs) { *rs = menu.smokec = !menu.smokec; }
void NightMode(bool* rs) {

}
void SkyColor(bool * rs) { *rs = menu.skyc = !menu.skyc; }
void SkyRotate(bool * rs) { *rs = menu.skyr = !menu.skyr; }
void fadeColor(bool * rs) { *rs = menu.fade = !menu.fade; }

int Sys_Milliseconds_t[2] = { 0x465CE0, 0xD67E98 };
int(*Sys_Milliseconds)() = (int(*)())Sys_Milliseconds_t;

int Com_Sprint_t[2] = { 0x3E4970, 0xD67E98 };
int(*Com_Sprint)(char *dest, int size, const char *fmt, ...) = (int(*)(char *, int, const char *, ...))Com_Sprint_t;

float sky_rotate;
bool runoncexxx = true;
void Smokehandle()
{

	if (menu.skyr)
	{
		static int itick, iwait;
		bool istate = ((Sys_Milliseconds() - itick) > iwait);
		if (istate)
		{
			if (sky_rotate >= 360)
				sky_rotate - 360;
			else
				sky_rotate += 0.10;

			WriteMemory(r_skyRotation, &sky_rotate, 4);//r_skyRotation
			
			

			itick = Sys_Milliseconds(), iwait = 1;
		}
	}


	/*if (local->LSD) { WriteMemory(lsdshit, &local->LSD, 4); }
	if (local->props) { WriteMemory(propsizes, &local->props, 4); WriteMemory(0x00893744, NOPE, 4); WriteMemory(0x0893750, NOPE, 4); WriteMemory(0x089375C, NOPE, 4); }*/
	
	
	if (menu.smokec)
	{
		WriteMemory(0x009E50D0, &menu.skin, 16);
		runoncexxx = true;
	}
	else if (!menu.smokec && runoncexxx)
	{
		WriteMemory(0x009E50D0, &color(255, 255, 255, 255), 16);
		runoncexxx = false;
	}
}
int Material_RegisterHandle_t[2] = { 0x763220, 0xD67E98 };
pvoid(*Material_RegisterHandle_f)(String font, int imageTrac, int r1) = (pvoid(*)(String, int, int))Material_RegisterHandle_t;

pvoid Material_RegisterHandle(String Material, int ImageTrac)
{
	return Material_RegisterHandle_f(Material, ImageTrac, 0);
}

struct Glyph
{
	unsigned __int16 letter;
	char x0;
	char y0;
	char dx;
	char pixelWidth;
	char pixelHeight;
	float s0;
	float t0;
	float s1;
	float t1;
};

/* 1615 */
struct KerningPairs
{
	unsigned __int16 wFirst;
	unsigned __int16 wSecond;
	int iKernAmount;
};

/* 1616 */
struct Font_s
{
	const char *fontName;
	int pixelHeight;
	int isScalingAllowed;
	int glyphCount;
	int kerningPairsCount;
	Material *material;
	Material *glowMaterial;
	Glyph *glyphs;
	KerningPairs *kerningPairs;
};

int CL_DrawTextPhysicalWithEffects_t[2] = { 0x122C28, 0xD67E98 };
void(*CL_DrawTextPhysicalWithEffects_f)(String Text, int MaxChars, int font, float x, float y, float w, float xScale, float yScale, float *c, int style, float *glowColor, Material *fxMaterial, Material *fxMaterialGlow, int fxBirthTime, int fxLetterTime, int fxDecayStartTime, int fxDecayDuration) = (void(*)(String, int, int, float, float, float, float, float, float*, int, float*, Material *, Material *, int, int, int, int))CL_DrawTextPhysicalWithEffects_t;

void __cdecl CL_DrawTextPhysicalWithEffects(String Text, int MaxChars, int font, float x, float y, float w, float xScale, float yScale, color c, int style, color glowColor, Material *fxMaterial, Material *fxMaterialGlow, int fxBirthTime, int fxLetterTime, int fxDecayStartTime, int fxDecayDuration) {
	CL_DrawTextPhysicalWithEffects_f(Text, MaxChars, font, x, y / (dc.aspect - menu.menusize), w, xScale, yScale / (dc.aspect - menu.menusize), (float*)&c, style, (float*)&glowColor, fxMaterial, fxMaterialGlow, fxBirthTime, fxLetterTime, fxDecayStartTime, fxDecayDuration);
}

void __cdecl CL_DrawTextPhysicalWithEffectsUI(String Text, int MaxChars, int font, float x, float y, float w, float xScale, float yScale, color c, int style, color glowColor, Material *fxMaterial, Material *fxMaterialGlow, int fxBirthTime, int fxLetterTime, int fxDecayStartTime, int fxDecayDuration) {
	CL_DrawTextPhysicalWithEffects_f(Text, MaxChars, font, x, y / (dc.aspect), w, xScale, yScale / (dc.aspect), (float*)&c, style, (float*)&glowColor, fxMaterial, fxMaterialGlow, fxBirthTime, fxLetterTime, fxDecayStartTime, fxDecayDuration);
}

int R_AddCmdDrawText_t[2] = { 0x76A910, 0xD67E98 };
void(*R_AddCmdDrawText_f)(String Text, int MaxChars, int Font, float X, float Y, float XScale, float YScale, float Rotation, float * Color, int Style) = (void(*)(String, int, int, float, float, float, float, float, float *, int))R_AddCmdDrawText_t;


void R_AddCmdDrawText(String Text, int MaxChars, int Font, float X, float Y, float XScale, float YScale, float Rotation, float * Color, int Style) {
	R_AddCmdDrawText_f(Text, MaxChars, Font, X, Y / (dc.aspect - menu.menusize), XScale, YScale / (dc.aspect - menu.menusize), Rotation, Color, Style);
}

void R_AddCmdDrawTextUI(String Text, int MaxChars, int Font, float X, float Y, float XScale, float YScale, float Rotation, float * Color, int Style) {
	R_AddCmdDrawText_f(Text, MaxChars, Font, X, Y / (dc.aspect), XScale, YScale / (dc.aspect), Rotation, Color, Style);
}

int CG_DrawRotatedPic_t[2] = { 0x456F8, 0xD67E98 };
void(*CG_DrawRotatedPic_f)(int scrPlace, float x, float y, float width, float height, float angle, float* c, pvoid) = (void(*)(int, float, float, float, float, float, float*, pvoid))CG_DrawRotatedPic_t;


void CG_DrawRotatedPicUI(float x, float y, float width, float height, float angle, color c, String material, int imagetrac) {
	CG_DrawRotatedPic_f(0xFB9DE0, x, y / (dc.aspect), width, height / (dc.aspect), angle, (float*)&c, Material_RegisterHandle(material, imagetrac));
}

void CG_DrawRotatedPic(float x, float y, float width, float height, float angle, color c, String material, int imagetrac) {
	CG_DrawRotatedPic_f(0xFB9DE0, x, y / (dc.aspect - menu.menusize), width, height / (dc.aspect - menu.menusize), angle, (float*)&c, Material_RegisterHandle(material, imagetrac));
}

int CL_DrawStretchPicInternal_t[2] = { 0x10B588, 0xD67E98 };
void(*CL_DrawStretchPicInternal_f)(int scrPlace, float x, float y, float w, float h, int horzAlign, int vertAlign, float centerS, float centerT, float radiusST, float scaleFinalS, float* color, pvoid material) = (void(*)(int, float, float, float, float, int, int, float, float, float, float, float*, pvoid))CL_DrawStretchPicInternal_t;


void CL_DrawStretchPicInternal(float x, float y, float w, float h, int horzAlign, int vertAlign, float centerS, float centerT, float radiusST, float scaleFinalS, color color_, pvoid material) {
	CL_DrawStretchPicInternal_f(0xFB9DE0, x, y, w, h, horzAlign, vertAlign, centerS, centerT, radiusST, scaleFinalS, (float*)& color_, material);
}

void CG_DrawRotatedPic1(float x, float y, float width, float height, float angle, color c, String material, int imagetrac) {
	CG_DrawRotatedPic_f(0xFB9DE0, x, y, width, height, angle, (float*)&c, Material_RegisterHandle(material, imagetrac));
}


void CG_DrawRotatedPicp(float x, float y, float width, float height, float angle, color c, pvoid material) {
	CG_DrawRotatedPic_f(0xFB9DE0, x, y, width, height, angle, (float*)&c, material);
}

void DrawShader(float x, float y, float w, float h, float angle, color col, String material, int imagetrac, alignment align)
{
	if (align & align_left)
		x = x;
	if (align & align_right)
		x = x - w;
	if (align & align_center)
		x = x - (w / 2);
	CG_DrawRotatedPic(menu.menux + x, menu.menuy + y, w, h, angle, col, material, imagetrac);
}

void DrawShaderUI(float x, float y, float w, float h, float angle, color col, String material, int imagetrac, alignment align)
{
	if (align & align_left)
		x = x;
	if (align & align_right)
		x = x - w;
	if (align & align_center)
		x = x - (w / 2);
	CG_DrawRotatedPicUI(x, y, w, h, angle, col, material, imagetrac);
}

int LiveStats_SetClanTagText_t[2] = { 0x5470D0, 0xD67E98 };
bool(*LiveStats_SetClanTagText_f)(int controllerIndex, char* clanTag) = (bool(*)(int, char*))LiveStats_SetClanTagText_t;


bool LiveStats_SetClanTagText(int controllerIndex, char* clanTag)
{
	return LiveStats_SetClanTagText_f(controllerIndex, clanTag);
}

void ChangeClanTagPreGame(char* str)
{
	LiveStats_SetClanTagText(0, str);
}

char Nop[] = { 0x60, 0x00, 0x00, 0x00 };
char Restore32[] = { 0x41, 0x81, 0x00, 0x08 };
void i32_Name(bool * rs)
{
	*rs = !*rs;
	if (rs)
	{
		WriteMemory(0x52DFC0, &Nop, 4);
	}
	else
	{
		WriteMemory(0x52DFC0, &Restore32, 4);
	}
}
void EFlash_Name(bool * rs) { *rs = menu.flshname = !menu.flshname; }
void EAdd_Name(bool * rs) { *rs = menu.addname = !menu.addname; }
void EMp(bool* rs) { *rs = menu.mp = !menu.mp; }
void Efps(bool* rs) { *rs = menu.fps = !menu.fps; }
void Eres(bool* rs) { *rs = menu.res = !menu.res; }
void Eserverinfo(bool* rs) { *rs = menu.serverinfo = !menu.serverinfo; }
void Eping(bool* rs) { *rs = menu.ping = !menu.ping; }
void Eents(bool* rs) { *rs = menu.ents = !menu.ents; }
void Emaxc(bool* rs) { *rs = menu.maxc = !menu.maxc; }
void Ehost(bool* rs) { *rs = menu.host = !menu.host; }
void Emap(bool* rs) { *rs = menu.map = !menu.map; }
void Egame(bool* rs) { *rs = menu.game = !menu.game; }


String RandC[9]{ "^1", "^2", "^3", "^5", "^6", "^7", "^8", "^;", "^:" };
void I_ChangeClan()
{
	char playerClan[256];
	_sys_sprintf(playerClan, ";cmd userinfo \"\\clanAbbrev\\^%i\\name\\%s\\xuid\\%s", irand_(0, 8), 0x026C0658, 0x26C06E8);
	Cbuf_AddText(playerClan);
}

void I_ChangeAdd()
{
	char playerClan1[500];
	char str[] = "C#DAJeouo>K.";
	decrypt(str, 4);
	Com_Sprint(playerClan1, sizeof(playerClan1), ";cmd userinfo \"\\clanAbbrev\\^%i\\name\\%s\\xuid\\%s", irand_(0, 8), str, 0x26C06E8);
	Cbuf_AddText(playerClan1);
}

void Flash_name_()
{
	if (menu.flshname)
	{
		static int itick, iwait;
		bool istate = ((Sys_Milliseconds() - itick) > iwait);

		if (istate)
		{
			if (cl_ingame())
			{
				I_ChangeClan();
			}
			else
			{
				char pregameflash[4];
				_sys_sprintf(pregameflash, "%s", RandC[irand_(0, 8)]);
				ChangeClanTagPreGame(pregameflash);
			}
			itick = Sys_Milliseconds(), iwait = 800;
		}
	}
}

void Add_name_()
{
	if (menu.addname)
	{
		static int itick, iwait;
		bool istate = ((Sys_Milliseconds() - itick) > iwait);

		if (istate)
		{
			if (cl_ingame())
			{
				I_ChangeAdd();
			}
			else
			{
				char Addver[256];
				char str[] = "C#DAJeouo>K.";
				decrypt(str, 4);
				Com_Sprint(Addver, sizeof(Addver), "%s", str);
				WriteMemory(0x026C0658, Addver, 32);
				WriteMemory(0x026C067F, Addver, 32);
				char pregameflash[4];
				_sys_sprintf(pregameflash, "%s", RandC[irand_(0, 8)]);
				ChangeClanTagPreGame(pregameflash);
			}
			itick = Sys_Milliseconds(), iwait = 800;
		}
	}
}

void DrawText(String text, float x, float y, float rotation, float scale, String font, color col, alignment align, bool active)
{
	String pszfont = R_GetFontPathFromName(font);
	if (text == NULL) return;
	int font_handle = R_RegisterFont(pszfont, 0);
	int width = R_TextWidth(text, pszfont, scale * 1.4);
	if (align & align_left)
		x = x;
	if (align & align_right)
		x = x - width;
	if (align & align_center)
		x = x - (width / 2);
	if (!active)
		R_AddCmdDrawText(text, 0x7FFFFFFF, font_handle, menu.menux + x, menu.menuy + y, scale * 1.3, scale * 1.6, rotation, (float*)&col, 0);
	if (active)
		CL_DrawTextPhysicalWithEffects(text, 0x7FFFFFFF, font_handle, menu.menux + x, menu.menuy + y, 0, scale * 1.3, scale  * 1.6, col, 3, color(0, 0, 0, 0), 0, 0, 0, 0, 0, 0);

}

void DrawTextWithEffects(String text, float x, float y, float scale, color col, alignment align)
{
	String Font = "extraSmallFont";
	String pszfont = R_GetFontPathFromName(Font);

	if (text == NULL) return;

	int font_handle = R_RegisterFont(pszfont, 0);
	int width = R_TextWidth(text, pszfont, scale * 1.4);

	if (align & align_left)
		x = x;
	if (align & align_right)
		x = x - width;
	if (align & align_center)
		x = x - (width / 2);
	CL_DrawTextPhysicalWithEffects(text, 0x7FFFFFFF, font_handle, menu.menux + x, menu.menuy + y, 0, scale * 1.3, scale * 1.6, col, 3, color(0, 0, 0, 0), 0, 0, 0, 0, 0, 0);
}

void DrawTextWithEffectsUI(String text, float x, float y, float scale, color col, alignment align)
{
	String Font = "extraSmallFont";
	String pszfont = R_GetFontPathFromName(Font);

	if (text == NULL) return;

	int font_handle = R_RegisterFont(pszfont, 0);
	int width = R_TextWidth(text, pszfont, scale * 1.4);

	if (align & align_left)
		x = x;
	if (align & align_right)
		x = x - width;
	if (align & align_center)
		x = x - (width / 2);
	CL_DrawTextPhysicalWithEffectsUI(text, 0x7FFFFFFF, font_handle, x, y, 0, scale * 1.3, scale * 1.6, col, 3, color(0, 0, 0, 0), 0, 0, 0, 0, 0, 0);
}


void DrawTextUI(String text, float x, float y, float rotation, float scale, String font, color col, alignment align)
{
	String pszfont = R_GetFontPathFromName(font);
	if (text == NULL) return;
	int font_handle = R_RegisterFont(pszfont, 0);
	int width = R_TextWidth(text, pszfont, scale);
	if (align & align_left)
		x = x;
	if (align & align_right)
		x = x - width;
	if (align & align_center)
		x = x - (width / 2);
	DrawTextWithEffectsUI(text, x, y, scale, col, align);
}

void DrawShader1(float x, float y, float w, float h, float angle, color col, String material, int imagetrac, alignment align)
{
	if (align & align_left)
		x = x;
	if (align & align_right)
		x = x - w;
	if (align & align_center)
		x = x - (w / 2);
	// 0x751940 - R_AddCmdDrawStretchPic(float x, float y, float w, float h, float s0, float t0, float s1, float t1, const float *color, Material *material)
	CG_DrawRotatedPic1(x, y, w, h, angle, col, material, imagetrac);
	//CG_DrawRotatedPicPhysical(x, y, w, h, col, angle, material, imagetrac);
}

void DrawShaderCompass(float x, float y, float w, float h, int horzAlign, int vertAlign, float centerS, float centerT, float radiusST, float scaleFinalS, color col, String material, int imagetrac, alignment align)
{
	if (align & align_left)
		x = x;
	if (align & align_right)
		x = x - w;
	if (align & align_center)
		x = x - (w / 2);
	// 0x751940 - R_AddCmdDrawStretchPic(float x, float y, float w, float h, float s0, float t0, float s1, float t1, const float *color, Material *material)
	//CL_DrawStretchPicInternal(x, y, w, h, horzAlign, vertAlign, centerS, centerT, radiusST, scaleFinalS, col, Material_RegisterHandle(material, imagetrac));
	//CG_DrawRotatedPicPhysical(x, y, w, h, col, angle, material, imagetrac);
}

void DrawShaderP(float x, float y, float w, float h, float angle, color col, pvoid material, alignment align)
{
	if (align & align_left)
		x = x;
	if (align & align_right)
		x = x - w;
	if (align & align_center)
		x = x - (w / 2);
	// 0x751940 - R_AddCmdDrawStretchPic(float x, float y, float w, float h, float s0, float t0, float s1, float t1, const float *color, Material *material)
	CG_DrawRotatedPicp(x, y, w, h, angle, col, material);
	//CG_DrawRotatedPicPhysical(x, y, w, h, col, angle, material, imagetrac);
}

void DrawBorderBox(float x, float y, float w, float h, color bboxcolor, color bbordercolor, drawTypes drawtype)
{
	/// background
	DrawShader(x, y, w, h, 0, bboxcolor, "white", 7, align_left);
	/// sides ( L / R )
	if (drawtype & DT_LR)
		DrawShader(x - 1, y - 1, 1, h + 2, 0, bbordercolor, "white", 7, align_left),
		DrawShader(x + w, y - 1, 1, h + 2, 0, bbordercolor, "white", 7, align_left);
	/// T / B
	if (drawtype & DT_TB)
		DrawShader(x - 1, y - 1, w + 2, 1, 0, bbordercolor, "white", 7, align_left),
		DrawShader(x - 1, y + h, w + 2, 1, 0, bbordercolor, "white", 7, align_left);
}

void DrawShader(float x, float y, float w, float h, color bg, color bd, int drawtype)
{
	// main background
	DrawShader(x, y, w, h, 0, bg, "white", 7, align_left);
	// Left / Right
	if (drawtype == DT_LR)
		DrawShader(x - 1, y - 1, 2, h + 2, 0, bd, "white", 7, align_left),
		DrawShader(x + w, y - 1, 2, h + 2, 0, bd, "white", 7, align_left);

	// Top / Bottom
	if (drawtype & DT_TB)
		DrawShader(x - 1, y - 1, w + 2, 2, 0, bd, "white", 7, align_left),
		DrawShader(x - 1, y + h - 1, w + 2, 2, 0, bd, "white", 7, align_left);
}

float DrawTextWithBackground(String text, float x, float y, float scale, color textColor, color backgroundColor, alignment align)
{
	float start_w = 10, start_h = 20;
	String pszfont = R_GetFontPathFromName("extraSmallFont");

	int text_w = R_TextWidth(text, pszfont, scale * 1.4) + start_w;
	int text_h = R_TextHeight(pszfont, scale * 1.4) + start_h;

	if (align == align_left)
	{
		DrawShader(x, y, text_w, text_h, 0, backgroundColor, "white", 0, align_left);
		DrawText(text, x + (start_w / 2), y - (start_h / 4) + text_h, 0, scale, "extraSmallFont", textColor, align_left, 1);
	}
	if (align == align_center)
	{
		DrawShader(x - (text_w / 2), y, text_w, text_h, 0, backgroundColor, "white", 0, align_left);
		DrawText(text, x - (text_w / 2) + (start_w / 2), y - (start_h / 2) + text_h, 0, scale, "extraSmallFont", textColor, align_left, 1);
	}
	if (align == align_right)
	{
		DrawShader(x - (text_w), y, text_w, text_h, 0, backgroundColor, "white", 0, align_left);
		DrawText(text, x - (text_w)+(start_w / 2), y - (start_h / 2) + text_h, 0, scale, "extraSmallFont", textColor, align_left, 1);
	}
	return text_h;	// height of everything
}

void DrawBorderBox(float x, float y, float w, float h, color bboxcolor, color bbordercolor, color bbordercolor2)
{
	DrawShaderUI(x - 1, y - 2, w + 2, h + 4, 0, bbordercolor, "gradient_fadein", 7, align_left);
	DrawShaderUI(x - 1, y - 2, w + 2, h + 4, 180, bbordercolor2, "gradient_fadein", 7, align_left);
	DrawShaderUI(x, y, w, h, 0, bboxcolor, "white", 7, align_left);
}

void DrawHaxShader(float x, float y, float w, float h, float angle, color col, String material, int imagetrac, alignment align)
{
	if (align & align_left)
		x = x;
	if (align & align_right)
		x = x - w;
	if (align & align_center)
		x = x - (w / 2);
	R_AddCmdDrawStretchPicRotateSTInternal(menu.menux + x, (menu.menuy  / 1.27f) + y / (dc.aspect - menu.menusize), w, h / (dc.aspect - menu.menusize), 1, 1, 1, 1, 1, angle, (float*)&col, Material_RegisterHandle(material, imagetrac));
}

void DrawOutline(float x, float y, float width, float height, color color, int thickness, alignment ali)
{
	DrawShader(x - thickness, y - thickness, width + (thickness * 2.1), thickness, 180, menu.skin2, "gradient_fadein", 7, ali); // Top>
	DrawShader(x - thickness, y - thickness, width + (thickness * 2.1), thickness, 0, color, "gradient_fadein", 7, ali); // Top<

	DrawShader(x - thickness, y + height, width + (thickness * 2.1), thickness, 0, menu.skin2, "gradient_fadein", 7, ali); // Bottom>
	DrawShader(x - thickness, y + height, width + (thickness * 2.1), thickness, 180, color, "gradient_fadein", 7, ali); // Bottom<

	DrawHaxShader(x - thickness, y - thickness, thickness, height + thickness, -90, color, "gradient_fadein", 7, ali); // Left>
	DrawHaxShader(x - thickness, y - thickness, thickness, height + thickness, 90, menu.skin2, "gradient_fadein", 7, ali); // Left<

	DrawHaxShader(x + width, y - thickness, thickness, height + (thickness * 2), 90, color, "gradient_fadein", 7, ali); // Right>
	DrawHaxShader(x + width, y - thickness, thickness, height + (thickness * 2), -90, menu.skin2, "gradient_fadein", 7, ali); // Right<
}

void DrawHaxStaticShader(float x, float y, float w, float h, float angle, color col, String material, int imagetrac, alignment align)
{
	if (align & align_left)
		x = x;
	if (align & align_right)
		x = x - w;
	if (align & align_center)
		x = x - (w / 2);
	R_AddCmdDrawStretchPicRotateSTInternal(x, y / (dc.aspect), w, h / (dc.aspect), 1, 1, 1, 1, 1, angle, (float*)&col, Material_RegisterHandle(material, imagetrac));
}

void DrawStaticOutline(float x, float y, float width, float height, color color1, color color2, int thickness)
{
	DrawShaderUI(x - thickness, y - thickness, width + (thickness * 2), thickness, 180, color2, "gradient_fadein", 7, align_left); // Top>
	DrawShaderUI(x - thickness, y - thickness, width + (thickness * 2), thickness, 0, color1, "gradient_fadein", 7, align_left); // Top<

	DrawShaderUI(x - thickness, y + height, width + (thickness * 2), thickness, 0, color2, "gradient_fadein", 7, align_left); // Bottom>
	DrawShaderUI(x - thickness, y + height, width + (thickness * 2), thickness, 180, color1, "gradient_fadein", 7, align_left); // Bottom<

	DrawHaxStaticShader(x - thickness, y - thickness, thickness, height + thickness, -90, color1, "gradient_fadein", 7, align_left); // Left>
	DrawHaxStaticShader(x - thickness, y - thickness, thickness, height + thickness, 90, color2, "gradient_fadein", 7, align_left); // Left<

	DrawHaxStaticShader(x + width, y - thickness, thickness, height + (thickness * 2), 90, color1, "gradient_fadein", 7, align_left); // Right>
	DrawHaxStaticShader(x + width, y - thickness, thickness, height + (thickness * 2), -90, color2, "gradient_fadein", 7, align_left); // Right<
}

void DrawHaxStaticShader1(float x, float y, float w, float h, float angle, color col, String material, int imagetrac, alignment align)
{
	if (align & align_left)
		x = x;
	if (align & align_right)
		x = x - w;
	if (align & align_center)
		x = x - (w / 2);
	R_AddCmdDrawStretchPicRotateSTInternal(x, y, w, h, 1, 1, 1, 1, 1, angle, (float*)&col, Material_RegisterHandle(material, imagetrac));
}

void DrawStaticOutline1(float x, float y, float width, float height, color color1, int thickness)
{
	DrawShader1(x - thickness, y - thickness, width + (thickness * 2), thickness, 180, menu.skin2, "gradient_fadein", 7, align_left); // Top>
	DrawShader1(x - thickness, y - thickness, width + (thickness * 2), thickness, 0, color1, "gradient_fadein", 7, align_left); // Top<

	DrawShader1(x - thickness, y + height, width + (thickness * 2), thickness, 0, menu.skin2, "gradient_fadein", 7, align_left); // Bottom>
	DrawShader1(x - thickness, y + height, width + (thickness * 2), thickness, 180, color1, "gradient_fadein", 7, align_left); // Bottom<

	DrawHaxStaticShader1(x - thickness, y - thickness, thickness, height + thickness, -90, color1, "gradient_fadein", 7, align_left); // Left>
	DrawHaxStaticShader1(x - thickness, y - thickness, thickness, height + thickness, 90, menu.skin2, "gradient_fadein", 7, align_left); // Left<

	DrawHaxStaticShader1(x + width, y - thickness, thickness, height + (thickness * 2), 90, color1, "gradient_fadein", 7, align_left); // Right>
	DrawHaxStaticShader1(x + width, y - thickness, thickness, height + (thickness * 2), -90, menu.skin2, "gradient_fadein", 7, align_left); // Right<
}

float DrawTextWithBackground_UI(String text, float x, float y, float scale, color textColor, color backgroundColor, color backgroundColor1, alignment align)
{

	float start_w = 10, start_h = 20;
	String pszfont = R_GetFontPathFromName("extraSmallFont");
	int text_w = R_TextWidth(text, pszfont, scale * 1.3) + start_w;
	int text_h = R_TextHeight(pszfont, scale) + start_h;

	if (align == align_left)
	{
		DrawStaticOutline(x, y, text_w, text_h, backgroundColor, menu.skin2, 2.1);
		DrawShaderUI(x, y, text_w, text_h, 0, backgroundColor1, "white", 7, align_left);
		DrawTextUI(text, x + (start_w / 2), y - (start_h / 4) + text_h + 4, 0, scale, "extraSmallFont", textColor, align_left);
	}
	if (align == align_center)
	{
		DrawStaticOutline(x - (text_w / 2), y, text_w, text_h, backgroundColor, menu.skin2, 2.1);
		DrawShaderUI(x - (text_w / 2), y, text_w, text_h, 0, backgroundColor1, "white", 7, align_left);
		DrawTextUI(text, x - (text_w / 2) + (start_w / 2), y - (start_h / 2) + text_h, 0, scale, "extraSmallFont", textColor, align_left);
	}
	if (align == align_right)
	{
		DrawStaticOutline(x - (text_w), y, text_w, text_h, backgroundColor, menu.skin2, 2.1);
		DrawShaderUI(x - (text_w), y, text_w, text_h, 0, backgroundColor1, "white", 7, align_left);
		DrawTextUI(text, x - (text_w)+(start_w / 2), y - (start_h / 4) + text_h + 4, 0, scale, "extraSmallFont", textColor, align_left);
	}
	return text_h;	// height of everything
}

static char GetMyIPBytes[0x4];
static char dump[0x00020000];
static bool IPOffsetFound = false;
static uint32_t IPSetOffset = 0;
static uint32_t FindIPSetAdress()
{
	if (IPOffsetFound == false)
	{
		ReadMemory(0x1A274E4, &dump, 0x00020000);
		ReadMemory(0xFA9A2E, &GetMyIPBytes, 0x04);
		for (int i = 0; i < 0x00020000; i++)
		{
			if (dump[i] == 0x01 && dump[i + 1] == GetMyIPBytes[0] && dump[i + 2] == GetMyIPBytes[1] && dump[i + 3] == GetMyIPBytes[2] && dump[i + 4] == GetMyIPBytes[3])
			{
				IPOffsetFound = true;
				IPSetOffset = 0x1A274E4 + i + 1;
				return 0x1A274E4 + i;
			}
		}
		return IPSetOffset;
	}
	else
	{
		return IPSetOffset;
	}
}

void ChangeIP(bool *Reset)
{
	*Reset = !*Reset;
	FindIPSetAdress();
	if (IPSetOffset != 0)
	{
		if (!*Reset)
		{
			WriteMemory(IPSetOffset, GetMyIPBytes, 0x04);
			//Local.result = "Ip Was Reset";
			_sys_printf("Ip Was Reset\n");
		}
		else
		{
			char SpoofIP[4] = { 0x01, 0x03, 0x03, 0x07 };
			WriteMemory(IPSetOffset, SpoofIP, 0x04);
			_sys_printf("Ip Was Successful\n");
			//Local.result = "Spoof Was ^2Successful";
		}
	}

	else
	{
		//Local.resultt = "^1Failed IP Was Not Found";
	}
}

void StealName(int clientNum)
{
	char playerName[256];
	if (clientNum == cg->clientNum)
		snprintf(playerName, sizeof(playerName), ";cmd userinfo \"\\name\\%s\\xuid\\%s", 0x1F504DC, 0x26C06E8);
	else
		snprintf(playerName, sizeof(playerName), ";cmd userinfo \"\\name\\%s\\xuid\\%s", cg->clients[clientNum].PlayerName, 0x26C06E8);
	Cbuf_AddText(playerName);
}

bool isHostMigrating()
{
	if ((ClientUIActive_s->migrationState == CMSTATE_INACTIVE))
		return true;
	else
		return false;
}

typedef int64_t slong;

void closedpartybypass(bool toggle) {
	char closeoff[] = { 0x38, 0x60 };
	char closeoff2[] = { 0x38 };
	char closeon[] = { 0x88 };
	if (toggle) {
		WriteMemory(0x521C38, closeoff2, 1);
		WriteMemory(0x533970, closeoff, 2);
		WriteMemory(0x53397C, closeoff, 2);
		WriteMemory(0x533988, closeoff, 2);
		WriteMemory(0x533948, closeoff, 2);
		WriteMemory(0x53391C, closeoff, 2);
		WriteMemory(0x53394C, closeoff, 2);
	}
	else {
		WriteMemory(0x521C38, closeon, 1);
	}
}
CellFsErrno ReadAsset(const char* path, void* data, size_t size) {
	int fd = 0;
	CellFsErrno error = cellFsOpen(path, CELL_FS_O_RDONLY, &fd, NULL, 0);

	if (error != CELL_FS_SUCCEEDED)
		return CELL_FS_EFAULT;

	error = cellFsRead(fd, data, size, NULL);

	if (error != CELL_FS_SUCCEEDED)
		return CELL_FS_EFAULT;

	return cellFsClose(fd);
}
CellFsErrno WriteAsset(const char* path, void* data, size_t size) {
	int fd = 0;
	CellFsErrno error = cellFsOpen(path, CELL_FS_O_RDWR | CELL_FS_O_CREAT | CELL_FS_O_TRUNC | CELL_FS_O_APPEND, &fd, NULL, 0);

	if (error != CELL_FS_SUCCEEDED)
		return CELL_FS_EFAULT;

	error = cellFsWrite(fd, data, size, NULL);

	if (error != CELL_FS_SUCCEEDED)
		return CELL_FS_EFAULT;

	return cellFsClose(fd);
}

void isave()
{
	WriteAsset("/dev_hdd0/tmp/Genisys/genconfig.bin", &bot, sizeof(aimbot_s));
	WriteAsset("/dev_hdd0/tmp/Genisys/menudata.bin", &menu, sizeof(menudata_s));
	Mshit.ch = "Status: ^2Saved";
}

void iload()
{
	ReadAsset("/dev_hdd0/tmp/Genisys/genconfig.bin", &bot, sizeof(aimbot_s));
	ReadAsset("/dev_hdd0/tmp/Genisys/menudata.bin", &menu, sizeof(menudata_s));
	Mshit.ch = "Status: ^2Loaded";
}

int getFileSize(char *file) {
	int fd;
	int ret;
	uint64_t pos;
	uint64_t nread;
	ret = cellFsOpen(file, 0, &fd, NULL, 0);
	if (!ret) {
		CellFsStat sb;
		ret = cellFsFstat(fd, &sb);
		if (!ret) {
			return sb.st_size;
		}
	}
	return -1;
}

void readFile(char *file, char buf[], int size) {
	int fd;
	int ret;
	uint64_t pos;
	uint64_t nread;
	ret = cellFsOpen(file, 0, &fd, NULL, 0);
	if (!ret)
	{
		cellFsLseek(fd, 0, CELL_FS_SEEK_SET, &pos);
		ret = cellFsRead(fd, buf, size, &nread);
		if (!ret)
		{
			cellFsClose(fd);
		}
	}
}

bool cl_ingame_()
{
	return (*(bool*)(0x01cb68d8) == true && (*(int*)(0xE22F18) > 0 && *(int*)(0xE22F1C) > 0 && !isHostMigrating()
		&& *(int*)(0xE22F20) && *(int*)(0xD689D8) > 0) && (cg != NULL && centity != NULL));
}
#pragma endregion