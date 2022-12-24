#ifndef cheats_mp_h
#define cheats_mp_h

void Render_Wallhack(bool * rs);
void Render_Chams(bool * rs);
void slide_fovx(float value);
void wint(int rank_id);
void slide_zoommap(float value);
void toggleantifreeze(bool * rs);
void Sint(int id);
void StyleInt(int rank_id);
void toggleconsole(bool * rs);
void toggleucs(bool * rs);
void unlimitedrank(int rank_id);
void FXint(int rank_id);
void Dvisint(float rank_id);
void slide_Aws(float value);
void slide_ymap(float value);
void slide_xmap(float value);
void toggleP(bool *rs);
void togglePi(bool * rs);
void CG_SetThirdPerson(bool * rs);

static int ranks[] = { 0,800,1900,3300,5300,7900,11100,14900,19300,24300,30100,36700,44100,52300,61300,71100,81700,93100,105300,118300,132100,146700,162100,178300,195300,213100,231700,251100,271300,292300,314100,337100,361300,386700,413300,441100,470100,500300,531700,564300,598100,633100,669300,706700,745300,785100,826100,868300,911700,958300,1002100,1049100,1097300,1146700,1197300,1249100 };

#pragma region account
void rank(int rank_id);
void Prrank(int rank_id);
void unlock_all();
#pragma endregion

#endif