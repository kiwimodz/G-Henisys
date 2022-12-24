#include <devstation\System.h>
#include <devstation\Math.h>
#include <devstation\Vector.h>
#include <hook.h>
#include <Structures.h>
#include <Functions.h>
#include <visuals_mp.h>
#include <aimassist_mp.h>
#include <menu.h>
#include <console.h>


#pragma region visual handles
void draw_allies(bool * rs) { bot.esp.ballies = !bot.esp.ballies; }
void draw_radar(bool * rs) { bot.esp.bradar = !bot.esp.bradar; }
void draw_axis(bool * rs) { bot.esp.baxis = !bot.esp.baxis; }
void set_bound(int index) { bot.esp.bound = index; }
void set_snap(int index) { bot.esp.snaplines = index; }
void draw_bones(bool * rs) { bot.esp.bbones = !bot.esp.bbones; }
void draw_vangles(bool * rs) { bot.esp.bvangles = !bot.esp.bvangles; }
void draw_myvangles(bool * rs) { bot.esp.myvangles = !bot.esp.myvangles; }
void draw_compass(bool * rs) { bot.esp.bcompass = !bot.esp.bcompass; }
void draw_radartype(bool* rs) { bot.esp.bradartype = !bot.esp.bradartype; }
void draw_healthbar(bool * rs) { bot.esp.bhealthbar = !bot.esp.bhealthbar; }
void draw_proxwarn(bool * rs) { bot.esp.bprox = !bot.esp.bprox; }
void draw_crossh(bool * rs) { bot.esp.bdynamic = !bot.esp.bdynamic; }
void draw_names(bool * rs) { bot.esp.bnames = !bot.esp.bnames; }
void draw_dist(bool * rs) { bot.esp.bdist = !bot.esp.bdist; }
void draw_chams(bool * rs) { bot.esp.bchams = !bot.esp.bchams; }
void draw_wall(bool * rs) { bot.esp.bwall = !bot.esp.bwall; }
void draw_ewall(bool * rs) { bot.esp.ebwall = !bot.esp.ebwall; }

void draw_weapsworld(bool * rs) { bot.esp.bweapsworld = !bot.esp.bweapsworld; }
void draw_nadesworld(bool * rs) { bot.esp.bnadesworld = !bot.esp.bnadesworld; }
void draw_scavsworld(bool * rs) { bot.esp.bpickupscavsworld = !bot.esp.bpickupscavsworld; }
void draw_weappickupidsworld(bool * rs) { bot.esp.bpickupweaponsworld = !bot.esp.bpickupweaponsworld; }
void draw_weappickupidsradar(bool * rs) { bot.esp.bradrpickupweaps = !bot.esp.bradrpickupweaps; }
void draw_draw_scavsradar(bool * rs) { bot.esp.bradrpickupscavs = !bot.esp.bradrpickupscavs; }
void draw_hellisradar(bool * rs) { bot.esp.bradrhelis = !bot.esp.bradrhelis; }
void draw_doggosradar(bool * rs) { bot.esp.bradrdogos = !bot.esp.bradrdogos; }
void draw_vehiclesradar(bool * rs) { bot.esp.bradrvehicles = !bot.esp.bradrvehicles; }
void draw_turretsradar(bool * rs) { bot.esp.bradrturrets = !bot.esp.bradrturrets; }
void draw_artilleryradar(bool * rs) { bot.esp.bradrartillery = !bot.esp.bradrartillery; }
void draw_worldents(bool * rs) { bot.esp.benableworldents = !bot.esp.benableworldents; }
void draw_nadesradar(bool * rs) { bot.esp.bradrnades = !bot.esp.bradrnades; }
void draw_xhscavs(bool * rs) { bot.esp.bxhscavs = !bot.esp.bxhscavs; }
void draw_xhweaps(bool * rs) { bot.esp.bxhweapspickupids = !bot.esp.bxhweapspickupids; }
void draw_targetfinder(bool * rs) { bot.esp.btargetfinder = !bot.esp.btargetfinder; }
void draw_targetinfo(bool * rs) { bot.esp.btargetinfo = !bot.esp.btargetinfo; }
#pragma endregion

int CG_IsClientInOurParty_t[2] = { 0x714C8, 0xD67E98 };
bool(*CG_IsClientInOurParty_f)(int localClientNum, int clientNum) = (bool(*)(int localClientNum, int clientNum))CG_IsClientInOurParty_t;


bool __cdecl CG_IsClientInOurParty(int localClientNum, int clientNum)
{
	CG_IsClientInOurParty_f(localClientNum, clientNum);
}

int CG_DrawOverheadNames_t[2] = { 0x3ECD8, 0xD67E98 };
void(*CG_DrawOverheadNames_f)(int localClientNum, centity_s *cent, float alpha, int mode) = (void(*)(int, centity_s *, float, int))CG_DrawOverheadNames_t;


void __cdecl CG_DrawOverheadNames(int localClientNum, centity_s *cent, float alpha, int mode)
{
	CG_DrawOverheadNames_f(localClientNum, cent, alpha, mode);
}


bool Prox_in_Circle(Vector3 center, int radius, Vector3 Ent)
{
	return (((center.x - Ent.x) * (center.x - Ent.x)) + ((center.y - Ent.y) * (center.y - Ent.y)) < (radius * radius));//is enermy near
}

Vector3 AnglesToForward(Vector3 startO, Vector3 Angles, float scale)
{
	Vector3 forwardedAngle;
	AngleVectors_(Angles, &forwardedAngle, 0, 0);
	return (startO + (forwardedAngle * scale));
}

void DrawLine(float x1, float y1, float x2, float y2, color col)
{
	float X, Y, Angle, L1, L2, H1;
	H1 = y2 - y1;
	L1 = x2 - x1;
	L2 = Sqrt(L1 * L1 + H1 * H1);
	X = x1 + ((L1 - L2) / 2);
	Y = y1 + (H1 / 2);
	Angle = (float)Atan2(H1, L1) * (180 / 3.14159265358979323846);
	CG_DrawRotatedPic1(X, Y, L2, 1, Angle, col, "white", 7);
}

void DrawLine_(float x1, float y1, float x2, float y2, color col, int s)
{
	float X, Y, Angle, L1, L2, H1;
	H1 = y2 - y1;
	L1 = x2 - x1;
	L2 = sqrtf(L1 * L1 + H1 * H1);
	X = x1 + ((L1 - L2) / 2);
	Y = y1 + (H1 / 2);
	Angle = (float)atan2f(H1, L1) * (180 / 3.14159265358979323846);
	CG_DrawRotatedPic1(X, Y, L2, s, Angle, col, "white", 7);
}

