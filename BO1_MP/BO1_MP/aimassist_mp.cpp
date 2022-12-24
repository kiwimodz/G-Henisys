#include <devstation\System.h>
#include <devstation\Math.h>
#include <devstation\Vector.h>

#include <hook.h>
#include <CellPad.h>
#include <Structures.h>
#include <visuals_mp.h>
#include <Functions.h>
#include <aimassist_mp.h>
#include <menu.h>
aimbot_s bot;

char nop2[] = { 0x60, 0x00, 0x00, 0x00 };
char recss[] = { 0x4B, 0xFF, 0xE6, 0x09 };
char recsss[] = { 0xF8, 0x21, 0xFF, 0x21 };
char stdu[] = { 0xF8, 0x21, 0xFF, 0x21 };
char blr[] = { 0x4E, 0x80, 0x00, 0x20 };
char rec[] = { 0x48, 0x50, 0x6D, 0x65 };

void noshit()
{

}

#pragma region aim functions
void enable_aimbot(bool * rs) { bot.benable = !bot.benable; }
void enable_cancelreload(bool * rs) { bot.cancelreload = !bot.cancelreload; }
void aim_type(int type) { bot.aimtype = (aimtype_t)type; }
void tag_type(int type) { bot.tagtype = (tagtype_t)type; }
void key_type(int type) { bot.keytype = (keytype_t)type; }
void enable_visible(bool * rs) {  bot.bvisible = !bot.bvisible; }
void enable_autowall(bool * rs) { bot.bautowall = !bot.bautowall; }
void enable_aim(bool * rs) { bot.baimrequired = !bot.baimrequired; }
void enable_antiaim(bool * rs) {  bot.bantiaim = !bot.bantiaim; }
void enable_spinbot(bool * rs) { bot.bspinbot = !bot.bspinbot; }
void enable_reversebot(bool * rs) { bot.breversebot = !bot.breversebot; }
void enable_lockup(bool* rs) { bot.blockup = !bot.blockup; }
void enable_nospread(bool * rs) { bot.bnospread = !bot.bnospread; }
void enable_noflinch(bool* rs) { bot.bnoflinch = !bot.bnoflinch; noshit();}
void enable_norec(bool* rs) {bot.bnorec = !bot.bnorec; noshit();}
void enable_nosway(bool* rs) { bot.bnosway = !bot.bnosway; noshit(); }
void enable_nobob(bool * rs) {  bot.bnobob = !bot.bnobob; noshit();}
void enable_aimatfeet(bool * rs) { bot.baimatfeet = !bot.baimatfeet; }
void enable_autobone(bool * rs) { bot.bautobone = !bot.bautobone; }
void enable_autoshoot(bool * rs) {bot.bautoshoot = !bot.bautoshoot; }
void slide_prediction(float value) { bot.fprediction = value; }
void spin_scale(float value) { bot.spinscale = value; }
void pcorrectiion_scale(float value) { bot.fpcorrection = value; }
void pitch_scale(float value) { bot.pitchscale = value; }
void roll_scale(float value) { bot.rollscale = value; }
void lag_scale(float value) { bot.fakelagscale = value; }
void enable_ntiaim(bool * rs) { bot.benableanti = !bot.benableanti; }

#pragma endregion
#pragma region autowall

int BG_GetWeaponVariantDef_t[2] = { 0x606EE0, 0xD67E98 };
WeaponVariantDef*(*BG_GetWeaponVariantDef_f)(unsigned int r1) = (WeaponVariantDef*(*)(unsigned int))BG_GetWeaponVariantDef_t;

WeaponVariantDef* BG_GetWeaponVariantDef(unsigned int weapon) {
	return BG_GetWeaponVariantDef_f(weapon);
}

int BG_GetWeaponDef_t[2] = { 0x606F08, 0xD67E98 };
WeaponDef*(*BG_GetWeaponDef_f)(int r1) = (WeaponDef*(*)(int))BG_GetWeaponDef_t;

