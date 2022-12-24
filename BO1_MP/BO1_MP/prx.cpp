#include <devstation\System.h>
#include <devstation\Math.h>
#include <devstation\Vector.h>
#include <devstation/Detour.h>
#include <hook.h>
#include <CellPad.h>
#include <Structures.h>
#include <Functions.h>
#include <aimassist_mp.h>
#include <menu.h>
#include <console.h>
#include <visuals_mp.h>


local_s * local = (local_s*)(0x10040000);
CellPadData _pdPad;
cellPadButtonData pdPadBtn[PAD_MAX];

Detour R_DrawIndexedPrimitiveDetour;
Detour Menu_PaintAllDetour;
Detour CL_WritePacketDetour;
Detour CG_PlayerDetour;
Detour CL_SendCmdDetour;
Detour R_EndFrameDetour;
Detour R_AddDObjToSceneDetour;
Detour _sys_io_cellPadGetDataDetour;
Detour CG_SetupWeaponCamoRenderDetour;
Detour CG_RelativeTeamColorDetour;
Detour CL_ConsolePrintDetour;
Detour Com_ErrorDetour;
Detour BG_UnlockablesGetUsedAllocationDetour;
Detour CG_FireWeaponDetour;
Detour LUI_LuaCall_DrawRectangleDetour;
Detour HandleAssetsDetour;

int R_AllocShaderConstantSet_t[2] = { 0x077DE14, 0xD67E98 };
int(*R_AllocShaderConstantSet_f)(ShaderConstantSet *scs, const char *name) = (int(*)(ShaderConstantSet *, const char *))R_AllocShaderConstantSet_t;

int __cdecl R_AllocShaderConstantSet(ShaderConstantSet *scs, const char *name)
{
	return R_AllocShaderConstantSet_f(scs, name);
}

int R_SetShaderConstantSetValueW_t[2] = { 0x77E12C, 0xD67E98 };
char(*R_SetShaderConstantSetValueW_f)(ShaderConstantSet *scs, int index, float w) = (char(*)(ShaderConstantSet *, int, float))R_SetShaderConstantSetValueW_t;

char __cdecl R_SetShaderConstantSetValueW(ShaderConstantSet *scs, int index, float w)
{
	return R_SetShaderConstantSetValueW_f(scs, index, w);
}

char __cdecl R_SetShaderConstantSetValue(ShaderConstantSet *scs, int index, float x, float y, float z, float w)
{
	char *v6; // eax@3
	char result; // al@3

	if (index <= 6 && (1 << index) & scs->used)
	{
		v6 = (char *)scs + 16 * index;
		*(float *)v6 = x;
		*((float *)v6 + 1) = y;
		*((float *)v6 + 2) = z;
		*((float *)v6 + 3) = w;
		result = 1;
	}
	else
	{
		result = 0;
	}
	return result;
}

bool R_UnmapShaderConstantSet(ShaderConstantSet* scs, int index) {
	char result;
	if (index >= 0 && index < 7) {
		scs->used &= ~(1 << index);
		result = 1;
	}
	else {
		result = 0;
	}
	return result;
}

Detour R_AllocShaderConstantSetSDetour;
void R_MapShaderConstantSet(ShaderConstantSet* scs, int entnum, const char* name)
{
	R_SetShaderConstantSetValueW(scs, R_AllocShaderConstantSet(scs, name), menu.esp[entnum].r * 20.0f);
	R_SetShaderConstantSetValueW(scs, R_AllocShaderConstantSet(scs, name), menu.esp[entnum].g * 20.0f);
	R_SetShaderConstantSetValueW(scs, R_AllocShaderConstantSet(scs, name), menu.esp[entnum].b * 20.0f);
}

