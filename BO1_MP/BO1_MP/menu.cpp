#include <devstation\System.h>
#include <devstation\Math.h>
#include <devstation\Vector.h>

#include <hook.h>
#include <CellPad.h>
#include <Structures.h>
#include <Functions.h>
#include <menu.h>

#include <aimassist_mp.h>
#include <visuals_mp.h>
#include <cheats_mp.h>

menudata_s menu;
int cur_index_theme = 0;
menushit Mshit;

//static color Red = { 255, 0, 0, 255 };
//color colors[22] = { dflash, Red, color(255, 255, 0, 255), color(255, 165, 0, 255), color(0, 128, 0, 255), color(0, 0, 255, 255), color(128, 0, 128, 255), color(255, 192, 203, 255), color(127, 255, 212, 255), color(135, 206, 235, 255), color(42, 82, 190, 255), color(255, 0, 255, 255), color(153, 50, 204, 255), color(201, 160, 220, 255), color(50, 205, 50, 255), color(255, 166, 201, 255), color(255, 215, 0, 255), color(255, 69, 0, 255), color(128, 128, 128, 255), color(0, 0, 0, 255), color(255, 255, 255, 255) };
float floatBetweenZeroAndOne = 0.25f;

#define Pri02X			"02X:"
void GetConsoleinfo()
{
	char MacAddress[30];

	//CellNetCtlInfo netInfo1;

	//cellNetCtlGetInfo(CELL_NET_CTL_INFO_ETHER_ADDR, &netInfo1);

	//const char * Mac = (const char *)netInfo1.ether_addr.data;

	//snprintf(MacAddress, sizeof(MacAddress), "%" Pri02X "%" Pri02X  "%" Pri02X  "%" Pri02X  "%" Pri02X  "%" Pri02X, Mac[0] & 0xFF, Mac[1] & 0xFF, Mac[2] & 0xFF, Mac[3] & 0xFF, Mac[4] & 0xFF, Mac[5] & 0xFF);

	//_sys_printf("%s\n", MacAddress);
}

void flash(color * rain)
{
	if (rain->a <= 0) rain->a = 1.0;
	if (rain->r <= 0 && rain->g <= 0 && rain->b <= 0)
		rain->r = 1.0f;
	if (rain->r > 0 && rain->b <= 0.15 / 255.00f)
	{
		rain->r -= menu.menufade / 255.00f;
		rain->g += menu.menufade / 255.00f;
		rain->a = rain->a;
	}
	if (rain->g > 0 && rain->r <= 0.15 / 255.00f)
	{
		rain->g -= menu.menufade / 255.00f;
		rain->b += menu.menufade / 255.00f;
		rain->a = rain->a;
	}
	if (rain->b > 0 && rain->g <= 0.15 / 255.00f)
	{
		rain->r += menu.menufade / 255.00f;
		rain->b -= menu.menufade / 255.00f;
		rain->a = rain->a;
	}
}

void flash2(color * rain)
{
	if (rain->a <= 0) rain->a = 1.0;
	if (rain->r <= 0 && rain->g <= 0 && rain->b <= 0)
		rain->r = 0.95f;
	if (rain->r > 0 && rain->b <= 0.15 / 255.00f)
	{
		rain->r -= menu.menufade / 255.00f;
		rain->g += menu.menufade / 255.00f;
		rain->a = rain->a;
	}
	if (rain->g > 0 && rain->r <= 0.15 / 255.00f)
	{
		rain->g -= menu.menufade / 255.00f;
		rain->b += menu.menufade / 255.00f;
		rain->a = rain->a;
	}
	if (rain->b > 0 && rain->g <= 0.15 / 255.00f)
	{
		rain->r += menu.menufade / 255.00f;
		rain->b -= menu.menufade / 255.00f;
		rain->a = rain->a;
	}
}

bool SLLR;
void _Buttoninfo()
{
		if (!Mshit.Mopened)
		{
			DrawTextWithBackground_UI("Press ^BPS3ButtonShoulderL^ & ^BPS3ButtonDpadL^ to open the menu", 15, dc.height + (dc.height / 1.41), .94, color(255, 255, 255, 255), menu.skin, color(52, 52, 52, 255), align_left);
		}

		else if (Mshit.id > ID_MAIN)
		{
			DrawTextWithBackground_UI("Press ^BPS3ButtonCircle^ to go back || ^BPS3ButtonDpadU^ / ^BPS3ButtonDpadD^ to scroll || ^BPS3ButtonX^ to select", 15, (dc.height + dc.height / 1.41), .90, color(255, 255, 255, 255), menu.skin, color(52, 52, 52, 255), align_left);

		}

		else 
		{
			DrawTextWithBackground_UI("Press ^BPS3ButtonCircle^ to close the menu || ^BPS3ButtonDpadU^ / ^BPS3ButtonDpadD^ to scroll || ^BPS3ButtonX^ to select", 15, (dc.height + dc.height / 1.41), .90, color(255, 255, 255, 255), menu.skin, color(52, 52, 52, 255), align_left);

		}
}

size_t stringlength(const char * s) {
	size_t s_len;
	for (int i = 0; i < strlen(s) - 1; i++)
	{
		if (s[i] != '\0')
			s_len++;
	}
	return s_len;
}

#pragma region command stuff
void local_command_complete(int localClientNum, const wchar_t * wstr, unsigned int length)
{
	char * buffer = (char*)_sys_malloc(length);
	WideCharToMultibyte(wstr, length, buffer);
	if (strlen(buffer) <= 0) return;
	Cbuf_AddText(buffer);
}

void Change_Name_complete(int localClientNum, const wchar_t * wstr, unsigned int length)
{
	char * buffer = (char*)_sys_malloc(length);
	WideCharToMultibyte(wstr, length, buffer);
	//size_t slen = stringlength(buffer);
	if (strlen(buffer) <= 0) return;
	//buffer[slen - 1] = '\0';
	if (cl_ingame())
	{
		char ingameflash[256];
		_sys_sprintf(ingameflash, ";cmd userinfo \"\\clanAbbrev\\\\name\\%s\\xuid\\%s", buffer, 0x26C06E8);
		WriteMemory(0x026C0658, buffer, 32);
		WriteMemory(0x026C067F, buffer, 32);
		Cbuf_AddText(ingameflash);
	}
	else
	{
		WriteMemory(0x026C0658, buffer, 32);
		WriteMemory(0x026C067F, buffer, 32);
	}
}

void dokeyboard()
{
	XShowKeyboardUI(0, L"Local Command", L"", 32, local_command_complete, 0);
}

void dokeyboard1()
{
	XShowKeyboardUI(0, L"Change Name", L"", 32, Change_Name_complete, 0);
}

void local_command()
{
	dokeyboard();
}

void ChangeName()
{
	dokeyboard1();
}

void EndGame()
{
	char buffer[50];
	_sys_sprintf(buffer, "cmd mr %i %i endround", *(int*)(0xF11D9C), 3);
	Cbuf_AddText(buffer);
}

void Disconnect()
{
	char buffer[50];
	_sys_sprintf(buffer, "disconnect 1");
	Cbuf_AddText(buffer);
}

#pragma endregion
#pragma region misc functions
#define ready ((Sys_Milliseconds() - Mshit.tick) > Mshit.wait)
#define active (Mshit.scroll[Mshit.id] == Mshit.maxscroll[Mshit.id])
#define comboactive (menu.combos[Mshit.id][Mshit.scroll[Mshit.id]].scroll == menu.combos[Mshit.id][Mshit.scroll[Mshit.id]].maxscroll)
void movement_event()
{
	static int itick, iwait;
	bool istate = ((Sys_Milliseconds() - itick) > iwait);
	if (istate)
	{
		menu.height < (Mshit.maxscroll[Mshit.id] * 30) ? menu.height += 30 : menu.height >(Mshit.maxscroll[Mshit.id] * 30) ? menu.height -= 30 : menu.height = (Mshit.maxscroll[Mshit.id] * 30);

		Mshit.Mopened ? ((menu.x > 640) ? menu.x -= 150 : menu.x = 640) : (menu.x < 1800) ? menu.x += 150 : menu.x = 1800;

		menu.sypos1 < (Mshit.scroll[Mshit.id] * 30) ? menu.sypos1 += 30 : menu.sypos1 >(Mshit.scroll[Mshit.id] * 30) ? menu.sypos1 -= 30 : menu.sypos1 = (Mshit.scroll[Mshit.id] * 30);
		for (int i = 0; i < 10; i++)
		{
			local->consoley[i] > (i * 35) ? local->consoley[i] -= 1 : local->consoley[i] = (i * 35);
		}
		itick = Sys_Milliseconds(), iwait = (dc.fps < 55.0) ? (1.0 - 60.0 + dc.fps) : (1.0);
	}
}

int CG_CycleWeapon_t[2] = { 0xF6D34, 0xD67E98 };
void(*CG_CycleWeapon_f)(int localClientNum, int cycleForward) = (void(*)(int localClientNum, int cycleForward))CG_CycleWeapon_t;

void CG_CycleWeapon(int localClientNum, int cycleForward)
{
	CG_CycleWeapon_f(localClientNum, cycleForward);
}

void Wait(int timeout)
{
	Mshit.tick = Sys_Milliseconds();
	Mshit.wait = (dc.fps < 55.0) ? (timeout - 60.0 + dc.fps) : (timeout);
}