WeaponDef * BG_GetWeaponDef(int Weapon)
{
	return BG_GetWeaponDef_f(Weapon);
}

int BulletTrace_t[2] = { 0xE9FBC, 0xD67E98 };
bool(*BulletTrace_f)(int localClientNum, BulletFireParams* bulletFireParams, WeaponDef * weaponIndex, centity_s * centityAttacker, BulletTraceResults  *btr, int surfacetype, bool simulate) = (bool(*)(int , BulletFireParams* , WeaponDef * , centity_s * , BulletTraceResults  *, int , bool ))BulletTrace_t;

bool BulletTrace(int localClientNum, BulletFireParams* bulletFireParams, WeaponDef * weaponIndex, centity_s * centityAttacker, BulletTraceResults  *btr, int surfacetype, bool simulate)
{
	return BulletTrace_f(localClientNum, bulletFireParams, weaponIndex, centityAttacker, btr, surfacetype, simulate);
}

int idk1_t[2] = { 0x3CFD98, 0xD67E98 };
void(*idk1_f)(float* r1, float* r2, float* r3, float* r4 ) = (void(*)(float* , float* , float* , float* ))idk1_t;

void anglevectors(Vector3 v, Vector3 * forward, Vector3 * right, Vector3 * up)
{
	float fv[] = { v.x, v.y, v.z };
	float vf[3], vr[3], vu[3];
	idk1_f(fv, vf, vr, vu);
	*forward = Vector3(vf[0], vf[1], vf[2]);
	*right = Vector3(vr[0], vr[1], vr[2]);
	*up = Vector3(vu[0], vu[1], vu[2]);
}

struct orientation_t
{
	Vector3 origin;
	Vector3 axis[3];
};

#define __PAIR__(high, low) (((unsigned long)(high)<<sizeof(high)*8) | low)

int BG_AdvanceTrace_t[2] = { BG_AdvanceTrace_a, 0xD67E98 };
bool(*BG_AdvanceTrace_f)(BulletFireParams *bp, BulletTraceResults *br, float dist) = (bool(*)(BulletFireParams *, BulletTraceResults *, float))BG_AdvanceTrace_t;

bool __cdecl BG_AdvanceTrace(BulletFireParams *bp, BulletTraceResults *br, float dist)
{
	return  BG_AdvanceTrace_f(bp, br, dist);
}
#define min(a,b)(((a) < (b)) ? (a) : (b))

int BG_GetSurfacePenetrationDepth_t[2] = { 0x05EFFC0, 0xD67E98 };
float (*BG_GetSurfacePenetrationDepth_f)(PenetrateType pentype, int surfaceType) = (float(*)(PenetrateType , int ))BG_GetSurfacePenetrationDepth_t;

float BG_GetSurfacePenetrationDepth(PenetrateType pentype, int surfaceType) {

	return  BG_GetSurfacePenetrationDepth_f(pentype, surfaceType);;
}

float Get3dDistance(Vector3 myCoords, Vector3 enemyCoords)
{
	return sqrtf(
		powf(double(enemyCoords.x - myCoords.x), 2.0) +
		powf(double(enemyCoords.y - myCoords.y), 2.0) +
		powf(double(enemyCoords.z - myCoords.z), 2.0)
	);
}

#define VA(...) Invoke<const char *>(0x03E58B0 , __VA_ARGS__)
#define VectorMA(v, s, b, o) ((o).x=(v).x+(b).x*(s),(o).y=(v).y+(b).y*(s),(o).z=(v).z+(b).z*(s))
#define VectorScale(v, s, o) ((o).x=(v).x*(s),(o).y=(v).y*(s),(o).z=(v).z*(s))

void _VectorMA(const Vector3 veca, float scale, const Vector3 vecb, Vector3 vecc) {
	vecc.x = veca.x + scale*vecb.x;
	vecc.y = veca.y + scale*vecb.y;
	vecc.z = veca.z + scale*vecb.z;
}