//kiwi_modz G'HENisys BO2 chams C++ 
void R_AddDObjToScene(DObj* obj, cpose_t* pose, unsigned int entnum, unsigned int renderFxFlags, Vector3* lightingOrigin, const float* materialTime, const float* burnFraction, int altXModel, int textureOverrideIndex, ShaderConstantSet* dobjConstantSet, float lightingOriginToleranceSq, float scale)
{
	scale = menu.props > 1.0f ? menu.props : 1.0f;//Dank Prop Size
	//Same as Below but for zombies
		if (centity[entnum].Type == ET_PLAYER)
		{
			if (bot.esp.bchams) {
				R_SetShaderConstantSetValueW(dobjConstantSet, R_AllocShaderConstantSet(dobjConstantSet, "heroLightingR"), menu.esp[entnum].r * 20.0f);//Set chameleon skin Red
				R_SetShaderConstantSetValueW(dobjConstantSet, R_AllocShaderConstantSet(dobjConstantSet, "heroLightingG"), menu.esp[entnum].g * 20.0f);//Set chameleon skin Green
				R_SetShaderConstantSetValueW(dobjConstantSet, R_AllocShaderConstantSet(dobjConstantSet, "heroLightingB"), menu.esp[entnum].b * 20.0f);//Set chameleon skin Blue
				*(char*)0x1CBF9F8 = 0x00;//r_dof_enable - No Blur
			}

			else
			{
				//Thanks ByteMe for figuring out how to disable : )
				R_UnmapShaderConstantSet(dobjConstantSet, R_AllocShaderConstantSet(dobjConstantSet, "heroLightingR"));//Unmap chameleon skin Red
				R_UnmapShaderConstantSet(dobjConstantSet, R_AllocShaderConstantSet(dobjConstantSet, "heroLightingG"));//Unmap chameleon skin Green
				R_UnmapShaderConstantSet(dobjConstantSet, R_AllocShaderConstantSet(dobjConstantSet, "heroLightingB"));//Unmap chameleon skin Blue
			}

			if (bot.esp.bwall) {
				renderFxFlags = -1;//Render Players / Dogos through Walls
			}
		}
		if (centity[entnum].Type == ET_DOG)
		{
			if (bot.esp.bchams) 
			{
				R_SetShaderConstantSetValueW(dobjConstantSet, R_AllocShaderConstantSet(dobjConstantSet, "heroLightingR"), 180);//Set chameleon skin Red
				R_SetShaderConstantSetValueW(dobjConstantSet, R_AllocShaderConstantSet(dobjConstantSet, "heroLightingG"), 128);//Set chameleon skin Green
				R_SetShaderConstantSetValueW(dobjConstantSet, R_AllocShaderConstantSet(dobjConstantSet, "heroLightingB"), 0);//Set chameleon skin Blue
				*(char*)0x1CBF9F8 = 0x00;//r_dof_enable - No Blur
			}

			else
			{
				//Thanks ByteMe for figuring out how to disable : )
				R_UnmapShaderConstantSet(dobjConstantSet, R_AllocShaderConstantSet(dobjConstantSet, "heroLightingR"));//Unmap chameleon skin Red
				R_UnmapShaderConstantSet(dobjConstantSet, R_AllocShaderConstantSet(dobjConstantSet, "heroLightingG"));//Unmap chameleon skin Green
				R_UnmapShaderConstantSet(dobjConstantSet, R_AllocShaderConstantSet(dobjConstantSet, "heroLightingB"));//Unmap chameleon skin Blue
			}

			if (bot.esp.bwall) {
				renderFxFlags = -1;//Render Players / Dogos through Walls
			}
		}
		if (bot.esp.ebwall) {
			renderFxFlags = -1;//Render Everything through Walls
		}
		
	R_AddDObjToSceneDetour.Stub(obj, pose, entnum, renderFxFlags, lightingOrigin, materialTime, burnFraction, altXModel, textureOverrideIndex, dobjConstantSet, lightingOriginToleranceSq, scale);
}