void MakeLines(Vector3 Origin, float X1, float Y1, float Z1, float X2, float Y2, float Z2, color colors, int size = 1)
{
	Vector2 Screen1, Screen2;
	Vector3 Origin1(Origin.x + X1, Origin.y + Y1, (Origin.z + Z1) - 5);
	Vector3 Origin2(Origin.x + X2, Origin.y + Y2, (Origin.z + Z2) - 5);
	if (WorldPosToScreenPos(Origin1, &Screen1) && WorldPosToScreenPos(Origin2, &Screen2)) {
		DrawLine(Screen1.x, Screen1.y, Screen2.x, Screen2.y, colors);
	}
}

void DrawVAngles(Vector3 FromOrigin, int Entity, color ESP)
{
	Vector2 Screen1, Screen2;
	float Scale = 400;
	Vector3 From(FromOrigin.x, FromOrigin.y, FromOrigin.z);
	Vector3 ToForward = AnglesToForward(From, cgst->clients[Entity].viewAngle, Scale);
	if (WorldPosToScreenPos(From, &Screen1))
	{
		if (WorldPosToScreenPos(ToForward, &Screen2))
		{
			DrawLine(Screen1.x, Screen1.y, Screen2.x, Screen2.y, ESP);
		}
	}
}

void DCrosshair(color ESP)
{
	float_t Size = (8 + (cg->spreadMultiplier / 8));
	Vector2 Center = { cg->refdef.Width / 2, cg->refdef.Height / 2 };
	DrawLine(Center.x - 15, Center.y + 15, Center.x - 4 - Size / 2, Center.y + 4, ESP);//Bottom left to center
	DrawLine(Center.x + 15, Center.y + 15, Center.x + 4 + Size / 2, Center.y + 4, ESP);// Bottom right to center
	DrawLine(Center.x + 15, Center.y - 15, Center.x + 4 + Size / 2, Center.y - 4, ESP);//Top right to center
	DrawLine(Center.x - 15, Center.y - 15, Center.x - 4 - Size / 2, Center.y - 4, ESP);//Top left to center
}

void HealthBar(cg_s * cgss)
{
	/// Healthbar Variables
	color hcolor = cgss->health >= 80 ? color(0, 255, 0, 255) : ((cgss->health >= 50 && cgss->health < 80) ? color(255, 255, 0, 255) : color(255, 0, 0, 255));
	float_t Width = 200, Height = 15, X = cgss->refdef.Width / 2, Y = cgss->refdef.Height - 27;
	float_t wFactor = (Width / 100), wScale = cgss->health * wFactor;
	/// Draw Healthbar
	DrawShader1(X - Width / 2, Y, Width, Height, 0, color(0, 0, 0, 100), "white", 7, align_left);
	DrawShader1(X - Width / 2 + 1, Y + 1, cgss->health > 100 ? wScale = 100 * wFactor - 2 : wScale - 2, Height - 2, 0, hcolor, "white", 7, align_left);
	char boolBuff[100];
	Com_Sprint(boolBuff, sizeof(boolBuff), "Health %i/100", cgss->health);
	DrawTextWithEffectsUI(boolBuff, X, Y + (dc.height / 1.41) + 22, .84, color(255, 255, 255, 255), align_center);
}

void DrawOutline(float x, float y, float width, float height, color color, const char *material, int thickness)
{
	DrawShader1(x - thickness, y - thickness, width + (thickness * 2), thickness, 0, color, "white", 7, align_left); // Top
	DrawShader1(x - thickness, y + height, width + (thickness * 2), thickness, 0, color, "white", 7, align_left); // Bottom
	DrawShader1(x - thickness, y - thickness, thickness, height + thickness, 0, color, "white", 7, align_left); // Left
	DrawShader1(x + width, y - thickness, thickness, height + (thickness * 2), 0, color, "white", 7, align_left); // Right
}

void DrawBorderBox(Vector2 HeadPosition, Vector2 FootPosition, color BoxColor)
{
	float BoxHeight = (FootPosition.y - HeadPosition.y), BoxWidth = BoxHeight / 1.8;

	DrawShader1((FootPosition.x - (BoxWidth / 2) - 1), (FootPosition.y - BoxHeight - 1), BoxWidth, 3, 0, color(0, 0, 0, 255), "white", 7, align_left);//top
	DrawShader1((FootPosition.x - (BoxWidth / 2) - 1), FootPosition.y - 1, BoxWidth + 2, 3, 0, color(0, 0, 0, 255), "white", 7, align_left);//bot
	DrawShader1((FootPosition.x - (BoxWidth / 2) - 1), (FootPosition.y - BoxHeight) - 1, 3, BoxHeight, 0, color(0, 0, 0, 255), "white", 7, align_left);//left
	DrawShader1((FootPosition.x + (BoxWidth / 2) - 1), (FootPosition.y - BoxHeight) - 1, 3, BoxHeight + 3, 0, color(0, 0, 0, 255), "white", 7, align_left);//right

	DrawShader1((FootPosition.x - (BoxWidth / 2)), (FootPosition.y - BoxHeight), BoxWidth, 1, 0, BoxColor, "white", 7, align_left);//top
	DrawShader1((FootPosition.x - (BoxWidth / 2)), FootPosition.y, BoxWidth + 1, 1, 0, BoxColor, "white", 7, align_left);
	DrawShader1((FootPosition.x - (BoxWidth / 2)), (FootPosition.y - BoxHeight), 1, BoxHeight, 0, BoxColor, "white", 7, align_left);
	DrawShader1((FootPosition.x + (BoxWidth / 2)), (FootPosition.y - BoxHeight), 1, BoxHeight, 0, BoxColor, "white", 7, align_left);
}

float GetBoxWidth(int client) {
	if (centity[client].Flags & STANCE_PRONE)
		return 35;
	else return 17;
}

float GetBoxHeight(int client) {
	if (centity[client].Flags & STANCE_PRONE)
		return 25;
	else if (centity[client].Flags &  STANCE_CROUCH)
		return 55;
	else return 70;
}

void Draw3DTriBox(int client, color sColor)
{
	Vector3 Center = centity[client].Origin;
	Center.z += 5;
	float W = GetBoxWidth(client), H = GetBoxHeight(client);
	W *= 1.5;
	H *= 1.2;
	//bottom
	MakeLines(Center, -W, -W, 0, W, -W, 0, sColor, 1);
	MakeLines(Center, -W, -W, 0, -W, W, 0, sColor, 1);
	MakeLines(Center, W, W, 0, W, -W, 0, sColor, 1);
	MakeLines(Center, W, W, 0, -W, W, 0, sColor, 1);
	//middle
	MakeLines(Center, -W, -W, 0, 0, 0, H, sColor, 1);
	MakeLines(Center, -W, W, 0, 0, 0, H, sColor, 1);
	MakeLines(Center, W, -W, 0, 0, 0, H, sColor, 1);
	MakeLines(Center, W, W, 0, 0, 0, H, sColor, 1);
}