double __cdecl Vec3DistanceSq(const float *p1, const float *p2)
{
	float v_4; // ST04_4@1
	float v_8; // ST08_4@1

	v_4 = p2[1] - p1[1];
	v_8 = p2[2] - p1[2];
	return v_8 * v_8 + v_4 * v_4 + (float)(*p2 - *p1) * (float)(*p2 - *p1);
}

double __cdecl Abs(const float *v)
{
	return (float)sqrtf((float)((float)((float)(*v * *v) + (float)(v[1] * v[1])) + (float)(v[2] * v[2])));
}

int Trace_GetEntityHitId_t[2] = { 0x306CC0, 0xD67E98 };
signed int(*Trace_GetEntityHitId_f)(trace1_t *trace) = (signed int(*)(trace1_t *))Trace_GetEntityHitId_t;

signed int __cdecl Trace_GetEntityHitId(trace1_t *trace)
{
	return Trace_GetEntityHitId_f(trace);
}
double __cdecl Vec3Distance(Vector3 *v1, Vector3 *v2)
{
	Vector3 dir; // [sp+4h] [bp-Ch]@1

	dir.x = v2 - v1;
	dir.y = v2->y - v1->y;
	dir.z = v2->z - v1->z;
	return Abs((const float*)&dir);
}
const double XM_PI = 3.14;

void VectorAngles(Vector3 &forward, Vector3 &angles)
{
	float tmp, yaw, pitch;

	if (forward.z == 0 && forward.x == 0)
	{
		yaw = 0;

		if (forward.z > 0)
			pitch = 90;
		else
			pitch = 270;
	}
	else
	{
		yaw = (atan2f(forward.z, -forward.x) * 180 / XM_PI) - 90;

		if (yaw < 0)
			yaw += 360;

		tmp = sqrtf(forward.x * forward.x + forward.z * forward.z);
		pitch = (atan2f(forward.y, tmp) * 180 / XM_PI);

		if (pitch < 0)
			pitch += 360;
	}

	angles.x = -pitch;
	angles.y = yaw;
	angles.z = 0;
}