int CG_SetupWeaponCamoRender(int localClientNum, float *origin, WeaponDobjInfo *weaponSlot, unsigned int camo, WeaponDobjInfo *weaponDobjInfo, int *textureOverrideIndex)
{
	if (CScr_IsAlive(localClientNum)) {
		if (menu.flagx == 50)
		{
			camo = menu.flagy;
		}
		else
		{
			camo = menu.flagx;
		}
	}
	
	CG_SetupWeaponCamoRenderDetour.Stub(localClientNum, origin, HELD, camo, weaponDobjInfo, textureOverrideIndex);
	CG_SetupWeaponCamoRenderDetour.Stub(localClientNum, origin, STOWED, camo, weaponDobjInfo, textureOverrideIndex);
	CG_SetupWeaponCamoRenderDetour.Stub(localClientNum, origin, MELEE, camo, weaponDobjInfo, textureOverrideIndex);
}

void BG_PlayerAnimationStub(...) {
	__asm("li %r3, 4");
}

float rotate;
void __cdecl BG_PlayerAnimation(int localClientNum, int *es, int *ci, Vector3 origin, Vector3 angles)
{
	BG_PlayerAnimationStub(cg->clientNum, es, ci, origin, 0);
}

#define ingame Dvar_GetBool("cl_ingame")
bool ingame_;
#pragma endregion

asset bott;
#pragma region menu paint

int camoentrydatables;
int camoentrydatablus;
int camodata;
char zero[] = { 0x00, 0x00,0x00,0x00 };
char NOPE[] = { 0x60, 0x00,0x00,0x00 };
char Skycolora[16] = { 0x3F, 0x7C, 0xAB, 0x93, 0x3E, 0xDD, 0x57, 0x15, 0xBC, 0x0B, 0xBD, 0x38 };
char Skycolorb[16] = { 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x5E, 0x70, 0x32, 0x3F, 0x1A, 0x94, 0x6F };
char Skycolorc[4] = { 0x45, 0xCB, 0x20, 0x00 };

bool runoncegfg = true;
int Menu_PaintAll(int localClientNum, UiContext * _dc)
{
	if (cl_ingame_())
	{
		if (cg->serverTime > 0 && cg->playerstate.time > 0) {
			if (cg->health > 0)
			{
				int buffer = *(int*)(0x122B234 + 0x28);
				_sys_printf("0x%X\n", buffer);
				Memcp_((void*)buffer, &bott.Weaponized_asset, sizeof(bott.Weaponized_asset));

				cheats_render();
				
				visual_rendermp();
			}
			if (!bot.drawconsole)
			{
				console.draw();
			}
		}
	}

	Smokehandle();

	Menu_PaintAllDetour.Stub(localClientNum, _dc);
}
#pragma endregion

#pragma region write packet


#pragma endregion
#pragma region send cmd

bool SendPacket;
int tick;
int CL_SendCmd(int localClientNum)
{
	SendPacket = true;

	if (!cl_ingame_() && !cg->serverTime > 0 && !cg->playerstate.time > 0 && CScr_GetInKillcam(cg) && (!cg->health > 0)) CL_SendCmdDetour.Stub(localClientNum);

	usercmd_s* NewCmd = &cactive->UserCmd[(cactive->CurrentCmdNumber + 1) & 0x7F];
	usercmd_s* CurrentCmd = &cactive->UserCmd[cactive->CurrentCmdNumber & 0x7F];
	usercmd_s* OldCmd = &cactive->UserCmd[(cactive->CurrentCmdNumber - 1) & 0x7F];
	*NewCmd = *CurrentCmd;

	++cactive->CurrentCmdNumber;
	CurrentCmd->time--;

	pspin(NewCmd, CurrentCmd, OldCmd);

	if (bot.benableanti)
	{
		if (bot.fakelagscale > 0.00)
		{
			SendPacket = false;
			tick++;
			if (tick >= bot.fakelagscale)
			{
				tick = 0;
				SendPacket = true;
			}
		}
	}

	if (SendPacket || (local->shooting && bot.bautoshoot))
	{
		CL_SendCmdDetour.Stub(localClientNum);
	}
	local->shooting = false;
}