int pp = 0;
void Cancel_Reload()
{
	if (ready)
	{
		CG_CycleWeapon(0, 0);
		pp++;
		Wait(35);
	}
	if (pp == 2)
	{
		local->canreload = false;
		pp = 0;
	}
}

int SND_Play_t[2] = { 0x4FFA10, 0xD67E98 };
void(*SND_Play_f)(String alias, int fadeTimeMs, float attenuation, int r1, int r2, int r3, int r4) = (void(*)(String , int , float , int , int , int , int ))SND_Play_t;


void SND_Play(String alias, int fadeTimeMs, float attenuation)
{
	SND_Play_f(alias, fadeTimeMs, attenuation, 0, 0, 0, 0);
	Wait(150);
}

void decrypt(char str[], int key)
{
	unsigned int i;
	for (i = 0; i<strlen(str); ++i)
	{
		str[i] = str[i] + key;
	}
}


char * get_ip_address()
{
	char* ip_address;
	int ret;
	union CellNetCtlInfo info;

	ret = cellNetCtlGetInfo(CELL_NET_CTL_INFO_IP_ADDRESS, &info);
	if (ret < 0) {
		/* Error handling */
	}

	memcpy(ip_address, info.ip_address, sizeof(info.ip_address));

	return ip_address;
}

int UI_SafeTranslateString_t[2] = { 0x0370D9C, 0xD67E98 };
String(*UI_SafeTranslateString_f)(String s) = (String(*)(String))UI_SafeTranslateString_t;


int SL_ConvertToString_t[2] = { 0x048E2DC, 0xD67E98 };
String(*SL_ConvertToString_f)(short s) = (String(*)(short))SL_ConvertToString_t;


void Ui_interface()
{
	char MenuBuff[100];
	int size = 25;
#pragma region Encrypting title
	char str[] = "C#DAJeouo^ugese[ik`v";
	decrypt(str, 4);
#pragma endregion
	
	Com_Sprint(MenuBuff, sizeof(MenuBuff), "%s", str);
	DrawTextWithBackground_UI(MenuBuff, 14, 25, .86, color(255, 255, 255, 255), menu.skin, color(52, 52, 52, 255), align_left);
	float height = DrawTextWithBackground_UI("Multiplayer", dc.width - 15, size, .94, color(255, 255, 255, 255), menu.skin, color(52, 52, 52, 255), align_right) + 10;
	if (!menu.fps)
	{
		Com_Sprint(MenuBuff, sizeof(MenuBuff), "FPS: %.f", dc.fps);
		height += DrawTextWithBackground_UI(MenuBuff, dc.width - 15, size + height, .94, color(255, 255, 255, 255), menu.skin, color(52, 52, 52, 255), align_right) + 10;
	}
	if (!menu.res)
	{
		Com_Sprint(MenuBuff, sizeof(MenuBuff), "Resolution: %i x %i", dc.width, dc.height);
		height += DrawTextWithBackground_UI(MenuBuff, dc.width - 15, size + height, .94, color(255, 255, 255, 255), menu.skin, color(52, 52, 52, 255), align_right) + 20;
	}
	if (!menu.serverinfo)
	{
		Com_Sprint(MenuBuff, sizeof(MenuBuff), "%s", "Server Info:");
		height += DrawTextWithBackground_UI(MenuBuff, dc.width - 15, size + height, .94, color(255, 255, 255, 255), menu.skin, color(52, 52, 52, 255), align_right) + 10;
		if (!menu.host)
		{
			Com_Sprint(MenuBuff, sizeof(MenuBuff), "Host Name: %s", Dvar_GetString("party_hostname"));
			height += DrawTextWithBackground_UI(MenuBuff, dc.width - 15, size + height, .94, color(255, 255, 255, 255), menu.skin, color(52, 52, 52, 255), align_right) + 10;
		}
		if (!menu.map)
		{
			Com_Sprint(MenuBuff, sizeof(MenuBuff), "Map Name: %s", Dvar_GetString("party_mapname"));
			height += DrawTextWithBackground_UI(MenuBuff, dc.width - 15, size + height, .94, color(255, 255, 255, 255), menu.skin, color(52, 52, 52, 255), align_right) + 10;
		}
		if (!menu.game)
		{
			Com_Sprint(MenuBuff, sizeof(MenuBuff), "Game Type: %s", Dvar_GetString("party_gametype"));
			height += DrawTextWithBackground_UI(MenuBuff, dc.width - 15, size + height, .94, color(255, 255, 255, 255), menu.skin, color(52, 52, 52, 255), align_right) + 10;
		}

		if (menu.game && menu.host && menu.map)
		{
			menu.serverinfo = true;
		}
	}
	if (cl_ingame_())
	{
		if (!menu.serverinfo)
		{
			if (!menu.ping)
			{
				Com_Sprint(MenuBuff, sizeof(MenuBuff), "Latency: %i", cg->ping);
				height += DrawTextWithBackground_UI(MenuBuff, dc.width - 15, size + height, .94, color(255, 255, 255, 255), menu.skin, color(52, 52, 52, 255), align_right) + 10;
			}
			if (!menu.ents)
			{
				Com_Sprint(MenuBuff, sizeof(MenuBuff), "Entitys On Screen: %i", bot.esp.getNumberOfEntities);
				height += DrawTextWithBackground_UI(MenuBuff, dc.width - 15, size + height, .94, color(255, 255, 255, 255), menu.skin, color(52, 52, 52, 255), align_right) + 10;
			}
			if (!menu.maxc)
			{
				Com_Sprint(MenuBuff, sizeof(MenuBuff), "Max Clients: %i", bot.esp.maxclients);
				height += DrawTextWithBackground_UI(MenuBuff, dc.width - 15, size + height, .94, color(255, 255, 255, 255), menu.skin, color(52, 52, 52, 255), align_right) + 20;
			}

			if (menu.game && menu.host && menu.map && menu.maxc && menu.ents && menu.ping)
			{
				menu.serverinfo = true;
			}
		}

		if (bot.esp.btargetinfo)
		{
			Com_Sprint(MenuBuff, sizeof(MenuBuff), "%s", "Target Info:");
			height += DrawTextWithBackground_UI(MenuBuff, dc.width - 15, size + height, .94, color(255, 255, 255, 255), menu.skin, color(52, 52, 52, 255), align_right) + 10;

			if (local->target_num != -1)
			{
				Com_Sprint(MenuBuff, sizeof(MenuBuff), "Name: %s", cg->clients[local->target_num].PlayerName);
				height += DrawTextWithBackground_UI(MenuBuff, dc.width - 15, size + height, .94, color(255, 255, 255, 255), menu.skin, color(52, 52, 52, 255), align_right) + 10;
				int GDistance = (Distance(centity[local->target_num].Origin, centity[cg->clientNum].Origin) / 12 / 3.28);
				Com_Sprint(MenuBuff, sizeof(MenuBuff), "Distance: %im", GDistance);
				height += DrawTextWithBackground_UI(MenuBuff, dc.width - 15, size + height, .94, color(255, 255, 255, 255), menu.skin, color(52, 52, 52, 255), align_right) + 10;
				int widd = centity[local->target_num].WeaponID;
				if (!widd)return;
				WeaponVariantDef* weapVDef = BG_GetWeaponVariantDef(widd);
				if (weapVDef)
				{
					Com_Sprint(MenuBuff, sizeof(MenuBuff), "Weapon: %s", UI_SafeTranslateString_f(weapVDef->szDisplayName));
					height += DrawTextWithBackground_UI(MenuBuff, dc.width - 15, size + height, .94, color(255, 255, 255, 255), menu.skin, color(52, 52, 52, 255), align_right) + 10;
				}
				Com_Sprint(MenuBuff, sizeof(MenuBuff), "Bone: %s", SL_ConvertToString_f(bot.psztag[local->target_num]));//SL_ConvertToString
				height += DrawTextWithBackground_UI(MenuBuff, dc.width - 15, size + height, .94, color(255, 255, 255, 255), menu.skin, color(52, 52, 52, 255), align_right) + 10;
				Com_Sprint(MenuBuff, sizeof(MenuBuff), "Visible: %s", bot.bvisible_esp[local->target_num] ? "^2True" : "^1False");
				height += DrawTextWithBackground_UI(MenuBuff, dc.width - 15, size + height, .94, color(255, 255, 255, 255), menu.skin, color(52, 52, 52, 255), align_right) + 10;
				Com_Sprint(MenuBuff, sizeof(MenuBuff), "Hittable: %s", bot.bautowall_esp[local->target_num] ? "^2True" : "^1False");
				height += DrawTextWithBackground_UI(MenuBuff, dc.width - 15, size + height, .94, color(255, 255, 255, 255), menu.skin, color(52, 52, 52, 255), align_right) + 10;

				if (bot.baimatfeet)
				{
					Com_Sprint(MenuBuff, sizeof(MenuBuff), "Has Shield: %s", bot.sc[local->target_num] ? "^2True" : "^1False");
					height += DrawTextWithBackground_UI(MenuBuff, dc.width - 15, size + height, .94, color(255, 255, 255, 255), menu.skin, color(52, 52, 52, 255), align_right) + 10;
				}

			}
		}
	}
}