bool something;
int counter = 0;
void Bullet_FirePenetrate(BulletFireParams& bp, BulletTraceResults& br, Vector3 End)
{
	bp.weaponEntIndex = 1022;
	bp.ignoreEntIndex = cg->clientNum;
	bp.damageMultiplier = 1.1f;
	bp.methodOfDeath = 9;
	bp.origStart = cg->refdef.ViewOrigin;
	bp.start = cg->refdef.ViewOrigin;
	bp.end = End;

	Vector3 delta = End - cg->refdef.ViewOrigin;
	//Vector3 angles;

	//VectorAngles(delta, angles);
	bp.dir = delta;
	
	WeaponDef *weapDef = BG_GetWeaponDef(88);
	if (!weapDef)
		return;
	float bulletMultiplier = 2.0f;
	float fxDist = 30.0f;

	if (!BulletTrace(0, &bp, weapDef, &centity[cg->clientNum], &br, 0, false))
		return;

	if (weapDef->penetrateType <= 0)
		return;

	if (br.trace.partGroup == 20)
	{
		return;
	}

	for (int i = 0; i < 9; i++)
	{
		float frontSurfaceDepth = BG_GetSurfacePenetrationDepth(PENETRATE_TYPE_LARGE, br.surfaceType) * bulletMultiplier;

		if (br.trace.sflags & 4)
			frontSurfaceDepth = 100.0f;

		if (frontSurfaceDepth <= 0.0f)
			break;

		Vector3 firstHitPos = br.hitPos;
		Vector3 savedLastHitPos = br.hitPos;
	
		if (!BG_AdvanceTrace(&bp, &br, (0.13500000536441803f)))
			break;

		bool frontWallTrace = BulletTrace(0, &bp, weapDef, &centity[cg->clientNum], &br, br.surfaceType, false);

		BulletFireParams backWallBp;
		_sys_memcpy(&backWallBp, &bp, sizeof(BulletFireParams));

		backWallBp.dir.x = bp.dir.x * -1.0f;
		backWallBp.dir.y = bp.dir.y * -1.0f;
		backWallBp.dir.z = bp.dir.z * -1.0f;

		backWallBp.start = bp.end;

		backWallBp.end.x = (backWallBp.dir.x * 0.009999999776482582f) + savedLastHitPos.x;
		backWallBp.end.y = (backWallBp.dir.y * 0.009999999776482582f) + savedLastHitPos.y;
		backWallBp.end.z = (backWallBp.dir.z * 0.009999999776482582f) + savedLastHitPos.z;

		BulletTraceResults backWallBr;
		_sys_memcpy(&backWallBr, &br, sizeof(BulletTraceResults));

		if (backWallBr.trace.partGroup == 20)
		{
			return;
		}
		
		backWallBr.trace.normal.x = backWallBr.trace.normal.x * -1.0f;
		backWallBr.trace.normal.y = backWallBr.trace.normal.y * -1.0f;
		backWallBr.trace.normal.z = backWallBr.trace.normal.z * -1.0f;


		if (frontWallTrace)
			if (BG_AdvanceTrace(&backWallBp, &backWallBr, 0.009999999776482582f));

		bool backWallTrace = BulletTrace(0, &backWallBp, weapDef, &centity[cg->clientNum], &backWallBr, backWallBr.surfaceType, false);

		bool staticModel = (backWallTrace) && backWallBr.trace.allsolid || br.trace.startsolid && backWallBr.trace.startsolid;

			
		if (backWallTrace || staticModel)
			goto next;

		if (!frontWallTrace)
			break;

		if (br.trace.allsolid)
			continue;

		float x = (br.hitPos.x - firstHitPos.x);
		float y = (br.hitPos.y - firstHitPos.y);
		float z = (br.hitPos.z - firstHitPos.z);
		float length = ((x * x) + (y * y), (z * z));

		if (length <= (fxDist * fxDist))
			continue;

		if (weapDef->weaponType != 0)
			continue;

	next:
		float totalDepth = 0.0f;

		if (staticModel)
			totalDepth = (backWallBp.end - backWallBp.start).getLength();
		else
			totalDepth = (backWallBr.hitPos - savedLastHitPos).getLength();

		if (totalDepth < 1.0f)
			totalDepth = 1.0f;

		if (backWallTrace)
		{
			float backSurfaceDepth = BG_GetSurfacePenetrationDepth(PENETRATE_TYPE_LARGE, backWallBr.surfaceType);

			frontSurfaceDepth = min(frontSurfaceDepth, backSurfaceDepth) * bulletMultiplier;

			if (backWallBr.trace.surfaceType & 4)
				frontSurfaceDepth = 200.0f;

			if (frontSurfaceDepth <= 0.0f)
				break;
		}

		float dmg = bp.damageMultiplier - (totalDepth / frontSurfaceDepth);
		bp.damageMultiplier = dmg;

		if (dmg <= 0.0f)
			break;

		if (staticModel || weapDef->weaponType != 0)
			continue;

		float x2 = (backWallBr.hitPos.x - firstHitPos.x);
		float y2 = (backWallBr.hitPos.y - firstHitPos.y);
		float z2 = (backWallBr.hitPos.z - firstHitPos.z);
		float length2 = ((x2 * x2) + (y2 * y2) + (z2 * z2));

		if (length2 <= (fxDist * fxDist))
			continue;

		if (frontWallTrace)
			continue;
	}
}

#pragma endregion

int DobjClient_t[2] = { 0x015708, 0xD67E98 };
bool(*DobjClient_f)(centity_s * cent, short tag, Vector3 * pos) = (bool(*)(centity_s * , short , Vector3 * ))DobjClient_t;

float GetDistance(Vector3 c1, Vector3 c2) {
	float dx = c2.x - c1.x;
	float dy = c2.y - c1.y;
	float dz = c2.z - c1.z;

	return sqrtf((dx * dx) + (dy * dy) + (dz * dz));
}