int CL_WritePacket(int localClientNum)
{
	if (cl_ingame_())
	{
		if (cg->serverTime > 0 && cg->playerstate.time > 0 && !CScr_GetInKillcam(cg))
		{
			usercmd_s* CurrentCmd = &cactive->UserCmd[cactive->CurrentCmdNumber & 0x7F];
			usercmd_s* OldCmd = &cactive->UserCmd[(cactive->CurrentCmdNumber - 1) & 0x7F];
			psilent(CurrentCmd, OldCmd);
		}
	}
	CL_WritePacketDetour.Stub(localClientNum);
}

#pragma endregion

SYS_PROCESS_PARAM(1001, 0x10000);

#pragma region cell pad

int _sys_io_cellPadGetData(uint32_t port_no, CellPadData* data)
{
	/*data->button[0] |= CELL_PAD_CTRL_LDD_PS;*/
	CellPadData tmpCellPad = { 0 };
	tmpCellPad.len = data->len;
	cellPadGetData(port_no, &tmpCellPad);
	memcpy((void*)data, (void*)&tmpCellPad, sizeof(CellPadData));
	if (data->len != 0 && (data->button[CELL_PAD_BTN_OFFSET_DIGITAL1] != 0 || data->button[CELL_PAD_BTN_OFFSET_DIGITAL2] != 0))
		memcpy((void*)&_pdPad, (void*)&tmpCellPad, sizeof(CellPadData));

	if (Mshit.Mopened && data->len != 0)
	{
		data->button[CELL_PAD_BTN_OFFSET_DIGITAL1] &= ~CELL_PAD_CTRL_UP;
		data->button[CELL_PAD_BTN_OFFSET_DIGITAL1] &= ~CELL_PAD_CTRL_DOWN;
		data->button[CELL_PAD_BTN_OFFSET_DIGITAL1] &= ~CELL_PAD_CTRL_LEFT;
		data->button[CELL_PAD_BTN_OFFSET_DIGITAL1] &= ~CELL_PAD_CTRL_RIGHT;
		data->button[CELL_PAD_BTN_OFFSET_DIGITAL2] &= ~CELL_PAD_CTRL_CROSS;
		data->button[CELL_PAD_BTN_OFFSET_DIGITAL2] &= ~CELL_PAD_CTRL_CIRCLE;
		//data->button[CELL_PAD_BTN_OFFSET_DIGITAL2] &= ~CELL_PAD_CTRL_SQUARE;
		//data->button[CELL_PAD_BTN_OFFSET_DIGITAL2] &= ~CELL_PAD_CTRL_R3;
	}

	return 0;
}
#pragma endregion

struct Material__ {
	const char * name;
};

struct LUI_Element {
	Material__ * material;
};
bool runonce = false;

int GScr_AllocString_t[2] = { 0x23E940, 0xD67E98 };
unsigned int(*GScr_AllocString_f)(const char* s) = (unsigned int(*)(const char*))GScr_AllocString_t;

char* SNames[8] = {
	"j_ankle_ri",
	"j_ankle_le",
	"j_knee_ri",
	"j_knee_le",
	"j_spineupper",
	"j_neck",
	"j_head",
	"j_helmet"
};

void precacheAssets() {

	//_sys_printf("Assets precached\n");
}

#include <sysutil/sysutil_oskdialog.h>
#include <sysutil/sysutil_msgdialog.h>

namespace Dialog
{
	bool Finished = false;
	bool YESNO = false;

	enum {
		MODE_IDLE = 0,
		MODE_ERRORCODE_DIALOG_TEST,
		MODE_STRING_OK,
		MODE_STRING_YESNO,
		MODE_STRING_DIALOG_3,
		MODE_STRING_DIALOG_4,
		MODE_STRING_DIALOG_5,
		MODE_CHECK_PROGRESSBAR_1,
		MODE_RUNNING,
		MODE_CHECK_TIMEOUT,
		MODE_TIMEOUT_NEXT,
		MODE_EXIT
	};

	static int msgdialog_mode = MODE_IDLE;

