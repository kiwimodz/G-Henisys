#ifndef aimassist_mp_h
#define aimassist_mp_h


//#define  CG_ReadNextSnapshot(localClientNum) Invoke<snapshot_s*>(0xC564C, 0)

#define penetrationDepthTable ((float*)0x296EB30)

//bool AimTarget_GetTarget(int localClientNum, unsigned int * ptarget);
#pragma region aim functions
void enable_ntiaim(bool * rs);
void enable_aimbot(bool * rs);
void enable_hvh(bool * rs);
WeaponDef * BG_GetWeaponDef(int Weapon);
WeaponVariantDef* BG_GetWeaponVariantDef(unsigned int weapon);
void aim_type(int type);
void tag_type(int type);
void key_type(int type);
void enable_visible(bool * rs);
void enable_autowall(bool * rs);
void enable_aim(bool * rs);
void pcorrectiion_scale(float value);
void enable_antiaim(bool * rs);
void enable_spinbot(bool * rs);
void enable_reversebot(bool * rs);
void enable_lockup(bool* rs);
void enable_cancelreload(bool* rs);
void enable_nospread(bool * rs);
void enable_noflinch(bool* rs);
void enable_nosway(bool * rs);
void enable_aimatfeet(bool * rs);
void enable_autoshoot(bool * rs);
void enable_norec(bool * rs);
void slide_prediction(float value);
bool riotshieldCheck(int client);
void enable_autobone(bool * rs);
void spin_scale(float value);
void pitch_scale(float value);
void roll_scale(float value);
void lag_scale(float value);
void enable_nobob(bool * rs);
void pspin(usercmd_s * NewCmd, usercmd_s* CurrentCmd, usercmd_s* OldCmd);
void psilent(usercmd_s* CurrentCmd, usercmd_s* OldCmd);
void aimbot();
void GetNearestPlayerzm();
void GetNearestPlayermp();
#endif