void Draw3DBox(int client, color scolor)
{
	Vector3 Center = centity[client].Origin;
	Center.z += 5;

	float W = GetBoxWidth(client), H = GetBoxHeight(client);

	MakeLines(Center, -W, W, 0, W, W, 0, scolor);
	MakeLines(Center, -W, W, 0, -W, W, H, scolor);
	MakeLines(Center, W, W, 0, W, W, H, scolor);
	MakeLines(Center, -W, W, H, W, W, H, scolor);

	MakeLines(Center, -W, W, 0, -W, -W, 0, scolor);
	MakeLines(Center, W, -W, 0, W, W, 0, scolor);
	MakeLines(Center, W, -W, 0, -W, -W, 0, scolor);
	MakeLines(Center, -W, -W, 0, -W, -W, H, scolor);

	MakeLines(Center, W, -W, 0, W, -W, H, scolor);
	MakeLines(Center, -W, W, H, -W, -W, H, scolor);
	MakeLines(Center, W, -W, H, W, W, H, scolor);
	MakeLines(Center, W, -W, H, -W, -W, H, scolor);
}

void DrawBorderBox(int client, Vector2 HeadPosition, Vector2 FootPosition, color Boxcolor)
{
	float BoxHeight = (FootPosition.y - HeadPosition.y);
	float BoxWidth;

	if (centity[client].Flags & STANCE_PRONE)
		BoxWidth = BoxHeight / 0.9;
	else
		BoxWidth = BoxHeight / 1.8;

	DrawShader1((FootPosition.x - (BoxWidth / 2)), (FootPosition.y - BoxHeight), BoxWidth, 1, 0, Boxcolor, "white", 7, align_left);
	DrawShader1((FootPosition.x - (BoxWidth / 2)), FootPosition.y, BoxWidth, 1, 0, Boxcolor, "white", 7, align_left);
	DrawShader1((FootPosition.x - (BoxWidth / 2)), (FootPosition.y - BoxHeight), 1, BoxHeight, 0, Boxcolor, "white", 7, align_left);
	DrawShader1((FootPosition.x + (BoxWidth / 2)), (FootPosition.y - BoxHeight), 1, BoxHeight, 0, Boxcolor, "white", 7, align_left);
}


void DrawBoxSolid(int client, Vector2 HeadPosition, Vector2 FootPosition, color BoxColor)
{
	float BoxHeight = (FootPosition.y - HeadPosition.y);
	float BoxWidth;
	if (centity[client].Flags & STANCE_PRONE)
		BoxWidth = BoxHeight / 0.9;
	else
		BoxWidth = BoxHeight / 1.8;

	BoxColor.a = 0.60f;

	DrawShader1((HeadPosition.x - (BoxWidth / 2) - 1), FootPosition.y - BoxHeight - 1, BoxWidth, BoxHeight, 0, BoxColor, "white", 7, align_left);//filled

}


void DrawCorneredBox(int client, Vector2 head, Vector2 foot, color color)
{
	float BoxHeight = (foot.y - head.y);
	float BoxWidth;

	if (centity[client].Flags & STANCE_PRONE)
		BoxWidth = BoxHeight / 0.9;
	else
		BoxWidth = BoxHeight / 1.8;

	int WidthThird = BoxWidth / 4;
	int HeightThird = WidthThird;
	/* draw eight lines */
	//topleft 
	DrawShader1(head.x - BoxWidth / 2, foot.y - BoxHeight - 1, WidthThird, 1, 0, color, "white", 7, align_left);//h
	DrawShader1(head.x - BoxWidth / 2, foot.y - BoxHeight - 1, 1, HeightThird, 0, color, "white", 7, align_left); //v
																								  //topright
	DrawShader1((head.x + BoxWidth / 2) - WidthThird, foot.y - BoxHeight - 1, WidthThird, 1, 0, color, "white", 7, align_left); //h
	DrawShader1(head.x + BoxWidth / 2, foot.y - BoxHeight - 1, 1, HeightThird, 0, color, "white", 7, align_left);//v
																								 //bottom left
	DrawShader1(head.x - BoxWidth / 2, foot.y - 3, WidthThird, 1, 0, color, "white", 7, align_left); //h
	DrawShader1(head.x - BoxWidth / 2, foot.y - HeightThird - 3, 1, HeightThird, 0, color, "white", 7, align_left);//v
																																 //bottom right
	DrawShader1((head.x + BoxWidth / 2) - WidthThird, foot.y - 3, WidthThird, 1, 0, color, "white", 7, align_left);//h
	DrawShader1(head.x + BoxWidth / 2, foot.y - HeightThird - 3, 1, HeightThird + 1, 0, color, "white", 7, align_left); //v		
}

void HandleESPBox(int Index, int client, Vector2 FeetPos, Vector2 HeadPos, color scolor)
{
	if (bot.esp.bound == 0)
		null;
	if (bot.esp.bound == 1)
		DrawBorderBox(HeadPos, FeetPos, scolor);
	if (bot.esp.bound == 2)
		DrawCorneredBox(client, HeadPos, FeetPos, scolor);
	if (bot.esp.bound == 3)
		DrawBoxSolid(client, HeadPos, FeetPos, scolor);
	if (bot.esp.bound == 4)
		Draw3DBox(client, scolor);
	if (bot.esp.bound == 5)
		Draw3DTriBox(client, scolor);
}

void DrawBone(centity_s * Entity, short from, short to, color color)
{
	Vector2 FromCoords, ToCoords;
	Vector3 fromv, tov;
	AimTarget_GetTagPos(Entity, from, &fromv);
	AimTarget_GetTagPos(Entity, to, &tov);
	if (WorldPosToScreenPos(fromv, &FromCoords) && WorldPosToScreenPos(tov, &ToCoords))
		DrawLine(FromCoords.x, FromCoords.y, ToCoords.x, ToCoords.y, color);
}