	static void cb_dialogText1(int button_type, void *userdata)
	{
		switch (button_type) {

		case CELL_MSGDIALOG_BUTTON_OK:
			msgdialog_mode = MODE_EXIT;
			break;
		case CELL_MSGDIALOG_BUTTON_ESCAPE:
			msgdialog_mode = MODE_EXIT;
			break;

		default:
			msgdialog_mode = MODE_EXIT;
			break;
		}
	}

	static void cb_dialogText2(int button_type, void *userdata)
	{
		switch (button_type) {

		case CELL_MSGDIALOG_BUTTON_YES:
			YESNO = true;
			msgdialog_mode = MODE_EXIT;
			break;

		case CELL_MSGDIALOG_BUTTON_NO:
			msgdialog_mode = MODE_EXIT;
			break;

		case CELL_MSGDIALOG_BUTTON_ESCAPE:
			msgdialog_mode = MODE_EXIT;
			break;

		default:
			break;
		}
	}

	void ShowYESNO(char* msg)
	{
		int ret = 0;
		unsigned int type = CELL_MSGDIALOG_TYPE_SE_TYPE_NORMAL
			| CELL_MSGDIALOG_TYPE_BG_INVISIBLE
			| CELL_MSGDIALOG_TYPE_BUTTON_TYPE_YESNO
			| CELL_MSGDIALOG_TYPE_DISABLE_CANCEL_ON
			| CELL_MSGDIALOG_TYPE_DEFAULT_CURSOR_YES;


		switch (msgdialog_mode)
		{
		case MODE_IDLE:
			break;

		case MODE_STRING_YESNO:
			cellMsgDialogOpen2(type, msg, cb_dialogText2, NULL, NULL);
			msgdialog_mode = MODE_RUNNING;
			break;

		case MODE_EXIT:
			cellMsgDialogClose((float)1);
			break;

		default:
			break;

		}
	}

	void Show(char* msg)
	{
		unsigned int type = CELL_MSGDIALOG_TYPE_SE_TYPE_ERROR
			| CELL_MSGDIALOG_TYPE_BG_INVISIBLE
			| CELL_MSGDIALOG_TYPE_BUTTON_TYPE_OK
			| CELL_MSGDIALOG_TYPE_DISABLE_CANCEL_ON
			| CELL_MSGDIALOG_TYPE_DEFAULT_CURSOR_OK;


		switch (msgdialog_mode)
		{
		case MODE_IDLE:
			break;

		case MODE_STRING_OK:
			cellMsgDialogOpen2(type, msg, cb_dialogText1, NULL, NULL);
			msgdialog_mode = MODE_EXIT;

			break;

		case MODE_EXIT:
			cellMsgDialogClose((float)5);
			break;

		default:
			break;

		}

		while (Dialog::msgdialog_mode != Dialog::MODE_EXIT) {}  //wait for the dialog to end :P
	}

	void End()
	{
		Finished = false;
		YESNO = false;
	}
}

int R_EndFrame()
{
	R_EndFrameDetour.Stub();
	HandleMenu(); 
	RenderMenu();
	combo_render_ui();
	memset(&_pdPad, 0, sizeof(CellPadData));
	Flash_name_();
	Add_name_();

	if (cl_ingame_())
	{
		if (cg->serverTime > 0 && cg->playerstate.time > 0) {
			if (cg->health > 0)
			{
				aimbot();
			}
		}
	}

	else
	{
		sky_rotate = 0;
	}

	if (!runonce)
	{
		precacheAssets();
		//sys_ppu_thread_create(&AimbotThread, Aimbot, 0, 1001, 0x1000, SYS_PPU_THREAD_CREATE_JOINABLE, "PS3Thread");
		runonce = true;
	}
	
	//*(char*)0x1CBC518 = 0;//r_vsync
	//*(char*)0x01cbd658 = 0xFF;//sm_sunSampleSizeNear
	//*(char*)0x01cbb4f8 = 1;//r_fullbright
	//*(char*)0x01cb73b8 = 1;//lui_disable_blur
}

#pragma region ...
SYS_MODULE_INFO(BO1_MP, 0, 1, 1);
SYS_MODULE_START(_BO1_MP_prx_entry);