short HandleTag(int i)
{
	if (bot.tagtype == AUTO_BONE)
		return autobone(i);
	if (bot.tagtype == tj_head)
		return AimBoneIndex[j_head];
	if (bot.tagtype == tj_spine4)
		return AimBoneIndex[j_spineupper];
	if (bot.tagtype == tj_knee_le)
		return AimBoneIndex[j_knee_le];
	if (bot.tagtype == tj_ankle_le)
		return AimBoneIndex[j_ankle_le];
}

bool AimTarget_IsWallableWithPrediction(int i, float fpredict)
{
	BulletFireParams bp;
	BulletTraceResults br;
	Vector3 targetbone;
	targetbone = local->player[i].vtag[bot.psztag[i]];
	Bullet_FirePenetrate(bp, br, targetbone);
	return bp.ignoreEntIndex == i;
}

bool AimTarget_IsVisible(int i, float fpredict)
{
	bool Trace;
	BulletFireParams bp;
	BulletTraceResults br;
	Vector3 targetbone;
	targetbone = local->player[i].vtag[bot.psztag[i]];
	WeaponDef* weapDef = BG_GetWeaponDef(cg->playerstate.weapon);
	if (!weapDef)
		return;

	bp.weaponEntIndex = 1022;
	bp.ignoreEntIndex = cg->clientNum;
	bp.damageMultiplier = 1.0f;
	bp.methodOfDeath = 9;
	bp.origStart = cg->refdef.ViewOrigin;
	bp.start = cg->refdef.ViewOrigin;
	bp.end = targetbone;
	Vector3 delta = targetbone - cg->refdef.ViewOrigin;

	bp.dir = delta;
	Trace = BulletTrace(0, &bp, weapDef, &centity[cg->clientNum], &br, br.surfaceType, false);
		
	if (!Trace) return;

	if (BG_AdvanceTrace(&bp, &br, 0.009999999776482582f));

	return br.trace.fraction >= 0.98f && br.trace.partGroup != 20;
}

bool Vischeckmp(int i) {
	if (!bot.psztag) return;
	bot.bvisible_esp[i] = false, bot.bautowall_esp[i] = false;
	if (bot.bvisible && bot.bautowall)
		return (AimTarget_IsVisible(i, bot.fprediction) ? (bot.bvisible_esp[i] = true) : (AimTarget_IsWallableWithPrediction(i, bot.fprediction)) ? (bot.bautowall_esp[i] = true) : (bot.bvisible_esp[i] = false, bot.bautowall_esp[i] = false));
	if (bot.bvisible && !bot.bautowall)
		return (AimTarget_IsVisible(i, bot.fprediction) ? (bot.bvisible_esp[i] = true) : (bot.bvisible_esp[i] = false));
	if (!bot.bvisible && bot.bautowall)
		return (AimTarget_IsWallableWithPrediction(i, bot.fprediction) ? (bot.bautowall_esp[i] = true) : bot.bautowall_esp[i] = false);
	if (!bot.bvisible && !bot.bautowall)
		return true;  bot.bautowall_esp[i] = false; bot.bvisible_esp[i] = false;
}

int CG_GetPredictedPlayerState_t[2] = { 0x6AD5C, 0xD67E98 };
playerstate_s* (*CG_GetPredictedPlayerState_f)(int) = (playerstate_s * (*)(int))CG_GetPredictedPlayerState_t;

bool btrighoot;
void GetNearestPlayermp()
{
	local->target_num = -1;
	local->alive = false;
	float flMax = 999999999;
	ShouldSimulateCheck();

	for (int i = 0; i < 18; i++)
	{
		if (!CScr_IsAlive(i)) continue;
		if (i == cg->clientNum) continue;
		if (centity[cg->clientNum].WeaponID == 89) continue;
		if (bot.psztag == NULL) bot.psztag[i] = AimBoneIndex[j_head];
		if (bot.baimatfeet) riotshieldCheck(i);
		else bot.psztag[i] = HandleTag(i), bot.sc[i] = false;
		if (local->iplayer[i] == true) continue;
		float flDis = Distance(centity[i].Origin, centity[cg->clientNum].Origin);
		if (CG_IsEntityFriendlyNotEnemy(&centity[i])) continue;
		if (!Vischeckmp(i)) continue;
		if (local->pplayer[i] == true || (flDis < flMax)) {
			flMax = flDis;
			local->target_num = i;
			local->alive = true;
			if (bot.aimtype == AIM_TYPE_TRIGGERBOT && AimingAtEnemyAimbot(i)) {
				btrighoot = true;
			}
		}
	}
}