void DoAllBones(centity_s * i, color ESPcolor)
{
	/*DrawBone(i, EspBoneIndex[j_knee_le], EspBoneIndex[j_mainroot], ESPcolor);
	DrawBone(i, EspBoneIndex[j_elbow_ri], EspBoneIndex[j_wrist_ri], ESPcolor);
	DrawBone(i, EspBoneIndex[j_neck], EspBoneIndex[j_elbow_ri], ESPcolor);
	DrawBone(i, EspBoneIndex[j_ankle_ri], EspBoneIndex[j_knee_ri], ESPcolor);
	DrawBone(i, EspBoneIndex[j_elbow_le], EspBoneIndex[j_wrist_le], ESPcolor);
	DrawBone(i, EspBoneIndex[j_ankle_le], EspBoneIndex[j_knee_le], ESPcolor);
	DrawBone(i, EspBoneIndex[j_knee_ri], EspBoneIndex[j_mainroot], ESPcolor);
	DrawBone(i, EspBoneIndex[j_mainroot], EspBoneIndex[j_neck], ESPcolor);
	DrawBone(i, EspBoneIndex[j_neck], EspBoneIndex[j_elbow_le], ESPcolor);
	DrawBone(i, EspBoneIndex[j_neck], EspBoneIndex[j_head], ESPcolor);*/
}

#pragma region crosshair compass
Vector2 cCenter;

int CG_DrawWarningPointer_t[2] = { 0x39FA8, 0xD67E98 };
void(*CG_DrawWarningPointer_f)(int client, float centerX, float centerY, Vector3 *grenadeOffset, float *color, const float radiusOffset, const float scaleFactor) = (void(*)(int, float, float, Vector3 *, float *, const float, const float))CG_DrawWarningPointer_t;


void  CG_DrawWarningPointer(int i, color c, const float radiusOffset, const float scaleFactor)
{
	float centerX = cg->refdef.Width / 2;
	float centerY = cg->refdef.Height / 2;
	Vector3 grenadeOffset;
	grenadeOffset -= (centity[cg->clientNum].Origin - centity[i].Origin);
	CG_DrawWarningPointer_f(0, centerX, centerY, &grenadeOffset, (float*)&color(0, 0, 0, 255), radiusOffset + 0.6, scaleFactor);
	CG_DrawWarningPointer_f(0, centerX, centerY, &grenadeOffset, (float*)&c, radiusOffset, scaleFactor);
}

#pragma endregion

void HandleSnapLines(int client, Vector2 * FeetLocation, Vector2 * HeadLocation, color sColor)
{
	if (bot.esp.snaplines == 0) return;
	switch (bot.esp.snaplines) {
	case 0:
		//Off
		break;
	case 1: DrawLine(dc.width / 2, dc.height - dc.height + 15, HeadLocation->x, HeadLocation->y, sColor);
		break;
	case 2: DrawLine(dc.width / 2, dc.height / 2, FeetLocation->x, FeetLocation->y, sColor);
		break;
	case 3: DrawLine(dc.width / 2, dc.height - 15, FeetLocation->x, FeetLocation->y, sColor);
		break;
	}
}

void prox(int i)
{
	if (Prox_in_Circle(centity[cg->clientNum].Origin, 350.0, centity[i].Origin))
	{
		DrawTextWithEffectsUI("[Enemy] is near", cg->refdef.Width / 2, 34, .95, color(255, 0, 0, 255), align_center);
	}
}
int num[2048];
void dist(int i, Vector2 FootPosition, color Color)
{
	FootPosition.y += 20;
	int Distance1 = centityt[i].nextState.lerp.u.scriptMover.flags/*(Distance(centity[i].Origin, centity[cg->clientNum].Origin) / 12 / 3.28)*/;
	char boolBuff[100];
	snprintf(boolBuff, sizeof(boolBuff), "Zombie %i", Distance1);
	DrawTextWithEffectsUI(boolBuff, FootPosition.x, FootPosition.y, .80f, Color, align_left);

}

Vector2 RadarCenter_;
float RadarSize[2];
Vector2 Center_;

bool CScr_IsAlive(int i) {
	if ((centity[i].Type == ET_Player))
	{
		return (!cg->clients[i].Dead) && strcmp(cg->clients[i].PlayerModel, "");
	}
	else
	{
		return false;
	}
}


void EntityCount()
{
		bot.esp.getNumberOfEntities = 0;
		bot.esp.maxclients = 0;
		Vector2 ET_ItemPosition;

		for (int i = 0; i < 1048; i++)
		{
			Vector3 EntOrigin = centity[i].Origin;

			if (centity[i].Type > 0)
			{
				if (((centity[i].State & (1 << 6)) != 0))
				{
					if (WorldPosToScreenPos(EntOrigin, &ET_ItemPosition))
					{
						bot.esp.getNumberOfEntities++;
					}
				}
			}

			if (centity[i].Type == ET_PLAYER)
			{
				bot.esp.maxclients++;
			}
		}
}//septics cancer 

void EntityVisuals(int i)
{
	//CrosshairCompassWeapEntityVisuals(i);
	if (bot.esp.benableworldents)
	{
		Vector2 Location;
		Vector2 ET_ItemPosition;
		Vector3 EntOrigin = centity[i].Origin;
		int wid = centity[i].WeaponID;
		int pid = centity[i].pickupId;

		WeaponVariantDef*  weapondef = BG_GetWeaponVariantDef(wid);
		WeaponVariantDef*  weapondefid = BG_GetWeaponVariantDef(pid);
		if (!weapondefid)return;
		if (!weapondef)return;

		if (centity[i].Type > 0)
		{

			if (WorldPosToScreenPos(EntOrigin, &ET_ItemPosition))
			{
				if (centity[i].Type == ET_ITEM)
				{
					if (((centity[i].State & (1 << 6)) != 0))
					{
						if (!strcmp(weapondefid->name, "scavenger_item_mp") && bot.esp.bpickupscavsworld)//scavs
						{
							DrawShaderP(ET_ItemPosition.x - 70 / 2, ET_ItemPosition.y, 70, 40, 0, color(255, 255, 255, 255), Material_RegisterHandle("hud_scavenger_pickup", 0), align_left);
						}
						else if (weapondefid->weapDef->hudIcon && bot.esp.bpickupweaponsworld)//weaps pick up
						{
							DrawShaderP(ET_ItemPosition.x - 70 / 2, ET_ItemPosition.y, 70, 40, 0, color(255, 255, 255, 255), weapondefid->weapDef->hudIcon, align_left);
						}
					}
				}
				if (centity[i].Type == ET_MISSILE && bot.esp.bnadesworld)//nades
				{
					if (((centity[i].State & (1 << 6)) != 0))
					{
						if (weapondefid->weapDef->hudIcon)
						{
							DrawShaderP(ET_ItemPosition.x - 40 / 2, ET_ItemPosition.y, 40, 40, 0, color(255, 255, 255, 255), weapondefid->weapDef->hudIcon, align_left);
						}
					}
				}
				if (centity[i].Type == ET_PLAYER && bot.esp.bweapsworld)
				{
					if (CScr_IsAlive(i))
					{
						if (weapondef->weapDef->hudIcon)//weapons
						{
							DrawShaderP(ET_ItemPosition.x - 70 / 2, ET_ItemPosition.y, 70, 40, 0, color(255, 255, 255, 255), weapondef->weapDef->hudIcon, align_left);
						}
						else
						{
							DrawShaderP(ET_ItemPosition.x - 70 / 2, ET_ItemPosition.y, 70, 40, 0, color(255, 255, 255, 255), Material_RegisterHandle("hint_mantle", 0), align_left);
						}
					}
				}
			}
		}
	}
}