sys_prx_id_t export_module;
int info;
int res;
char nop[] = { 0x60, 0x00, 0x00, 0x00 };

int Menu_PaintAll_a = 0x3971A0;
int CL_WritePacket_a = 0x116524;
int CL_SendCmd_a = 0x103024;
int SND_EndFrame_a = 0x503064;
int R_AddDObjToScene_a = 0x76F1B0;
int _sys_io_cellPadGetData_a = 0x8DDD84;
int CG_SetupWeaponCamoRender_a = 0xE1AB8;
int CG_RelativeTeamColor_a = 0x46308;
int CL_ConsolePrint_a = 0x0110388;
int Com_Error_a = 0x31EE80;
int LUI_LuaCall_DrawRectangle_a = 0x67C48C; 
int BG_CalculateWeaponMovement_a = 0x6108E0;
int BG_UnlockablesGetUsedAllocation_a = 0x005E79E4;
int BG_SetAmmoInClip_a = 0x00602864;
int CG_Player_a = 0x000829D0;
int BG_GetAmmoInClip_a = 0x0603694;
int R_DrawIndexedPrimitive_a = 0x07BBD1C;
int CG_FireWeapon_a = 0x000F9798;
int HandleAssets_a = 0x7B6198;

struct weaponState_t
{
	playerState_s *ps;
	float xyspeed;
	float frametime;
	float fLastIdleFactor;
	int time;
	int damageTime;
	float v_dmg_pitch;
	float v_dmg_roll;
	int *removeMeUnusedInt;
	Vector3 baseAngles;
	Vector3 baseOrigin;
	Vector3 recoilAngles;
	Vector3 recoilSpeed;
	Vector3 swayAngles;
	Vector3 swayOrigin;
	Vector3 swayViewAngles;
	Vector3 bobAngles;
	int shellShockStart;
	int shellShockDuration;
	int shellShockFadeTime;
};

Vector3 zero_ = Vector3(1, 1, 1);
void __cdecl BG_CalculateWeaponMovement(weaponState_t *ws, Vector3 *origin, Vector3 *angles)
{
	//origin = &zero_;
	//BG_CalculateWeaponMovementStub(ws, origin, zero_);
}

int CL_ConsolePrint(int localClientNum, int channel, const char *txt, int duration, int pixelWidth, int flags)
{
	if (bot.drawconsole)
	{
		CL_ConsolePrintDetour.Stub(localClientNum, channel, txt, duration, pixelWidth, flags);
	}
	else
	{
		if (channel < 10)
		{
			console.write(txt, color(255, 255, 255, 255), color(52, 52, 52, 255), (color)menu.skin, (color)menu.skin2);
		}
	}
}

int Com_Error(int code, const char * fmt, char * ap)
{
	char buffer[400];
	Com_Sprint(buffer, sizeof(buffer), fmt, ap);
	console.write(buffer, color(255, 25, 25, 255), color(52, 52, 52, 255), (color)menu.skin, (color)menu.skin2);
	Com_ErrorDetour.Stub(code, fmt, ap);
}

void LUI_LuaCall_DrawRectangleH(LUI_Element * r3, float f1, float f2, float f3, float f4, float red, float green, float blue, float alpha, int r9, int r10) {

	const char * icon = r3->material->name;
	if (strstr(icon, "menu_mp_soldiers"))
	{
			red = menu.skin.r;
			green = menu.skin.g;
			blue = menu.skin.b;
			alpha = menu.skin.a / 2;
	}

	if (strstr(icon, "smoke"))
	{
		red = menu.skin.r / 2;
		green = menu.skin.g / 2;
		blue = menu.skin.b / 2;
		alpha = menu.skin.a / 2;
	}

	if (
		
		strstr(icon, "lui_bkg")
		|| strstr(icon, "menu_mp_cac_backing")
		|| strstr(icon, "menu_mp_backing_frame") || strstr(icon, "holotable"))
		//strstr(icon, "fog"))
		//|| strstr(icon, "grid"))
	{
		red = menu.skin.r;
		green = menu.skin.g;
		blue = menu.skin.b;
		alpha = menu.skin.a;
	}

	//_sys_printf("%s\n", icon);

	LUI_LuaCall_DrawRectangleDetour.Stub(r3, f1, f2, f3, f4, red, green, blue, alpha, r9, r10);
}