enum buttonslol {
	B_X = 0x1000,
	B_Triangle = 0x8000,
	B_Square = 0x4000,
	B_Circle = 0x2000,
	B_DpadUp = 0x0001,
	B_DpadDown = 0x0002,
	B_DpadLeft = 0x0004,
	B_DpadRight = 0x0008,
	B_R1 = 0x0200,
	B_R2 = 0x0800,
	B_R3 = 0x0080,
	B_L1 = 0x0100,
	B_L2 = 0x0400,
	B_L3 = 0x0040,
	B_Start = 0x0010,
	B_Select = 0x0020,
};
bool isButtonDown(int button) {
	return *(short*)0x1EF77B2 & button;
}

void SnapAimbot()
{
	static Vector3 OldAngles;
	static bool ResetAngles;
	if (bot.keytype == KEY_NONE)
	{
		goto Next;
	}

	else if (bot.keytype == KEY_L1)
	{
		if (isButtonDown(B_L1))
		{
			goto Next;
		}
		else
		{
			goto End;
		}
	}
	Next:
	if (local->target_num == -1 && ResetAngles)
		cactive->ViewAngles = OldAngles, ResetAngles = false;
	else if (!ResetAngles && local->target_num != -1)
		OldAngles = cactive->ViewAngles, ResetAngles = true;
	End:
}
bool next_0;
void AimTarget_GetTarget() {
	
	GetNearestPlayermp();//get nearest target number

	if (bot.aimtype == AIM_TYPE_SNAP) {

		SnapAimbot();
	}

	if (local->target_num != -1 && bot.psztag != NULL) {//continue if bone and target is valid

		playerstate_s* playerState = CG_GetPredictedPlayerState_f(0);//fill playerstate

		int ammo = BG_GetAmmoInClip(playerState, playerState->weapon);//get ammo in clip
		
		if (bot.cancelreload)
		{
			if (ammo <= 0)
			{
				next_0 = true;
			}

			if (next_0 && ammo != 0)
			{
				local->canreload = true;
				next_0 = false;
			}
		}


		if (ammo <= 0)return;//kill aimbot if no ammo is in clip

		Vector3 diff = local->player[local->target_num].vtag[bot.psztag[local->target_num]] - cg->refdef.ViewOrigin;//bone position 

		VectoAngles(diff, &local->vangles);//vector to angles

		if (bot.aimtype == AIM_TYPE_AIM_BOT || bot.aimtype == AIM_TYPE_SNAP) {

			if ((bot.keytype == KEY_L1) && isButtonDown(B_L1)) {

				cactive->ViewAngles = local->vangles - cactive->BaseAngles;//write aimbot angles to players angles 
			}

			else if (bot.keytype == KEY_NONE) {

				cactive->ViewAngles = local->vangles - cactive->BaseAngles;//write aimbot angles to players angles 
			}
		}
	}
}

void aimbot()
{
	if (!bot.benable) return;

	AimTarget_GetTarget();
}

#define	SHORT2ANGLE(x)	( (x) * ( 360.0f / 65536.0f ) )
#pragma region Movement Fix
char ClampChar_r(const int i)
{
	if (i < -128) {
		return -128;
	}
	if (i > 127) {
		return 127;
	}
	return i;
}