struct turretcheck {
	char pad576[0x240];
	int f0x240;
};

struct compass_shit
{
	float compassNorthYaw;
	Vector2 compassNorth;
	void * compassMapMaterial;
	void * compassMapScrambledMaterial;
	Vector2 compassMapUpperLeft;
	Vector2 compassMapWorldSize;
};

/* 4439 */
struct CompassActor
{
	int lastUpdate;
	float lastPos[2];
	float lastEnemyPos[2];
	float satelliteEnemyPos[2];
	float lastYaw;
	int pingTime;
	int beginFadeTime;
	int beginRadarFadeTime;
	int beginSatelliteFadeTime;
	int beginStaticImageFadeTime;
	int beginVoiceFadeTime;
	bool enemy;
	bool inVehicle;
	unsigned int perks[2];
	int needsRevive;
	float currentFadeTimeAmount;
};

/* 4440 */
struct __declspec(align(4)) CompassFakeFire
{
	float pos[2];
	float yaw;
	int entityNum;
	int beginFadeTime;
	bool enemy;
	bool satellite;
};

/* 4441 */
struct CompassVehicle
{
	int entityNum;
	int lastUpdate;
	float lastPos[2];
	float lastYaw;
	team_t team;
	int ownerIndex;
};

/* 4442 */
struct __declspec(align(4)) CompassDogs
{
	int entityNum;
	int lastUpdate;
	float lastPos[2];
	float lastYaw;
	team_t team;
	int ownerIndex;
	bool enemy;
};

/* 4443 */
struct __declspec(align(4)) CompassTurrets
{
	int entityNum;
	int lastUpdate;
	int beginFadeTime;
	float lastPos[2];
	float lastYaw;
	team_t team;
	int ownerIndex;
	bool enemy;
	bool firing;//0x21
};

/* 4444 */
struct CompassArtillery
{
	float pos[2];
	float realPos[2];
	int fireTime;
};

/* 4445 */
struct CompassHelicopter
{
	int entityNum;
	int lastUpdate;
	float lastPos[2];
	float lastYaw;
	team_t team;
	int ownerIndex;
};

/* 4446 */
struct CompassGuidedMissile
{
	int entityNum;
	int lastUpdate;
	vec2_t lastPos;
	float lastYaw;
	bool isDrone;
	team_t team;
	int ownerIndex;
};

#define compass_data ((compass_shit*)(*(int*)(0xE22F18) + 0x69B78))
#define FLOAT_1_0 1.0f
#define compass_max_range (*(float*)(0x01cc9d78))
#define color_white color(255, 255, 255, 255)
#define __mask_neg_float -1.0f

int CG_Vehicle_GetVehicleDef_t[2] = { 0xCBBF0, 0xD67E98 };
VehicleDef*(*CG_Vehicle_GetVehicleDef_f)(centity_s * cent) = (VehicleDef*(*)(centity_s *))CG_Vehicle_GetVehicleDef_t;

VehicleDef * CG_Vehicle_GetVehicleDef(centity_s * cent) {
	return CG_Vehicle_GetVehicleDef_f(cent);
}

float _mm_xor_ps(float v15, float _mask__NegFloat_)
{
	return v15 * _mask__NegFloat_;
}

int CG_CompassCalcDimensions_t[2] = { 0x2F810, 0xD67E98 };
void(*CG_CompassCalcDimensions_f)(int compassType, cg_sa *cgaa, rectDef_s *parentRect, rectDef_s *rect, float *x, float *y, float *w, float *h) = (void(*)(int, cg_sa *, rectDef_s *, rectDef_s *, float *, float *, float *, float *))CG_CompassCalcDimensions_t;

void __cdecl CG_CompassCalcDimensions(int compassType, cg_sa *cgaa, rectDef_s *parentRect, rectDef_s *rect, float *x, float *y, float *w, float *h)
{
	CG_CompassCalcDimensions_f(compassType, cgaa, parentRect, rect, x, y, w, h);
}

int R_AddCmdDrawStretchPicRotateSTInternal_t[2] = { 0x76A55C, 0xD67E98 };
void(*R_AddCmdDrawStretchPicRotateSTInternal_f)(float x, float y, float w, float h, float centerS, float centerT, float radiusST, float scaleFinalS, float scaleFinalT, float angle, const float * color, void * material) = (void(*)(float, float, float, float, float, float, float, float, float, float, const float *, void *))R_AddCmdDrawStretchPicRotateSTInternal_t;

void __cdecl R_AddCmdDrawStretchPicRotateSTInternal(float x, float y, float w, float h, float centerS, float centerT, float radiusST, float scaleFinalS, float scaleFinalT, float angle, const float * color, void * material)
{
	R_AddCmdDrawStretchPicRotateSTInternal_f(x, y, w, h, centerS, centerT, radiusST, scaleFinalS, scaleFinalT, angle, color, material);
}

int ScrPlace_ApplyRect_t[2] = { 0x15FFE0, 0xD67E98 };
void(*ScrPlace_ApplyRect_f)(int r1, float *x, float *y, float *w, float *h, int horzAlign, int vertAlign) = (void(*)(int, float *, float *, float *, float *, int, int))ScrPlace_ApplyRect_t;


void __cdecl ScrPlace_ApplyRect(float *x, float *y, float *w, float *h, int horzAlign, int vertAlign)
{
	ScrPlace_ApplyRect_f(0xFB9DE0, x, y, w, h, horzAlign, vertAlign);
}

void __cdecl CL_DrawStretchPicRotatedSTInternal(float x, float y, float w, float h, int horzAlign, int vertAlign, float centerS, float centerT, float radiusST, float scaleFinalS, float scaleFinalT, float angle, color c, pvoid Material)
{
	ScrPlace_ApplyRect(&x, &y, &w, &h, horzAlign, vertAlign);
	R_AddCmdDrawStretchPicRotateSTInternal(x, y, w, h, centerS, centerT, radiusST, scaleFinalS, scaleFinalT, angle, (float*)&c, Material);
}