enum loadoutClass_t {
	CLASS_INVALID = 0xFFFFFFFF,
	CUSTOM_CLASS_1 = 0x0,
	CUSTOM_CLASS_FIRST = 0x0,
	CUSTOM_CLASS_2 = 0x1,
	CUSTOM_CLASS_3 = 0x2,
	CUSTOM_CLASS_4 = 0x3,
	CUSTOM_CLASS_5 = 0x4,
	BASIC_CUSTOM_CLASS_COUNT = 0x5,
	CUSTOM_CLASS_6 = 0x5,
	CUSTOM_CLASS_7 = 0x6,
	CUSTOM_CLASS_8 = 0x7,
	CUSTOM_CLASS_9 = 0x8,
	CUSTOM_CLASS_10 = 0x9,
	CUSTOM_CLASS_COUNT = 0xA,
	DEFAULT_CLASS_FIRST = 0xA,
	DEFAULT_CLASS_SMG = 0xA,
	DEFAULT_CLASS_CQB = 0xB,
	DEFAULT_CLASS_ASSAULT = 0xC,
	DEFAULT_CLASS_LMG = 0xD,
	DEFAULT_CLASS_SNIPER = 0xE,
	DEFAULT_CLASS_LAST = 0xE,
	TOTAL_CLASS_COUNT = 0xF,
};

int BG_UnlockablesGetUsedAllocationH(int *cacRoot, loadoutClass_t customClass) {

	if (local->unlimitedSlots) {
		return 0;
	}
	BG_UnlockablesGetUsedAllocationDetour.Stub(cacRoot, customClass);
}

void CG_FireWeaponH(int localClientNum, centity_t* cent, int event, int eventParm, const unsigned __int16 tagName, Weapon weapon, playerState_s* ps, bool leftGun)
{
	if (CScr_IsAlive(localClientNum)) {
		if (menu.flagx == 50)
		{
			menu.flagy = irand_(0, 45);
		}
	}
	CG_FireWeaponDetour.Stub(localClientNum, cent, event, eventParm, tagName, weapon, ps, leftGun);
}

void CG_Player(int localClientNum, centity_s *cent)
{
	int ent = cent->ClientNumber;
	if (ent != cg->clientNum)
	{
		if (!CG_IsEntityFriendlyNotEnemy(&centity[ent]))
		{
			if (CScr_IsAlive(ent))
			{
				AimTarget_GetTagPos_f(&centity[ent], AimBoneIndex[j_helmet], &local->player[ent].vtag[AimBoneIndex[j_helmet]]);
				AimTarget_GetTagPos_f(&centity[ent], AimBoneIndex[j_head], &local->player[ent].vtag[AimBoneIndex[j_head]]);
				AimTarget_GetTagPos_f(&centity[ent], AimBoneIndex[j_neck], &local->player[ent].vtag[AimBoneIndex[j_neck]]);
				AimTarget_GetTagPos_f(&centity[ent], AimBoneIndex[j_spineupper], &local->player[ent].vtag[AimBoneIndex[j_spineupper]]);
				AimTarget_GetTagPos_f(&centity[ent], AimBoneIndex[j_knee_le], &local->player[ent].vtag[AimBoneIndex[j_knee_le]]);
				AimTarget_GetTagPos_f(&centity[ent], AimBoneIndex[j_knee_ri], &local->player[ent].vtag[AimBoneIndex[j_knee_ri]]);
				AimTarget_GetTagPos_f(&centity[ent], AimBoneIndex[j_ankle_le], &local->player[ent].vtag[AimBoneIndex[j_ankle_le]]);
				AimTarget_GetTagPos_f(&centity[ent], AimBoneIndex[j_ankle_ri], &local->player[ent].vtag[AimBoneIndex[j_ankle_ri]]);
			}
		}
	}
	CG_PlayerDetour.Stub(localClientNum, cent);
}