void FixMovement(usercmd_s * pCmd, float CurAngle, float OldAngle, float fOldForward, float fOldSidemove)
{
	float deltaView = CurAngle - OldAngle, f1, f2;

	if (OldAngle < 0.f)
		f1 = 360.0f + OldAngle;
	else
		f1 = OldAngle;

	if (CurAngle < 0.0f)
		f2 = 360.0f + CurAngle;
	else
		f2 = CurAngle;

	if (f2 < f1)
		deltaView = abs(f2 - f1);
	else
		deltaView = 360.0f - abs(f1 - f2);
	deltaView = 360.0f - deltaView;

	pCmd->fDir = ClampChar_r((int)(cosf(DEG2RAD(deltaView)) * fOldForward + cosf(DEG2RAD(deltaView + 90.f)) * fOldSidemove));
	pCmd->rDir = ClampChar_r((int)(sinf(DEG2RAD(deltaView)) * fOldForward + sinf(DEG2RAD(deltaView + 90.f)) * fOldSidemove));
}

#pragma endregion
#pragma region spread fix

#pragma endregion
#pragma region pspread
Vector3 viewAngles;

#define ANGLE2SHORT(x) ((int)((x) * 65536.0f / 360.0f ) & 65535)
#define M_PI 3.14159265359f
#define	SHORT2ANGLE(x)	((x) * ( 360.0f / 65536.0f ))

int BG_GetSpreadForWeapon_t[2] = { 0x5F09C8, 0xD67E98 };
void(*BG_GetSpreadForWeapon_f)(playerstate_s * ps, int weapon, float* min, float* maxx) = (void(*)(playerstate_s*, int, float*, float*))BG_GetSpreadForWeapon_t;

int BG_seedRandWithGameTime_t[2] = { 0x05D6C54, 0xD67E98 };
void(*BG_seedRandWithGameTime_f)(unsigned int * pHoldRand) = (void(*)(unsigned int*))BG_seedRandWithGameTime_t;

int CG_BulletEndpos_t[2] = { 0xEBB48, 0xD67E98 };
void(*CG_BulletEndpos_f)(unsigned int *randSeed, const float spread, Vector3 *start, Vector3 *end, Vector3 *dir, Vector3 *forwardDir, Vector3 *rightDir, Vector3 *upDir, const float maxRange, int weapon, int shotIndex, int maxShotIndex) = (void(*)(unsigned int *, const float, Vector3 *, Vector3 *, Vector3 *, Vector3 *, Vector3 *, Vector3 *, const float, int, int, int))CG_BulletEndpos_t;

void NoSpread(usercmd_s * cmd)
{
	Vector3 viewAngles, spreadDirection, spreadEndVec, viewAxis[3];

	playerstate_s * playerState = CG_GetPredictedPlayerState_f(0);

	int wnum = cg->playerstate.weapon;

	if (!wnum)
		return;

	WeaponDef * weapondef = BG_GetWeaponDef(wnum);

	if (!weapondef)
		return;

	float minSpread, maxSpread, spread;
	BG_GetSpreadForWeapon_f(playerState, playerState->weapon, &minSpread, &maxSpread);

	if (cg->zoomProgress)
	{
		spread = (maxSpread - weapondef->fAdsSpread) * (cg->spreadMultiplier / 255.0f) + weapondef->fAdsSpread;
	}
	else
	{
		spread = (minSpread + ((maxSpread - minSpread) * (cg->spreadMultiplier / 255.0f)));
	}
	
	anglevectors(local->vangles, &viewAxis[0], &viewAxis[1], &viewAxis[2]);

	unsigned int seed = playerState->time;
	BG_seedRandWithGameTime_f(&seed);

	CG_BulletEndpos_f(&seed, spread, &local->vangles, &spreadEndVec, &spreadDirection, &viewAxis[0], &viewAxis[1], &viewAxis[2], 8192.0f, playerState->weapon, 0, 1);
	VectoAngles(spreadDirection, &viewAngles);

	cmd->viewAngles[1] += ANGLE2SHORT(local->vangles.y - viewAngles.y);
	cmd->viewAngles[0] += ANGLE2SHORT(local->vangles.x - viewAngles.x);
}