enum CompassType
{
	COMPASS_TYPE_PARTIAL = 0x0,
	COMPASS_TYPE_FULL = 0x1,
};

rectDef_s parentRect, rect;
void __cdecl CG_CompassDrawPlayerMap(CompassType compassType)
{
	/// stack
	Vector2 east, south, mapCenter;
	float delta, delta_4, texCenter, texCenter_4, texRadius, scaleFinalS, scaleFinalT, rotation, x, y, w, h;
	/// radar_render #begin
	float width = 213, hight = 163;

	parentRect.w = width/* + local->bgbgradarsizex*/;
	parentRect.h = hight/* + local->bgbgradarsizey*/;

	rect.w = width + local->bgbgradarsizex;
	rect.h = hight + local->bgbgradarsizey;
	rect.x = -97;
	rect.y = 31;

	w = width + local->bgbgradarsizex;
	h = hight + local->bgbgradarsizey;

	mapCenter.x = cg->refdef.ViewOrigin.x;
	mapCenter.y = cg->refdef.ViewOrigin.y;

	east.x = compass_data->compassNorth.y;
	east.y = _mm_xor_ps(compass_data->compassNorth.x, __mask_neg_float);
	south.x = _mm_xor_ps(compass_data->compassNorth.x, __mask_neg_float);
	south.y = _mm_xor_ps(compass_data->compassNorth.y, __mask_neg_float);

	delta = mapCenter.x - compass_data->compassMapUpperLeft.x;
	delta_4 = mapCenter.y - compass_data->compassMapUpperLeft.y;
	texCenter = (float)((float)(delta * east.x) + (float)(delta_4 * east.y)) / compass_data->compassMapWorldSize.x;
	texCenter_4 = (float)((float)(delta * south.x) + (float)(delta_4 * south.y)) / compass_data->compassMapWorldSize.y;
	if (compass_data->compassMapWorldSize.x <= compass_data->compassMapWorldSize.y)
	{
		texRadius = (float)(0.5 * compass_max_range) / compass_data->compassMapWorldSize.y;
		scaleFinalS = compass_data->compassMapWorldSize.y / compass_data->compassMapWorldSize.x;
		scaleFinalT = FLOAT_1_0;
	}
	else
	{
		texRadius = (float)(0.5 * compass_max_range) / compass_data->compassMapWorldSize.x;
		scaleFinalS = FLOAT_1_0;
		scaleFinalT = compass_data->compassMapWorldSize.x / compass_data->compassMapWorldSize.y;
	}

	rotation = _mm_xor_ps((cg->playerstate.viewAngles.y - compass_data->compassNorthYaw), __mask_neg_float);

	CG_CompassCalcDimensions(compassType, cga, &parentRect, &rect, &x, &y, &w, &h);
	if (compassType != 1)
	{
		CL_DrawStretchPicRotatedSTInternal(x, y, w, h, rect.horzAlign, rect.vertAlign, texCenter, texCenter_4, texRadius, scaleFinalS, scaleFinalT, rotation, color_white, compass_data->compassMapMaterial);
	}
	else
	{
		CL_DrawStretchPicInternal(x, y, w, h, rect.horzAlign, rect.vertAlign, 0.0, 0.0, 1.0, 1.0, color_white, compass_data->compassMapMaterial);
	}
}

int Com_SessionMode_IsMode_t[2] = { Com_SessionMode_IsMode_a, 0xD67E98 };
bool(*Com_SessionMode_IsMode_f)(eSessionModes_mode mode) = (bool(*)(eSessionModes_mode))Com_SessionMode_IsMode_t;

bool __cdecl Com_SessionMode_IsMode(eSessionModes_mode mode) {
	return Com_SessionMode_IsMode_f(mode);
}


void drawcompass__()
{
	if (bot.esp.bradar)
	{
		DrawShader1(RadarCenter_.x - RadarSize[0], (RadarCenter_.y - RadarSize[1] / 2) + 1, RadarSize[0] * 2, RadarSize[1], 0, color(0, 0, 0, 200), "white", 0, align_left);//back
		CG_CompassDrawPlayerMap(COMPASS_TYPE_PARTIAL);
	}
}

void DrawRadarOutLines()
{
	if (bot.esp.bradar)
	{
		if (cg->zoomProgress > 0)
		{
			DrawLine(RadarCenter_.x - RadarSize[0] / 2 + cg->zoomProgress * 30, RadarCenter_.y - RadarSize[1] / 2, RadarCenter_.x, RadarCenter_.y, color(255, 255, 255, 100));//dynamic line
			DrawLine(RadarCenter_.x + RadarSize[0] / 2 - cg->zoomProgress * 30, RadarCenter_.y - RadarSize[1] / 2, RadarCenter_.x, RadarCenter_.y, color(255, 255, 255, 100));//dynamic line
		}
		else
		{
			DrawLine(RadarCenter_.x - RadarSize[0] / 2 + cg->spreadMultiplier / 8, RadarCenter_.y - RadarSize[1] / 2, RadarCenter_.x, RadarCenter_.y, color(255, 255, 255, 100));//dynamic line
			DrawLine(RadarCenter_.x + RadarSize[0] / 2 - cg->spreadMultiplier / 8, RadarCenter_.y - RadarSize[1] / 2, RadarCenter_.x, RadarCenter_.y, color(255, 255, 255, 100));//dynamic line
		}

		DrawStaticOutline1(RadarCenter_.x - RadarSize[0], (RadarCenter_.y - RadarSize[1] / 2) + 1, RadarSize[0] * 2, RadarSize[1], menu.skin, 2.1);//Draw border

		DrawShader1(RadarCenter_.x - RadarSize[0], RadarCenter_.y, RadarSize[0] * 2, .55, 0, color(255, 255, 255, 100), "white", 9, align_left); // horz
		DrawShader1(RadarCenter_.x, RadarCenter_.y - RadarSize[1] / 2, .55, RadarSize[1], 0, color(255, 255, 255, 100), "white", 9, align_left); // vert
		DrawShader1(RadarCenter_.x - 10, RadarCenter_.y - 10, 21, 21, 0, menu.skin, "compassping_player", 7, align_left);
	}
}