#define Menu_PaintAllDef Menu_PaintAllDetour.Hook(Menu_PaintAll_a, Menu_PaintAll);
#define CL_WritePacketDef CL_WritePacketDetour.Hook(CL_WritePacket_a, CL_WritePacket);
#define CG_PlayerDef CG_PlayerDetour.Hook(CG_Player_a, CG_Player);
#define CL_SendCmdDef CL_SendCmdDetour.Hook(CL_SendCmd_a, CL_SendCmd);
#define R_EndFrameDef R_EndFrameDetour.Hook(SND_EndFrame_a, R_EndFrame);
#define R_AddDObjToSceneDef R_AddDObjToSceneDetour.Hook(R_AddDObjToScene_a, R_AddDObjToScene);
#define _sys_io_cellPadGetDataDef _sys_io_cellPadGetDataDetour.Hook(_sys_io_cellPadGetData_a, _sys_io_cellPadGetData);
#define CG_SetupWeaponCamoRenderDef CG_SetupWeaponCamoRenderDetour.Hook(CG_SetupWeaponCamoRender_a, CG_SetupWeaponCamoRender);
#define CG_RelativeTeamColorDef CG_RelativeTeamColorDetour.Hook(CG_RelativeTeamColor_a, CG_RelativeTeamColor);
#define CL_ConsolePrintDef CL_ConsolePrintDetour.Hook(CL_ConsolePrint_a, CL_ConsolePrint);
#define Com_ErrorDef Com_ErrorDetour.Hook(Com_Error_a, Com_Error);
#define BG_UnlockablesGetUsedAllocationDef BG_UnlockablesGetUsedAllocationDetour.Hook(BG_UnlockablesGetUsedAllocation_a, BG_UnlockablesGetUsedAllocationH);
#define CG_FireWeaponDef CG_FireWeaponDetour.Hook(CG_FireWeapon_a, CG_FireWeaponH);
#define LUI_LuaCall_DrawRectangleDef LUI_LuaCall_DrawRectangleDetour.Hook(LUI_LuaCall_DrawRectangle_a, LUI_LuaCall_DrawRectangleH);

char jmp[2] = { 0x48, 0x00 };
char lir3[4] = { 0x38, 0x60, 0x00, 0x01 };

extern "C" int _BO1_MP_prx_entry(void)
{

	float kek = 2500.0f;
	WriteMemory(compassMaxRange, &kek, 4);
	local->xsint = 5;
	local->zoommap = kek;
	local->target_num = -1;
	cellPadInit(1);
	PadInit();
	Mshit.ch = "Status: Waiting";
	local->stausrank = "Status: Waiting";
	local->unlimitedSlots = true;
	bot.fpcorrection = 1.0f;
	menu.menufade = 0.600f;
	menu.menusize = 0.505f;
	menu.frenderfovx = 65.000f;
	menu.props = 1.000f;
	bot.fprediction = 1.32f;
	menu.fade = false;
	dflash = color(0, 0, 1, 0.9);
	dflash1 = color(0, 0, 1, 0.9);
	local->radarsizex = 160;
	local->radarsizey = 245;
	local->bgradarsizey = 168;
	local->bgradarsizex = 174;
	Menu_PaintAllDef;
	CG_PlayerDef;
	CL_SendCmdDef;
	CL_WritePacketDef;
	R_EndFrameDef;
	R_AddDObjToSceneDef;
	_sys_io_cellPadGetDataDef; 
	CG_SetupWeaponCamoRenderDef; 
	CG_RelativeTeamColorDef; 
	CL_ConsolePrintDef;
	Com_ErrorDef;
	BG_UnlockablesGetUsedAllocationDef;
	CG_FireWeaponDef;
	LUI_LuaCall_DrawRectangleDef;
	return SYS_PRX_RESIDENT;
}
//000427B0 cg_lagometer bool


#pragma endregion