int MenuW = 400;
void addTitle(String title, int ret_id)
{

	Mshit.active_option = (Mshit.scroll[Mshit.id] == Mshit.maxscroll[Mshit.id]);
	
	DrawShader(menu.x, 200, MenuW, 60 + menu.height, 0, color(0, 0, 0, 200), "white", 7, align_center);//back

	DrawShader(menu.x, 200, MenuW, 40, 0, color(52, 52, 52, 255), "white", 7, align_center);//title back

	DrawTextWithEffects(title, menu.x, 240, 1, menu.skin, align_center);//title

	if (Mshit.id == ID_PLAYERS)
	{
		int longip;
		ReadMemory(0x00f9e726 + (Mshit.scroll[Mshit.id] * 328), &longip, 4);
		int * paddress = lformat(longip);
		String name = cg->clients[Mshit.scroll[Mshit.id]].PlayerName;
		char name_format[100];
		_sys_sprintf(name_format, "Name: %s", !strcmp(name, "") ? "Not Connected" : name);
		char* playerIP;
		int ip = *(int*)(0x00F9E726 + Mshit.scroll[Mshit.id] * 0x148);
		if (ip != 0) {
			int p1 = (ip & 0xff000000) >> 24;
			int p2 = (ip & 0x00ff0000) >> 16;
			int p3 = (ip & 0x0000ff00) >> 8;
			int p4 = (ip & 0x000000ff) >> 0;
			char boolBuff[100];
			snprintf(boolBuff, sizeof(boolBuff), "%i.%i.%i.%i", p1, p2, p3, p4);
			playerIP = boolBuff;
		}
		else
			playerIP = "0.0.0.0";

		DrawShader(menu.x, 200 + 60 + menu.height + 30, MenuW, 60, 0, color(0, 0, 0, 200), "white", 7, align_center);
		DrawText(name_format, (menu.x + 5) - (MenuW / 2), 282 + menu.height + 33, 0, .84, "extraSmallFont", color(255, 255, 255, 255), align_left, 0);
		DrawText(playerIP, (menu.x + 5) - (MenuW / 2), 282 + menu.height + 63, 0, .84, "extraSmallFont", color(255, 255, 255, 255), align_left, 0);
	}
	
	

	char menu_number[100];
	_sys_sprintf(menu_number, "%i/%i", Mshit.scroll[Mshit.id] + 1, Mshit.maxscroll[Mshit.id]);

	Mshit.maxscroll[Mshit.id] = 0;
	Mshit.prev[Mshit.id] = ret_id;
	DrawShader(menu.x, 260 + (menu.height - menu.height) + menu.sypos1 - 2, MenuW, 24, 0, color(52, 52, 52, 255), "white", 7, align_center);
	DrawShader(menu.x, 200 + 60 + menu.height, MenuW, 30, 0, color(52, 52, 52, 255), "white", 7, align_center);
	DrawText(menu_number, menu.x + 188, 277 + menu.height + (30 / 3), 0, .84, "extraSmallFont", menu.skin, align_right, 1);

	DrawOutline(menu.x - 200, 200, MenuW, 90 + menu.height, menu.skin, 2.1, align_left);//outline
}