double __cdecl AngleNormalize360(const float angle)
{
	float v2; // [sp+8h] [bp-14h]@2
	float v3; // [sp+Ch] [bp-10h]@1
	float result; // [sp+14h] [bp-8h]@1

	v3 = floor((float)(angle * 0.0027777778));
	result = ((float)(angle * 0.0027777778) - v3) * 360.0;
	if ((float)(result - 360.0) < 0.0)
		v2 = ((float)(angle * 0.0027777778) - v3) * 360.0;
	else
		v2 = result - 360.0;
	return v2;
}

#define s_compassHelicopter ((CompassHelicopter*)(0xDEA600))
#define s_compassActors ((CompassActor*)(0xDE78A0))
#define s_compassFakeFire ((CompassFakeFire*)(0xDE8620))
#define s_compassVehicles ((CompassVehicle*)(0xDE8E20))
#define s_compassDogs ((CompassDogs*)(0xDEB5E0))
#define s_compassTurrets ((CompassTurrets*)(0xDE9220))
#define s_compassArtillery ((CompassArtillery*)(0xDEA420))
#define s_compassGuidedMissiles ((CompassGuidedMissile*)(0xDEA980))


void DrawRadarDynamics(int i, color ESP, CompassType compasstype)
{
	if (bot.esp.bradar)
	{
		int wid = centity[i].WeaponID;
		int pid = centity[i].pickupId;
		WeaponVariantDef*  weapondef = BG_GetWeaponVariantDef(wid);
		WeaponVariantDef*  weapondefid = BG_GetWeaponVariantDef(pid);

		float RotateX, RotateY;
		if (!weapondefid)return;
		if (!weapondef)return;
		if (centity[i].Type > 0)
		{
			color compasscolor = CG_IsEntityFriendlyNotEnemy(&centity[i]) ? color(0, 255, 255, 255) : color(255, 0, 0, 255);
			color finalcolor = (i == cg->clientNum) ? color(0, 255, 255, 255) : compasscolor;
			int RadarX, RadarY;
			RadarSize[0] = local->radarsizex;
			RadarSize[1] = local->radarsizey;
			RadarCenter_.x = local->bgradarsizex;
			RadarCenter_.y = local->bgradarsizey;

		
			float Angle = cg->playerstate.viewAngles.y / 180 * 3.141;

			RadarX = centity[cg->clientNum].Origin.x - centity[i].Origin.x;
			RadarY = centity[cg->clientNum].Origin.y - centity[i].Origin.y;

			float RotateX = RadarY * cosf(Angle) - RadarX * sinf(Angle);
			float RotateY = RadarX * cosf(Angle) + RadarY * sinf(Angle);

			float FinalX = RadarCenter_.x + RotateX / (8.1875f + (local->scale / 320.0f));//clamps players x on max range scale
			float FinalY = RadarCenter_.y + RotateY / (10.5f + (local->scale / 256.0f));//clamps players y on max range scale

			if (FinalX < RadarCenter_.x - RadarSize[0]) FinalX = (RadarCenter_.x - RadarSize[0]) + 2;
			if (FinalY < RadarCenter_.y - RadarSize[1] / 2) FinalY = (RadarCenter_.y - RadarSize[1] / 2) + 2;

			if (FinalX > RadarCenter_.x + RadarSize[0]) FinalX = (RadarCenter_.x + RadarSize[0]) - 2;
			if (FinalY > RadarCenter_.y + RadarSize[1] / 2) FinalY = (RadarCenter_.y + RadarSize[1] / 2) - 2;

			if (((centity[i].State & (1 << 6)) != 0))
			{
				if (centity[i].Type == ET_HELICOPTER && bot.esp.bradrhelis)
				{
					VehicleDef * vd = CG_Vehicle_GetVehicleDef(&centity[i]);
					pvoid * mat = vd->compassIconMaterial;
					if (!strstr(*(char**)mat, "None") && mat != NULL)
					{
						DrawShaderP(FinalX - 55 / 2, FinalY - 55 / 2, 55, 55, cg->playerstate.viewAngles.y - centityt[i].pose.angles[1], finalcolor, mat, align_left);
					}
				}
				if (centity[i].Type == ET_VEHICLE && bot.esp.bradrvehicles)
				{
					VehicleDef * vd = CG_Vehicle_GetVehicleDef(&centity[i]);
					pvoid * mat = vd->compassIconMaterial;
					if (!strstr(*(char**)mat, "None") && mat != NULL)
					{
						DrawShaderP(FinalX - 20, FinalY - 20, 40, 40, (cg->playerstate.viewAngles.y - centityt[i].pose.angles[1]), finalcolor, mat, align_left);
					}
				}
				if (centity[i].Type == ET_DOG && bot.esp.bradrdogos)
				{
					DrawShaderP(FinalX - 10, FinalY - 10, 20, 20, 0, finalcolor, Material_RegisterHandle("compassping_dog", 0), align_left);
				}

				if (centity[i].Type == ET_TURRET && bot.esp.bradrturrets)
				{
					if (centityt[i].nextState.lerp.u.turret.flags > 101)
					{
						DrawShaderP(FinalX - 20, FinalY - 20, 40, 40, cg->playerstate.viewAngles.y - centityt[i].pose.angles[1], finalcolor, Material_RegisterHandle("compass_sg_white", 9), align_left);
					}
					else
					{
						Vector3 Turret_Angle = *(Vector3*)&centityt[i].nextState.lerp.u.turret.gunAngles;
						float Rotation = (cg->playerstate.viewAngles.y - (centityt[i].pose.angles[1]) - Turret_Angle.y);
						DrawShaderP(FinalX - 20, FinalY - 20, 40, 40, Rotation, finalcolor, Material_RegisterHandle("compass_turret_white", 9), align_left);
					}
				}

				if (centity[i].Type == ET_MISSILE && bot.esp.bradrartillery)
				{

					if (centityt[i].nextState.weapon == 143 || centityt[i].nextState.weapon == 144)
					{
						DrawShaderP(FinalX - 25, FinalY - 25, 50, 50, AngleNormalize360(cg->playerstate.viewAngles.y - centityt[i].pose.angles[1]), finalcolor, Material_RegisterHandle("compass_hk", 0), align_left);
					}
					else if (centityt[i].nextState.weapon == 148 || centityt[i].nextState.weapon == 149 || centityt[i].nextState.weapon == 150 || centityt[i].nextState.weapon == 146 || centityt[i].nextState.weapon == 145)
					{
						DrawShaderP(FinalX - 25, FinalY - 25, 50, 50, 0, compasscolor, Material_RegisterHandle("waypoint_recon_artillery_strike", 0), align_left);
					}
				}
				float w = 35, h = 25;
				if (centity[i].Type == ET_ITEM)
				{
					if (!strcmp(weapondefid->name, "scavenger_item_mp") && bot.esp.bradrpickupscavs)
					{
						DrawShaderP(FinalX - w / 2, FinalY - h, 35, 25, 0, color(255, 255, 255, 255), Material_RegisterHandle("hud_scavenger_pickup", 0), align_left);
					}
					else if (weapondefid->weapDef->hudIcon && bot.esp.bradrpickupweaps)
					{
						DrawShaderP(FinalX - 20, FinalY - 20, 40, 40, 0, color(255, 255, 255, 255), weapondefid->weapDef->hudIcon, align_left);
					}
				}
				if (centity[i].Type == ET_MISSILE)
				{
					if (weapondefid->weapDef->hudIcon && bot.esp.bradrnades)//nades
					{
						DrawShaderP(FinalX - 10, FinalY - 10, 20, 20, 0, color(255, 255, 255, 255), weapondefid->weapDef->hudIcon, align_left);
					}
				}
			}
			if (CScr_IsAlive(i) && i != cg->clientNum && centity[i].Type == ET_PLAYER)
			{
				DrawShader1(FinalX - 10, FinalY - 10, 20, 20, (cg->playerstate.viewAngles.y - centityt[i].pose.angles[1]), ESP, "compassping_player", 9, align_left);
			}
		}
	}
}

