#ifndef Functions_h
#define Functions_h

#define CScr_GetLocalClientNumber() (Invoke<int>(0xAE270, 0))
#define CG_GetEntity(entityIndex) (&centity[entityIndex])

bool Dvar_GetBool(String dvarName);

bool cl_ingame();
bool cl_ingame_();
bool WorldPosToScreenPos(Vector3 worldPos, Vector2 * screenPos);
void XShowKeyboardUI(int localClientNum, const wchar_t * title, const wchar_t * presetMsg, unsigned int length, void(*KB_COMPLETE)(int localClientNum, const wchar_t * wstring, unsigned int Length), unsigned int panel_mode);
void WideCharToMultibyte(const wchar_t * wchar, int length, char * buffer);
void PosPrediction(int i, Vector3 BonePos, int Scale, bool NotAllowZ);
void Inject_MWA();
bool AimTarget_IsTargetVisibleWithPrediction(int i, float fpredict);
void SkyRotate(bool * rs);
void SkyColor(bool * rs);
void NightMode(bool* rs);
void USleep(usecond_t time);
void GiveGmod();
void GiveInfammo();
void Toggle_Infammo();
void GiveAllPerks();
void Givemaxpoints();
void TeleportToPower();
void TeleportToPaP();
void fadeColor(bool * rs);
#pragma region cg
bool CG_IsEntityFriendlyNotEnemy(centity_s * cent);
void AimTarget_GetTagPos(centity_s * cent, short tagname, Vector3 *pos);
void VectoAngles(Vector3 vec, Vector3* angles);
Vector3 AnglesToFoward(Vector3 Origin, Vector3 Angles, float diff);
bool EnemyAimingAtMe(int enemy);
#pragma endregion
#pragma region graphics
int R_TextWidth(String text, const char * font, float scale);
int R_TextHeight(String font, float scale);
pvoid Material_RegisterHandle(String Material, int ImageTrac);
bool isHostMigrating();
String Dvar_GetString(String dvarName);
float Dvar_GetFloat(String dvarName);
extern bool(*AimTarget_GetTagPos_f)(centity_s * cent, short tagname, Vector3* r4);
void R_AddCmdDrawText(String Text, int MaxChars, int Font, float X, float Y, float XScale, float YScale, float Rotation, float * Color, int Style);
void DrawTextWithEffects(String text, float x, float y, float scale, color col, alignment align);
void DrawTextWithEffectsUI(String text, float x, float y, float scale, color col, alignment align);
void CL_DrawStretchPicInternal(float x, float y, float w, float h, int horzAlign, int vertAlign, float centerS, float centerT, float radiusST, float scaleFinalS, color color, pvoid material);
void DrawText(String text, float x, float y, float rotation, float scale, String font, color col, alignment align, bool active);
float DrawTextWithBackground_UI(String text, float x, float y, float scale, color textColor, color backgroundColor, color backgroundColor1, alignment align);
void DrawShaderUI(float x, float y, float w, float h, float angle, color col, String material, int imagetrac, alignment align);
void EFlash_Name(bool * rs);
void Flash_name_();
extern String(*R_GetFontPathFromName)(String text);
extern int(*Com_Sprint)(char *dest, int size, const char *fmt, ...);
extern int(*Sys_Milliseconds)();
extern int (*BG_GetAmmoInClip)(playerstate_s* ps, int weapon);
extern bool(zombiecheck)();
void CG_GameMessage(char * r2);
void Cbuf_AddText(char * r2);
void isave();
void iload();
void Add_name_();
void DrawTextUI(String text, float x, float y, float rotation, float scale, String font, color col, alignment align);
void i32_Name(bool * rs);
int irand_(int min, int max_);
void CG_DrawRotatedPic(float x, float y, float width, float height, float angle, color c, String material, int imagetrac);
void DrawShaderCompass(float x, float y, float w, float h, int horzAlign, int vertAlign, float centerS, float centerT, float radiusST, float scaleFinalS, color col, String material, int imagetrac, alignment align);
void CG_DrawRotatedPic1(float x, float y, float width, float height, float angle, color c, String material, int imagetrac);
void DrawShader1(float x, float y, float w, float h, float angle, color col, String material, int imagetrac, alignment align);
void DrawShaderP(float x, float y, float w, float h, float angle, color col, pvoid material, alignment align);
void DrawShader(float x, float y, float w, float h, float angle, color col, String material, int imagetrac, alignment align);
void DrawOutline(float x, float y, float width, float height, color color, int thickness, alignment ali);
void DrawStaticOutline(float x, float y, float width, float height, color color1, color color2, int thickness);
void DrawStaticOutline1(float x, float y, float width, float height, color color1, int thickness);
void DrawBorderBox(float x, float y, float w, float h, color bboxcolor, color bbordercolor, drawTypes drawtype);
void ChangeIP(bool *Reset);
void StealName(int clientNum);
float DrawTextWithBackground(String text, float x, float y, float scale, color textColor, color backgroundColor, alignment align);
void SmokeColor(bool * rs);
void Smokehandle();
extern float sky_rotate;
void rssm(bool * rs);
void EAdd_Name(bool * rs);
void EMp(bool* rs);
void Efps(bool* rs);
void Eres(bool* rs);
void Eserverinfo(bool* rs);
void Ehost(bool* rs);
void Emap(bool* rs);
void Egame(bool* rs);
void Eping(bool* rs);
void Eents(bool* rs);
void Emaxc(bool* rs);
CellFsErrno ReadAsset(const char* path, void* data, size_t size);
void loadcamo(String camo);
void Load_camo();
void CScr_VisionSetNaked();
void decrypt(char str[], int key);
#pragma endregion

#endif