void addSubmenu(String title, int sub_id)
{
	if (active && PadDown(PAD_CROSS) && ready)
		SND_Play("cac_screen_fade", 3, 3),
		Mshit.id = sub_id, Wait(200);

	DrawShader(menu.x + 190, 264 + (Mshit.maxscroll[Mshit.id] * 30), 15, 15, 180, color(255, 255, 255, 255), "menu_safearea_arrow", 7, align_right);
	DrawText(title, (active ? (menu.x + 10) : (menu.x + 5)) - (MenuW / 2), 282 + (Mshit.maxscroll[Mshit.id] * 30), 0, .84, "extraSmallFont", active ? menu.skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	Mshit.maxscroll[Mshit.id]++;

}

void addColorSubmenu(String title, int sub_id, int i)
{
	if (active && PadDown(PAD_CROSS) && ready)
		SND_Play("cac_screen_fade", 3, 3),
		Mshit.id = sub_id, Wait(200);

	DrawShader(menu.x + 190, 264 + (Mshit.maxscroll[Mshit.id] * 30), 15, 15, 0, menu.skin, "white", 0, align_right);
	DrawText(title, (active ? (menu.x + 10) : (menu.x + 5)) - (MenuW / 2), 282 + (Mshit.maxscroll[Mshit.id] * 30), 0, .84, "extraSmallFont", active ? menu.skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	Mshit.maxscroll[Mshit.id]++;
}

void addColormenu(String title, color col)
{
	if (active && PadDown(PAD_CROSS) && ready)
		SND_Play("cac_screen_fade", 3, 3),
		Wait(200),
	
	menu.colorslide.a = col.a,
	menu.colorslide.r = col.r,
	menu.colorslide.g = col.g,
	menu.colorslide.b = col.b,
	menu.colorslide1.a = col.a,
	menu.colorslide1.r = col.r,
	menu.colorslide1.g = col.g,
	menu.colorslide1.b = col.b,

	menu.skin.a = col.a,
	menu.skin.r = col.r,
	menu.skin.g = col.g,
	menu.skin.b = col.b,
	menu.skin2.a = col.a,
	menu.skin2.r = col.r,
	menu.skin2.g = col.g,
	menu.skin2.b = col.b;

	DrawShader(menu.x + 190, 264 + (Mshit.maxscroll[Mshit.id] * 30), 15, 15, 0, col, "white", 0, align_right);
	DrawText(title, (active ? (menu.x + 10) : (menu.x + 5)) - (MenuW / 2), 282 + (Mshit.maxscroll[Mshit.id] * 30), 0, .84, "extraSmallFont", active ? menu.skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	Mshit.maxscroll[Mshit.id]++;
}

void addColorSubmenu1(String title, int sub_id, int i)
{
	if (active && PadDown(PAD_CROSS) && ready)
		SND_Play("cac_screen_fade", 3, 3),
		Mshit.id = sub_id, Wait(200);

	DrawShader(menu.x + 190, 264 + (Mshit.maxscroll[Mshit.id] * 30), 15, 15, 0, menu.skin2, "white", 0, align_right);
	DrawText(title, (active ? (menu.x + 10) : (menu.x + 5)) - (MenuW / 2), 282 + (Mshit.maxscroll[Mshit.id] * 30), 0, .84, "extraSmallFont", active ? menu.skin2 : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	Mshit.maxscroll[Mshit.id]++;
}

void addOption(String title)
{
	DrawText(title, (active ? (menu.x + 10) : (menu.x + 5)) - (MenuW / 2), 282 + (Mshit.maxscroll[Mshit.id] * 30), 0, .84, "extraSmallFont", active ? menu.skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	Mshit.maxscroll[Mshit.id]++;
}


void addKOption(const char* title, void(*func)())
{
	if (active && ready && PadDown(PAD_CROSS))
		func(), Wait(150);

	DrawText(title, (active ? (menu.x + 10) : (menu.x + 5)) - (MenuW / 2), 282 + (Mshit.maxscroll[Mshit.id] * 30), 0, .84, "extraSmallFont", active ? menu.skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	Mshit.maxscroll[Mshit.id]++;
}

void addOption(const char* title, void(*func)())
{
	if (active && ready && PadDown(PAD_CROSS))
		func();

	DrawText(title, (active ? (menu.x + 10) : (menu.x + 5)) - (MenuW / 2), 282 + (Mshit.maxscroll[Mshit.id] * 30), 0, .84, "extraSmallFont", active ? menu.skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	Mshit.maxscroll[Mshit.id]++;
}

void addCOption(const char* title,  char * des, void(*func)())
{
	if (active && ready && PadDown(PAD_CROSS))
		func();
	char MenuBuff[100];
	snprintf(MenuBuff, sizeof(MenuBuff), "%s", des);
	if (active)DrawText(MenuBuff, (menu.x + 5) - (MenuW / 2), 277 + menu.height + (30 / 3), 0, .84, "extraSmallFont", menu.skin, align_left, 1);
	DrawText(title, (active ? (menu.x + 10) : (menu.x + 5)) - (MenuW / 2), 282 + (Mshit.maxscroll[Mshit.id] * 30), 0, .84, "extraSmallFont", active ? menu.skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	Mshit.maxscroll[Mshit.id]++;
}

void addCamoOption(const char* title, const char* Camo)
{
	if (active)
	{
		if (ready)
		{
			if (PadDown(PAD_CROSS))
			{
				SND_Play("cac_grid_equip_item", 3, 3);
				blah();
				Wait(150);
			}
		}
	}

	DrawText(title, (active ? (menu.x + 10) : (menu.x + 5)) - (MenuW / 2), 282 + (Mshit.maxscroll[Mshit.id] * 30), 0, .84, "extraSmallFont", active ? menu.skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	Mshit.maxscroll[Mshit.id]++;
}

void addBar(String title, float Min, float Max, void(*func_setbarvalue)(float value), float* barvalue, char(*menudescription), bool bSLLR)
{
	float incrementValue = (Max - Min) / 100;
	if (menu.barslidevalue[Mshit.id][Mshit.maxscroll[Mshit.id]] <= Min)
		menu.barslidevalue[Mshit.id][Mshit.maxscroll[Mshit.id]] = Min;
	if (menu.barslidevalue[Mshit.id][Mshit.maxscroll[Mshit.id]] >= Max)
		menu.barslidevalue[Mshit.id][Mshit.maxscroll[Mshit.id]] = Max;

	if (*barvalue <= Min)
		*barvalue = Min;
	if (*barvalue >= Max)
		*barvalue = Max;
	//drawBar
	char MenuBuff[100];
	Com_Sprint(MenuBuff, sizeof(MenuBuff), "%s scale %.2f", menudescription, *barvalue);
	if (active)
	{
		SLLR = bSLLR;
		if (ready)
		{
			if (PadDown(PAD_RIGHT) || PadDown(PAD_LEFT))
			{
				SND_Play("cac_safearea", 3, 3),
					menu.barslidevalue[Mshit.id][Mshit.scroll[Mshit.id]] += (PadDown(PAD_RIGHT)) ? incrementValue : 0;
				menu.barslidevalue[Mshit.id][Mshit.scroll[Mshit.id]] -= (PadDown(PAD_LEFT)) ? incrementValue : 0;
				func_setbarvalue(menu.barslidevalue[Mshit.id][Mshit.scroll[Mshit.id]]); 
				memset(&_pdPad, 0, sizeof(CellPadData));
				Wait(10);
				
			}
		}
	}
	else {
		SLLR = false;
	}
	// increment & decrement the value of x using cSliderPos (it will go from 0-100 no matter what min and max you put)
	DrawShader(menu.x + 190, 270 + (Mshit.maxscroll[Mshit.id] * 30), 100, 3, 180, color(90, 90, 90, 255), "white", 7, align_right); //bar ( full length )
	DrawShader(menu.x + 90, 270 + (Mshit.maxscroll[Mshit.id] * 30), (((*barvalue - Min) / incrementValue)/* - (1)*/), 3, 180, menu.skin, "white", 7, align_left); //bar ( full length )
	if (active)DrawText(MenuBuff, (menu.x + 5) - (MenuW / 2), 277 + menu.height + (30 / 3), 0, .84, "extraSmallFont", menu.skin, align_left, 1);
	DrawShader(menu.x + 90 + (((*barvalue - Min) / incrementValue) /*- (1)*/), 266 + (Mshit.maxscroll[Mshit.id] * 30), 3, 10, 180, color(255, 255, 255, 255), "white", 7, align_left);// slider bar
	DrawText(title, (active ? (menu.x + 10) : (menu.x + 5)) - (MenuW / 2), 282 + (Mshit.maxscroll[Mshit.id] * 30), 0, .84, "extraSmallFont", active ? menu.skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	Mshit.maxscroll[Mshit.id]++;
}

void addColorBar(String title, float Min, float Max, void(*func_setbarvalue)(float value), char(*menudescription), float * value, bool bSLLR)
{
	float incrementValue = (Max - Min) / 100;

	if (menu.barslidevalue[Mshit.id][Mshit.maxscroll[Mshit.id]] <= Min)
		menu.barslidevalue[Mshit.id][Mshit.maxscroll[Mshit.id]] = Min;
	if (menu.barslidevalue[Mshit.id][Mshit.maxscroll[Mshit.id]] >= Max)
		menu.barslidevalue[Mshit.id][Mshit.maxscroll[Mshit.id]] = Max;

	if (*value <= Min)
		*value = Min;
	if (*value >= Max)
		*value = Max;

	//drawBar
	char MenuBuff[100];
	Com_Sprint(MenuBuff, sizeof(MenuBuff), "%s scale %.2f", menudescription, *value);
	if (active)
	{
	
		if (ready)
		{

			if (!menu.fade)
			{
				if (PadDown(PAD_RIGHT) || PadDown(PAD_LEFT))
				{

					SND_Play("cac_safearea", 3, 3),
						menu.barslidevalue[Mshit.id][Mshit.scroll[Mshit.id]] += (PadDown(PAD_RIGHT)) ? incrementValue : 0;
					menu.barslidevalue[Mshit.id][Mshit.scroll[Mshit.id]] -= (PadDown(PAD_LEFT)) ? incrementValue : 0;
					func_setbarvalue(menu.barslidevalue[Mshit.id][Mshit.scroll[Mshit.id]]);
					memset(&_pdPad, 0, sizeof(CellPadData));
					Wait(30);
					
				}
			}
		}
	}

	else {
		SLLR = false;
	}

	menu.barslidevalue[Mshit.id][Mshit.maxscroll[Mshit.id]] = *value;

	DrawShader(menu.x + 190, 270 + (Mshit.maxscroll[Mshit.id] * 30), 100, 3, 180, color(90, 90, 90, 255), "white", 7, align_right); //bar ( full length )
	DrawShader(menu.x + 90, 270 + (Mshit.maxscroll[Mshit.id] * 30), (((menu.barslidevalue[Mshit.id][Mshit.maxscroll[Mshit.id]] - Min) / incrementValue)), 3, 180, menu.skin, "white", 7, align_left); //bar ( full length )
	if (active)DrawText(MenuBuff, (menu.x + 5) - (MenuW / 2), 277 + menu.height + (30 / 3), 0, .84, "extraSmallFont", menu.skin, align_left, 1);
	DrawShader(menu.x + 90 + (((menu.barslidevalue[Mshit.id][Mshit.maxscroll[Mshit.id]] - Min) / incrementValue)), 266 + (Mshit.maxscroll[Mshit.id] * 30), 3, 10, 180, color(255, 255, 255, 255), "white", 7, align_left);// slider bar
	DrawText(title, (active ? (menu.x + 10) : (menu.x + 5)) - (MenuW / 2), 282 + (Mshit.maxscroll[Mshit.id] * 30), 0, .84, "extraSmallFont", active ? menu.skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	Mshit.maxscroll[Mshit.id]++;
}

void addColorBar1(String title, float Min, float Max, void(*func_setbarvalue)(float value), char(*menudescription), float * value, bool bSLLR)
{
	float incrementValue = (Max - Min) / 100;

	if (menu.barslidevalue[Mshit.id][Mshit.maxscroll[Mshit.id]] <= Min)
		menu.barslidevalue[Mshit.id][Mshit.maxscroll[Mshit.id]] = Min;
	if (menu.barslidevalue[Mshit.id][Mshit.maxscroll[Mshit.id]] >= Max)
		menu.barslidevalue[Mshit.id][Mshit.maxscroll[Mshit.id]] = Max;

	if (*value <= Min)
		*value = Min;
	if (*value >= Max)
		*value = Max;
	//drawBar
	char MenuBuff[100];
	Com_Sprint(MenuBuff, sizeof(MenuBuff), "%s scale %.2f", menudescription, *value);
	if (active)
	{
		if (ready)
		{
			if (!menu.fade)
			{
				if (PadDown(PAD_RIGHT) || PadDown(PAD_LEFT))
				{

					SND_Play("cac_safearea", 3, 3),
						menu.barslidevalue[Mshit.id][Mshit.scroll[Mshit.id]] += (PadDown(PAD_RIGHT)) ? incrementValue : 0;
					menu.barslidevalue[Mshit.id][Mshit.scroll[Mshit.id]] -= (PadDown(PAD_LEFT)) ? incrementValue : 0;
					func_setbarvalue(menu.barslidevalue[Mshit.id][Mshit.scroll[Mshit.id]]);
					memset(&_pdPad, 0, sizeof(CellPadData));
					Wait(30);
					
				}
			}
		}
	}

	else {
		SLLR = false;
	}

	menu.barslidevalue[Mshit.id][Mshit.maxscroll[Mshit.id]] = *value;
	
	DrawShader(menu.x + 190, 270 + (Mshit.maxscroll[Mshit.id] * 30), 100, 3, 180, color(90, 90, 90, 255), "white", 7, align_right); //bar ( full length )
	DrawShader(menu.x + 90, 270 + (Mshit.maxscroll[Mshit.id] * 30), (((menu.barslidevalue[Mshit.id][Mshit.maxscroll[Mshit.id]] - Min) / incrementValue)), 3, 180, menu.skin2, "white", 7, align_left); //bar ( full length )
	if (active)DrawText(MenuBuff, (menu.x + 5) - (MenuW / 2), 277 + menu.height + (30 / 3), 0, .84, "extraSmallFont", menu.skin2, align_left, 1);
	DrawShader(menu.x + 90 + (((menu.barslidevalue[Mshit.id][Mshit.maxscroll[Mshit.id]] - Min) / incrementValue)), 266 + (Mshit.maxscroll[Mshit.id] * 30), 3, 10, 180, color(255, 255, 255, 255), "white", 7, align_left);// slider bar
	DrawText(title, (active ? (menu.x + 10) : (menu.x + 5)) - (MenuW / 2), 282 + (Mshit.maxscroll[Mshit.id] * 30), 0, .84, "extraSmallFont", active ? menu.skin2 : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	Mshit.maxscroll[Mshit.id]++;
}


void addInt1(String title, int Min, int Max, int step, void(*func_setbarvalue)(int value), int * value, char(*menudescription), bool bSLLR)
{
	if (Mshit.barslide[Mshit.id][Mshit.maxscroll[Mshit.id]] <= Min)
		Mshit.barslide[Mshit.id][Mshit.maxscroll[Mshit.id]] = Min;
	if (Mshit.barslide[Mshit.id][Mshit.maxscroll[Mshit.id]] >= Max)
		Mshit.barslide[Mshit.id][Mshit.maxscroll[Mshit.id]] = Max;

	if (*value <= Min)
		*value = Min;
	if (*value >= Max)
		*value = Max;
	//drawBar
	char psz_value[0x200];
	_sys_sprintf(psz_value, "%i", *value);
	char MenuBuff[100];
	snprintf(MenuBuff, sizeof(MenuBuff), "%s", menudescription);
	if (active)
	{
		SLLR = bSLLR;
		if (ready)
		{
			if (PadDown(PAD_RIGHT) || PadDown(PAD_LEFT)) {
				SND_Play("cac_safearea", 3, 3),
					Mshit.barslide[Mshit.id][Mshit.scroll[Mshit.id]] += (PadDown(PAD_RIGHT)) ? (int)step : 0;
				Mshit.barslide[Mshit.id][Mshit.scroll[Mshit.id]] -= (PadDown(PAD_LEFT)) ? (int)step : 0;
				func_setbarvalue(Mshit.barslide[Mshit.id][Mshit.scroll[Mshit.id]] - 1);
				Wait(60);
			}
		}
	}

	else {
		SLLR = false;
	}

	/*Mshit.barslide[Mshit.id][Mshit.maxscroll[Mshit.id]] = *value;*/
	if (active)DrawText(MenuBuff, (menu.x + 5) - (MenuW / 2), 277 + menu.height + (30 / 3), 0, .84, "extraSmallFont", menu.skin, align_left, 1);

	DrawText(psz_value, menu.x + 190, 282 + (Mshit.maxscroll[Mshit.id] * 30), 0, .84, "extraSmallFont", active ? menu.skin : color(255, 255, 255, 255), align_right, active ? 1 : 0);
	DrawText(title, (active ? (menu.x + 10) : (menu.x + 5)) - (MenuW / 2), 282 + (Mshit.maxscroll[Mshit.id] * 30), 0, .84, "extraSmallFont", active ? menu.skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	Mshit.maxscroll[Mshit.id]++;
}

void addInt(String title, int Min, int Max, int step, void(*func_setbarvalue)(int value), char(*menudescription), bool bSLLR)
{
	if (Mshit.barslide[Mshit.id][Mshit.maxscroll[Mshit.id]] <= Min)
		Mshit.barslide[Mshit.id][Mshit.maxscroll[Mshit.id]] = Min;
	if (Mshit.barslide[Mshit.id][Mshit.maxscroll[Mshit.id]] >= Max)
		Mshit.barslide[Mshit.id][Mshit.maxscroll[Mshit.id]] = Max;
	//drawBar
	char MenuBuff[100];
	snprintf(MenuBuff, sizeof(MenuBuff), "%s", menudescription);
	if (active)
	{
		SLLR = bSLLR;
		if (ready)
		{
			if (PadDown(PAD_RIGHT) || PadDown(PAD_LEFT)) {
				SND_Play("cac_safearea", 3, 3),
					Mshit.barslide[Mshit.id][Mshit.scroll[Mshit.id]] += (PadDown(PAD_RIGHT)) ? (int)step : 0;
				Mshit.barslide[Mshit.id][Mshit.scroll[Mshit.id]] -= (PadDown(PAD_LEFT)) ? (int)step : 0;
				func_setbarvalue(Mshit.barslide[Mshit.id][Mshit.scroll[Mshit.id]] - 1);
				Wait(60);
			}
		}
	}

	else {
		SLLR = false;
	}

	char psz_value[0x200];
	_sys_sprintf(psz_value, "%i", Mshit.barslide[Mshit.id][Mshit.maxscroll[Mshit.id]]);
	if (active)DrawText(MenuBuff, (menu.x + 5) - (MenuW / 2), 277 + menu.height + (30 / 3), 0, .84, "extraSmallFont", menu.skin, align_left, 1);

	DrawText(psz_value, menu.x + 190, 282 + (Mshit.maxscroll[Mshit.id] * 30), 0, .84, "extraSmallFont", active ? menu.skin : color(255, 255, 255, 255), align_right, active ? 1 : 0);
	DrawText(title, (active ? (menu.x + 10) : (menu.x + 5)) - (MenuW / 2), 282 + (Mshit.maxscroll[Mshit.id] * 30), 0, .84, "extraSmallFont", active ? menu.skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	Mshit.maxscroll[Mshit.id]++;
}

void addFPS(String title, float fps)
{
	char MenuBuff[0x200];
	Com_Sprint(MenuBuff, sizeof(MenuBuff), "%.f", fps);
	DrawText(MenuBuff, menu.x + 190, 282 + (Mshit.maxscroll[Mshit.id] * 30), 0, .84, "extraSmallFont", active ? menu.skin : color(255, 255, 255, 255), align_right, active ? 1 : 0);
	DrawText(title, (active ? (menu.x + 10) : (menu.x + 5)) - (MenuW / 2), 282 + (Mshit.maxscroll[Mshit.id] * 30), 0, .84, "extraSmallFont", active ? menu.skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	Mshit.maxscroll[Mshit.id]++;
}

void addCheck1(String title, void(*check_rs)(bool * rs), char(*menudescription), bool * onoff)
{
	char MenuBuff[100];
	snprintf(MenuBuff, sizeof(MenuBuff), "%s", menudescription);
	if (active && ready && PadDown(PAD_CROSS) && check_rs != NULL)
	{
		SND_Play("cac_grid_equip_item", 3, 3),
			check_rs(&menu.checkresult[Mshit.id][Mshit.scroll[Mshit.id]]), Wait(200);
	}

	menu.checkresult[Mshit.id][Mshit.scroll[Mshit.id]] = *onoff;
	DrawShader(menu.x + 190, 262 + (Mshit.maxscroll[Mshit.id] * 30), 18, 18, 0, menu.checkresult[Mshit.id][Mshit.maxscroll[Mshit.id]] ? color(255, 255, 255, 255) : color(51, 51, 51, 200), "menu_mp_killstreak_select", 7, align_right);
	if (active)DrawText(MenuBuff, (menu.x + 5) - (MenuW / 2), 277 + menu.height + (30 / 3), 0, .84, "extraSmallFont", menu.skin, align_left, 1);
	DrawText(title, (active ? (menu.x + 10) : (menu.x + 5)) - (MenuW / 2), 282 + (Mshit.maxscroll[Mshit.id] * 30), 0, .84, "extraSmallFont", active ? menu.skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	Mshit.maxscroll[Mshit.id]++;
}


void addCheck(String title, void(*check_rs)(bool * rs), char(*menudescription))
{

	char MenuBuff[100];
	snprintf(MenuBuff, sizeof(MenuBuff), "%s", menudescription);
	if (active && ready && PadDown(PAD_CROSS) && check_rs != NULL)
		SND_Play("cac_grid_equip_item", 3, 3),
		check_rs(&menu.checkresult[Mshit.id][Mshit.scroll[Mshit.id]]), Wait(200);

	DrawShader(menu.x + 190, 262 + (Mshit.maxscroll[Mshit.id] * 30), 18, 18, 0, menu.checkresult[Mshit.id][Mshit.maxscroll[Mshit.id]] ? color(255, 255, 255, 255) : color(51, 51, 51, 200), "menu_mp_killstreak_select", 7, align_right);
	if (active)DrawText(MenuBuff, (menu.x + 5) - (MenuW / 2), 277 + menu.height + (30 / 3), 0, .84, "extraSmallFont", menu.skin, align_left, 1);
	DrawText(title, (active ? (menu.x + 10) : (menu.x + 5)) - (MenuW / 2), 282 + (Mshit.maxscroll[Mshit.id] * 30), 0, .84, "extraSmallFont", active ? menu.skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	Mshit.maxscroll[Mshit.id]++;
}



void addCheck2(String title, void(*check_rs)(bool * rs), bool check, char(*menudescription))
{

	char MenuBuff[100];
	snprintf(MenuBuff, sizeof(MenuBuff), "%s", menudescription);
	if (active && ready && PadDown(PAD_CROSS) && check_rs != NULL)
		SND_Play("cac_grid_equip_item", 3, 3),
		check_rs(&menu.checkresult[Mshit.id][Mshit.scroll[Mshit.id]]), Wait(200);

	DrawShader(menu.x + 190, 262 + (Mshit.maxscroll[Mshit.id] * 30), 18, 18, 0, check ? color(255, 255, 255, 255) : color(51, 51, 51, 200), "menu_mp_killstreak_select", 7, align_right);
	if (active)DrawText(MenuBuff, (menu.x + 5) - (MenuW / 2), 277 + menu.height + (30 / 3), 0, .84, "extraSmallFont", menu.skin, align_left, 1);
	DrawText(title, (active ? (menu.x + 10) : (menu.x + 5)) - (MenuW / 2), 282 + (Mshit.maxscroll[Mshit.id] * 30), 0, .84, "extraSmallFont", active ? menu.skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	Mshit.maxscroll[Mshit.id]++;
}

void addArray(String option, String items[], size_t size, void(*func)(int index), bool bSLLR)
{
	int count = size - 1;
	if (active)
	{
		SLLR = bSLLR;
		if (ready)
		{
			if (PadDown(PAD_LEFT))
			{
				SND_Play("cac_safearea", 3, 3),
					Mshit.islide[Mshit.id][Mshit.scroll[Mshit.id]] = (Mshit.islide[Mshit.id][Mshit.scroll[Mshit.id]] <= 0) ? count : Mshit.islide[Mshit.id][Mshit.scroll[Mshit.id]] - 1,
					func(Mshit.islide[Mshit.id][Mshit.scroll[Mshit.id]]), Wait(150);
			}
			if (PadDown(PAD_RIGHT))
			{
				SND_Play("cac_safearea", 3, 3),
					Mshit.islide[Mshit.id][Mshit.scroll[Mshit.id]] = (Mshit.islide[Mshit.id][Mshit.scroll[Mshit.id]] >= count) ? 0 : Mshit.islide[Mshit.id][Mshit.scroll[Mshit.id]] + 1,
					func(Mshit.islide[Mshit.id][Mshit.scroll[Mshit.id]]), Wait(150);
			}
		}
	}

	else {
		SLLR = false;
	}
	String psz_cur = items[Mshit.islide[Mshit.id][Mshit.maxscroll[Mshit.id]]];
	DrawText(option, (active ? (menu.x + 10) : (menu.x + 5)) - (MenuW / 2), 282 + (Mshit.maxscroll[Mshit.id] * 30), 0, .84, "extraSmallFont", active ? menu.skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	DrawText(items[Mshit.islide[Mshit.id][Mshit.maxscroll[Mshit.id]]], menu.x + 190, 282 + (Mshit.maxscroll[Mshit.id] * 30), 0, .84, "extraSmallFont", active ? menu.skin : color(255, 255, 255, 255), align_right, active ? 1 : 0);
	Mshit.maxscroll[Mshit.id]++;

}

#pragma region render combo
int test;
void combo_render_ui()
{
	menudata_s * com;
	if (menu.combos[Mshit.id][Mshit.scroll[Mshit.id]].opened && menu.combo_active)
	{
		const char * * data = menu.combos[Mshit.id][Mshit.scroll[Mshit.id]].data;
		DrawShader(menu.x + 190, 267 + 15 - 23 + ((Mshit.scroll[Mshit.id]) * 30), 100, menu.combos[Mshit.id][Mshit.scroll[Mshit.id]].maxscroll * 30, 0, color(90, 90, 90, 230), "white", 7, align_right);
		DrawShader(menu.x + 190, 267 + 15 - 23 + ((Mshit.scroll[Mshit.id]) * 30) + (menu.combos[Mshit.id][Mshit.scroll[Mshit.id]].scroll * 30), 100, 23, 0, color(0, 0, 0, 190), "white", 7, align_right);
		for (int i = 0; i < menu.combos[Mshit.id][Mshit.scroll[Mshit.id]].maxscroll; i++)
			DrawText(data[i], menu.x + 143, 267 + 15 + ((Mshit.scroll[Mshit.id]) * 30) + (i * 30), 0, .82, "extraSmallFont", (menu.combos[Mshit.id][Mshit.scroll[Mshit.id]].scroll == i) ? menu.skin : color(255, 255, 255, 255), align_center, 1);
	}
}
#pragma endregion



void addCombo(const char * option, const char * data[], int size, int tag, void(*func)(int info), const char (*menudescription[]))
{
	int id = Mshit.id;
	menu.combos[Mshit.id][Mshit.maxscroll[Mshit.id]].data = data;
	menu.combos[Mshit.id][Mshit.maxscroll[Mshit.id]].maxscroll = size;
	menu.combos[Mshit.id][Mshit.maxscroll[Mshit.id]].size = size;
	menu.combos[Mshit.id][Mshit.maxscroll[Mshit.id]].func = func;
	char MenuBuff[100];
	snprintf(MenuBuff, sizeof(MenuBuff), "%s", menudescription[tag]);
	if (menu.combos[Mshit.id][Mshit.scroll[Mshit.id]].opened && menu.combo_active)
	{
		if (ready)
		{
			if (PadDown(PAD_CROSS))
			{
				menu.combo_active = menu.combos[Mshit.id][Mshit.scroll[Mshit.id]].opened = false;
				SND_Play("cac_grid_equip_item", 3, 3);
				Wait(150);
			}
				

			if (PadDown(PAD_CIRCLE))
			{
				menu.combo_active = false;
				menu.combos[Mshit.id][Mshit.scroll[Mshit.id]].opened = false;
				SND_Play("caC_main_exit_cac", 3, 3);
				Wait(150);
			}

			if (PadDown(PAD_UP))
			{
				menu.combos[Mshit.id][Mshit.scroll[Mshit.id]].scroll = menu.combos[Mshit.id][Mshit.scroll[Mshit.id]].scroll <= 0 ? menu.combos[Mshit.id][Mshit.scroll[Mshit.id]].maxscroll - 1 : menu.combos[Mshit.id][Mshit.scroll[Mshit.id]].scroll - 1, menu.combos[Mshit.id][Mshit.scroll[Mshit.id]].func(menu.combos[Mshit.id][Mshit.scroll[Mshit.id]].scroll);
				SND_Play("cac_grid_nav", 3, 3);
				Wait(150);
				
			}
			if (PadDown(PAD_DOWN))
			{
				menu.combos[Mshit.id][Mshit.scroll[Mshit.id]].scroll = menu.combos[Mshit.id][Mshit.scroll[Mshit.id]].scroll >= menu.combos[Mshit.id][Mshit.scroll[Mshit.id]].maxscroll - 1 ? 0 : menu.combos[Mshit.id][Mshit.scroll[Mshit.id]].scroll + 1, menu.combos[Mshit.id][Mshit.scroll[Mshit.id]].func(menu.combos[Mshit.id][Mshit.scroll[Mshit.id]].scroll);
				SND_Play("cac_grid_nav", 3, 3);
				Wait(150);
			}
		}
	}

	if (active && ready && PadDown(PAD_CROSS) && !menu.combos[Mshit.id][Mshit.maxscroll[Mshit.id]].opened)
	{
		menu.combos[Mshit.id][Mshit.maxscroll[Mshit.id]].opened = true;
		SND_Play("cac_grid_equip_item", 3, 3);
		menu.combo_active = true;
		Wait(150);
	}
	if (!menu.combos[Mshit.id][Mshit.maxscroll[Mshit.id]].opened)
		DrawShader(menu.x + 190, 267 + 15 - 23 + (Mshit.maxscroll[Mshit.id] * 30), 100, 23, 0, color(90, 90, 90, 230), "white", 7, align_right),
		DrawText(data[tag], menu.x + 143, 267 + 15 + (Mshit.maxscroll[Mshit.id] * 30), 0, .82, "extraSmallFont", active ? menu.skin : color(255, 255, 255, 255), align_center, 1);
	
	if (active)DrawText(MenuBuff, (menu.x + 5) - (MenuW / 2), 277 + menu.height + (30 / 3), 0, .84, "extraSmallFont", menu.skin, align_left, 1);
	DrawText(option, (active ? (menu.x + 10) : (menu.x + 5)) - (MenuW / 2), 282 + (Mshit.maxscroll[Mshit.id] * 30), 0, .84, "extraSmallFont", active ? menu.skin : color(255, 255, 255, 255), align_left, 1);
	Mshit.maxscroll[Mshit.id]++;
}

void addPlayerSub(String playername, int id)
{
	if (active && PadDown(PAD_CROSS) && ready)
		SND_Play("cac_screen_fade", 3, 3),
		Mshit.id = id, Wait(200);
	addOption(playername);

}
#pragma endregion

void slide_chams_r(float value)
{
	WriteMemory(0x01CC1438, &value, 4);
}

void slide_chams_g(float value)
{
	WriteMemory(0x01CC1438 + 0x4, &value, 4);
}

void slide_chams_b(float value)
{
	WriteMemory(0x01CC1438 + 0xC, &value, 4);
}

void SlideRed(float r)
{
	menu.colorslide.r = r;
}

void SlideGreen(float r)
{
	menu.colorslide.g = r;
}

void SlideBlue(float r)
{
	menu.colorslide.b = r;
}

void SlideRed1(float r)
{
	menu.colorslide1.r = r;
}

void SlideGreen1(float r)
{
	menu.colorslide1.g = r;
}

void SlideBlue1(float r)
{
	menu.colorslide1.b = r;
}

void slide_props(float r)
{
	menu.props = r;
}

void set_color(int index)
{
	cur_index_theme = index;
}

void Fmj_scale(float value) { menu.fmj = value; }
void Damage_scale(float value) { menu.damage = value; }
void Menusize_scale(float value) { menu.menusize = value; }
void Menufade_scale(float value) { menu.menufade = value; }

bool ronece = false;
void SignIn()
{
	if(!ronece)
	Cbuf_AddText("xsigninlive");
	ronece = true;
}
bool runonce1;
void cheats_render()
{
	if (menu.frenderfovx < 66.0f)
		return;
	if (CScr_IsAlive(cg->clientNum))
	{	
		if (runonce1)
		{
			char buffer[60];
			_sys_sprintf(buffer, "cg_fov %i\n", (int)menu.frenderfovx);
			Cbuf_AddText(buffer);
			//_sys_printf("FOV\n");
			runonce1 = false;
		}
	}
	else
	{
		runonce1 = true;
	}
}

bool runonlyonce = true, resettheme = false;

void enableresettheme()
{
	resettheme = true;
	menu.menux = 0;
	menu.menuy = 0;
}

void MoveUp()
{
	menu.menuy-=10;
}
void MoveDown()
{
	menu.menuy+=10;
}

void MoveLeft()
{
	menu.menux-=10;
}

void MoveRight()
{
	menu.menux+=10;
}

void RenderMenu()
{
	_Buttoninfo();
	if (local->canreload)
	{
		Cancel_Reload();
	}
	movement_event();
	flash(&dflash);
	flash2(&dflash1);
	Ui_interface();


	if (dc.height > 720)
	{
		
		char MenuBuff[100];
		char str[] = "]0Dqqnq9]6Okd`rdpthssgdf`ld`mcbg`mfdxntqqdrnktshnmsn017/w61/vhsghmxntqbnmrnkdrchrok`xrdsshmfr";
		decrypt(str, 1);
		DrawTextWithBackground_UI(str, dc.width / 2, dc.height / 2, .94, color(255, 255, 255, 255), menu.skin, color(52, 52, 52, 255), align_center);
	}
	else
	{
		if (runonlyonce || resettheme)
		{
			menu.colorslide = color(128, 15, 255, 255);

			menu.colorslide1 = color(128, 15, 255, 255);

			menu.skin = color(128, 15, 255, 255);

			menu.skin2 = color(128, 15, 255, 255);

			resettheme = false;
			runonlyonce = false;
		}

		if (!menu.fade)
		{
			menu.skin.a = menu.colorslide.a; menu.skin.r = menu.colorslide.r; menu.skin.g = menu.colorslide.g; menu.skin.b = menu.colorslide.b;
			menu.skin2.a = menu.colorslide1.a; menu.skin2.r = menu.colorslide1.r; menu.skin2.g = menu.colorslide1.g; menu.skin2.b = menu.colorslide1.b;
		}

		if (menu.fade)
		{
			menu.skin = dflash;
			menu.skin2 = dflash1;
			menu.colorslide.a = dflash.a;
			menu.colorslide.r = dflash.r;
			menu.colorslide.g = dflash.g;
			menu.colorslide.b = dflash.b;

			menu.colorslide1.a = dflash1.a;
			menu.colorslide1.r = dflash1.r;
			menu.colorslide1.g = dflash1.g;
			menu.colorslide1.b = dflash1.b;
		}

		if (!Mshit.Mopened && menu.x >= 1800) return;

		switch (Mshit.id)
		{
		case ID_MAIN:
			char MenuBuff[100];
			char str[] = "A!B?Hcmsm";
			decrypt(str, 6);
			Com_Sprint(MenuBuff, sizeof(MenuBuff), "%s", str);
			addTitle(MenuBuff, ID_MAIN);
			addSubmenu("Aimbot", ID_AIMBOT);
			addSubmenu("Esp", ID_ESP);
			addSubmenu("Antiaim", ID_ANTIAIM);
			addSubmenu("Cheats", ID_CHEATS);
			addSubmenu("Players", ID_PLAYERS);
			addSubmenu("Account", ID_ACCOUNT);
			addSubmenu("Theme", ID_THEME);
			addSubmenu("Config", ID_HVH);
			addSubmenu("Settings", ID_SETTINGS);
			break;
		case ID_AIMBOT:
			addTitle("Aimbot", ID_MAIN);
			addCheck2("Enable", enable_aimbot, bot.benable, "Enable auto-aim to targets");
			addCombo("Method", aimtypes, SizeOf(aimtypes), bot.aimtype, aim_type, aimtypesDec), SLLR = true;
			addCombo("Tag", tagtypes, SizeOf(tagtypes), bot.tagtype, tag_type, tagtypesDec), SLLR = true;
			addCombo("Aim Key", keytypes, SizeOf(keytypes), bot.keytype, key_type, keytypesDec), SLLR = true;
			addBar("Prediction Scale", 1.316, 3.316, slide_prediction, &bot.fprediction, "Predict targets new origin", true), SLLR = true;
			addCheck2("Visible", enable_visible, bot.bvisible, "Engage targets when visible");
			addCheck2("Autowall", enable_autowall, bot.bautowall, "Engage targets if bullets trace through walls");
			addCheck2("Remove Spread", enable_nospread, bot.bnospread, "Removes weapons spread");
			addCheck2("Remove Flinch", enable_noflinch, bot.bnoflinch, "Removes flinch when hit");
			addCheck2("Remove Sway", enable_nosway, bot.bnosway, "Removes weapons sway");
			addCheck2("Remove Bob", enable_nobob, bot.bnobob, "Removes weapons bob");
			addCheck2("Remove Recoil", enable_norec, bot.bnorec, "Removes weapons recoil");
			addCheck2("Cancel Reload", enable_cancelreload, bot.cancelreload, "Cancels reload animation");
			addCheck2("Anti Shield Damage", enable_aimatfeet, bot.baimatfeet, "Ignores bones behind the shield");
			addCheck2("Autoshoot", enable_autoshoot, bot.bautoshoot, "Auto engages targets");
			break;
		case ID_ANTIAIM:
			addTitle("Antiaim", ID_MAIN);
			addCheck2("Enable", enable_ntiaim, bot.benableanti, "Enable anti aim");
			addCheck2("Riot Backwards", enable_reversebot, bot.breversebot, "Riot backwards");
			addCheck2("Lock Up", enable_lockup, bot.blockup, "Locks angles up");
			addBar("Jitter Scale", 0, 3, pitch_scale, &bot.pitchscale, "Up / down jitter", true);
			addBar("Spin Scale", 0, 29.75, spin_scale, &bot.spinscale, "360 Spin", true);
			addBar("Fake Lag Scale", 0, 20, lag_scale, &bot.fakelagscale, "Artificial lag", true);
			
			break;
		case ID_ESP:
			addTitle("Extra-Sensory Perception", ID_MAIN);
			addCheck2("Friendlys", draw_allies, bot.esp.ballies, "Draw friendlys");
			addCheck2("Enemys", draw_axis, bot.esp.baxis, "Draw enemys");
			addCombo("Bound", bound_type, SizeOf(bound_type), bot.esp.bound, set_bound, bound_typedec);//need to fix sizeof
			addCombo("Snaplines", snap_type, SizeOf(snap_type), bot.esp.snaplines, set_snap, snap_typedec);
			addCheck2("Names", draw_names, bot.esp.bnames, "Draw players names");
			addCheck2("Crosshair Compass", draw_compass, bot.esp.bcompass, "Draw player pointers around crosshair");
			addCheck2("Health Bar", draw_healthbar, bot.esp.bhealthbar, "Draw your current health bar");
			addCheck2("Dynamic Crosshair", draw_crossh, bot.esp.bdynamic, "Draw halo styled dynamic crosshair");
			addCheck2("Target Info", draw_targetinfo, bot.esp.btargetinfo, "Draw targets information");
			addCheck2("Proximity Warning", draw_proxwarn, bot.esp.bprox, "Draw proximity warnings");
			addCheck2("V-Angles", draw_vangles, bot.esp.bvangles, "Draw players view angles (possible drop in fps)");
			addCheck2("Target Finder", draw_targetfinder, bot.esp.btargetfinder, "Draw target finder");
			addSubmenu("External Radar", ID_RADAR);
			addSubmenu("Chams", ID_CHAMS);
			addSubmenu("World Entitys", ID_WORLDENTS);
			break;
		case ID_CHAMS:
			addTitle("Chams", ID_ESP);
			addCheck2("Enable", draw_chams, bot.esp.bchams, "Color players chameleon skin");
			addCheck2("Player Wallhack", draw_wall, bot.esp.bwall, "Render players through walls");
			addCheck2("Entity Wallhack", draw_ewall, bot.esp.ebwall, "Render Entitys through walls");
			break;
		case ID_WORLDENTS:
			addTitle("World Entity ESP", ID_ESP);
			addCheck2("Enable", draw_worldents, bot.esp.benableworldents, "Enable world entitys esp");
			addCheck2("Weapons", draw_weapsworld, bot.esp.bweapsworld, "Draw Players current weapons");
			addCheck2("Weapon Items", draw_weappickupidsworld, bot.esp.bpickupweaponsworld, "Draw weapon pick up items");
			addCheck2("Grenades", draw_nadesworld, bot.esp.bnadesworld, "Draw nades");
			addCheck2("Scavenger Bags", draw_scavsworld, bot.esp.bpickupscavsworld, "Draw scavenger bag pick up entitys");
			break;
		case ID_CROSSHAIR:
			addTitle("Crosshair Compass", ID_ESP);
			addCheck("Enable", draw_compass, "");
			addCheck("Weapon Items", draw_xhweaps, "");
			addCheck("Scavenger Bags", draw_xhscavs, "");
			break;
		case ID_RADAR:
			addTitle("External Radar", ID_ESP);
			addCheck2("Enable", draw_radar, bot.esp.bradar, "Draws custom radar");
			addBar("Compass Scale", 0.0f, 2500.0f, slide_zoommap, &local->scale, "Maps range", true);
			addCheck2("Weapon Items", draw_weappickupidsradar, bot.esp.bradrpickupweaps, "Draw Players current weapons");
			addCheck2("Grenades", draw_nadesradar, bot.esp.bradrnades, "Draw nades");
			addCheck2("Scavenger Bags", draw_draw_scavsradar, bot.esp.bradrpickupscavs, "Draw scavenger bag pick up entitys");
			addCheck2("Helicopters", draw_hellisradar, bot.esp.bradrhelis, "Draw helicopters");
			addCheck2("Dogs", draw_doggosradar, bot.esp.bradrdogos, "Draw dogs");
			addCheck2("Vehicles", draw_vehiclesradar, bot.esp.bradrvehicles, "Draw vehicles");
			addCheck2("Turrets", draw_turretsradar, bot.esp.bradrturrets, "Draw turrets");
			addCheck2("Artillery", draw_artilleryradar, bot.esp.bradrartillery, "Draw artillery");
			break;
		case ID_CHEATS:
			addTitle("Cheats", ID_MAIN);
			addCheck2("Unlimited Class Slots", toggleucs, local->unlimitedSlots, "Toggle unlimited class slots");
			addCheck("32 Name Patcher", i32_Name, "Toggle 32 char name");
			addKOption("Change Name", ChangeName);
			addCheck("Flash Name", EFlash_Name, "Flash gamer tag ingame / pregame");
			addCheck("Advertise Menu", EAdd_Name, "Advertise the menu ingame / pregame");
			addBar("Fov", 65, 135, slide_fovx, &menu.frenderfovx, "Field of view", runonce1 = true);
			addBar("Prop Size", 1.0f, 10.0f, slide_props, &menu.props, "Props size", true);
			addCheck("RSS Mode", rssm, "Toggle rainbow six siege mode");
			addCheck2("Smoke Color", SmokeColor, menu.smokec, "Toggle smoke color modification");
			addCheck2("Night Mode", NightMode, menu.nightmode, "Toggle night mode - credit Pyrex");
			addCheck2("Sky Color", SkyColor, menu.skyc, "Toggle sky color modification");
			addCheck2("Sky Rotate", SkyRotate, menu.skyr, "Toggle sky rotation");
			addCheck("Third Person", CG_SetThirdPerson, "Toggle 3rd person");
			addCheck("Spoof IP", ChangeIP, "Spoof ip (will block all memory based pullers)");
			addOption("End Game", EndGame);
			addOption("Leave Game", Disconnect);
			break;
		case ID_PLAYERS:
			addTitle("Players", ID_MAIN);
			char MenuBufff[100];
			for (clientinfo_t cinfo : cg->clients)
				Com_Sprint(MenuBufff, sizeof(MenuBufff), "%s %s", cinfo.PlayerName, local->pplayer[cinfo.anull] ? "^2[Prioritized]" : local->iplayer[cinfo.anull] ? "^1[Ignored]" : ""),
				addPlayerSub(!strcmp(cinfo.PlayerName, "") ? "Not Connected" : MenuBufff, ID_PLAYERS_SUB);
			break;
		case ID_PLAYERS_SUB:
			String pszname = cg->clients[Mshit.scroll[ID_PLAYERS]].PlayerName;
			addTitle(!strcmp(pszname, "") ? "Not Connected" : pszname, ID_PLAYERS);
			addCheck2("Prioritize", toggleP, local->pplayer[Mshit.scroll[ID_PLAYERS]], "Prioritize player");
			addCheck2("Ignore", togglePi, local->iplayer[Mshit.scroll[ID_PLAYERS]], "Ignore player");
			break;
		case ID_ACCOUNT:
			addTitle("Account", ID_MAIN);
			addInt("Rank", 0, 55, 1, rank, "Change rank (sets instantly)", true);
			addInt("Prestige", 0, 255, 1, Prrank, "Change Prestige (sets instantly)", true);
			addCOption("Unlock all", local->stausrank, unlock_all);
			addInt("Fake Rank Unlimited", 0, 1000, 1, unlimitedrank, "Change fake rank", true);
			break;
		case ID_SETTINGS:
			addTitle("Settings", ID_MAIN);
			addSubmenu("Server Info", SERVER_INFO);
			addCheck2("Disable FPS", Efps, menu.fps, "Toggle fps");
			addCheck2("Disable Resolution", Eres, menu.res, "Toggle resolution");
			addCheck2("Disable Console", toggleconsole, bot.drawconsole, "Toggle custom in game console / kill feed");
			addKOption("Local Command", local_command);
			break;
		case SERVER_INFO:
			addTitle("Server Info", ID_SETTINGS);
			addCheck2("Disable Server Info", Eserverinfo, menu.serverinfo, "Toggle server info");
			addCheck2("Disable Host Name", Ehost, menu.host, "Toggle host");
			addCheck2("Disable Map Name", Emap, menu.map, "Toggle map");
			addCheck2("Disable Game Type Name", Egame, menu.game, "Toggle game type");
			addCheck2("Disable Ping", Eping, menu.ping, "Toggle ping");
			addCheck2("Disable Entitys", Eents, menu.ents, "Toggle ");
			addCheck2("Disable Max Clients", Emaxc, menu.maxc, "Toggle game type");
			break;
		case ID_THEME:
			addTitle("Theme", ID_MAIN);
			addSubmenu("Preset Themes", ID_CUSTOMTHEME);
			addSubmenu("Placement", ID_PLACEMENT);
			addColorSubmenu("Primary Color", ID_PRIMERY, 0);
			addColorSubmenu1("Secondary Color", ID_SECONDARY, 1);
			addCheck("Enable Fade", fadeColor, "Disables both color transitions");
			if (menu.fade)
			{
				addBar("Rain Fade", 0.6f, 5.0f, Menufade_scale, &menu.menufade, "Color transition speed", true);
			}
			addOption("Reset Theme", enableresettheme);
			break;
		case ID_CUSTOMTHEME:
			addTitle("Preset Themes", ID_THEME);
			addColormenu("Red", color(255, 0, 0, 255));
			addColormenu("Yellow", color(255, 255, 0, 255));
			addColormenu("Orange", color(255, 128, 0, 255));
			addColormenu("Green", color(128, 255, 0, 255));
			addColormenu("Blue", color(0, 128, 255, 255));
			addColormenu("Purple", color(128, 0, 255, 255));
			addColormenu("Pink", color(255, 0, 128, 255));
			addColormenu("Aqua Green", color(24, 119, 72, 255));
			addColormenu("Sky Blue", color(24, 189, 240, 255));
			addColormenu("Cerulean", color(65, 60, 219, 255));
			addColormenu("Magenta", color(254, 39, 57, 255));
			addColormenu("Wisteria", color(12, 186, 92, 255));
			addColormenu("Lime Green", color(53, 254, 75, 255));
			addColormenu("Golden Yellow", color(207, 179, 55, 255));
			addColormenu("Red Orange", color(204, 51, 27, 255));
			break;
		case ID_PRIMERY:
			addTitle("Primary Color", ID_THEME);
			addColorBar("Red", 0.0f, 1.0f, SlideRed, "Red color", &menu.skin.r, true);
			addColorBar("Green", 0.0f, 1.0f, SlideGreen, "Green color", &menu.skin.g, true);
			addColorBar("Blue", 0.0f, 1.0f, SlideBlue, "Blue color", &menu.skin.b, true);
			break;
		case ID_SECONDARY:
			addTitle("Secondary Color", ID_THEME);
			addColorBar1("Red", 0.0f, 1.0f, SlideRed1, "Red color", &menu.skin2.r, true);
			addColorBar1("Green", 0.0f, 1.0f, SlideGreen1, "Green color", &menu.skin2.g, true);
			addColorBar1("Blue", 0.0f, 1.0f, SlideBlue1, "Blue color", &menu.skin2.b, true);
			break;
		case ID_HVH:
			addTitle("Config Setting", ID_MAIN);
			addCOption("Load Config", Mshit.ch, iload);
			addCOption("Save Config", Mshit.ch, isave);
			addCheck("Enable HVH Setting", enable_hvh, "Kiwis recommended hvh settings");
			break;
		case ID_PLACEMENT:
			addTitle("Move Menu", ID_THEME);
			addOption("Move Up", MoveUp);
			addOption("Move Down", MoveDown);
			addOption("Move Left", MoveLeft);
			addOption("Move Right", MoveRight);
			//addBar("Size", 0.01f, 2.0f, Dvisint, menu.dvis, "", true);

			break;
		default:
			addTitle("Does Not Exist", ID_MAIN);
			addSubmenu("Return Home", ID_MAIN);
			break;
		}
	}
		//memset(&_pdPad, 0, sizeof(CellPadData));
}


bool onceonly = true;
void HandleMenu()
{
	if ((Sys_Milliseconds() - Mshit.tick) > Mshit.wait)
	{
		if (PadDown(PAD_L1) && PadDown(PAD_LEFT) && !Mshit.Mopened)
			Mshit.id = ID_MAIN, Mshit.Mopened = true, Wait(200);

		if (Mshit.Mopened)
		{
			if (PadDown(PAD_L1) && PadDown(PAD_LEFT))
			{
				SND_Play("cac_screen_hpan", 3, 3);
			}

			int id = Mshit.id;
			if (!menu.combos[Mshit.id][Mshit.scroll[Mshit.id]].opened && !menu.combo_active)
			{
				if (PadDown(PAD_UP))
					Mshit.scroll[id] = (Mshit.scroll[id] <= 0) ? Mshit.maxscroll[id] - 1 : Mshit.scroll[id] - 1, Wait(150),
					SND_Play("cac_grid_nav", 3, 3);
				if (PadDown(PAD_DOWN))
					Mshit.scroll[id] = (Mshit.scroll[id] >= Mshit.maxscroll[id] - 1) ? 0 : Mshit.scroll[id] + 1, Wait(150),
					SND_Play("cac_grid_nav", 3, 3);


				if (PadDown(PAD_CIRCLE))
				{
					if (Mshit.id > ID_MAIN)
						Mshit.id = Mshit.prev[Mshit.id], Wait(200),
						SND_Play("caC_main_exit_cac", 3, 3);
					else
						Mshit.Mopened = false, Mshit.id = ID_MAIN, Wait(200),
						SND_Play("cac_cmn_backout", 3, 3);
				}
			}
		}
		
	}
	//memset(&_pdPad, 0, sizeof(CellPadData));
}