void DrawTargetScanner(float x, float y, float width, float height, color cross)
{
	bool targetInBox = false;
	Vector2 screen;

	DrawStaticOutline1(x, y, width, height, menu.skin, 2.1);//border
	if (local->alive)
	{
		Vector3 tov;

		AimTarget_GetTagPos(&centity[local->target_num], bot.psztag[local->target_num], &tov);

		targetInBox = (WorldPosToScreenPos(tov, &screen)
			&& screen.x < x + width
			&& screen.x > x
			&& screen.y < y + height
			&& screen.y > y);

		if (targetInBox)
		{
			DrawLine_(x, screen.y, screen.x, screen.y, cross, 2.1);
			DrawLine_(screen.x, (y + height / 2) - (height / 2), screen.x, screen.y, cross, 2.1);
			DrawLine_(screen.x, screen.y, (x + width / 2) + (width / 2), screen.y, cross, 2.1);
			DrawLine_(screen.x, screen.y, screen.x, (y + height / 2) + (height / 2), cross, 2.1);
		}
	}
}
bool ballies[2048];
bool baxis[2048];

int SL_GetString_t[2] = { SL_GetString_a, 0xD67E98 };
short(*SL_GetString_f)(const char *str, unsigned int user) = (short(*)(const char *, unsigned int))SL_GetString_t;

Vector3 AnglesToForward_(Vector3 *Angles, float Distance) {
	float angle, sp, sy, cp, cy, PiDiv;
	PiDiv = M_PI / 180.0f;
	angle = Angles->y * PiDiv;
	sy = sinf(angle);
	cy = cosf(angle);
	angle = Angles->x * PiDiv;
	sp = sinf(angle);
	cp = cosf(angle);
	Vector3 temp = Vector3(cp * cy * Distance, cp * sy * Distance, -sp * Distance);
	return temp;
}

void visual_rendermp()
{	EntityCount();
	if (!bot.esp.ballies && !bot.esp.baxis) return;

	Vector2 HeadPosition, FootPosition;
	short bone = EspBoneIndex[j_head];
	drawcompass__();
	DrawRadarOutLines();

	float DF = cg->zoomProgress > 0 ? (70 - cg->zoomProgress * 3) : (70 + cg->spreadMultiplier / 8);

	for (int i = 0; i < 1048; i++)
	{
	
		ballies[i] = false;
		baxis[i] = false;
		if (bot.esp.ballies && CG_IsEntityFriendlyNotEnemy(&centity[i]))
		{
			ballies[i] = true;
		}
		else
		{
			if (bot.esp.baxis)
				baxis[i] = true;
		}


		if (i == cg->clientNum) continue;
		if (!bot.esp.ballies && ballies[i]) continue;
		if (!bot.esp.baxis && baxis[i]) continue;
		EntityVisuals(i);

		if (CScr_IsAlive(i))
		{
			Vector3 HeadOrigin;
			AimTarget_GetTagPos(&centity[i], bone, &HeadOrigin);
			Vector3 FootOrigin = centity[i].Origin;
			HeadOrigin.z += 12;
			FootOrigin.z -= 5;

			if (EspBoneIndex == NULL)return;

			if (i < 18)
			{
				if (local->target_num == i) menu.esp[i] = (((bot.bvisible_esp[i]) ? color(24, 100, 255, 255) : (bot.bautowall_esp[i]) ? color(255, 255, 22, 255) : color(255, 255, 255, 255)));
				else if (ballies[i]) menu.esp[i] = bot.bvisible_esp[i] ? color(0, 255, 0, 255) : color(0, 200, 0, 200);
				else if (baxis[i]) menu.esp[i] = (((bot.bvisible_esp[i]) ? color(24, 67, 255, 255) : (bot.bautowall_esp[i]) ? color(255, 255, 0, 255) : color(255, 0, 0, 255)));
			}

			if (bot.esp.bcompass) CG_DrawWarningPointer(i, menu.esp[i], DF, 0.8f);

			if (bot.esp.bprox) prox(i);

			if (WorldPosToScreenPos(FootOrigin, &FootPosition) && WorldPosToScreenPos(HeadOrigin, &HeadPosition))
			{
				HandleSnapLines(i, &FootPosition, &HeadPosition, menu.esp[i]);
				if (bot.esp.bbones) DoAllBones(&centity[i], menu.esp[i]);
				if (bot.esp.bvangles) DrawVAngles(HeadOrigin, i, menu.esp[i]);
				if (bot.esp.bnames) CG_DrawOverheadNames(0, &centity[i], 1.0f, FullName);
				if (bot.esp.bdist) dist(i, FootPosition, color(255, 255, 255, 255));
				HandleESPBox(bot.esp.bound, i, FootPosition, HeadPosition, menu.esp[i]);
			}
		}
		DrawRadarDynamics(i, menu.esp[i], bot.esp.bradartype ? COMPASS_TYPE_FULL : COMPASS_TYPE_PARTIAL);
	}

	if (bot.esp.bhealthbar) HealthBar(cg);
	if (bot.esp.bdynamic) DCrosshair(color(255, 255, 255, 255));
	if (bot.esp.btargetfinder) DrawTargetScanner(70, 49, cg->refdef.Width - 150, cg->refdef.Height - 120, color(255, 255, 255, 255));
}