#pragma endregion
float spinY, spinR, spinP;
bool ssw = false;

void pspin(usercmd_s * NewCmd, usercmd_s* CurrentCmd, usercmd_s* OldCmd)
{
	if (bot.benableanti)
	{
		if (cg->playerstate.weapon == 89) return;

		if (CScr_IsAlive(cg->clientNum))
		{
			if (bot.spinscale > 0.00)
				spinY = (spinY > 360) ? (spinY - 360) : (spinY + bot.spinscale), NewCmd->viewAngles[1] = ANGLE2SHORT(spinY);
			if (bot.pitchscale > 0.00)
				NewCmd->viewAngles[0] = ANGLE2SHORT((!(NewCmd->time % (int)bot.pitchscale) ? 69.999999999999999f : -69.999999999999999f) - cactive->BaseAngles.x);
			if (bot.breversebot)
				NewCmd->viewAngles[1] -= ANGLE2SHORT(180.0f), bot.bspinbot = false, bot.spinscale = 0.0f;
			if (bot.blockup)
				NewCmd->viewAngles[0] -= ANGLE2SHORT(55.0f), bot.pitchscale = 0.0f;
		}
		else
		{
			cactive->ViewAngles = cactive->BaseAngles;
			cactive->ViewAngles.y = 0;
		}
	}
}

void psilent(usercmd_s* CurrentCmd, usercmd_s* OldCmd)
{
	if (!bot.benable) return;
	
	playerstate_s* playerState = CG_GetPredictedPlayerState_f(0);
	int ammo = BG_GetAmmoInClip(playerState, playerState->weapon);
	if (ammo <= 0)return;
	
	if (!local->alive) return;

	float OldAngleY = SHORT2ANGLE(OldCmd->viewAngles[1]);

	if (bot.aimtype == AIM_TYPE_SILENT)
	{
		if (!isButtonDown(B_L3))
		{
			OldCmd->viewAngles[0] = ANGLE2SHORT(local->vangles.x - cactive->BaseAngles.x),//slient
			OldCmd->viewAngles[1] = ANGLE2SHORT(local->vangles.y - cactive->BaseAngles.y);
			FixMovement(OldCmd, SHORT2ANGLE(OldCmd->viewAngles[1]), OldAngleY, (float)OldCmd->fDir, (float)OldCmd->rDir);//move fix for slient
		}
	}

	if (bot.aimtype == AIM_TYPE_TRIGGERBOT)
	{
		OldCmd->viewAngles[0] = ANGLE2SHORT(local->vangles.x - cactive->BaseAngles.x),//do trigger here not done yet
			OldCmd->viewAngles[1] = ANGLE2SHORT(local->vangles.y - cactive->BaseAngles.y);
		FixMovement(OldCmd, SHORT2ANGLE(OldCmd->viewAngles[1]), OldAngleY, (float)OldCmd->fDir, (float)OldCmd->rDir);//move fix for slient

		if (btrighoot && cg->playerstate.weapon != 89)
		{
			if (bot.keytype == KEY_L1)
			{
				if (isButtonDown(B_L1))
				{
					OldCmd->buttons &= ~AUTO_SHOOT;
					CurrentCmd->buttons |= AUTO_SHOOT;
					btrighoot = false;
				}
			}
			else
			{
				OldCmd->buttons &= ~AUTO_SHOOT;
				CurrentCmd->buttons |= AUTO_SHOOT;
				btrighoot = false;
			}
		}
	}

	if (((CurrentCmd->buttons & AUTO_SHOOT) || (local->shoot && bot.bautoshoot)) && cg->playerstate.weapon != 89 && bot.aimtype != AIM_TYPE_TRIGGERBOT)
	{
		if (!local->alive) return;
		local->shooting = true;
		OldCmd->buttons &= ~AUTO_SHOOT;
		CurrentCmd->buttons |= AUTO_SHOOT;
	}

	if (bot.bnospread)
		NoSpread(OldCmd);
}
