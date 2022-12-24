#ifndef Structures_h
#define Structures_h
/*

This file contains definitions used by the Hex-Rays decompiler output.
It has type definitions and convenience macros to make the
output more readable.

Copyright (c) 2007-2011 Hex-Rays

*/
#if defined(__GNUC__)
typedef          long long ll;
typedef unsigned long long ull;
#define __int64 long long
#define __int32 int
#define __int16 short
#define __int8  char
#define MAKELL(num) num ## LL
#define FMT_64 "ll"
#elif defined(_MSC_VER)
typedef          __int64 ll;
typedef unsigned __int64 ull;
#define MAKELL(num) num ## i64
#define FMT_64 "I64"
#elif defined (__BORLANDC__)
typedef          __int64 ll;
typedef unsigned __int64 ull;
#define MAKELL(num) num ## i64
#define FMT_64 "L"
#else
#error "unknown compiler"
#endif
typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned long ulong;

typedef          char   int8;
typedef   signed char   sint8;
typedef unsigned char   uint8;
typedef          short  int16;
typedef   signed short  sint16;
typedef unsigned short  uint16;
typedef          int    int32;
typedef   signed int    sint32;
typedef unsigned int    uint32;
typedef ll              int64;
typedef ll              sint64;
typedef ull             uint64;

// Partially defined types:
#define _BYTE  uint8
#define _WORD  uint16
#define _DWORD uint32
#define _QWORD uint64
#if !defined(_MSC_VER)
#endif

#ifndef _WINDOWS_
typedef int8 BYTE;
typedef int16 WORD;
typedef int32 DWORD;
typedef int32 LONG;
#endif
typedef int64 QWORD;
#ifndef __cplusplus
typedef int bool;       // we want to use bool in our C programs
#endif

						// Some convenience macros to make partial accesses nicer
						// first unsigned macros:
#define LOBYTE(x)   (*((_BYTE*)&(x)))   // low byte
#define LOWORD(x)   (*((_WORD*)&(x)))   // low word
#define LODWORD(x)  (*((_DWORD*)&(x)))  // low dword
#define HIBYTE(x)   (*((_BYTE*)&(x)+1))
#define HIWORD(x)   (*((_WORD*)&(x)+1))
#define HIDWORD(x)  (*((_DWORD*)&(x)+1))
#define BYTEn(x, n)   (*((_BYTE*)&(x)+n))
#define WORDn(x, n)   (*((_WORD*)&(x)+n))
#define BYTE1(x)   BYTEn(x,  1)         // byte 1 (counting from 0)
#define BYTE2(x)   BYTEn(x,  2)
#define BYTE3(x)   BYTEn(x,  3)
#define BYTE4(x)   BYTEn(x,  4)
#define BYTE5(x)   BYTEn(x,  5)
#define BYTE6(x)   BYTEn(x,  6)
#define BYTE7(x)   BYTEn(x,  7)
#define BYTE8(x)   BYTEn(x,  8)
#define BYTE9(x)   BYTEn(x,  9)
#define BYTE10(x)  BYTEn(x, 10)
#define BYTE11(x)  BYTEn(x, 11)
#define BYTE12(x)  BYTEn(x, 12)
#define BYTE13(x)  BYTEn(x, 13)
#define BYTE14(x)  BYTEn(x, 14)
#define BYTE15(x)  BYTEn(x, 15)
#define WORD1(x)   WORDn(x,  1)
#define WORD2(x)   WORDn(x,  2)         // third word of the object, unsigned
#define WORD3(x)   WORDn(x,  3)
#define WORD4(x)   WORDn(x,  4)
#define WORD5(x)   WORDn(x,  5)
#define WORD6(x)   WORDn(x,  6)
#define WORD7(x)   WORDn(x,  7)

						// now signed macros (the same but with sign extension)
#define SLOBYTE(x)   (*((int8*)&(x)))
#define SLOWORD(x)   (*((int16*)&(x)))
#define SLODWORD(x)  (*((int32*)&(x)))
#define SHIBYTE(x)   (*((int8*)&(x)+1))
#define SHIWORD(x)   (*((int16*)&(x)+1))
#define SHIDWORD(x)  (*((int32*)&(x)+1))
#define SBYTEn(x, n)   (*((int8*)&(x)+n))
#define SWORDn(x, n)   (*((int16*)&(x)+n))
#define SBYTE1(x)   SBYTEn(x,  1)
#define SBYTE2(x)   SBYTEn(x,  2)
#define SBYTE3(x)   SBYTEn(x,  3)
#define SBYTE4(x)   SBYTEn(x,  4)
#define SBYTE5(x)   SBYTEn(x,  5)
#define SBYTE6(x)   SBYTEn(x,  6)
#define SBYTE7(x)   SBYTEn(x,  7)
#define SBYTE8(x)   SBYTEn(x,  8)
#define SBYTE9(x)   SBYTEn(x,  9)
#define SBYTE10(x)  SBYTEn(x, 10)
#define SBYTE11(x)  SBYTEn(x, 11)
#define SBYTE12(x)  SBYTEn(x, 12)
#define SBYTE13(x)  SBYTEn(x, 13)
#define SBYTE14(x)  SBYTEn(x, 14)
#define SBYTE15(x)  SBYTEn(x, 15)
#define SWORD1(x)   SWORDn(x,  1)
#define SWORD2(x)   SWORDn(x,  2)
#define SWORD3(x)   SWORDn(x,  3)
#define SWORD4(x)   SWORDn(x,  4)
#define SWORD5(x)   SWORDn(x,  5)
#define SWORD6(x)   SWORDn(x,  6)
#define SWORD7(x)   SWORDn(x,  7)


						// Helper functions to represent some assembly instructions.

#ifdef __cplusplus

						// Fill memory block with an integer value
inline void memset32(void *ptr, uint32 value, int count)
{
	uint32 *p = (uint32 *)ptr;
	for (int i = 0; i < count; i++)
		*p++ = value;
}

// Generate a reference to pair of operands
template<class T>  int16 __PAIR__(int8  high, T low) { return (((int16)high) << sizeof(high) * 8) | uint8(low); }
template<class T>  int32 __PAIR__(int16 high, T low) { return (((int32)high) << sizeof(high) * 8) | uint16(low); }
template<class T>  int64 __PAIR__(int32 high, T low) { return (((int64)high) << sizeof(high) * 8) | uint32(low); }
template<class T> uint16 __PAIR__(uint8  high, T low) { return (((uint16)high) << sizeof(high) * 8) | uint8(low); }
template<class T> uint32 __PAIR__(uint16 high, T low) { return (((uint32)high) << sizeof(high) * 8) | uint16(low); }
template<class T> uint64 __PAIR__(uint32 high, T low) { return (((uint64)high) << sizeof(high) * 8) | uint32(low); }

// rotate left
template<class T> T __ROL__(T value, uint count)
{
	const uint nbits = sizeof(T) * 8;
	count %= nbits;

	T high = value >> (nbits - count);
	value <<= count;
	value |= high;
	return value;
}

// rotate right
template<class T> T __ROR__(T value, uint count)
{
	const uint nbits = sizeof(T) * 8;
	count %= nbits;

	T low = value << (nbits - count);
	value >>= count;
	value |= low;
	return value;
}

// carry flag of left shift
template<class T> int8 __MKCSHL__(T value, uint count)
{
	const uint nbits = sizeof(T) * 8;
	count %= nbits;

	return (value >> (nbits - count)) & 1;
}

// carry flag of right shift
template<class T> int8 __MKCSHR__(T value, uint count)
{
	return (value >> (count - 1)) & 1;
}

// sign flag
template<class T> int8 __SETS__(T x)
{
	if (sizeof(T) == 1)
		return int8(x) < 0;
	if (sizeof(T) == 2)
		return int16(x) < 0;
	if (sizeof(T) == 4)
		return int32(x) < 0;
	return int64(x) < 0;
}

// overflow flag of subtraction (x-y)
template<class T, class U> int8 __OFSUB__(T x, U y)
{
	if (sizeof(T) < sizeof(U))
	{
		U x2 = x;
		int8 sx = __SETS__(x2);
		return (sx ^ __SETS__(y)) & (sx ^ __SETS__(x2 - y));
	}
	else
	{
		T y2 = y;
		int8 sx = __SETS__(x);
		return (sx ^ __SETS__(y2)) & (sx ^ __SETS__(x - y2));
	}
}

// overflow flag of addition (x+y)
template<class T, class U> int8 __OFADD__(T x, U y)
{
	if (sizeof(T) < sizeof(U))
	{
		U x2 = x;
		int8 sx = __SETS__(x2);
		return ((1 ^ sx) ^ __SETS__(y)) & (sx ^ __SETS__(x2 + y));
	}
	else
	{
		T y2 = y;
		int8 sx = __SETS__(x);
		return ((1 ^ sx) ^ __SETS__(y2)) & (sx ^ __SETS__(x + y2));
	}
}

// carry flag of subtraction (x-y)
template<class T, class U> int8 __CFSUB__(T x, U y)
{
	int size = sizeof(T) > sizeof(U) ? sizeof(T) : sizeof(U);
	if (size == 1)
		return uint8(x) < uint8(y);
	if (size == 2)
		return uint16(x) < uint16(y);
	if (size == 4)
		return uint32(x) < uint32(y);
	return uint64(x) < uint64(y);
}

// carry flag of addition (x+y)
template<class T, class U> int8 __CFADD__(T x, U y)
{
	int size = sizeof(T) > sizeof(U) ? sizeof(T) : sizeof(U);
	if (size == 1)
		return uint8(x) > uint8(x + y);
	if (size == 2)
		return uint16(x) > uint16(x + y);
	if (size == 4)
		return uint32(x) > uint32(x + y);
	return uint64(x) > uint64(x + y);
}

#else
						// The following definition is not quite correct because it always returns
						// uint64. The above C++ functions are good, though.
#define __PAIR__(high, low) (((uint64)(high)<<sizeof(high)*8) | low)
						// For C, we just provide macros, they are not quite correct.
#define __ROL__(x, y) __rotl__(x, y)      // Rotate left
#define __ROR__(x, y) __rotr__(x, y)      // Rotate right
#define __CFSHL__(x, y) invalid_operation // Generate carry flag for (x<<y)
#define __CFSHR__(x, y) invalid_operation // Generate carry flag for (x>>y)
#define __CFADD__(x, y) invalid_operation // Generate carry flag for (x+y)
#define __CFSUB__(x, y) invalid_operation // Generate carry flag for (x-y)
#define __OFADD__(x, y) invalid_operation // Generate overflow flag for (x+y)
#define __OFSUB__(x, y) invalid_operation // Generate overflow flag for (x-y)
#endif

						// No definition for rcl/rcr because the carry flag is unknown
#define __RCL__(x, y)    invalid_operation // Rotate left thru carry
#define __RCR__(x, y)    invalid_operation // Rotate right thru carry
#define __MKCRCL__(x, y) invalid_operation // Generate carry flag for a RCL
#define __MKCRCR__(x, y) invalid_operation // Generate carry flag for a RCR
#define __SETP__(x, y)   invalid_operation // Generate parity flag for (x-y)

						// In the decompilation listing there are some objects declarared as _UNKNOWN
						// because we could not determine their types. Since the C compiler does not
						// accept void item declarations, we replace them by anything of our choice,
						// for example a char:

#define _UNKNOWN char

#ifdef _MSC_VER
#define snprintf _snprintf
#define vsnprintf _vsnprintf
#endif

union __m128
{
	float m128_f32[4];
	int64_t m128_u64[2];
	char m128_i8[16];
	short m128_i16[8];
	int m128_i32[4];
	int64_t m128_i64[2];
	char m128_u8[16];
	short m128_u16[8];
	unsigned int m128_u32[4];
};

#define VA(...) Invoke<const char *>(0x03E58B0 , __VA_ARGS__)

enum addresses
{

};
enum drawTypes
{
	DT_LR,
	DT_TB
};
enum keys
{
	Cross = 1,
	Circle = 2,
	Square = 3,
	Triangle = 4,
	L1 = 5,
	R1 = 6,
	Start = 14,
	Select = 15,
	L3 = 16,
	R3 = 17,
	L2 = 18,
	R2 = 19,
	DPAD_UP = 20,
	DPAD_DOWN = 21,
	DPAD_LEFT = 22,
	DPAD_RIGHT = 23,
	APAD_UP = 28,
	APAD_DOWN = 29,
	APAD_LEFT = 30,
	APAD_RIGHT = 31,
};
enum entityType_t
{
	ET_General = 0,
	ET_Player = 1,
	ET_Corpse = 2,
	ET_Item = 3,
	ET_Missile = 4,
	ET_Invisible_entity = 5,
	ET_Scriptmover = 6,
	ET_Sound_blend = 7,
	ET_FX = 8,
	ET_Loop_FX = 9,
	ET_Primary_Light = 10,
	ET_Turret = 11,
	ET_Helicopter = 12,
	ET_Plane = 13,
	ET_Vehicle = 14,
	ET_Vehicle_corpse = 15,
	ET_Actor = 16,
	ET_DOG = 16,
	ET_Actor_spawner = 17,
	ET_Actor_corpse = 18,
	ET_Streamer_Hint = 19,
};


enum Cg_DrawNameMode_t
{
	Abbreviated = 0,
	ClanTagOnly = 1,
	FullName = 2,
	RankIconOnly = 3,
};

enum alignment
{
	align_left,
	align_right,
	align_center,
};

#pragma region cg
typedef struct
{
	char padding00[0x8];		 //0x8
	int Width;					 //0x8
	int Height;					 //0xC
	char padding01[0x14];		 //0x10
	Vector3 Fov_v;				 //0x24
	char padding02[0x4];		 //0x30
	float Fov;					 //0x34
	Vector3 ViewOrigin;			 //0x38
	char padding03[0x4];		 //0x44
	Vector3 ViewAxis[3];		 //0x48
} refdef_s;// 0x6C

struct playerstate_s
{
	unsigned int time;			/// 0x00000
	char _000000000[0x1B4];		/// 0x00004
	int weapon;					/// 0x001B8
	char _000000001[0x3C];		/// 0x001BC
	Vector3 viewAngles;			/// 0x001F8
	char _00000001[0x55E4];		/// 0x00204
};

enum stance_t : int
{
	STANCE_STANDING = 0x0,
	STANCE_CROUCH = 0x4,
	STANCE_PRONE = 0x8,
};

class score_s
{
public:
	__int32 ping;     //0x0000 
	__int32 status_icon;   //0x0004 
	__int32 place;     //0x0008 
	__int32 score;     //0x000C 
	__int32 kills;     //0x0010 
	__int32 assists;    //0x0014 
	__int32 deaths;     //0x0018 
	int scoreboardColumns[4];  //0x001C 
};         //0x002C
class clientControllers_t
{
public:
	Vector3 angles[6];     //0x0000 
	Vector3 tag_origin_angles;   //0x0048 
	Vector3 tag_origin_offset;   //0x0054 
};         //0x0060
class clientinfo_s
{
public:
	__int32 infoValid;    //0x0000 
	__int32 nextValid;    //0x0004 
	__int32 clientNum;    //0x0008 
	char name[32];     //0x000C 
	__int32 team;     //0x002C 
	__int32 oldteam;    //0x0030 
	__int32 ffateam;    //0x0034 
	char _0x0038[40];
	__int32 rank;     //0x0060 
	__int32 prestige;    //0x0064 
	__int32 needsRevive;   //0x0068 
	char _0x006C[4];
	int perks[2];     //0x0070 
	__int64 xuid;     //0x0078 
	char clantag[8];
	score_s score;     //0x0088 
	char _0x00B4[28];
	__int32 Dead;   //0x00D0 
	__int32 hRankIcon;    //0x00D4 
	__int32 location;    //0x00D8 
	__int32 health;     //0x00DC 
	char model[64];     //0x00E0 
	char attachModelNames[6][64]; //0x0120 
	char attachTagNames[6][64];  //0x02A0 
	char _0x0420[156];
	float lerpMoveDir;    //0x04BC 
	float lerpLean;     //0x04C0 
	Vector3 playerAngles;    //0x04C4 
	__int32 leftHandGun;   //0x04D0 
	__int32 dobjDirty;    //0x04D4 
	clientControllers_t control; //0x04D8 
	char _0x0538[136];
	__int32 pXAnimTree;    //0x05C0 
	__int32 iDObjWeapon;   //0x05C4 
	char _0x05C8[576];
};//Size=0x0808

typedef struct
{
	int somethinghax;             //0x0
	int somethinghax1;             //0x4
	int null_;                     //0x8
	char Name[0x20];         //0xC
	int Team;                     //0x2C
	char padding01[0x5F];         //0x30
	bool Dead;                     //0x8F
	char padding04[0x24];         //
	char CurrentWeaponName[32];  //0xB4
	char paddin05[0x3F0];         //D4
	Vector3 viewAngle;             //0x4C4
	char _0x4D0[0xF4];
	int Weapon;                     //0x5C4
	char padding03[0x240];         //0x5C8

							   //Size: 0x808
} compassviewangleshit;

typedef struct
{
	int somethinghax;			 //0x0
	int somethinghax1;			 //0x4
	int anull;					 //0x8
	char PlayerName[0x20];		 //0xC
	int Team;					 //0x2C
	char padding01[0x5F];		 //0x30
	bool Dead;					 //0x8F
	char padding02[0x60];		 //0x90
	char PlayerModel[0x20];      //0xF0
	char padding03[0x4B7];
	char Weapon;				 //0x5C7
	char padding04[0x240];		 //0x5C8
								 //Size: 0x808
} clientinfo_t;

struct cg_s
{
	int clientNum;				/// 0x00000
	char padding00[0x1C];		/// 0x00004
	int serverTime;				/// 0x00020
	char _00000001[0x60];		/// 0x00024
	int ping;					/// 0x00084
	char _000000011[0x30];		/// 0x00088
	Vector3 origin;				/// 0x000B8
	char _00000002[0xC8];		/// 0x000C4
	stance_t stance;			/// 0x0018C
	char _00000003[0x4C];		/// 0x00190
	int maxEntities;			/// 0x001DC
	char _00000004[0x90];		/// 0x001E0
	float zoomProgress;			/// 0x00270
	char _00000005[0x54];		/// 0x00274
	int health;					/// 0x002C8
	char _0x000006[0x4];		/// 0x002CC
	int maxHealth;				/// 0x002D0
	char _00000007[0x98];		/// 0x002D4
	float weaponKickProgress;	/// 0x0036C
	char _00000008[0x48038];	/// 0x00370
	playerstate_s playerstate;	/// 0x483A8
	refdef_s refdef;			/// 0x4DB90
	char _00000009[0x1C1A4];	/// 0x4DBFC
	clientinfo_t clients[18];	/// 0x69DA0
	char _0000000A[0xE060];		/// 0x72E30
	float spreadMultiplier;		/// 0x80E90
};

struct cg_st
{
	int clientNum;				/// 0x00000
	char padding00[0x1C];		/// 0x00004
	int serverTime;				/// 0x00020
	char _00000001[0x94];		/// 0x00024
	Vector3 origin;				/// 0x000B8
	char _00000002[0xC8];		/// 0x000C4
	stance_t stance;			/// 0x0018C
	char _00000003[0x4C];		/// 0x00190
	int maxEntities;			/// 0x001DC
	char _00000004[0x90];		/// 0x001E0
	float zoomProgress;			/// 0x00270
	char _00000005[0x54];		/// 0x00274
	int health;					/// 0x002C8
	char _0x000006[0x4];		/// 0x002CC
	int maxHealth;				/// 0x002D0
	char _00000007[0x98];		/// 0x002D4
	float weaponKickProgress;	/// 0x0036C
	char _00000008[0x48038];	/// 0x00370
	playerstate_s playerstate;	/// 0x483A8
	refdef_s refdef;			/// 0x4DB90
	char _00000009[0x1C1A4];	/// 0x4DBFC
	compassviewangleshit clients[18];	/// 0x69DA0
	char _0000000A[0xE060];		/// 0x72E30
	float spreadMultiplier;		/// 0x80E90
};
#pragma endregion
#pragma region cgs
struct cgs_s
{
	int viewX;
	int viewY;
	int viewWidth;
	int viewHeight;
	float viewAspect;
	char _0000000[16];
	int serverCommandSequence;
	int processedSnapshotNum;
	int localServer;
	char gametype[32];
	char szHostName[256];
	int maxclients;
	char mapname[64];
	int gameEndTime;
	int voteTime;
	int voteYes;
	int voteNo;
};
#pragma endregion
#pragma region client active
typedef struct
{
	int time;		// 0x00-0x04
	int buttons;		// 0x04-0x08
	int Buf8;			// 0x08-0x0C
	int viewAngles[3];		// 0x0C-0x18
	int weapon;			// 0x18-0x1C
	int offHandIndex;	// 0x1C-0x20
	int Buf20;			// 0x20-0x24
	char fDir;	// 0x24-0x25
	char rDir;		// 0x25-0x26
	char Buf[0x16];		// 0x26-0x3C
}usercmd_s;

typedef struct
{
	char padding00[0x44];	       		//	0x00
	bool ADS;							//	0x44
	char padding01[0xC3];				//	0x45
	Vector3 BaseAngles;					//	0x108
	char padding02[0x2B80];				//	0x114
	Vector3 ViewAngles;					//	0x2C94
	char padding03[0x40010];			//	0x2C9C
	usercmd_s UserCmd[128];				//	0x42CB0
	int CurrentCmdNumber;				//	0x44AB0
}clientactive_s;

#pragma endregion
#pragma region centity


enum clientMigState_t
{
	CMSTATE_INACTIVE = 0x0,
	CMSTATE_OLDHOSTLEAVING = 0x1,
	CMSTATE_LIMBO = 0x2,
	CMSTATE_NEWHOSTCONNECT = 0x3,
	CMSTATE_COUNT = 0x4,
};

typedef struct
{
	clientMigState_t migrationState;
	char padding[0x10];
}ClientUIActive_t;


#define ClientUIActive_s (*(ClientUIActive_t**)(0xD689DC))


//#define local ((local_s*)(0x10020000))	// free memory for structure usage
//

typedef struct centity_s
{
	__int16 lightingHandle; //0x0000 
	unsigned char eType; //0x0002 
	unsigned char localClientNum; //0x0003 
	char _0x0004[40];
	Vector3 Origin; //0x002C 
	char _0x0038[284];
	__int32 Flags; //0x0154 
	__int32 eFlags2; //0x0158 
	unsigned char trType; //0x015C 
	char _0x015D[3];
	__int32 trTime; //0x0160 
	__int32 trDuration; //0x0164 
	Vector3 NewOrigin; //0x0168 
	Vector3 trDelta; //0x0174 
	char _0x0180[36];
	float leanf; //0x01A4 
	__int32 movementDir; //0x01A8 
	__int32 movemcentity; //0x01AC 
	__int32 WeaponID; //0x01B0 
	__int32 OldWeapon; //0x01B4 
	__int32 offHandWeaponModel; //0x01B8 
	__int32 meleeWeapon; //0x01BC 
	unsigned char offhandeWeaponModel; //0x01C0 
	unsigned char meleeWeaponModel; //0x01C1 
	unsigned char vehicleType; //0x01C2 
	unsigned char vehicleAnimBoneIndex; //0x01C3 
	unsigned char vehicleSeat; //0x01C4 
	unsigned char stowedweaponCamo; //0x01C5 
	char _0x01C6[10];
	__int32 ClientNumber; //0x01D0 
	__int32 nextLerpeFlags; //0x01D4 
	__int32 nextLerpeFlags1; //0x01D8 
	unsigned char nextLerptrType; //0x01DC 
	char _0x01DD[3];
	__int32 nextlerptrtime; //0x01E0 
	__int32 nextlerptrduration; //0x01E4 
	Vector3 OldOrigin; //0x01E8 
	Vector3 nextLerptrdelta; //0x01F4 
	char _0x0200[47];
	char NotRobots;//0x22F Check if its == 0x2 
	char _0x230[42];
	bool Alive; //0x25A
	char _0x025B[77];
	__int16 Type; //0x02A8
	char _0x02Adc[0xA];
	int pickupId; // 0x2B4
	char _0x02AA[0xB4];
	char State;     //0x36C 
	char padding05[0x7];  //0x36D

}centity_s, *pCentity_t;//Size = 0x0374

typedef struct centity_sent
{
	char padding01[0x2C];         //0x0
	Vector3 Origin;                 //0x2C
	char padding02[0x11C];         //0x38
	int Flags;                     //0x154
	char padding938[0x10];        //0x158
	Vector3 NewOrigin;            //0x168
	char _0x0174[0x38];
	int AltType;                   //0x1AC
	int WeaponID;
	int OldWeapon;
	char padding03[0x18];         //0x1B0
	int ClientNumber;             //0x1D0
	char padding04[0x14];       //0x1D4
	Vector3 OldOrigin;            //0x1E8
	char _0x1F4[0xB4];
	short Type;                    //0x2A8
	char _0x02AA[0xC2];
	char State;                     //0x36C    
	char padding05[0x7];         //0x36D
								 //size 0x374
}Centity_ts, *pCentity_ts;

struct local_s
{
public:
	bool unlimitedSlots;
	int consoley[10];
	bool alive;
	bool shoot;
	bool shooting;
	bool canreload;
	bool antifreeze;
	bool pplayer[12];
	bool iplayer[12];
	char* stausrank;
	float zoommap;
	float scale, radarsizex, radarsizey, bgradarsizex, bgradarsizey, bgbgradarsizex, bgbgradarsizey;;
	int wflag, xsint, styleint, buttint;
	int target_num;
	Vector3 vangles;
	struct Player
	{
		Vector3 vtag[8];
	}player[12];
};
extern local_s * local;
static String aimtypesDec[] = { "Lock on effect", "Silent effect", "Snap effect", "Autoshoot if looking at the target" };
static String aimtypes[] = { "Aimbot", "Silentbot", "Snapbot", "Triggerbot" };
static String tagtypesDec[] = { "Automatically iterates through every bone", "Head", "Spine", "Left Knee", "Left Ankle" };
static String tagtypes[] = { "Auto Bone", "Head", "Spine", "Left Knee", "Left Ankle" };
static String keytypesDec[] = { "None", "Engages aimbot / autoshoot via L1" };
static String keytypes[] = { "None", "L1"};
enum aimtype_t
{
	AIM_TYPE_AIM_BOT,
	AIM_TYPE_SILENT,
	AIM_TYPE_SNAP,
	AIM_TYPE_TRIGGERBOT,
};

enum tagtype_t
{
	AUTO_BONE,
	tj_head,
	tj_spine4,
	tj_knee_le,
	tj_ankle_le,
};

enum keytype_t
{
	KEY_NONE,
	KEY_L1,
};


enum aimbotBoneIndexes_t {
	j_ankle_ri,
	j_ankle_le,
	j_knee_ri,
	j_knee_le,
	j_spineupper,
	j_neck,
	j_head,
	j_helmet,
};

extern short EspBoneIndex[];
extern short AimBoneIndex[];
extern short SldBoneIndex[];
extern short LaserBoneIndex[];

extern char* SNames[];
extern char* ANames[];



typedef struct aimbot_s
{
	bool drawconsole, bautobone, baimatfeet, bshieldtrace, benableanti, benablehvh, benable, benable1, bvisible, bautowall, bvisible_esp[18], bautowall_esp[18], baimrequired, bantiaim, bspinbot, breversebot, blockup, bnospread, bnoflinch, bnosway, bnorec, bnobob, bautoshoot, cancelreload;
	
	struct Visible
	{
		bool bone[21];
	}visible[18];

	struct Hittable
	{
		short bone[21];
	}hittable[18];
	
	struct visuals_s
	{
		bool ballies, baxis, bbones, bvangles, myvangles, bcompass, bradar, bradartype, btargetinfo, bprox, bdynamic, bnames, bdist, bwall, ebwall, bchams, bhealthbar, bweapsworld, bnadesworld, bpickupscavsworld, bpickupweaponsworld, bradrpickupweaps, bradrpickupscavs, bradrhelis, bradrturrets, bradrvehicles, bradrdogos, bradrartillery, bradrnades, bxhscavs, bxhweapspickupids, benableworldents, btargetfinder, bentcount;
		int bound, snaplines, espvisions, colori;
		int modm;
		int penm;
		int getNumberOfEntities;
		int maxclients;
	}esp;

	aimtype_t aimtype;
	tagtype_t tagtype;
	keytype_t keytype;
	float fprediction, damage, dist, fmj, spinscale, rollscale, fakelagscale, fpcorrection, pitchscale;
	int loop_number_aimbot, loop_tick_aimbot;
	short psztag[18];
	bool sc[18];
};
extern aimbot_s bot;

#pragma endregion
#pragma region ui
struct UiContext
{
	int x;				// 0x0000
	int y;				// 0x0004
	int frameTime;		// 0x0008
	int realTime;		// 0x000C
	char padding[0xC];	// 0x0010
	int width;			// 0x001C
	int height;			// 0x0020
	float aspect;		// 0x0024
	float fps;			// 0x0028
};

struct color
{
	float r, g, b, a;
	color() { r = g = b = a = 0.0; }
	color(float r, float g, float b, float a) { this->r = r / 255.0f, this->g = g / 255.0f, this->b = b / 255.0f, this->a = a / 255.0f; }
};

#pragma endregion
#pragma region weapon def
#pragma region enums

struct GfxImage
{
	char unknown1[6];
	char unk[0xe];
	//CellGcmTexture texture;	// modified, missing 10 bytes, size = 0xE
	char mapType;
	char unknown3;
	char unknown4;
	char unknown5;
	int size;
	unsigned __int16 width;
	unsigned __int16 height;
	unsigned __int16 depth;
	char levelCount;
	char streaming;
	unsigned int baseSize;
	char *pixels;
	char unknownData2[0x7C];
	char streamedPartCount;
	String name;
	unsigned int hash;
};


typedef struct WeaponizedGfx
{
	//char padd0[0x77];
	float Reflection;
	char padd1[0x1C];
	float Layer3Scroll;
	char padd2[0x1C];
	float Emissive_Amo;
	char padd3[0xFC];
	float Layer1Scroll;
	char padd4[0x7C];
	float Layer2Scroll;
	char padd6[0x11C];
	float Gloss_Amount;
	char padd7[0xEC];
}WeaponizedGfx, *PWeaponized_t;
#define Weaponized ((WeaponizedGfx*)(0x301cc2c0))

enum Bit
{
	AUTO_SHOOT = (1 << 31),
	AUTO_AIM = (1 << 20),
	RELOAD = (1 << 25),
	TRIANGLE = 4194312,
};

struct WeaponCamoSet {
	GfxImage *solidCamoImage;
	GfxImage *patternCamoImage;
	Vector2 patternOffset;
	float patternScale;
};

struct WeaponCamoMaterial {
	unsigned __int16 replaceFlags;
	unsigned __int16 numBaseMaterials;
	//Material **baseMaterials;
	//Material **camoMaterials;
	float shaderConsts[8];
};

struct WeaponCamoMaterialSet {
	unsigned int numMaterials;
	WeaponCamoMaterial *materials;
};

struct WeaponCamo {
	const char *name;
	GfxImage *solidBaseImage;
	GfxImage *patternBaseImage;
	WeaponCamoSet *camoSets;
	unsigned int numCamoSets;
	WeaponCamoMaterialSet *camoMaterials;
	unsigned int numCamoMaterials;
};

enum guidedMissileType_t
{
	MISSILE_GUIDANCE_NONE = 0x0,
	MISSILE_GUIDANCE_SIDEWINDER = 0x1,
	MISSILE_GUIDANCE_HELLFIRE = 0x2,
	MISSILE_GUIDANCE_JAVELIN = 0x3,
	MISSILE_GUIDANCE_BALLISTIC = 0x4,
	MISSILE_GUIDANCE_WIREGUIDED = 0x5,
	MISSILE_GUIDANCE_TVGUIDED = 0x6,
	MISSILE_GUIDANCE_COUNT = 0x7,
};
enum AnimationType : int {

	none = 0,
	adefault = 1,
	other = 2,
	sniper = 3,
	m203 = 4,
	hold = 5,
	briefcase = 6,
	reviver = 7,
	radio = 8,
	dualwield = 9,
	remotecontrol = 10,
	crossbow = 11,
	minigun = 12,
	beltfed = 13,
	g11 = 14,
	rearclip = 15,
	handleclip = 16,
	rearclipsniper = 17,
	ballisticknife = 18,
	singleknife = 19,
	nopump = 20,
	hatchet = 21,
	grimreaper = 22,
	zipline = 23,
	riotshield = 24,
	tablet = 25,
	turned = 26,
	screecher = 27,
	PLAYER_ANIM_TYPE_MAX
};
enum weapType_t
{
	WEAPTYPE_BULLET = 0x0,
	WEAPTYPE_GRENADE = 0x1,
	WEAPTYPE_PROJECTILE = 0x2,
	WEAPTYPE_BINOCULARS = 0x3,
	WEAPTYPE_GAS = 0x4,
	WEAPTYPE_BOMB = 0x5,
	WEAPTYPE_MINE = 0x6,
	WEAPTYPE_MELEE = 0x7,
	WEAPTYPE_NUM = 0x8,
};
enum weapClass_t
{
	WEAPCLASS_RIFLE = 0x0,
	WEAPCLASS_MG = 0x1,
	WEAPCLASS_SMG = 0x2,
	WEAPCLASS_SPREAD = 0x3,
	WEAPCLASS_PISTOL = 0x4,
	WEAPCLASS_GRENADE = 0x5,
	WEAPCLASS_ROCKETLAUNCHER = 0x6,
	WEAPCLASS_TURRET = 0x7,
	WEAPCLASS_NON_PLAYER = 0x8,
	WEAPCLASS_GAS = 0x9,
	WEAPCLASS_ITEM = 0xA,
	WEAPCLASS_MELEE = 0xB,
	WEAPCLASS_KILLSTREAK_ALT_STORED_WEAPON = 0xC,
	WEAPCLASS_NUM = 0xD,
};
enum PenetrateType
{
	PENETRATE_TYPE_SMALL = 0x1,
	PENETRATE_TYPE_MEDIUM = 0x2,
	PENETRATE_TYPE_LARGE = 0x3,
};
enum ImpactType
{
	IMPACT_TYPE_NONE = 0x0,
	IMPACT_TYPE_BULLET_SMALL = 0x1,
	IMPACT_TYPE_BULLET_LARGE = 0x2,
	IMPACT_TYPE_BULLET_AP = 0x3,
	IMPACT_TYPE_BULLET_XTREME = 0x4,
	IMPACT_TYPE_SHOTGUN = 0x5,
	IMPACT_TYPE_GRENADE_BOUNCE = 0x6,
	IMPACT_TYPE_GRENADE_EXPLODE = 0x7,
	IMPACT_TYPE_RIFLE_GRENADE = 0x8,
	IMPACT_TYPE_ROCKET_EXPLODE = 0x9,
	IMPACT_TYPE_ROCKET_EXPLODE_XTREME = 0xA,
	IMPACT_TYPE_PROJECTILE_DUD = 0xB,
	IMPACT_TYPE_MORTAR_SHELL = 0xC,
	IMPACT_TYPE_TANK_SHELL = 0xD,
	IMPACT_TYPE_BOLT = 0xE,
	IMPACT_TYPE_BLADE = 0xF,
	IMPACT_TYPE_COUNT = 0x10,
};
enum weapInventoryType_t
{
	WEAPINVENTORY_PRIMARY = 0x0,
	WEAPINVENTORY_OFFHAND = 0x1,
	WEAPINVENTORY_ITEM = 0x2,
	WEAPINVENTORY_ALTMODE = 0x3,
	WEAPINVENTORY_MELEE = 0x4,
	WEAPINVENTORYCOUNT = 0x5,
};
enum weapFireType_t
{
	WEAPON_FIRETYPE_FULLAUTO = 0x0,
	WEAPON_FIRETYPE_SINGLESHOT = 0x1,
	WEAPON_FIRETYPE_BURSTFIRE2 = 0x2,
	WEAPON_FIRETYPE_BURSTFIRE3 = 0x3,
	WEAPON_FIRETYPE_BURSTFIRE4 = 0x4,
	WEAPON_FIRETYPE_STACKED = 0x5,
	WEAPON_FIRETYPE_MINIGUN = 0x6,
	WEAPON_FIRETYPECOUNT = 0x7,
};
enum weapClipType_t
{
	WEAPON_CLIPTYPE_BOTTOM = 0x0,
	WEAPON_CLIPTYPE_TOP = 0x1,
	WEAPON_CLIPTYPE_LEFT = 0x2,
	WEAPON_CLIPTYPE_DP28 = 0x3,
	WEAPON_CLIPTYPE_PTRS = 0x4,
	WEAPON_CLIPTYPE_LMG = 0x5,
	WEAPON_CLIPTYPECOUNT = 0x6,
};
enum barrelType_t : int {

	BARREL_TYPE_SINGLE = 0x0,
	BARREL_TYPE_DUAL = 0x1,
	BARREL_TYPE_DUAL_ALTERNATE = 0x2,
	BARREL_TYPE_QUAD = 0x3,
	BARREL_TYPE_QUAD_ALTERNATE = 0x4,
	BARREL_TYPE_QUAD_DOUBLE_ALTERNATE = 0x5,
	BARREL_TYPE_COUNT = 0x6
};
enum OffhandClass {

	OFFHAND_CLASS_NONE = 0x0,
	OFFHAND_CLASS_FRAG_GRENADE = 0x1,
	OFFHAND_CLASS_SMOKE_GRENADE = 0x2,
	OFFHAND_CLASS_FLASH_GRENADE = 0x3,
	OFFHAND_CLASS_GEAR = 0x4,
	OFFHAND_CLASS_SUPPLYDROP_MARKER = 0x5,
	OFFHAND_CLASS_COUNT = 0x6,
};
enum OffhandSlot {

	OFFHAND_SLOT_NONE = 0x0,
	OFFHAND_SLOT_LETHAL_GRENADE = 0x1,
	OFFHAND_SLOT_TACTICAL_GRENADE = 0x2,
	OFFHAND_SLOT_EQUIPMENT = 0x3,
	OFFHAND_SLOT_SPECIFIC_USE = 0x4,
	OFFHAND_SLOT_COUNT = 0x5,
};
enum weapStance_t
{
	WEAPSTANCE_STAND = 0x0,
	WEAPSTANCE_DUCK = 0x1,
	WEAPSTANCE_PRONE = 0x2,
	WEAPSTANCE_NUM = 0x3,
};
enum activeReticleType_t
{
	VEH_ACTIVE_RETICLE_NONE = 0x0,
	VEH_ACTIVE_RETICLE_PIP_ON_A_STICK = 0x1,
	VEH_ACTIVE_RETICLE_BOUNCING_DIAMOND = 0x2,
	VEH_ACTIVE_RETICLE_COUNT = 0x3,
};
enum weaponIconRatioType_t
{
	WEAPON_ICON_RATIO_1TO1 = 0x0,
	WEAPON_ICON_RATIO_2TO1 = 0x1,
	WEAPON_ICON_RATIO_4TO1 = 0x2,
	WEAPON_ICON_RATIO_COUNT = 0x3,
};
enum ammoCounterClipType_t
{
	AMMO_COUNTER_CLIP_NONE = 0x0,
	AMMO_COUNTER_CLIP_MAGAZINE = 0x1,
	AMMO_COUNTER_CLIP_SHORTMAGAZINE = 0x2,
	AMMO_COUNTER_CLIP_SHOTGUN = 0x3,
	AMMO_COUNTER_CLIP_ROCKET = 0x4,
	AMMO_COUNTER_CLIP_BELTFED = 0x5,
	AMMO_COUNTER_CLIP_ALTWEAPON = 0x6,
	AMMO_COUNTER_CLIP_COUNT = 0x7,
};
enum weapOverlayReticle_t
{
	WEAPOVERLAYRETICLE_NONE = 0x0,
	WEAPOVERLAYRETICLE_CROSSHAIR = 0x1,
	WEAPOVERLAYRETICLE_NUM = 0x2,
};
enum weapOverlayInterface_t {

	WEAPOVERLAYINTERFACE_NONE = 0x0,
	WEAPOVERLAYINTERFACE_JAVELIN = 0x1,
	WEAPOVERLAYINTERFACE_TURRETSCOPE = 0x2,
	WEAPOVERLAYINTERFACE_MAX
};
enum weapProjExposion_t
{
	WEAPPROJEXP_GRENADE = 0x0,
	WEAPPROJEXP_ROCKET = 0x1,
	WEAPPROJEXP_FLASHBANG = 0x2,
	WEAPPROJEXP_NONE = 0x3,
	WEAPPROJEXP_DUD = 0x4,
	WEAPPROJEXP_SMOKE = 0x5,
	WEAPPROJEXP_HEAVY = 0x6,
	WEAPPROJEXP_FIRE = 0x7,
	WEAPPROJEXP_NAPALMBLOB = 0x8,
	WEAPPROJEXP_BOLT = 0x9,
	WEAPPROJEXP_NUM = 0xA,
};
enum WeapStickinessType {

	WEAPSTICKINESS_NONE = 0x0,
	WEAPSTICKINESS_ALL = 0x1,
	WEAPSTICKINESS_ALL_NO_SENTIENTS = 0x2,
	WEAPSTICKINESS_GROUND = 0x3,
	WEAPSTICKINESS_GROUND_WITH_YAW = 0x4,
	WEAPSTICKINESS_FLESH = 0x5,
	WEAPSTICKINESS_COUNT = 0x6
};

enum WeapRotateType {

	WEAPROTATE_GRENADE_ROTATE = 0x0,
	WEAPROTATE_BLADE_ROTATE = 0x1,
	WEAPROTATE_CYLINDER_ROTATE = 0x2,
	WEAPROTATE_COUNT = 0x3
};
#pragma endregion

typedef unsigned __int16 ScriptString;

struct ProjectileExplosionEffect {

	int * projExplosionEffect;
	bool projExplosionEffectForceNormalUp;
};

struct WeaponDef {

	const char *szOverlayName;//0x04
	int **gunXModel;
	int *handXModel;
	const char *szModeName;
	ScriptString(*noteTrackSoundMapKeys)[0x14];
	ScriptString(*notetrackSoundMapValues)[0x14];
	AnimationType playerAnimType;
	weapType_t weaponType;
	weapClass_t weaponClass;
	PenetrateType penetrateType;
	ImpactType impactType;
	weapInventoryType_t inventoryType;
	weapFireType_t fireType;
	weapClipType_t clipType;
	barrelType_t barrelType;
	int itemIndex;
	const char * parentWeaponName;
	int iJamFireTime;
	int overheatWeapon;
	float overheatRate;
	float cooldownRate;
	float overheatEndVal;
	bool coolWhileFiring;
	bool fuelTankWeapon;
	int iTankLifeTime;
	OffhandClass offhandClass;
	OffhandSlot offhandSlot;
	weapStance_t stance;
	int * viewFlashEffect;
	int * worldFlashEffect;
	int * barrelCooldownEffect;
	int barrelCooldownMinCount;
	Vector3 vViewFlashOffset;
	Vector3 vWorldFlashOffset;
	char * pickupSound;
	char * pickupSoundPlayer;
	char * ammoPickupSound;
	char * ammoPickupSoundPlayer;
	char * projectileSound;
	char * pullbackSound;
	char * pullbackSoundPlayer;
	char * fireSound;
	char * fireSoundPlayer;
	char * loopFireSound;
	char * loopFireSoundPlayer;
	char * loopFireEndSound;
	char * loopFireEndSoundPlayer;
	char * startFireSound;
	char * stopFireSound;
	char * killcamStartFireSound;
	char * startFireSoundPlayer;
	char * stopFireSoundPlayer;
	char * killcamStartFireSoundPlayer;
	char * lastShotSound;
	char * lastShotSoundPlayer;
	char * emptyFireSound;
	char * emptyFireSoundPlayer;
	char * crackSound;
	char * whizbySound;
	char * meleeSwipeSound;
	char * meleeSwipeSoundPlayer;
	char * meleeHitSound;
	char * meleeMissSound;
	char * rechamberSound;
	char * rechamberSoundPlayer;
	char * reloadSound;
	char * reloadSoundPlayer;
	char * reloadEmptySound;
	char * reloadEmptySoundPlayer;
	char * reloadStartSound;
	char * reloadStartSoundPlayer;
	char * reloadEndSound;
	char * reloadEndSoundPlayer;
	char * rotateLoopSound;
	char * rotateLoopSoundPlayer;
	char * rotateStopSound;
	char * rotateStopSoundPlayer;
	char * deploySound;
	char * deploySoundPlayer;
	char * finishDeploySound;
	char * finishDeploySoundPlayer;
	char * breakdownSound;
	char * breakdownSoundPlayer;
	char * finishBreakdownSound;
	char * finishBreakdownSoundPlayer;
	char * detonateSound;
	char * detonateSoundPlayer;
	char * nightVisionWearSound;
	char * nightVisionWearSoundPlayer;
	char * nightVisionRemoveSound;
	char * nightVisionRemoveSoundPlayer;
	char * altSwitchSound;
	char * altSwitchSoundPlayer;
	char * raiseSound;
	char * raiseSoundPlayer;
	char * firstRaiseSound;
	char * firstRaiseSoundPlayer;
	char * adsRaiseSoundPlayer;
	char * adsLowerSoundPlayer;
	char * putawaySound;
	char * putawaySoundPlayer;
	char * overheatSound;
	char * overheatSoundPlayer;
	char * adsZoomSound;
	char * shellCasing;
	char * shellCasingPlayer;
	char * * bounceSounds;    //Refer to surfaceNames_t
	const char * standMountedWeapdef;
	const char * crouchMountedWeapdef;
	const char * proneMountedWeapdef;
	unsigned int standMountedWeapIndex;
	unsigned int crouchMountedWeapIndex;
	unsigned int proneMountedWeapIndex;
	int * viewShellEjectEffect;
	int * worldShellEjectEffect;
	int * viewLastShotEjectEffect;
	int * worldLastShotEjectEffect;
	Vector3 vViewShellEjectOffset;
	Vector3 vWorldShellEjectOffset;
	Vector3 vViewShellEjectRotation;
	Vector3 vWorldShellEjectRotation;
	int *reticleCenter;
	int *reticleSide;
	int iReticleCenterSize;
	int iReticleSideSize;
	int iReticleMinOfs;
	activeReticleType_t activeReticleType;
	Vector3 vStandMove;
	Vector3 vStandRot;
	Vector3 vDuckedOfs;
	Vector3 vDuckedMove;
	Vector3 vDuckedSprintOfs;
	Vector3 vDuckedSprintRot;
	Vector2 vDuckedSprintBob;
	float fDuckedSprintCycleScale;
	Vector3 vSprintOfs;
	Vector3 vSprintRot;
	Vector2 vSprintBob;
	float fSprintCycleScale;
	Vector3 vLowReadyOfs;
	Vector3 vLowReadyRot;
	Vector3 vRideOfs;
	Vector3 vRideRot;
	Vector3 vDtpOfs;
	Vector3 vDtpRot;
	Vector2 vDtpBob;
	float fDtpCycleScale;
	Vector3 vMantleOfs;
	Vector3 vMantleRot;
	Vector3 vSlideOfs;
	Vector3 vSlideRot;
	Vector3 vDuckedRot;
	Vector3 vProneOfs;
	Vector3 vProneMove;
	Vector3 vProneRot;
	Vector3 vStrafeMove;
	Vector3 vStrafeRot;
	float fPosMoveRate;
	float fPosProneMoveRate;
	float fStandMoveMinSpeed;
	float fDuckedMoveMinSpeed;
	float fProneMoveMinSpeed;
	float fPosRotRate;
	float fPosProneRotRate;
	float fStandRotMinSpeed;
	float fDuckedRotMinSpeed;
	float fProneRotMinSpeed;
	int * *worldModel;
	int *worldClipModel;
	int *rocketModel;
	int *mountedModel;
	int *additionalMeleeModel;
	int * fireTypeIcon;
	int * hudIcon;
	weaponIconRatioType_t hudIconRatio;
	int * indicatorIcon;
	weaponIconRatioType_t indicatorIconRatio;
	int * ammoCounterIcon;
	weaponIconRatioType_t ammoCounterIconRatio;
	ammoCounterClipType_t ammoCounterClip;
	int iStartAmmo;
	int iMaxAmmo;
	int shotCount;
	const char *szSharedAmmoCapName;
	int iSharedAmmoCapIndex;
	int iSharedAmmoCap;
	bool unlimitedAmmo;
	bool ammoCountClipRelative;
	int damage[6];
	float damageRange[6];
	int minPlayerDamage;
	float damageDuration;
	float damageInterval;
	int playerDamage;
	int iMeleeDamage;
	int iDamageType;
	ScriptString explosionTag;
	int iFireDelay;
	int iMeleeDelay;
	int meleeChargeDelay;
	int iDetonateDelay;
	int iSpinUpTime;
	int iSpinDownTime;
	float spinRate;
	const char *spinLoopSound;
	const char *spinLoopSoundPlayer;
	const char *startSpinSound;
	const char *startSpinSoundPlayer;
	const char *stopSpinSound;
	const char *stopSpinSoundPlayer;
	bool applySpinPitch;
	int iFireTime;
	int iLastFireTime;
	int iRechamberTime;
	int iRechamberBoltTime;
	int iHoldFireTime;
	int iDetonateTime;
	int iMeleeTime;
	int iBurstDelayTime;
	int meleeChargeTime;
	int iReloadTimeRight;
	int iReloadTimeLeft;
	int reloadShowRocketTime;
	int iReloadEmptyTimeLeft;
	int iReloadAddTime;
	int iReloadEmptyAddTime;
	int iReloadQuickAddTime;
	int iReloadQuickEmptyAddTime;
	int iReloadStartTime;
	int iReloadStartAddTime;
	int iReloadEndTime;
	int iDropTime;
	int iRaiseTime;
	int iAltDropTime;
	int quickDropTime;
	int quickRaiseTime;
	int iFirstRaiseTime;
	int iEmptyRaiseTime;
	int iEmptyDropTime;
	int sprintInTime;
	int sprintLoopTime;
	int sprintOutTime;
	int lowReadyInTime;
	int lowReadyLoopTime;
	int lowReadyOutTime;
	int contFireInTime;
	int contFireLoopTime;
	int contFireOutTime;
	int dtpInTime;
	int dtpLoopTime;
	int dtpOutTime;
	int crawlInTime;
	int crawlForwardTime;
	int crawlBackTime;
	int crawlRightTime;
	int crawlLeftTime;
	int crawlOutFireTime;
	int crawlOutTime;
	int slideInTime;
	int deployTime;
	int breakdownTime;
	int iFlourishTime;
	int nightVisionWearTime;
	int nightVisionWearTimeFadeOutEnd;
	int nightVisionWearTimePowerUp;
	int nightVisionRemoveTime;
	int nightVisionRemoveTimePowerDown;
	int nightVisionRemoveTimeFadeInStart;
	int fuseTime;
	int aiFuseTime;
	int lockOnRadius;
	int lockOnSpeed;
	bool requireLockonToFire;
	bool noAdsWhenMagEmpty;
	bool avoidDropCleanup;
	unsigned int stackFire;
	float stackFireSpread;
	float stackFireAccuracyDecay;
	const char *stackSound;
	float autoAimRange;
	float aimAssistRange;
	bool mountableWeapon;
	float aimPadding;
	float enemyCrosshairRange;
	bool crosshairColorChange;
	float moveSpeedScale;
	float adsMoveSpeedScale;
	float sprintDurationScale;
	weapOverlayReticle_t adsOverlayReticle;
	weapOverlayInterface_t adsOverlayInterface;
	float overlayWidth;
	float overlayHeight;
	float fAdsBobFactor;
	float fAdsViewBobMult;
	bool bHoldBreathToSteady;
	float fHipSpreadStandMin;
	float fHipSpreadDuckedMin;
	float fHipSpreadProneMin;
	float hipSpreadStandMax;
	float hipSpreadDuckedMax;
	float hipSpreadProneMax;
	float fHipSpreadDecayRate;
	float fHipSpreadFireAdd;
	float fHipSpreadTurnAdd;
	float fHipSpreadMoveAdd;
	float fHipSpreadDuckedDecay;
	float fHipSpreadProneDecay;
	float fHipReticleSidePos;
	float fAdsIdleAmount;
	float fHipIdleAmount;
	float adsIdleSpeed;
	float hipIdleSpeed;
	float fIdleCrouchFactor;
	float fIdleProneFactor;
	float fGunMaxPitch;
	float fGunMaxYaw;
	float swayMaxAngle;
	float swayLerpSpeed;
	float swayPitchScale;
	float swayYawScale;
	float swayHorizScale;
	float swayVertScale;
	float swayShellShockScale;
	float adsSwayMaxAngle;
	float adsSwayLerpSpeed;
	float adsSwayPitchScale;
	float adsSwayYawScale;
	bool sharedAmmo;
	bool bRifleBullet;
	bool armorPiercing;
	bool bAirburstWeapon;
	bool bBoltAction;
	bool bUseAltTagFlash;
	bool bUseAntiLagRewind;
	bool bIsCarriedKillstreakWeapon;
	bool aimDownSight;
	bool bRechamberWhileAds;
	bool bReloadWhileAds;
	float adsViewErrorMin;
	float adsViewErrorMax;
	bool bCookOffHold;
	bool bClipOnly;
	bool bCanUseInVehicle;
	bool bNoDropsOrRaises;
	bool adsFireOnly;
	bool cancelAutoHolsterWhenEmpty;
	bool suppressAmmoReserveDisplay;
	bool laserSight;
	bool laserSightDuringNightvision;
	bool bHideThirdPerson;
	bool bHasBayonet;
	bool bDualWield;
	bool bExplodeOnGround;
	bool bThrowBack;
	bool bRetrievable;
	bool bDieOnRespawn;
	bool bNoThirdPersonDropsOrRaises;
	bool bContinuousFire;
	bool bNoPing;
	bool bForceBounce;
	bool bUseDroppedModelAsStowed;
	bool bNoQuickDropWhenEmpty;
	bool bKeepCrosshairWhenADS;
	bool bUseOnlyAltWeaoponHideTagsInAltMode;
	bool bAltWeaponAdsOnly;
	bool bAltWeaponDisableSwitching;
	int *killIcon;
	weaponIconRatioType_t killIconRatio;
	bool flipKillIcon;
	bool bNoPartialReload;
	bool bSegmentedReload;
	bool bNoADSAutoReload;
	int iReloadAmmoAdd;
	int iReloadStartAdd;
	const char *szSpawnedGrenadeWeaponName;
	const char *szDualWieldWeaponName;
	unsigned int dualWieldWeaponIndex;
	int iDropAmmoMin;
	int iDropAmmoMax;
	int iDropClipAmmoMin;
	int iDropClipAmmoMax;
	int iShotsBeforeRechamber;
	bool blocksProne;
	bool bShowIndicator;
	int isRollingGrenade;
	int useBallisticPrediction;
	int isValuable;
	int isTacticalInsertion;
	bool isReviveWeapon;
	bool bUseRigidBodyOnVehicle;
	int iExplosionRadius;
	int iExplosionRadiusMin;
	int iIndicatorRadius;
	int iExplosionInnerDamage;
	int iExplosionOuterDamage;
	float damageConeAngle;
	int iProjectileSpeed;
	int iProjectileSpeedUp;
	int iProjectileSpeedRelativeUp;
	int iProjectileSpeedForward;
	float fProjectileTakeParentVelocity;
	int iProjectileActivateDist;
	float projLifetime;
	float timeToAccelerate;
	float projectileCurvature;
	int *projectileModel;
	weapProjExposion_t projExplosion;
	ProjectileExplosionEffect projExplosionEffect[5];
	int * projDudEffect;
	const char *projExplosionSound;
	const char *projDudSound;
	const char *mortarShellSound;
	const char *tankShellSound;
	bool bProjImpactExplode;
	bool bProjSentientImpactExplode;
	bool bProjExplodeWhenStationary;
	bool bBulletImpactExplode;
	WeapStickinessType stickiness;
	WeapRotateType rotateType;
	bool plantable;
	bool hasDetonator;
	bool timedDetonation;
	bool noCrumpleMissile;
	bool rotate;
	bool keepRolling;
	bool holdButtonToThrow;
	bool offhandHoldIsCancelable;
	bool freezeMovementWhenFiring;
	float lowAmmoWarningThreshold;
	bool bDisallowAtMatchStart;
	float meleeChargeRange;
	bool bUseAsMelee;
	bool isCameraSensor;
	bool isAcousticSensor;
	bool isLaserSensor;
	bool isHoldUseGrenade;
	float *parallelBounce;
	float *perpendicularBounce;
	int * projTrailEffect;
	Vector3 vProjectileColor;
	guidedMissileType_t guidedMissileType;
	float maxSteeringAccel;
	int projIgnitionDelay;
	int projIgnitionEffect;
	const char *projIgnitionSound;
	float fAdsAimPitch;
	float fAdsCrosshairInFrac;
	float fAdsCrosshairOutFrac;
	int adsGunKickReducedKickBullets;
	float adsGunKickReducedKickPercent;
	float fAdsGunKickPitchMin;
	float fAdsGunKickPitchMax;
	float fAdsGunKickYawMin;
	float fAdsGunKickYawMax;
	float fAdsGunKickAccel;
	float fAdsGunKickSpeedMax;
	float fAdsGunKickSpeedDecay;
	float fAdsGunKickStaticDecay;
	float fAdsViewKickPitchMin;
	float fAdsViewKickPitchMax;
	float fAdsViewKickMinMagnitude;
	float fAdsViewKickYawMin;
	float fAdsViewKickYawMax;
	float fAdsRecoilReductionRate;
	float fAdsRecoilReductionLimit;
	float fAdsRecoilReturnRate;
	float fAdsViewScatterMin;
	float fAdsViewScatterMax;
	float fAdsSpread;
	int hipGunKickReducedKickBullets;
	float hipGunKickReducedKickPercent;
	float fHipGunKickPitchMin;
	float fHipGunKickPitchMax;
	float fHipGunKickYawMin;
	float fHipGunKickYawMax;
	float fHipGunKickAccel;
	float fHipGunKickSpeedMax;
	float fHipGunKickSpeedDecay;
	float fHipGunKickStaticDecay;
	float fHipViewKickPitchMin;
	float fHipViewKickPitchMax;
	float fHipViewKickMinMagnitude;
	float fHipViewKickYawMin;
	float fHipViewKickYawMax;
	float fHipViewScatterMin;
	float fHipViewScatterMax;
	float fAdsViewKickCenterDuckedScale;
	float fAdsViewKickCenterProneScale;
	float fAntiQuickScopeTime;
	float fAntiQuickScopeScale;
	float fAntiQuickScopeSpreadMultiplier;
	float fAntiQuickScopeSpreadMax;
	float fAntiQuickScopeSwayFactor;
	float fightDist;
	float maxDist;
	const char * aiVsAiAccuracyGraphName;
	const char * aiVsPlayerAccuracyGraphName;
	Vector2 * aiVsAiAccuracyGraphKnots;
	Vector2 * aiVsPlayerAccuracyGraphKnots;
	Vector2 * aiVsAiOriginalAccuracyGraphKnots;
	Vector2 * aiVsPlayerOriginalAccuracyGraphKnots;
	int aiVsAiAccuracyGraphKnotCount;
	int aiVsPlayerAccuracyGraphKnotCount;
	int aiVsAiOriginalAccuracyGraphKnotCount;
	int aiVsPlayerOriginalAccuracyGraphKnotCount;
	int iPositionReloadTransTime;
	float leftArc;
	float rightArc;
	float topArc;
	float bottomArc;
	float accuracy;
	float aiSpread;
	float playerSpread;
	float minTurnSpeed[2];
	float maxTurnSpeed[2];
	float pitchConvergenceTime;
	float yawConvergenceTime;
	float suppressTime;
	float maxRange;
	float fAnimHorRotateInc;
	float fPlayerPositionDist;
	const char *szUseHintString;
	const char *dropHintString;
	int iUseHintStringIndex;
	int dropHintStringIndex;
	float horizViewJitter;
	float vertViewJitter;
	float cameraShakeScale;
	int cameraShakeDuration;
	int cameraShakeRadius;
	float explosionCameraShakeScale;
	int explosionCameraShakeDuration;
	int explosionCameraSHakeRadius;
	const char *szScript;
	float destabilizationRateTime;
	float destabilizationCurvatureMax;
	int destabilizeDistance;
	float * locationDamageMultipliers;      //Refer to hitLocation_t
	const char *fireRumble;
	const char *meleeImpactRumble;
	const char *reloadRumble;
	const char *explosionRumble;
	int tracerType;
	int enemyTracerType;
	float adsDofStart;
	float adsDofEnd;
	float hipDofStart;
	float hipDofEnd;
	float scanSpeed;
	float scanAccel;
	int scanPauseTime;
	const char * flameTableFirstPerson;
	const char * flameTableThirdPerson;
	int firstPersonFlameTable;
	int thirdPersonFlameTable;
	int tagFx_preparationEffect;
	int tagFlash_preparationEffect;
	bool doGibbing;
	float maxGibDistance;
	float altScopeADSTransInTime;
	float altScopeADSTransOutTime;
	int iIntroFireTime;
	int iIntroFireLength;
	int meleeSwipeEffect;						//FxEffectDef
	int meleeImpactEffect;						//FxEffectDef
	int meleeImpactNoBloodEffect;
	const char *throwBackType;
	WeaponCamo camo;
	float customFloat[3];
	__declspec(align(4)) bool customBool0;
	__declspec(align(4)) bool customBool1;
	__declspec(align(4)) bool customBool2;
};



struct WeaponAttachment;

struct WeaponVariantDef {

	char * name;
	int iVariantCount;
	WeaponDef *weapDef;
	const char *szDisplayName;
	const char *szAltWeaponName;
	const char *szAttachmentUnique;
	WeaponAttachment *attachments;				//Count = 0x3F
	int *attachmentUniques;			//Count = 0x5F
	const char **szXAnims;					//Count = 0x58
	ScriptString(*hideTags)[0x20];
	int *attachViewModel;					//Count = 8
	int *attachWorldModel;					//Count = 8
	const char **attachViewModelTag;				//Count = 8
	const char **attachWorldModelTag;				//Count = 8
	Vector3 attachViewModelOffset[8];
	Vector3 attachWorldModelOffset[8];
	Vector3 attachViewModelRotation[8];
	Vector3 attachWorldModelRotation[8];
	Vector3 stowedModelOffsets;
	Vector3 stowedModelRotations;
	unsigned int altWeaponIndex;
	int iAttachments;
	bool bIgnoreAttachments;
	int iClipSize;
	int iReloadTime;
	int iReloadEmptyTime;
	int iReloadQuickTime;
	int iReloadQuickEmptyTime;
	int iAdsTransInTime;
	int iAdsTransOutTime;
	int iAltRaiseTime;
	const char *szAmmoDisplayName;
	const char *szAmmoName;
	int iAmmoIndex;
	const char *szClipName;
	int iClipIndex;
	float fAimAssistRangeAds;
	float fAdsSwayHorizScale;
	float fAdsSwayVertScale;
	float fAdsViewKickCenterSpeed;
	float fHipViewKickCenterSpeed;
	float fAdsZoomFov[3];
	float fAdsZoomInFrac;
	float fAdsZoomOutFrac;
	float fOverlayAlphaScale;
	float fOOPosAnimLength[2];
	bool bSilenced;
	bool bDualMag;
	bool bInfraRed;
	bool bTVGuided;
	unsigned int perks[2];
	bool bAntiQuickScope;
	pvoid overlayMaterial;
	pvoid overlayMaterialLowRes;
	pvoid dpadIcon;
	weaponIconRatioType_t dpadIconRatio;
	bool noAmmoOnDpadIcon;
	bool mmsWeapon;
	bool mmsInScope;
	float mmsFOV;
	float mmsAspect;
	float mmsMaxDist;
	Vector3 ikLeftHandIdlePos;
	Vector3 ikLeftHandOffset;
	Vector3 ikLeftHandRotation;
	bool bUsingLeftHandProneIK;
	Vector3 ikLeftHandProneOffset;
	Vector3 ikLeftHandProneRotation;
	Vector3 ikLeftHandUiViewerOffset;
	Vector3 ikLeftHandUiViewerRotation;
};

#pragma endregion
#pragma region trace
struct cplane_s
{
	float normal[3];
	float dist;
	char type;
	char signbits;
	char pad[2];
};
struct cbrushside_t
{
	cplane_s *plane;
	int cflags;
	int sflags;
};
struct __declspec(align(8)) cbrush_t
{
	float mins[3];
	int contents;
	float maxs[3];
	unsigned int numsides;
	cbrushside_t *sides;
	int axial_cflags[2][3];
	int axial_sflags[2][3];
	unsigned int numverts;
	float(*verts)[3];
};
union CollisionAabbTreeIndex
{
	int firstChildIndex;
	int partitionIndex;
};
const struct CollisionAabbTree
{
	float origin[3];
	unsigned __int16 materialIndex;
	unsigned __int16 childCount;
	float halfSize[3];
	CollisionAabbTreeIndex u;
};
union $D1861110FA451E2ECEED4FEED9352BD9
{
	CollisionAabbTree *tree;
	cbrush_t *brush;
};
struct col_prim_t
{
	int type;
	$D1861110FA451E2ECEED4FEED9352BD9 ___u1;
};
struct IgnoreEntParams
{
	int baseEntity;
	int parentEntity;
	bool ignoreSelf;
	bool ignoreParent;
	bool ignoreSiblings;
	bool ignoreChildren;
};
struct col_context_t
{
	int mask;
	col_prim_t *prims;
	int nprims;
	IgnoreEntParams *ignoreEntParams;
	int passEntityNum0;
	int passEntityNum1;
	int staticmodels;
	int locational;
	char *priorityMap;
	int(__cdecl *collide_entity_func)(int, col_context_t *);
};
union PackedUnitVec
{
	unsigned int packed;
	char array[4];
};
union float4
{
	float v[4];
	unsigned int u[4];
	PackedUnitVec unitVec[4];
};
struct hybrid_vector
{
	float4 vec;
};
struct cStaticModelWritable
{
	unsigned __int16 nextModelInWorldSector;
};
struct XModel
{
	const char *name;
	char numBones;
	char numRootBones;
	char numsurfs;
	char lodRampType;
};
struct cStaticModel_s
{
	cStaticModelWritable writable;
	XModel *xmodel;
	float origin[3];
	float invScaledAxis[3][3];
	float absmin[3];
	float absmax[3];
};

enum TraceHitType
{
	TRACE_HITTYPE_NONE = 0x0,
	TRACE_HITTYPE_ENTITY = 0x1,
	TRACE_HITTYPE_DYNENT_MODEL = 0x2,
	TRACE_HITTYPE_DYNENT_BRUSH = 0x3,
	TRACE_HITTYPE_GLASS = 0x4,
};


struct trace_t
{
	Vector3 normal;  // padd 4
	int Unknownwnwerelrelr;
	float fraction;
	int sflags;
	int cflags;
	TraceHitType hitType;
	uint16_t hitId;
	uint16_t modelIndex;
	uint16_t partName;
	uint16_t boneIndex;
	uint16_t partGroup;
	bool allsolid;
	bool startsolid;
	bool walkable;
	pvoid staticModel;
	int hitPartition;
};
#pragma endregion
#pragma region bullet shit
struct BulletFireParams
{
	int weaponEntIndex;
	int ignoreEntIndex;
	float damageMultiplier;
	int methodOfDeath;
	Vector3 origStart;
	Vector3 start;
	Vector3 end;
	Vector3 dir;
};

struct BulletTraceResults1
{
	trace_t trace;
	int* hitEnt; // gentity_s*
	float hitPos[3];
	int ignoreHitEnt;
	int hitSurfaceType;
};

struct BulletTraceResults2
{
	trace_t trace;//0x00
	int* hitEnt;//0x40
	float hitPos[3];//0x44
	bool ignoreHitEnt;//0x50
	char unk0[0x03];//0x54
	int hitSurfaceType;//0x57
	char unk1[0x08];//0x5A
					//0x63
};




//struct BulletTraceResults
//{
//	trace_t trace;
//	int hitEnt;
//	Vector3 hitPos;
//	bool ignoreHitEnt;
//	int depthSurfaceType; //0x4C
//	char _0x50[0x4]; //0x50
//	int hitSurfaceType; //0x54
//};

typedef struct asset
{
	unsigned char Weaponized_asset[87425];
};

extern asset bott;

#pragma endregion
#define dc (*(UiContext*)(0x1C1DA90))
#define gentity ((gentity_s*)(0x16B9F20))
#define cg (*(cg_s**)(0xE22F18))
#define cga (*(cg_sa**)(0xE22F18))
#define cgst (*(cg_st**)(0xE22F18))
#define cactive (*(clientactive_s**)(0xD689D8))
#define cactive3 (*(clientactive_tt**)(0xD689D8))

#define centity (*(centity_s**)(0xE22F20))
#define centityt (*(centity_t**)(0xE22F20))
#define centityent (*(centity_sent**)(0xE22F20))




#define min(a,b)(((a) < (b)) ? (a) : (b))
//Structures:

/* dvar->flags */
#define DVAR_ARCHIVE  (1 << 0) // 0x0001
#define DVAR_USERINFO  (1 << 1) // 0x0002
#define DVAR_SERVERINFO  (1 << 2) // 0x0004
#define DVAR_SYSTEMINFO  (1 << 3) // 0x0008
#define DVAR_INIT  (1 << 4) // 0x0010
#define DVAR_LATCH  (1 << 5) // 0x0020
#define DVAR_ROM  (1 << 6) // 0x0040
#define DVAR_CHEAT  (1 << 7) // 0x0080
#define DVAR_DEVELOPER  (1 << 8) // 0x0100
#define DVAR_SAVED  (1 << 9) // 0x0200
#define DVAR_NORESTART  (1 << 10) // 0x0400
#define DVAR_CHANGEABLE_RESET (1 << 12) // 0x1000
#define DVAR_EXTERNAL  (1 << 14) // 0x4000
#define DVAR_AUTOEXEC  (1 << 15) // 0x8000

/* Match Talk Flags */
#define TALK_EVERYONE_H_EVERYONE		(1<<0)
#define TALK_DEAD_CHAT_WITH_DEAD		(1<<1)
#define TALK_DEAD_CHAT_WITH_TEAM		(1<<2)
#define TALK_DEAD_H_TEAM_LIVING			(1<<3)
#define TALK_DEAD_H_ALL_LIVING			(1<<4)
#define TALK_DEAD_HEAR_KILLER			(1<<5)
#define TALK_KILERS_HEAR_VICTIM			(1<<6)

/* Archived UI Visibility Flags */
#define ARCHIVED_RADAR_ALLIES				(1<<2)
#define ARCHIVED_RADAR_AXIS					(1<<3)
#define ARCHIVED_BOMB_TIMER					(1<<5)
#define ARCHIVED_BOMB_TIMER_A				(1<<6)
#define ARCHIVED_BOMB_TIMER_B				(1<<7)
#define ARCHIVED_AMMOCOUNTERHIDE			(1<<8)
#define ARCHIVED_OVERTIME					(1<<14)

/* Unarchived UI Visibility Flags */
#define UNARCHIVED_FINAL_KILLCAM			(1<<0)
#define UNARCHIVED_ROUND_END_KILLCAM		(1<<1)
#define UNARCHIVED_ENABLE_POPUPS			(1<<4)
#define UNARCHIVED_HUD_HARDCORE				(1<<9)
#define UNARCHIVED_PREGAME					(1<<10)
#define UNARCHIVED_DRAWSPECTATORMESSAGES	(1<<11)
#define UNARCHIVED_DISABLEINGAMEMENU		(1<<12)
#define UNARCHIVED_GAME_ENDED				(1<<13)

typedef float vec_t;
typedef vec_t vec2_t[2];
typedef vec_t vec3_t[3];
typedef vec_t vec4_t[4];
typedef vec_t vec5_t[5];


struct Vector4
{
    union
    {
        struct
        {
            float x, y, z;
        };
        struct
        {
			float pitch, yaw, roll;
        };
    };
	float w;
	Vector4();
	Vector4(float x, float y, float z, float a);
};

template<int BIT_COUNT>
struct bitarray
{
	int array[(BIT_COUNT + 31) / 32];

	void setBit(unsigned int pos)
	{
		if (pos < BIT_COUNT)
		{
			array[pos / 32] |= 0x80000000 >> (pos % 32);
		}
	}

	bool testBit(unsigned int pos)
	{
		if (pos < BIT_COUNT)
		{
			return (array[pos / 32] & (0x80000000 >> (pos % 32))) != 0;
		}
		return false;
	}

	void resetBit(unsigned int pos)
	{
		if (pos < BIT_COUNT)
		{
			array[pos / 32] &= ~(0x80000000 >> (pos % 32));
		}
	}
};

enum Addresses {
	centity_t_a = 0xE22F20,
	centity_t_size = 0x374,
	cg_t_a = 0xE22F18,
	cg_t_size = 0x87A00, //localClients Only
	clientActive_t_a = 0xD689D8,
	scrPlaceView_a = 0xFB9DE0,
	playerstate_a = 0x3780EA28,
	aimRatio_a = 0x3780EC08,

	CG_GetPlayerViewOrigin_a = 0xEC748,
	CG_DobjGetWorldTagMatrix_a = 0x4C188,
	Com_GetClientDObj_a = 0x3275C0,
	SL_GetString_a = 0x48ED68,
	vectoangles_a = 0x3CAB90,
	CG_DobjGetWorldTagPos_a = 0x52ABC,
	AimTarget_GetTagPos_a = 0x015708,
	WorldPosToScreenPos_a = 0x5A480,
	AimTarget_IsTargetVisible_a = 0x15988,
	BG_GetSurfacePenetrationDepth_a = 0x5EFFC0,
	BG_AdvanceTrace_a = 0x5EFE18,
	FireBulletPenetrate_a = 0x0EAC28,
	Trace_GetEntityHitID_a = 0x306CC0,
	BulletTrace_a = 0xE9FBC,
	BG_GetWeaponDef_a = 0x606F08,
	BG_GetSpreadForWeapon_a = 0x5F09C8,
	BG_SeedRandWithGameTime_a = 0x5D6C54,
	CG_BulletEndPosition_a = 0xEBB48,
	CL_SetViewAngles_a = 0x10B978,
	Com_SessionMode_IsMode_a = 0x0319ECC,
	NoRecoil_a = 0xF9E54,
	RedBoxes_a = 0x783E0,
	toggleLaser_a = 0xEF68C,
	wallHack_a = 0x834D0,
	RedBoxes1_a = 0x78604,
	VSAT_a = 0x33C60,
	forceHost_a = 0x1CCF4D8,
	compassMaxRange = 0x01cc9d78,
	propsizes = 0x004E2A0,
	lsdshit = 0x00946a0c,
	skycolor = 0x00d7f530,
	crazysway = 0x00946a24,
	r_skyRotation = 0x01cc1798,
};
//nop  00893744 00893750 0089375C 
enum dvarType_t {
	DVAR_TYPE_INVALID = 0x0,
	DVAR_TYPE_BOOL = 0x1,
	DVAR_TYPE_FLOAT = 0x2,
	DVAR_TYPE_FLOAT_2 = 0x3,
	DVAR_TYPE_FLOAT_3 = 0x4,
	DVAR_TYPE_FLOAT_4 = 0x5,
	DVAR_TYPE_INT = 0x6,
	DVAR_TYPE_ENUM = 0x7,
	DVAR_TYPE_STRING = 0x8,
	DVAR_TYPE_COLOR = 0x9,
	DVAR_TYPE_INT64 = 0xA,
	DVAR_TYPE_LINEAR_COLOR_RGB = 0xB,
	DVAR_TYPE_COLOR_XYZ = 0xC,
	DVAR_TYPE_COUNT = 0xD,
};

enum eSessionModes_mode
{
	SESSIONMODE_OFFLINE = 0x0,
	SESSIONMODE_SYSTEMLINK = 0x1,
	SESSIONMODE_ONLINE = 0x2,
	SESSIONMODE_LOCAL = 0x3,
	SESSIONMODE_ZOMBIES = 0x4,
	SESSIONMODE_MAX = 0x5,
	SESSIONMODE_INVALID = 0x6,
};

enum entityType__t
{
	ET_GENERAL = 0x0,
	ET_PLAYER = 0x1,
	ET_PLAYER_CORPSE = 0x2,
	ET_ITEM = 0x3,
	ET_MISSILE = 0x4,
	ET_INVISIBLE = 0x5,
	ET_SCRIPTMOVER = 0x6,
	ET_SOUND_BLEND = 0x7,
	ET__FX = 0x8,
	ET_LOOP_FX = 0x9,
	ET_PRIMARY_LIGHT = 0xA,
	ET_TURRET = 0xB,
	ET_HELICOPTER = 0xC,
	ET_PLANE = 0xD,
	ET_VEHICLE = 0xE,
	ET_VEHICLE_CORPSE = 0xF,
	ET_ACTOR = 0x10,
	ET_ACTOR_SPAWNER = 0x11,
	ET_ACTOR_CORPSE = 0x12,
	ET_STREAMER_HINT = 0x13,
	ET_ZBARRIER = 0x14,
	ET_EVENTS = 0x15,
	ET_DEADBODY = 65536,
};

enum entityFlags_t
{
	FL_GODMODE = 0x1,
	FL_DEMI_GODMODE = 0x2,
	FL_NOTARGET = 0x4,
	FL_NO_KNOCKBACK = 0x8,
	FL_DROPPED_ITEM = 0x10,
	FL_NO_BOTS = 0x20,
	FL_NO_HUMANS = 0x40,
	FL_TOGGLE = 0x80,
	FL_SOFTACTIVATE = 0x100,
	FL_LOW_PRIORITY_USEABLE = 0x200,
	FL_NO_TACTICAL_INSERTION = 0x400,
	FL_DYNAMICPATH = 0x800,
	FL_SUPPORTS_LINKTO = 0x1000,
	FL_NO_AUTO_ANIM_UPDATE = 0x2000,
	FL_GRENADE_TOUCH_DAMAGE = 0x4000,
	FL_GRENADE_MARTYRDOM = 0x8000,
	FL_MISSILE_DESTABILIZED = 0x10000,
	FL_STABLE_MISSILES = 0x20000,
	FL_REPEAT_ANIM_UPDATE = 0x40000,
	FL_VEHICLE_TARGET = 0x80000,
	FL_GROUND_ENT = 0x100000,
	FL_CURSOR_HINT = 0x200000,
	FL_USE_TURRET = 0x400000,
	FL_MISSILE_ATTRACTOR = 0x800000,
	FL_TARGET = 0x1000000,
	FL_WEAPON_BEING_GRABBED = 0x2000000,
	FL_OBSTACLE = 0x4000000,
	FL_DODGE_LEFT = 0x8000000,
	FL_DODGE_RIGHT = 0x10000000,
	FL_BADPLACE_VOLUME = 0x20000000,
	FL_AUTO_BLOCKPATHS = 0x40000000,
	FL_MOVER_SLIDE = 0x80000000,
};

#pragma region local ui
#define isValid(str) (strcmp(str, ""))

enum uiType_t : int
{
	UI_TYPE_NONE,
	UI_TYPE_TEXT,
	UI_TYPE_MATERIAL,
};


struct rectDef_s
{
	float x;
	float y;
	float w;
	float h;
	int horzAlign;
	int vertAlign;
};

struct localui_s
{
	uiType_t type;
	float x;
	float y;
	float width;
	float height;
	float angle;
	float fontScale;
	color color;
	char text[0x30];
	char font[0x30];
	char material[0x30];
	alignment align;
};

struct ScreenPlacement
{
	vec2_t scaleVirtualToReal;
	vec2_t scaleVirtualToFull;
	vec2_t scaleRealToVirtual;
	vec2_t virtualViewableMin;
	vec2_t virtualViewableMax;
	vec2_t virtualTweakableMin;
	vec2_t virtualTweakableMax;
	vec2_t realViewportBase;
	vec2_t realViewportSize;
	vec2_t realViewportMid;
	vec2_t realViewableMin;
	vec2_t realViewableMax;
	vec2_t realTweakableMin;
	vec2_t realTweakableMax;
	vec2_t subScreen;
	float hudSplitscreenScale;
};

union DvarLimits {
	struct {
		int stringCount;
		const char** strings;
	} enumeration;

	struct {
		int min;
		int _max;
	} integer;

	struct {
		float min;
		float _max;
	} value, vector_;

	struct {
		int64_t min;
		int64_t _max;
	} integer64;
};

union DvarValue {
	bool enabled;
	int integer;
	unsigned int unsignedInt;
	int64_t integer64;
	int64_t unsignedInt64;
	float value;
	float vectorv[4];
	const char* string;
	char color[4];
};

struct dvar_t {
	const char* name;
	const char* description;
	int hash;
	unsigned int flags;
	dvarType_t type;
	bool modified;
	DvarValue current;
	DvarValue latched;
	DvarValue reset;
	DvarLimits domain;
	dvar_t* hashNext;
	int unknown3;
};


struct GfxCmdHeader {
	unsigned short byteCount;
	char id;
	char ui3d;
};

union GfxColor {
	unsigned int packed;
	char array[4];
};

struct GfxCmdDrawText2D {
	GfxCmdHeader header;
	int type;
	float x;
	float y;
	float w;
	float h;
	float rotation;
	void* font;
	float xScale;
	float yScale;
	GfxColor color;
	signed int maxChars;
	int renderFlags;
	int cursorPos;
	char cursorLetter;
	GfxColor glowForceColor;
	int fxBirthTime;
	int fxLetterTime;
	int fxDecayStartTime;
	int fxDecayDuration;
	int fxRedactDecayStartTime;
	int fxRedactDecayDuration;
	void* fxMaterial;
	void* fxMaterialGlow;
	float padding;
	char text[3];
};


struct GfxCmdStretchPic {
	GfxCmdHeader header;
	void* material;
	float x;
	float y;
	float w0;
	float w;
	float h;
	float s0;
	float t0;
	float s1;
	float t1;
	GfxColor color;
};

#define GLOBAL_CGAME_PTR_ADDR	0x00F56B78 // 1.04
#define GLOBAL_CLIENT_PTR_ADDR	0x00F56B74 // 1.04

typedef struct RefDef_t2//1.02
{
	int Width; //0x0000 
	int Height; //0x0004 
	char _0x0008[100];
	float Fov[2]; //0x006C 
	char _0x0078[8];
	float ViewOrigin[3]; //0x007C 
	char _0x0088[16];
	float ViewAxis[3]; //0x0048 
	char _0x00BC[728];
	float ViewOrigin1[3]; //0x0394 
	char _0x03A0[160];
} RefDef_t2;


typedef struct wrefdef//1.02
{
	int width; //0x0000 
	int height; //0x0004 
	char _0x0008[100];
	float Fov[2]; //0x006C 
	char _0x0078[8];
	float ViewOrigin[3]; //0x007C 
	char _0x0088[16];
	float ViewAxis[3]; //0x0048 
	char _0x00BC[728];
	float ViewOrigin1[3]; //0x0394 
	char _0x03A0[160];
} wrefdef;

typedef struct {
	char name[20];
} cliName;

typedef struct {
	char padding000[0x2B4]; // 0x0
	char identifierThing01; // 0x2B1
	char identifierThing02; // 0x2B2
	char identifierThing03; // 0x2B3
	char identifierThing04; // 0x2B4
							// 0x2B8
} WeaponInfoThing;

typedef struct {
	char padding000[0xC]; // 0x0
	char name[0x20]; // 0xC
	int team; // 0x2C
	char padding001[0x7D8]; // 0x30
							// 0x808
} ClientInfor;

typedef struct cg_ss {
	int servertime; //0x0000 
	int playerstate; //0x0004 
	int staminatimer; //0x0008 
	unsigned short playerstance; //0x000C 
	char _pad[10];
	int velocity; //0x0018 
	float Origin[3]; //0x001C 
	float Velocity[3]; //0x0028 
	char _pad1[44];
	float refdefViewAngleY; //0x0060 
	float refdefViewAngleX; //0x0064 
	char _pad2[232];
	int clientNum; //0x0150 
	char _pad3[4];
	float viewAngleY; //0x0158 
	float viewAngleX; //0x015C 
	char _pad4[4];
	int playerStanceInt; //0x0164 
	float playerStanceFlt; //0x0168 
	char _pad5[80];
	int MaxEntities; //0x01BC 
	char _pad6[432];
	int WeaponNum; //0x0370 
	unsigned short EquipmentState; //0x0374 2 = inhand
	unsigned short WeaponSwapState; //0x0376 
	float WeaponZoomFlt; //0x0378 
	float MovementSpreadMultiplier; //0x037C 
	char _pad7[4];
	float DefaultSpreadMultiplier; //0x0384 
	int WeaponState; //0x0388 
	char _pad8[352];
	char perkslot3; //0x04EC 
	char _pad9[19];
} cg_ss, *pcg_s1;

extern pcg_s1 cg1;

enum CommandMask {
	CMD_MASK_FIRE = 0x80000000,
	CMD_MASK_AIM = 0x00100080,
};

struct button_t {
	int buttons;
};

struct CCommand {
	int time;
	button_t button_bits;
	char padding[8];
	int viewAngles[3];
	char padding1[36];
};

typedef struct {
	CCommand commands[128]; // 0x0
	int currentIdx; // 0x1E00
} CInput;

typedef struct {
	CCommand commands[128]; // 0x0
	int currentIdx; // 0x1E00
} input_s;


typedef struct {
	char padding000[0x98]; // 0x0
	float origin[3]; // 0x98
	char padding001[0x64]; // 0xA4
	float refViewAngle[2]; // 0x108
	char padding002[0x2B84]; // 0x110
	float viewAngle[2]; // 0x2C94
	char padding003[0x40014]; // 0x2C9C
	CInput input; // 0x42CB0
} Client;

struct clientEntityS {
	char pad[0x02];
	bool Alive;
	char pad2[0x10];
	float Origin[3];
	char pad3[0xAf];
	int Flag;
};

struct GfxSkinCacheEntry
{
	unsigned int frameCount;
	int skinnedCachedOffset;
	unsigned short numSkinnedVerts;
	unsigned short ageCount;
};



struct CEntPlayerInfo
{
	clientControllers_t *control;
	char tag[6];
	float waterHeight;
	int nextWaterHeightCheck;
	int nextRippleTime;
};

struct ShaderConstantSet
{
	vec4_t value[7];
	char constantSource[7];
	char used;
};

struct cpose_t
{
	unsigned short lightingHandle;
	char eType;
	char eTypeUnion;
	char localClientNum;
	char isRagdoll;
	int ragdollHandle;
	int physObjId;
	int physUserBody;
	int killcamRagdollHandle;
	int physUserBodyProneFeet;
	char destructiblePose;
	int startBurnTime;
	float wetness;
	int cullIn;
	vec3_t origin;
	vec3_t angles;
	vec3_t absmin;
	vec3_t absmax;
	GfxSkinCacheEntry skinCacheEntry;
	char __unk1[0x72];
	ShaderConstantSet constantSet;
};

struct trajectory_t
{
	char trType; //0x0
	int trTime; //0x4
	int trDuration; //0x8
	vec3_t trBase; //0xC
	vec3_t trDelta; //0x18
};

struct LerpEntityStatePlayer
{
	float leanf; //0x0
	int movementDir; //0x4
	int moveType; //0x8
	int primaryWeapon; //0xC
	int stowedWeapon; //0x10
	int offhandWeapon; //0x14
	int meleeWeapon; //0x18
	char meleeWeaponCamo; //0x1C
	char meleeWeaponModel; //0x1D
	char vehicleType; //0x1E
	char vehicleAnimBoneIndex; //0x1F
	char vehicleSeat; //0x20
	char stowedWeaponCamo; //0x21
	char weaponHeat; //0x22
	char proneLegsAngle; //0x23
};

struct LerpEntityStateMissile
{
	int launchTime; //0x0
	int parentClientNum; //0x4
	int fuseTime; //0x8
	int forcedDud; //0xC
	int autoDetonateTime; //0x10
};

struct LerpEntityStateAnonymous
{
	int data[8]; //0x0
};

struct LerpEntityStateLoopFx
{
	float cullDist; //0x0
	int period; //0x4
};

struct LerpEntityStateTurret
{
	float gunAngles[3]; //0x0
	int ownerNum; //0xC
	int heatVal; //0x10
	int overheating; //0x14
	int pivotOffset; //0x18
	int flags; //0x1C
};

struct LerpEntityStateVehicle
{
	float steerYaw; //0x0
	float bodyRoll; //0x4
	struct
	{
		short pitch;
		short yaw;
	}gunnerAngles[4]; //0x8
	short throttle; //0x18
	short gunPitch; //0x1A
	short gunYaw; //0x1C
	char targetRotorSpeed; //0x1E
};

struct LerpEntityStateActor
{
	struct
	{
		int actornum;
	}index; //0x0
	int species; //0x4
	int team; //0x8
	int enemy; //0xC
	int freeCameraLockOnAllowed; //0x10
	struct
	{
		short fBodyPitch;
	}proneInfo;//0x14
	short aiType; //0x16
};

struct LerpEntityStateScriptMover
{
	char attachTagIndex[4]; //0x0
	int attachedTagIndex; //0x4
	short attachModelIndex[4]; //0x8
	short animScriptedAnim; //0x10
	short attachedEntNum; //0x12
	int attachedEntTime; //0x14
	short exploderIndex; //0x18
	char unk0[2]; //0x1A
	char flags; //0x1C
	char unk1[1]; //0x1D
	short aiType; //0x1E
};

struct LerpEntityStateZBarrier
{
	int barrierTypeIndex; //0x0
	struct
	{
		char flags;
		char animTime;
	}pieces[6]; //0x4
};



union $9B35D18BE7DE1A49784D3DA3953D5C89
{
	char iHeadIconTeam;
	short teamAndOwnerIndex;
};

union LerpEntityStateTypeUnion
{
	LerpEntityStatePlayer player;
	LerpEntityStateMissile missile;
	LerpEntityStateAnonymous anonymous;
	LerpEntityStateLoopFx loopFx;
	LerpEntityStateTurret turret;
	LerpEntityStateVehicle vehicle;
	LerpEntityStateActor actor;
	LerpEntityStateScriptMover scriptMover;
	LerpEntityStateZBarrier zbarrier;
};

struct LerpEntityState
{
	int eFlags; //0x0
	int eFlags2; //0x4
	trajectory_t pos;//0x8
	trajectory_t apos;//0x2C
	LerpEntityStateTypeUnion u; //0x50
	short useCount; //0x74
	union
	{
		char iHeadIconTeam;
		short teamAndOwnerIndex;
	}faction; //0x76
	unsigned int clientFields; //0x78
};

struct renderOptions_s
{
	unsigned int s;
};

struct actorAnimState_t
{
	short state;
	char subState;
	float fLeanAmount;
	float fAimUpDown;
	float fAimLeftRight;
};

union $8A55D3BB0C758A956A56F8E75035F352
{
	int hintString;
	int vehicleXModel;
	unsigned int secondBcAlias;
	unsigned int soundTag;
};

struct clientLinkInfo_t
{
	short parentEnt;
	char tagIndex;
	char flags;
};

union $32A75A724673AB33BA2D603F67D50EA7
{
	short brushmodel;
	short xmodel;
	short primaryLight;
	unsigned short bone1;
};

struct $190F2CF944EC18EE3AF27F473C4F9DBE
{
	unsigned int weaponIdx : 8;
	unsigned int attachment1 : 6;
	unsigned int attachment2 : 6;
	unsigned int attachment3 : 6;
	unsigned int padding : 6;
};

union Weapon
{
	$190F2CF944EC18EE3AF27F473C4F9DBE __s0;
	unsigned int weaponData;
};

union $5941A7488DBCD59DA5C855EBC8EBAB48
{
	char scale;
	char eventParm2;
	char helicopterStage;
	char destructibleid;
	char zombieShrinkOn;
};

struct entityState_s
{
	int number; //0x0
	LerpEntityState lerp; //0x4
	int time2; //0x80
	int loopSoundId; //0x84
	int solid; //0x88
	int renderOptions; //0x8C
	union
	{
		struct
		{
			int legsAnim; //0x90
			int torsoAnim; //0x94
			float fTorsoPitch; //0x98
			float fWaistPitch; //0x9C
		}anim;
		struct
		{
			char fov; //0x90
			char treeId; //0x91
			char animId; //0x92
		}moverState;
		struct
		{
			short flags; //0x90
			char vehicleDefIndex; //0x92
			char treeId; //0x93
			short animId; //0x94
			short attachModelIndex[2]; //0x96
			char attachTagIndex[2]; //0x9A
		}vehicleState;
		struct
		{
			short state; //0x90
			char subState; //0x92
			float fLeanAmount; //0x94
			float fAimUpDown; //0x98
			float fAimLeftRight; //0x9C
		}animState;
	}un2; //0x90
	union
	{
		char unk0[4]; //0xA0
	}un3; //0xA0
	int partBits[5]; //0xA4
	int clientLinkInfo; //0xB8
	char unk1[4]; //0xBC
	char events[4]; //0xC0
	int eventParms[4]; //0xC4
	unsigned int eventParm; //0xD4
	short eType; //0xD8
	short groundEntityNum; //0xDA
	union
	{
		char unk2[2]; //0xDC
	}index; //0xDC
	short otherEntityNum; //0xDE
	short attackerEntityNum; //0xE0
	short enemyModel; //0xE2
	int weapon; //0xE4
	int lastStandPrevWeapon; //0xE8
	unsigned short targetname; //0xEC
	short loopSoundFade; //0xEE
	short eventSequence; //0xF0
	char surfType; //0xF2
	char clientNum; //0xF3
	char iHeadIcon; //0xF4
	char weaponModel; //0xF5
	union
	{
		char hintString; //0xF6
		char helicopterStage; //0xF6
		char eventParm2; //0xF6
	}un1; // 0xF6
};

struct centity_t
{
	cpose_t pose;
	LerpEntityState prevState;
	entityState_s nextState;
	short previousEventSequence;
	int miscTime;
	int lastMuzzleFlash;
	int numShotsFiredLast;
	unsigned short attachModelNames[2];
	unsigned short attachTagNames[2];
	int *tree;
	int *destructible;
	int *nitrousVeh;
	int *linkInfo;
	int *vehicle;
	int *clientTagCache;
	int *aimTargetInfo;
	int *cScriptMover;
	int *scripted;
	int *zbarrier;
	int *droppedWeaponDobjInfo;
	int nextSlideFX;
	unsigned short flagIndex;
	unsigned short flagState;
	pvoid *compassMaterial;
	int lastTrailTime;
	unsigned int fxTrailHandle;
	unsigned int fxProjExplosion;
	unsigned int fxHeartbeat;
	unsigned int fxLaserSight;
	vec3_t oldLinkOrigin;
	vec3_t originError;
	vec3_t anglesError;
	char tracerDrawRateCounter;
	centity_t *updateDelayedNext;
	unsigned short classname;
	unsigned int stepSound;
	char footstepSurfaceOverride;
	char deployedRiotshieldHits[8];
	union {
		unsigned int packed_bits[2];
		char bits[8];
		struct {
			int cState1;
			int cState2;
		};
	} pBits;
};

enum objectiveState_t
{
	OBJST_EMPTY = 0x0,
	OBJST_ACTIVE = 0x1,
	OBJST_INVISIBLE = 0x2,
	OBJST_DONE = 0x3,
	OBJST_CURRENT = 0x4,
	OBJST_FAILED = 0x5,
	OBJST_NUMSTATES = 0x6,
};

struct objective_t
{
	objectiveState_t state; //0x0
	vec3_t origin; //0x4
	short entNum; //0x10
	vec2_t size; //0x14
	int icon; //0x1C
	short ownerNum; //0x20
	unsigned short name; //0x22
	short teamMask; //0x24
	char progress; //0x26
	int clientUseMask[1]; //0x28
	char gamemodeFlags; //0x2C
	char flags; //0x2D
	char teamNum; //0x2E
};

struct PlayerVehicleState
{
	vec3_t origin;//0
	vec3_t angles;//0xC
	vec3_t velocity;//0x18
	vec3_t angVelocity;//0x24
	vec2_t tilt;//0x30
	vec2_t tiltVelocity;//0x38
	float targetHeightDelta;//0x40
	float lastGroundHeight;//0x44
	int entity;//0x48
	int flags;//0x4C
	bool fullPhysics; //0x50
};

struct SprintState
{
	int sprintButtonUpRequired;//0x0
	int sprintDelay;//0x4
	int lastSprintStart;//0x8
	int lastSprintEnd;//0xC
	int sprintStartMaxLength;//0x10
	int sprintDuration;//0x14
	int sprintCooldown;//0x18
};

struct MantleState
{
	float yaw; //0x0
	int timer; //0x4
	int transIndex; //0x8
	int flags; //0xC
};


struct playerState_s
{
	int commandTime;//0x0
	int pm_type;//0x4
	int bobCycle; //0x8
	int pm_flags; //0xC
	long long weapFlags;//0x10
	int otherFlags;//0x18
	int pm_time;//0x1C
	short ownerNum;//0x20
	short name;//0x22
	char progress;//0x24
	vec3_t origin;//0x28
	vec3_t velocity;//0x34
	int remoteEyesEnt;//0x40
	int remoteEyesTagname;//0x44
	int remoteControlEnt;//0x48
	int weaponTime;//0x4C
	int weaponDelay;//0x50
	int weaponTimeLeft;//0x54
	int weaponDelayLeft;//0x58
	int weaponIdleTime;//0x5C
	int grenadeTimeLeft;//0x60
	int throwBackGrenadeOwner;//0x64
	int throwBackGrenadeTimeLeft;//0x68
	int weaponRestrictKickTime;//0x6C
	bool mountAvailable;//0x70
	bool bRunLeftGun;//0x71
	bool bCarryingTurret;//0x72
	float mountPos[3];//0x74
	float mountDir;//0x80
	bool bThirdPerson;//0x84
	int foliageSoundTime;//0x88
	int gravity;//0x8C
	float leanf;//0x90
	int speed;//0x94
	float delta_angles[3];//0x98
	int groundEntityNum;//0xA4
	int moverEntityNum;//0xA8
	int moverTimestamp;//0xAC
	int groundType;//0xB0
	float vLadderVec[3];//0xB4
	int jumpTime;//0xC0
	float jumpOriginZ;//0xC4
	int slideTime;//0xC8
	int moveType;//0xCC
	int legsTimer;//0xD0
	int torsoTimer;//0xD4
	short legsAnim;//0xD8
	short torsoAnim;//0xDA
	int legsAnimDuration;//0xDC
	int torsoAnimDuration;//0xE0
	int damageTimer;//0xE4
	int damageDuration;//0xE8
	int dmgDirection;//0xEC
	int dmgType;//0xF0
	int corpseIndex;//0xF4
	int movementDir;//0xF8
	int eFlags;//0xFC
	int eFlags2;//0x100
	PlayerVehicleState vehicleState;//0x104
	short predictableEventSequence;//0x158
	short predictableEventSequenceOld;//0x15A
	int predictableEvents[4];//0x15C
	int predictableEventParms[4];//0x16C
	short unpredictableEventSequence; //0x17C
	short oldUnpredictableEventSequence;//0x17E
	int unpredictableEvents[4];//0x180
	int unpredictableEventParms[4];//0x190
	int clientNum;//0x1A0
	int offHandWeapon;//0x1A4
	int offhandSecondary;//0x1A8
	int offhandPrimary;//0x1AC
	int renderOptions;//0x1B0
	int momentum;//0x1B4
	int weapon;//0x1B8
	unsigned int lastStandPrevWeapon;//0x1BC
	int lastWeaponAltModeSwitch;//0x1C0
	int stowedWeapon;//0x1C4
	char unusedCompatibilityPadding;//0x1C8
	unsigned int meleeWeapon;//0x1CC
	int weaponstate;//0x1D0
	int weaponstateLeft;//0x1D4
	unsigned int weaponShotCount;//0x1D8
	unsigned int weaponShotCountLeft;//0x1DC
	float fWeaponPosFrac;//0x1E0
	int adsDelayTime;//0x1E4
	int spreadOverride;//0x1E8
	int spreadOverrideState;//0x1EC
	int weaponSpinLerp;//0x1F0
	int viewmodelIndex;//0x1F4
	float viewangles[3];//0x1F8
	int viewHeightTarget;//0x204
	float viewHeightCurrent;//0x208
	int viewHeightLerpTime;//0x20C
	int viewHeightLerpTarget;//0x210
	int viewHeightLerpDown;//0x214
	float viewAngleClampBase[2];//0x218
	float viewAngleClampRange[2];//0x220
	int damageEvent;//0x228
	int damageYaw;//0x22C
	int damagePitch;//0x230
	int damageCount;//0x234
	int stats[4];//0x238
	struct
	{
		int weapon;//0x0
		int renderOptions;//0x4
		float heatPercent;//0x8
		int fuelTankTime;//0xC
		int adsZoomSelect;//0x10
		bool overHeating;//0x14
		bool needsRechamber;//0x15
		bool heldBefore;//0x16
		bool quickReload;//0x17
		bool blockWeaponPickup;//0x18
		char model;//0x19
	} heldWeapon[0xF];//0x248
	int ammo[0xF];//0x3EC
	int ammoClip[0xF];//0x428
	float proneDirection;//0x464
	float proneDirectionPitch;//0x468
	float proneTorsoPitch;//0x46C
	int viewlocked;//0x470
	short viewlocked_entNum;//0x474
	int vehiclePos;//0x478
	int vehicleType;//0x47C
	int vehicleAnimBoneIndex;//0x480
	int linkFlags;//0x484
	float linkAngles[3];//0x488
	int cursorHint;//0x494
	int cursorHintString;//0x498
	int cursorHintEntIndex;//0x49C
	int cursorHintWeapon;//0x4A0
	int iCompassPlayerInfo;//0x4A4
	int spyplaneTypeEnabled;//0x4A8
	int satelliteTypeEnabled;//0x4AC
	int locationSelectionInfo;//0x4B0
	int locationSelectionType;//0x4B4
	SprintState sprintState; //0x4B8
	float lastDtpEnd;//0x4D4
	float fTorsoPitch;//0x4D8
	float fWaistPitch;//0x4DC
	float holdBreathScale;//0x4E0
	int holdBreathTimer;//0x4E4
	int chargeShotTimer;//0x4E8
	int chargeShotLevel;//0x4EC
	int shotsFiredFromChamber;//0x4F0
	float quickScopeScale;//0x4F4
	int quickScopeTimer;//0x4F8
	int clientFields;//0x4FC
	int clientFields2;//0x500
	int clientFields3;//0x504
	int entityStateClientFields;//0x508
	float moveSpeedScaleMultiplier;//0x50C
	MantleState mantleState;//0x510
	int vehicleAnimStage;//0x520
	int vehicleEntryPoint;//0x524
	unsigned int scriptedAnim;//0x528
	int scriptedAnimTime;//0x52C
	int meleeChargeEnt;//0x530
	int meleeChargeDist;//0x534
	int meleeChargeTime;//0x538
	int weapLockFlags;//0x53C
	int weapLockedEntnum;//0x540
	unsigned int airburstMarkDistance;//0x544
	unsigned int perks[2];//0x548
	int actionSlotType[4];//0x550
	int actionSlotParam[4];//0x560
	int inventoryWeapon;//0x570
	short wiiumoteAimX;//0x574
	short wiiumoteAimY;//0x576
	char wiiuControllerType;//0x578
	char vehicleDefIndex;//0x579
	int entityEventSequence;//0x57C
	int weapAnim;//0x580
	int weapAnimLeft;//0x584
	float aimSpreadScale;//0x588
	int shellshockIndex;//0x58C
	int shellshockTime;//0x590
	int shellshockDuration;//0x594
	float dofNearStart;//0x598
	float dofNearEnd;//0x59C
	float dofFarStart;//0x5A0
	float dofFarEnd;//0x5A4
	float dofNearBlur;//0x5A8
	float dofFarBlur;//0x5AC
	float dofViewmodelStart;//0x5B0
	float dofViewmodelEnd;//0x5B4
	int waterlevel; //0x5B8
	int smokeColorIndex; //0x5BC
	int hudElemLastAssignedSoundID; //0x5C0
	int adsZoomSelect;//0x5C4
	int adsZoomLatchTime;//0x5C8
	bool adsZoomLatchState;//0x5CC
	int adsPrevZoomSelect;//0x5D0
	int adsPrevZoomSelectTime;//0x5D4
	int artilleryInboundIconLocation;//0x5D8
	float visionSetLerpRatio;//0x5DC
	int poisoned;//0x5E0
	int binocs;//0x5E4
	int scriptCursorHintString; //0x5E8
	objective_t objectives[32]; //0x5EC
	int deltaTime; //0xBEC
	int killCamEntity; //0xBF0
	int killCamTargetEntity; //0xBF4
	int introShotsFired; //0xBF8
	struct
	{
		char current[0xF04]; //0xBFC
		char archival[0xF04]; //0x1B00
	}hud;
	char unk_2A04[0xC]; //0x2A04
};


struct usercmd__s
{
	int serverTime; //0x0
	bitarray<51> buttons; //0x4
	int viewangles[3]; //0xC
	int weapon; // 0x18
	int offHandIndex; //0x1C
	int lastWeaponAltModeSwitch; //0x20
	signed char forwardmove; //0x24
	signed char rightmove; //0x25
	signed char upmove; //0x26
	signed char pitchmove; //0x27
	signed char yawmove; //0x28
	signed char rollmove; //0x29
	char pad[0x12]; //0x2A
};

enum DemoType
{
	DEMO_TYPE_NONE = 0x0,
	DEMO_TYPE_CLIENT = 0x1,
	DEMO_TYPE_SERVER = 0x2,
	DEMO_TYPE_SERVER_SNAPSHOT = 0x3,
};

enum CubemapShot
{
	CUBEMAPSHOT_NONE = 0x0,
	CUBEMAPSHOT_RIGHT = 0x1,
	CUBEMAPSHOT_LEFT = 0x2,
	CUBEMAPSHOT_BACK = 0x3,
	CUBEMAPSHOT_FRONT = 0x4,
	CUBEMAPSHOT_UP = 0x5,
	CUBEMAPSHOT_DOWN = 0x6,
	CUBEMAPSHOT_COUNT = 0x7,
};

enum team_t
{
	TEAM_FREE = 0x0,
	TEAM_BAD = 0x0,
	TEAM_ALLIES = 0x1,
	TEAM_AXIS = 0x2,
	TEAM_THREE = 0x3,
	TEAM_FOUR = 0x4,
	TEAM_FIVE = 0x5,
	TEAM_SIX = 0x6,
	TEAM_SEVEN = 0x7,
	TEAM_EIGHT = 0x8,
	TEAM_NUM_PLAYING_TEAMS = 0x9,
	TEAM_SPECTATOR = 0x9,
	TEAM_NUM_TEAMS = 0xA,
	TEAM_LOCALPLAYERS = 0xB,
	TEAM_FIRST_PLAYING_TEAM = 0x1,
	TEAM_LAST_PLAYING_TEAM = 0x8,
	TEAM_MAX = 0x9,
};

enum ffa_team_t
{
	TEAM_FFA_NONE = 0x0,
	TEAM_FFA_AXIS = 0x1,
	TEAM_FFA_ALLIES = 0x2,
	TEAM_FFA_THREE = 0x3,
};

enum VehicleAnimState
{
	VEHICLEANIMSTATE_IDLE = 0x0,
	VEHICLEANIMSTATE_ENTRY = 0x1,
	VEHICLEANIMSTATE_CHANGEPOS = 0x2,
	VEHICLEANIMSTATE_EXIT = 0x3,
	VEHICLEANIMSTATECOUNT = 0x4,
};


struct netUInt64
{
	unsigned int low;
	unsigned int high;
};

struct ArchivedMatchState
{
	int matchUIVisibilityFlags; //0x0
	int bombTimer[2]; //0x4
	int roundsPlayed; //0xC
	int worldFields[8]; //0x10
};

struct UnarchivedMatchState
{
	int teamScores[TEAM_MAX]; //0x0
	int matchUIVisibilityFlags; //0x24
	int scoreboardColumnTypes[5]; //0x28
	char sideHasMeat; //0x3C
	char initialPlayersConnected; //0x3D
	int talkFlags; //0x40
};

struct MatchState
{
	int index; //0x0
	ArchivedMatchState archivedState; //0x4
	UnarchivedMatchState unarchivedState; //0x34
	unsigned int pad[1]; //0x78
};

struct clientState_s
{
	int clientIndex;
	team_t team;
	ffa_team_t ffaTeam;
	int modelindex;
	int riotShieldNext;
	int attachModelIndex[6];
	int attachTagIndex[6];
	char name[32];
	float maxSprintTimeMultiplier;
	int rank;
	union {
		int prestige;
		int lastDaysPlayed;
	} __u10;
	int lastDamageTime;
	int lastStandStartTime;
	int turnedHumanTime;
	int beingRevived;
	union {
		int64_t xuid;
		netUInt64 xuid64;
	} __u15;
	union {
		int64_t leagueTeamID;
		netUInt64 leagueTeamID64;
	} __u16;
	int leagueDivisionID;
	union {
		int64_t leagueSubdivisionID;
		netUInt64 leagueSubdivisionID64;
	} __u17;
	int leagueSubdivisionRank;
	unsigned int perks[2];
	int voiceConnectivityBits;
	char clanAbbrev[8];
	int attachedVehEntNum;
	int attachedVehSeat;
	int needsRevive;
	int clanAbbrevEV;
	VehicleAnimState vehAnimState;
	score_s score;
	int clientUIVisibilityFlags;
	int offhandWeaponVisible;
};

struct actorState_s
{
	int actorIndex;
	int entityNum;
	int modelindex;
	int attachModelIndex[6];
	int attachTagIndex[6];
	unsigned int attachIgnoreCollision;
	char name[32];
	int animScriptedAnim;
};

struct snapshot_s
{
	int snapFlags;
	int ping;
	int serverTime;
	int physicsTime;
	playerState_s ps;
	int numEntities;
	int numClients;
	int numActors;
	entityState_s entities[512];
	clientState_s clients[18];
	actorState_s actors[32];
	MatchState matchState;
	unsigned __int16 entIndices[512];
	int serverCommandSequence;
};

enum thirdPersonType
{
	TP_OFF = 0x0,
	TP_FOR_MODEL = 0x1,
	TP_FOR_SHADOW = 0x2,
};

struct playerEntity_t
{
	float fLastWeaponPosFrac;
	int bPositionToADS;
	vec3_t vPositionLastOrg;
	float fLastIdleFactor;
	vec3_t baseMoveOrigin;
	vec3_t baseMoveAngles;
};

struct button_t_ {
	int buttons;
	int buttons2;
};
struct usercmd_s_ {
	int serverTime; //0x0 
	button_t_ button_bits; //0x4 
	int angles[3]; //0xC 
	int weapon; // 0x18 
	int offHandWeapon; //0x1C
	int lastWeaponAltModeSwitch; //0x20
	char forwardmove; //0x24 
	char rightmove; //0x25 
	char upmove; //0x26 
	char forwardlook; //0x27 
	char rightlook; //0x28 
	char uplook; //0x29 
	char unk2[0x12]; //0x2A
};
#pragma region gentity / gclient
struct perkBits_s
{
	__int32 bit; //0x0000 
	__int32 bit1; //0x0004 

}; //Size=0x0008
struct ammoPool_s
{
	__int32 count; //0x0000 
}; //Size=0x0004

class gclient_s
{
public:
	__int32 commandTime; //0x0000 
	__int32 pm_type; //0x0004 
	__int32 bobCycle; //0x0008 
	__int32 pm_flags; //0x000C 
	long long weaponflags; //0x0010 
	__int32 otherflags; //0x0018 
	__int32 pm_time; //0x001C 
	__int32 loopsoundid; //0x0020 
	__int32 loopsoundfade; //0x0024 
	vec3_t origin; //0x0028 
	vec3_t velocity; //0x0034 
	char pad_0x0040[0x44]; //0x0040
	__int32 bThirdPerson; //0x0084 
	__int32 foliageSoundTime; //0x0088 
	__int32 gravity; //0x008C 
	float leanf; //0x0090 
	__int32 speed; //0x0094 
	vec3_t delta_angles; //0x0098 
	__int32 groundEntityNum; //0x00A4 
	__int32 moverEntityNum; //0x00A8 
	__int32 moverTimestamp; //0x00AC 
	__int32 groundType; //0x00B0 
	vec3_t LadderVec; //0x00B4 
	__int32 jumpTime; //0x00C0 
	float jumporginZ; //0x00C4 
	char pad_0x00C8[0x34]; //0x00C8
	__int32 eFlags; //0x00FC 
	__int32 eFlags2; //0x0100 
	char pad_0x0104[0x9C]; //0x0104
	__int32 clientNum; //0x01A0 
	__int32 offHandWeapon; //0x01A4 
	__int32 offhandSecondary; //0x01A8 
	__int32 offhandPrimary; //0x01AC 
	char pad_0x01B0[0x8]; //0x01B0
	__int32 weapon; //0x01B8 
	char pad_0x01BC[0x8]; //0x01BC
	__int32 stowedweapon; //0x01C4 
	char pad_0x01C8[0x8]; //0x01C8
	__int32 weaponstate; //0x01D0 
	__int32 weaponstateleft; //0x01D4 
	char pad_0x01D8[0x1C]; //0x01D8
	__int32 viewmodelindex; //0x01F4 
	vec3_t viewangles; //0x01F8 
	__int32 viewtargetheight; //0x0204 
	float fviewtargetheight; //0x0208 
	char pad_0x020C[0x1E0]; //0x020C
	ammoPool_s ammo[15]; //0x03EC 
	ammoPool_s ammoclip[15]; //0x0428 
	char pad_0x0464[0xE4]; //0x0464
	perkBits_s perks; //0x0548 
	char pad_0x0550[0x4EC0]; //0x0550
	__int32 sessionState;  // 0x5410 
	char pad_0x5414[0x130];  // 0x5414
	char name[0x24];   // 0x5544
	char pad_0x5322[0x120];  // 0x5568
	__int32 lastCmdTime; //0x5688 
	int button_bits[2]; //0x568C 
	int oldbutton_bits[2]; //0x5694 
	int latched_button_bits[2]; //0x569C 
	int button_bitsSinceLastFrame[2]; //0x56A4 
	char pad_0x56AC[0x1C]; //0x56AC //0x5544
	__int32 inactivityTime; //0x56C8 
	__int32 inactivityWarning; //0x56CC 
	char pad_0x56D0[0xC]; //0x56D0
	float curaimspreadscale; //0x56DC 
	char pad_0x56E0[0x10C]; //0x56E0
	__int16 attachShieldTagName; //0x57EC 
	char pad_0x57EE[0x1E]; //0x57EE
}; //Size=0x580C
class gentity_s
{
public:
	__int32 number; //0x0000 
	__int32 eFlags; //0x0004 
	__int32 eFlags2; //0x0008 
	char pad_0x000C[0xC]; //0x000C
	vec3_t origin; //0x0018 
	char pad_0x0024[0x18]; //0x0024
	vec3_t angles; //0x003C 
	char pad_0x0048[0x90]; //0x0048
	__int16 eType; //0x00D8 
	__int16 groundEntityNum; //0x00DA 
	char pad_0x00DC[0x8]; //0x00DC
	__int32 weapon; //0x00E4 
	char pad_0x00E8[0x10]; //0x00E8
	unsigned char linked; //0x00F8 
	unsigned char bmodel; //0x00F9 
	unsigned char svFlag; //0x00FA 
	unsigned char inuse; //0x00FB 
	__int32 brodcastTime; //0x00FC 
	vec3_t mins; //0x0100 
	vec3_t maxs; //0x010C 
	__int32 contents; //0x0118 
	vec3_t absmin; //0x011C 
	vec3_t absmax; //0x0128 
	vec3_t currentorigin; //0x0134 
	vec3_t currentangles; //0x0140 
	__int32 ownerNum; //0x014C 
	__int32 eventTime; //0x0150 
	gclient_s* client; //0x0154 
	gclient_s* actor; //0x0158 
	gclient_s* sentient; //0x015C 
	__int16 model; //0x0160 
	unsigned char physicsObject; //0x0162 
	unsigned char takedamage; //0x0163 
	char pad_0x0164[0x4]; //0x0164
	__int16 unkidk1; //0x0168 
	__int16 classname; //0x016A 
	__int16 target; //0x016C 
	__int16 targetname; //0x016E 
	__int16 script_noteworthy; //0x0170 
	char pad_0x0172[0x6]; //0x0172
	__int32 spawnflags; //0x0178 
	__int32 flags; //0x017C 
	__int32 eventtime; //0x0180 
	char pad_0x0184[0x18]; //0x0184
	__int32 unkidk2; //0x019C 
	char pad_0x01A0[0x8]; //0x01A0
	__int32 health; //0x01A8 
	char pad_0x01AC[0x88]; //0x01AC
	__int32 index; //0x0234 
	char pad_0x0238[0xE4]; //0x0238

}; //Size=0x031C
#pragma endregion

#pragma endregion

struct BulletTraceResults__1
{
	trace_t trace;
	gentity_s *hitEnt;
	Vector3 hitPos;
	int ignoreHitEnt;
	int depthSurfaceType;
};

struct hybrid_vector1
{
	float vec[4];
};
struct __declspec(align(16)) trace1_t
{
	hybrid_vector1 normal;
	float fraction;
	int sflags;
	int cflags;
	TraceHitType hitType;
	unsigned __int16 hitId;
	unsigned __int16 modelIndex;
	unsigned __int16 partName;
	unsigned __int16 boneIndex;
	unsigned __int16 partGroup;
	bool allsolid;
	bool startsolid;
	bool walkable;
	void *staticModel;
	int hitPartition;
};
struct __declspec(align(16)) BulletTraceResults_1
{
	trace1_t trace;
	gentity_s *hitEnt;
	Vector3 hitPos;
	int ignoreHitEnt;
	int depthSurfaceType;
};


struct trace_ts {
	Vector3 normal; // 0x0
	char padding[4]; // 0xC
	float fraction; // 0x10
	int surfaceType; // 0x14
	int sflags; // 0x18
	int hitType; // 0x1C
	unsigned short hitId; // 0x20
	unsigned short modelIndex; // 0x22
	unsigned short boneIndex; // 0x24
	unsigned short partName; // 0x26
	unsigned short partGroup; // 0x28
	bool allsolid; // 0x2A
	bool startsolid; // 0x2B
	bool walkable; // 0x2C
	int hitPartition; // 0x30
};

struct BulletTraceResults {
	trace_ts trace; // 0x0
	char padding[0xC]; // 0x30
	int hitEnt; // 0x40
	Vector3 hitPos; // 0x44
	bool ignoreHitEnt; // 0x50
	int surfaceType; // 0x54
	char padding2[8]; // 0x58
};

struct GfxFilm
{
	bool enabled;
	vec4_t visColorRangeS;
	vec4_t visColorRangeE;
	vec4_t visColorShadowMatrixR;
	vec4_t visColorShadowMatrixG;
	vec4_t visColorShadowMatrixB;
	vec4_t visColorMidtoneMatrixR;
	vec4_t visColorMidtoneMatrixG;
	vec4_t visColorMidtoneMatrixB;
	vec4_t visColorHilightMatrixR;
	vec4_t visColorHilightMatrixG;
	vec4_t visColorHilightMatrixB;
	vec4_t visColorFinalGamma;
	vec4_t visColorFinalSaturation;
	vec4_t visColorFinalBlend;
	short lutA;
	short lutB;
	short lutC;
	short lutD;
	vec4_t lutBlendWeights;
	float filmLut;
	vec4_t sunFlareTint;
};

struct GfxBloom
{
	vec4_t visBloomLevelsRGBYInB;
	vec4_t visBloomLevelsRGBYInG;
	vec4_t visBloomLevelsRGBYInW;
	vec4_t visBloomLevelsRGBYOutB;
	vec4_t visBloomLevelsRGBYOutW;
	vec4_t visBloomRGBHi;
	vec4_t visBloomRGBLo;
	vec4_t visBloomYHi;
	vec4_t visBloomYLo;
};

struct GfxReviveFx
{
	bool enabled;
	float reviveEdgeColorTemp;
	float reviveEdgeSaturation;
	vec3_t reviveEdgeScale;
	vec3_t reviveEdgeContrast;
	vec3_t reviveEdgeOffset;
	float reviveEdgeMaskAdjust;
	float reviveEdgeAmount;
};

struct GfxLightScale
{
	float diffuseScale;
	float specularScale;
};

struct GfxVisionSet
{
	GfxFilm film;
	GfxBloom bloom;
	GfxReviveFx reviveFx;
	GfxLightScale charPrimaryLightScale;
};

struct GfxDepthOfField
{
	float viewModelStart;
	float viewModelEnd;
	float nearStart;
	float nearEnd;
	float farStart;
	float farEnd;
	float nearBlur;
	float farBlur;
	bool useAltMaterial;
};

struct GfxDoubleVision
{
	vec3_t direction;
	float motionBlurMagnitude;
	float deltaPerMS;
	float cur;
	float targ;
};

struct GfxCompositeFx
{
	vec2_t distortionScale;
	float blurRadius;
	float distortionMagnitude;
	float frameRate;
	int lastUpdate;
	int frame;
	int startMSec;
	int currentTime;
	int duration;
	bool enabled;
	bool scriptEnabled;
};

struct GfxGenericFilter
{
	bool passEnabled[8][4];
	int *passMaterial[8][4];
	int passTarget[8][4];
	int passSampler0[8][4];
	int passSampler1[8][4];
	float passParam[8][4][16];
	int passQuads[8][4];
	int bitFlag[8];
};

struct GfxSaveScreenParam
{
	float s0;
	float t0;
	float ds;
	float dt;
	int screenTimerId;
	char mode;
};

struct GfxBlendSaveScreenBlurredParam
{
	int fadeMsec;
	float s0;
	float t0;
	float ds;
	float dt;
	int screenTimerId;
	char enabled;
};

struct GfxBlendSaveScreenFlashedParam
{
	float intensityWhiteout;
	float intensityScreengrab;
	float s0;
	float t0;
	float ds;
	float dt;
	int screenTimerId;
	char enabled;
};

struct GfxSaveScreenFx
{
	GfxSaveScreenParam saveScreenParam;
	GfxBlendSaveScreenBlurredParam blendBlurredParam;
	GfxBlendSaveScreenFlashedParam blendFlashedParam;
};

struct GfxPoison
{
	float curAmountTarget;
	float curAmount;
};

struct GfxLightImage
{
	int *image;
	char samplerState;
};

struct GfxLightDef
{
	const char *name;
	GfxLightImage attenuation;
	int lmapLookupStart;
};

struct float44 {
	union {
		vec4_t m[4];
		float member[16];
	} __u0;
};

struct GfxLight
{
	char type;
	char canUseShadowMap;
	char shadowmapVolume;
	short cullDist;
	vec3_t color;
	vec3_t dir;
	vec3_t origin;
	float radius;
	float cosHalfFovOuter;
	float cosHalfFovInner;
	int exponent;
	unsigned int spotShadowIndex;
	float dAttenuation;
	float roundness;
	vec3_t angles;
	float spotShadowHiDistance;
	vec4_t diffuseColor;
	vec4_t shadowColor;
	vec4_t falloff;
	vec4_t aAbB;
	vec4_t cookieControl0;
	vec4_t cookieControl1;
	vec4_t cookieControl2;
	float44 viewMatrix;
	float44 projMatrix;
	GfxLightDef *def;
};

struct GfxViewport
{
	int x;
	int y;
	int width;
	int height;
};

struct GfxWorldFog
{
	float baseDist;
	float halfDist;
	float baseHeight;
	float halfHeight;
	float sunFogPitch;
	float sunFogYaw;
	float sunFogInner;
	float sunFogOuter;
	vec3_t fogColor;
	float fogOpacity;
	vec3_t sunFogColor;
	float sunFogOpacity;
};

struct WaterFogDef
{
	int startTime;
	int finishTime;
	vec4_t color;
	float fogStart;
	float density;
	float heightDensity;
	float baseHeight;
	vec4_t sunFogColor;
	vec3_t sunFogDir;
	float sunFogStartAng;
	float sunFogEndAng;
};

struct ExtraCamLodInfo
{
	vec3_t pos[4];
	unsigned int posValidBits;
};

struct GfxRippleWave
{
	vec3_t wavePosition;
	float waveWidth;
	float waveSpeedScale;
	float waveAmplitudeRatio;
	float waveInnerStart;
	float waveInnerEnd;
	float waveOuterStart;
	float waveOuterEnd;
	int waveTimeStamp;
};

struct refdef_t
{
	unsigned int x; //0
	unsigned int y;
	unsigned int width;
	unsigned int height;
	float sceneViewportX; //10
	float sceneViewportY; //14
	float sceneViewportWidth; //18
	float sceneViewportHeight; //1C
	float tanHalfFovX; //20
	float tanHalfFovY; //24
	float maincamTanHalfFovY; //28
	float extracamTanHalfFovY; //2C
	float unk_4;
	float fov_x; //30
	Vector3 vieworg;
	float yaw;
	vec3_t viewaxis[3];
	int frametime;
	int time;
	float zNear;
	float zFar;
	GfxVisionSet visionset;
	float blurRadius;
	GfxDepthOfField dof;
	float rimIntensity;
	vec4_t genericSceneVector0;
	vec4_t genericSceneVector1;
	vec4_t genericSceneVector2;
	vec4_t genericSceneVector3;
	vec4_t cameraVelocity;
	GfxDoubleVision doubleVision;
	GfxCompositeFx flameFx;
	GfxCompositeFx waterSheetingFx;
	GfxGenericFilter genericFilter;
	GfxPoison poisonFx;
	GfxCompositeFx electrifiedFx;
	GfxCompositeFx transportedFx;
	GfxSaveScreenFx saveScreenFx;
	float sunVisibility;
	GfxLight primaryLights[255];
	GfxViewport scissorViewport;
	bool useScissorViewport;
	int localClientNum;
	int hideMatureContent;
	int splitscreen;
	int splitscreenBlurEdges;
	int playerTeleported;
	int oldExposureId;
	int newExposureId;
	float lerpcount;
	int lastTime;
	float exposure;
	float linearExposure;
	unsigned short exposureMode;
	unsigned short worldFogMode;
	vec3_t worldFogVolumeEntryPosition;
	short newWorldFogVolumeId;
	short oldWorldFogVolumeId;
	int worldFogVolumeTimeStamp;
	int worldFogFlags;
	bool worldFogSnapTransition;
	bool worldFogUseSystemTime;
	GfxWorldFog worldFogOld;
	GfxWorldFog worldFogNow;
	short worldFogModifierVolumeId;
	int worldFogModifierTimeStamp;
	float worldFogModifierTimeScale;
	float worldFogModifierScaleD;
	float worldFogModifierScaleH;
	vec4_t worldFogModifierColorA;
	float nWorldFogModifierScaleD;
	float nWorldFogModifierScaleH;
	vec4_t nWorldFogModifierColor;
	vec3_t worldFogVolumeLastViewOrg;
	unsigned short lutBankMask;
	short lutScriptIndex;
	short newLutVolumeId;
	short oldLutVolumeId;
	int lutVolumeTimeStamp;
	float lutBlendWeights[32];
	float postEmissiveBrightening;
	bool noLodCullOut;
	float lodScaleRigid;
	float lodScaleSkinned;
	WaterFogDef waterFog;
	float adsZScale;
	ExtraCamLodInfo extraCamLodInfo;
	vec3_t preExtraCamVieworg;
	vec3_t preExtraCamViewaxis[3];
	float preExtraCamTanHalfFovX;
	float preExtraCamTanHalfFovY;
	float weaponTanHalfFovX;
	float weaponTanHalfFovY;
	bool sonarActive;
	bool sonarUseThermalMaterial;
	bool sonarOverrideBlend;
	float sonarTanHalfFovX;
	float sonarTanHalfFovY;
	hybrid_vector1 sonarViewScale;
	hybrid_vector1 sonarViewOffset;
	float sonarBlur;
	bool drawInfrared;
	float convergence;
	bool drawPostBlur;
	bool drawWaypointsPostBloom;
	bool useColorControl;
	float colorSaturation;
	float colorTemp;
	float colorHue;
	vec3_t colorScale;
	GfxRippleWave rWaves[1];
};

struct cg_sa
{
	int clientNum;				/// 0x00000
	char padding00[0x1C];		/// 0x00004
	int serverTime;				/// 0x00020
	char _00000001[0x60];		/// 0x00024
	int ping;					/// 0x00084
	char _000000011[0x30];		/// 0x00088
	Vector3 origin;				/// 0x000B8
	char _00000002[0xC8];		/// 0x000C4
	stance_t stance;			/// 0x0018C
	char _00000003[0x4C];		/// 0x00190
	int maxEntities;			/// 0x001DC
	char _00000004[0x90];		/// 0x001E0
	float zoomProgress;			/// 0x00270
	char _00000005[0x54];		/// 0x00274
	int health;					/// 0x002C8
	char _0x000006[0x4];		/// 0x002CC
	int maxHealth;				/// 0x002D0
	char _00000007[0x98];		/// 0x002D4
	float weaponKickProgress;	/// 0x0036C
	char _00000008[0x48038];	/// 0x00370
	playerstate_s playerstate;	/// 0x483A8
	refdef_t refdef;			/// 0x4DB90
	char _00000009[0x1C1A4];	/// 0x4DBFC
	clientinfo_s clients[18];	/// 0x69DA0
	char _0000000A[0xE060];		/// 0x72E30
	float spreadMultiplier;		/// 0x80E90
};

struct bullet_hit_info_t
{
	vec3_t hitp;
	vec3_t hitn;
	int sflags;
	float depth;
	int hitid;
	float range;
};

enum CameraMode
{
	CAM_NORMAL = 0x0,
	CAM_LINKED = 0x1,
	CAM_VEHICLE = 0x2,
	CAM_VEHICLE_THIRDPERSON = 0x3,
	CAM_VEHICLE_GUNNER = 0x4,
	CAM_TURRET = 0x5,
	CAM_MISSILE = 0x6,
	CAM_SPIKECAMERA = 0x7,
	CAM_SCRIPTED_EXTRACAM = 0x8,
	CAM_RADIANT = 0x9,
};

struct ScriptCamera
{
	int flags;
	vec3_t origin;
	vec3_t angles;
	vec3_t lookat;
	int originCent;
	int lookAtCent;
};

struct ScriptExtraCam
{
	vec3_t origin[4];
	vec3_t angles[4];
	int entNum[4];
	float fov[4];
	int curCameraIndex;
	bool multiCamEnabled;
	bool multiCamRequest;
};

struct Camera
{
	vec3_t lastViewOrg;
	vec3_t lastViewAngles;
	float lastFOV;
	int lastViewInputTime;
	float lastSpringOffset;
	float lastViewTraceFraction;
	int lastTime;
	int lastClientNum;
	vec3_t tweenStartOrg;
	vec3_t tweenStartAngles;
	float tweenStartFOV;
	int tweenStartTime;
	float tweenDuration;
	CameraMode lastCamMode;
	int lastVehicleDefIndex;
	int lastVehicleSeatPos;
	vec3_t missileViewAngles;
	bool missileWasKillCam;
	ScriptCamera scriptCam;
	ScriptExtraCam scriptExtraCam;
	bool useTagCamera;
	bool bWasRemoteTurretCam;
};

enum team_indicator
{
	TEAM_INDICATOR_FULL = 0x0,
	TEAM_INDICATOR_ABBREVIATED = 0x1,
	TEAM_INDICATOR_ICON = 0x2,
	TEAM_INDICATOR_COUNT = 0x3,
};

enum scoreboardColumnType_t
{
	SB_TYPE_INVALID = 0x0,
	SB_TYPE_NONE = 0x1,
	SB_TYPE_SCORE = 0x2,
	SB_TYPE_KILLS = 0x3,
	SB_TYPE_DEATHS = 0x4,
	SB_TYPE_ASSISTS = 0x5,
	SB_TYPE_DEFENDS = 0x6,
	SB_TYPE_PLANTS = 0x7,
	SB_TYPE_DEFUSES = 0x8,
	SB_TYPE_RETURNS = 0x9,
	SB_TYPE_CAPTURES = 0xA,
	SB_TYPE_DESTRUCTIONS = 0xB,
	SB_TYPE_KDRATIO = 0xC,
	SB_TYPE_SURVIVED = 0xD,
	SB_TYPE_STABS = 0xE,
	SB_TYPE_TOMAHAWKS = 0xF,
	SB_TYPE_HUMILIATED = 0x10,
	SB_TYPE_X2SCORE = 0x11,
	SB_TYPE_HEADSHOTS = 0x12,
	SB_TYPE_DOWNS = 0x13,
	SB_TYPE_REVIVES = 0x14,
	SB_TYPE_AGRKILLS = 0x15,
	SB_TYPE_HACKS = 0x16,
	SB_TYPE_POINTS_TO_WIN = 0x17,
	SB_TYPE_KILLS_CONFIRMED = 0x18,
	SB_TYPE_KILLS_DENIED = 0x19,
	NUM_SB_TYPES = 0x1A,
};

struct __declspec(align(4)) objectiveMapInfo_t
{
	int *icon;
	float iconSize;
	char ignoreEntity : 1;
	char rotateWithEntity : 1;
	char flipMaterial : 1;
	char clipToMap : 1;
	char colorMaterialInCode : 1;
	char stencilToPartialMap : 1;
};

enum InvalidCmdHintType
{
	INVALID_CMD_NONE = 0x0,
	INVALID_CMD_NO_AMMO_BULLETS = 0x1,
	INVALID_CMD_NO_AMMO_FRAG_GRENADE = 0x2,
	INVALID_CMD_NO_AMMO_SPECIAL_GRENADE = 0x3,
	INVALID_CMD_NO_AMMO_FLASH_GRENADE = 0x4,
	INVALID_CMD_NO_AMMO_EQUIPMENT = 0x5,
	INVALID_CMD_STAND_BLOCKED = 0x6,
	INVALID_CMD_CROUCH_BLOCKED = 0x7,
	INVALID_CMD_PRONE_BLOCKED = 0x8,
	INVALID_CMD_TARGET_TOO_CLOSE = 0x9,
	INVALID_CMD_LOCKON_REQUIRED = 0xA,
	INVALID_CMD_NOT_ENOUGH_CLEARANCE = 0xB,
	INVALID_CMD_CANT_PLACE_TURRET = 0xC,
	INVALID_CMD_CANT_EQUIP_WHILE_PRONE = 0xD,
	INVALID_CMD_CANT_PLANT_EQUIPMENT = 0xE,
};

enum SuccessfulCmdHintType
{
	SUCCESSFUL_CMD_NONE = 0x0,
	SUCCESSFUL_CMD_GOD_MODE_ON = 0x1,
	SUCCESSFUL_CMD_GOD_MODE_OFF = 0x2,
	SUCCESSFUL_CMD_DEMIGOD_MODE_ON = 0x3,
	SUCCESSFUL_CMD_DEMIGOD_MODE_OFF = 0x4,
	SUCCESSFUL_CMD_UFO_ON = 0x5,
	SUCCESSFUL_CMD_UFO_OFF = 0x6,
	SUCCESSFUL_CMD_WEAPNEXT = 0x7,
	SUCCESSFUL_CMD_WEAPPREV = 0x8,
	SUCCESSFUL_CMD_GIVE_ALL = 0x9,
	SUCCESSFUL_CMD_CAMLOCK_ON = 0xA,
	SUCCESSFUL_CMD_CAMLOCK_OFF = 0xB,
	SUCCESSFUL_CMD_LOOKSPRING_ON = 0xC,
	SUCCESSFUL_CMD_LOOKSPRING_OFF = 0xD,
};

struct viewDirectionalHitIndicator_t
{
	int time;
	vec3_t entOrigin;
};

struct viewDamage_t
{
	int time;
	int duration;
	float yaw;
};

enum ShockViewTypes
{
	SHELLSHOCK_VIEWTYPE_BLURRED = 0x0,
	SHELLSHOCK_VIEWTYPE_FLASHED = 0x1,
	SHELLSHOCK_VIEWTYPE_NONE = 0x2,
};

struct $1FFD506E5F9165F79F5344FD9C8F021D
{
	int blurredFadeTime;
	int blurredEffectTime;
	int flashWhiteFadeTime;
	int flashShotFadeTime;
	ShockViewTypes type;
};

/* 2956 */
struct $B32C35443884083D3CC13DCD5C8D7874
{
	int fadeTime;
	float kickRate;
	float kickRadius;
};

/* 2957 */
struct $16D8FAD28A08B38292F67C768CC14C4C
{
	bool affect;
	char loop[64];
	char loopSilent[64];
	char end[64];
	char endAbort[64];
	int fadeInTime;
	int fadeOutTime;
	float drylevel;
	float wetlevel;
	char roomtype[64];
	int modEndDelay;
	int loopFadeTime;
	int loopEndDelay;
	char snapshot[64];
};

/* 2958 */
struct $52C58A71BD00586BA7DCB8AF66236D72
{
	bool affect;
	int fadeTime;
	float mouseSensitivity;
	float maxPitchSpeed;
	float maxYawSpeed;
};

/* 2959 */
struct $02B41AB872540B0D7FA7A4D4D9EBD97F
{
	float scale;
};

/* 2960 */
struct $1BC6F870A2CCF543567EAA1D445E0BBA
{
	bool affect;
};

/* 2961 */
struct $50D21064AB3C35E3954292D19EEA2E03
{
	char name[32];
	int inTime;
	int outTime;
};

/* 2962 */
const struct shellshock_parms_t
{
	$1FFD506E5F9165F79F5344FD9C8F021D screenBlend;
	$B32C35443884083D3CC13DCD5C8D7874 view;
	$16D8FAD28A08B38292F67C768CC14C4C sound;
	$52C58A71BD00586BA7DCB8AF66236D72 lookControl;
	$02B41AB872540B0D7FA7A4D4D9EBD97F movement;
	$1BC6F870A2CCF543567EAA1D445E0BBA animation;
	$50D21064AB3C35E3954292D19EEA2E03 visionSet;
};

struct shellshock_t
{
	shellshock_parms_t *parms;
	int startTime;
	int duration;
	int loopEndTime;
	float sensitivity;
	vec2_t viewDelta;
	int hasSavedScreen;
	int visionSetStarted;
};

struct $F6DFD6D87F75480A1EF1906639406DF5
{
	int time;
	int duration;
};

enum KillCamEntityType
{
	KC_NO_ENTITY = 0x0,
	KC_HELICOPTER = 0x1,
	KC_DESTRUCTIBLE = 0x2,
	KC_SCRIPTED = 0x3,
	KC_EXPLOSIVE = 0x4,
	KC_FAST_EXPLOSIVE = 0x5,
	KC_ROCKET = 0x6,
	KC_DRONE = 0x7,
	KC_DOG = 0x8,
	KC_ARTILLERY = 0x9,
	KC_VEHICLE = 0xA,
	KC_TURRET = 0xB,
};

enum KillCamEntityRestState
{
	KC_ENT_MOVING = 0x0,
	KC_ENT_AT_REST = 0x1,
	KC_ENT_STUCK_GROUND = 0x2,
	KC_ENT_STUCK_WALL = 0x3,
};

struct visionSetVars_t
{
	bool filmEnable;
	vec4_t visBloomLevelsRGBYInB;
	vec4_t visBloomLevelsRGBYInG;
	vec4_t visBloomLevelsRGBYInW;
	vec4_t visBloomLevelsRGBYOutB;
	vec4_t visBloomLevelsRGBYOutW;
	vec4_t visBloomRGBHi;
	vec4_t visBloomRGBLo;
	vec4_t visBloomYHi;
	vec4_t visBloomYLo;
	vec4_t visColorRangeS;
	vec4_t visColorRangeE;
	vec4_t visColorShadowMatrixR;
	vec4_t visColorShadowMatrixG;
	vec4_t visColorShadowMatrixB;
	vec4_t visColorMidtoneMatrixR;
	vec4_t visColorMidtoneMatrixG;
	vec4_t visColorMidtoneMatrixB;
	vec4_t visColorHilightMatrixR;
	vec4_t visColorHilightMatrixG;
	vec4_t visColorHilightMatrixB;
	vec4_t visColorFinalGamma;
	vec4_t visColorFinalSaturation;
	vec4_t visColorFinalBlend;
	float filmLut;
	bool reviveEnable;
	float reviveEdgeColorTemp;
	float reviveEdgeSaturation;
	vec3_t reviveEdgeScale;
	vec3_t reviveEdgeContrast;
	vec3_t reviveEdgeOffset;
	float reviveEdgeMaskAdjust;
	float reviveEdgeAmount;
	bool charPrimaryUseTweaks;
	float charPrimaryDiffuseScale;
	float charPrimarySpecularScale;
	float masterRingmod;
	float reverbRingmod;
	float hiFilter;
	float lowFilter;
	vec4_t sunFlareTint;
	float postEmissiveBrightening;
	char name[64];
};

struct CompassScrambler
{
	vec2_t pos;
	int startTime;
	int handle;
};

enum visionSetLerpStyle_t
{
	VISIONSETLERP_UNDEFINED = 0x0,
	VISIONSETLERP_NONE = 0x1,
	VISIONSETLERP_TO_LINEAR = 0x2,
	VISIONSETLERP_TO_SMOOTH = 0x3,
	VISIONSETLERP_BACKFORTH_LINEAR = 0x4,
	VISIONSETLERP_BACKFORTH_SMOOTH = 0x5,
	VISIONSETLERP_CUSTOM_VALUE = 0x6,
};

struct visionSetLerpData_t
{
	int timeStart;
	int timeDuration;
	float lerpFraction;
	visionSetLerpStyle_t style;
};

struct $BE9F66374A020A9809EEAF403416A176
{
	float aimSpreadScale;
};

struct transPlayerState_t
{
	int otherFlags;
	int damageEvent;
	short predictableEventSequence;
	int predictableEvents[4];
	short unpredictableEventSequence;
	int unpredictableEvents[4];
};

struct hudElemSoundInfo_t
{
	int lastPlayedTime;
};

enum link_type_e
{
	PITCH_CTRL = 0x0,
	YAW_CTRL = 0x1,
	ROLL_CTRL = 0x2,
	SWIM_CTRL = 0x3,
	FULL_CTRL = 0x4,
	COMPASS_CTRL = 0x5,
};

struct footstepEvent_t
{
	centity_t *cent;
	unsigned short bone11;
	unsigned short notetrack;
	char moveType;
	char surface;
	unsigned int playerView : 1;
	unsigned int quiet : 1;
	unsigned int isLouder : 1;
	unsigned int footprint : 1;
};

struct targetInfo_t
{
	int entNum;
	vec3_t offset;
	int materialIndex;
	int offscreenMaterialIndex;
	int flags;
};

struct snd_context
{
	unsigned int type;
	unsigned int value;
};

/* 3014 */
struct snd_ambient_script_data
{
	bool isAmbientRoom;
	bool isAmbientPackage;
	bool isDefaultRoom;
	short entnums[16];
	char priorities[16];
	char name[64];
	unsigned int hash;
	int numContexts;
	snd_context contexts[16];
};

struct snd_ambient_collider
{
	int roomTriggerIndex;
	int previousRoomTriggerIndex;
	int packageTriggerIndex;
	int roomPriorityIndex;
	int packagePriorityIndex;
	int entnum;
	unsigned int hash;
	int colliderEntnum;
	bool firstFrame;
	bool inUse;
	unsigned int playerRingoff;
	bool updated;
	bool localPlayer;
};

struct ShieldHitDelayedEvent
{
	unsigned int eventParm;
};

enum WeaponDobjInfoSlot
{
	HELD = 0x0,
	STOWED = 0x1,
	MELEE = 0x2,
};

struct WeaponDobjInfoModelMask {
	WeaponDobjInfoSlot slot;
	bool weapon;
	union {
		int* weapDef;
		int* attachment;
	} __u2;
	unsigned int dobjModelMask;
};

struct WeaponDobjInfo
{
	char numModelMasks;
	WeaponDobjInfoSlot addingSlot;
	short lastAddedModel;
	WeaponDobjInfoModelMask modelMasks[8];
};

struct DroppedWeaponDobjInfo
{
	int entnum;
	WeaponDobjInfo weaponDobjInfo;
};

struct FogSettings
{
	float start;
	float r;
	float g;
	float b;
	float density;
	float heightDensity;
	float baseHeight;
	float fogColorScale;
	float sunFogColorR;
	float sunFogColorG;
	float sunFogColorB;
	float sunFogDirX;
	float sunFogDirY;
	float sunFogDirZ;
	float sunFogStartAng;
	float sunFogEndAng;
	float fogMaxOpacity;
};

struct cg_t
{
	int clientNum;
	int localClientNum;
	DemoType demoType;
	CubemapShot cubemapShot;
	int cubemapSize;
	int renderScreen;
	int latestSnapshotNum;
	int latestSnapshotTime;
	snapshot_s *snap;
	snapshot_s *nextSnap;
	snapshot_s activeSnapshots[2];
	bool slowMotionModified;
	float frameInterpolation;
	int frametime;
	int time;
	int oldTime;
	int physicsTime;
	int mapRestart;
	bool bThirdPerson;
	thirdPersonType renderingThirdPerson;
	char unk1[0x400];
	playerState_s predictedPlayerState;
	int lastPlayerStateOverride;
	centity_t predictedPlayerEntity;
	playerEntity_t playerEntity;
	int predictedErrorTime;
	vec3_t predictedError;
	playerState_s lastUIPlayerState;
	float landChange;
	int landTime;
	float heightToCeiling;
	int heightToCeilingTS;
	refdef_t refdef;
	vec3_t refdefViewAngles;
	Camera cameraData;
	float lastPelvisCameraOffset;
	vec3_t baseGunAngles;
	vec3_t swayViewAngles;
	vec3_t swayAngles;
	vec3_t swayOffset;
	vec3_t recoilAngles;
	vec3_t recoilSpeed;
	vec3_t damageKickAngles;
	int previousRecoilTime;
	float previousRecoilRatio;
	vec3_t lastStandSwayAngles;
	vec3_t lastStandSwayAVel;
	vec3_t lastStandSwayTarget;
	vec3_t radiantCameraOrigin;
	vec3_t radiantCameraAngles;
	int radiantCamInUse;
	int iEntityLastType[1792];
	int *pEntityLastXModel[1792];
	float zoomSensitivity;
	bool isLoading;
	char objectiveText[1024];
	team_indicator teamIndicator;
	bool colorBlindAssist;
	int teamPlayerMask[10][1];
	int vehicleInitView;
	vec3_t prevVehicleInvAxis[3];
	bool vehicleViewLocked;
	vec3_t vehicleViewLockedAngles;
	int missileInitView;
	vec3_t storedRemoteCameraAngles;
	vec3_t storedRemoteCameraOrigin;
	char scriptMainMenu[256];
	bool initialPlayersConnected;
	bool initialPlayersConnectedRespondedTo;
	int numScores;
	int teamScores[10];
	unsigned int teamHasMeat[10];
	int teamPings[10];
	int teamPlayers[10];
	int scoreOrder[18];
	scoreboardColumnType_t scoreboardColumnTypes[5];
	int matchUIVisibilityFlags;
	unsigned int talkFlags;
	objectiveMapInfo_t objectiveMapInfo[64][2];
	objective_t clientObjectives[32];
	int bombTimer[2];
	int showScores;
	int scoreFadeTime;
	int scoresTop;
	int scoresOffBottom;
	int scoresBottom;
	int selectedGamerIndex;
	int bannerLines[10];
	int64_t selectedGamerXuid;
	int selectedGamerClientNum;
	int drawHud;
	int timeScaleTimeStart;
	int timeScaleTimeEnd;
	float timeScaleStart;
	float timeScaleEnd;
	int crosshairClientNum;
	int crosshairClientLastTime;
	int crosshairClientStartTime;
	unsigned int crosshairTraceDistance;
	unsigned int airburstMarkDistance;
	int airburstMarkStartTime;
	int airburstMarkEndTime;
	int airburstMarkInProgress;
	int gpsJammerLastInactive;
	int bulletsFiredContinuously;
	int bulletsFiredContinuouslyLeft;
	int bulletsFiredStopTime;
	int cursorHintIcon;
	int cursorHintTime;
	int cursorHintFade;
	int cursorHintString;
	int vehicleHintTime;
	int lastVehicleSeat;
	int driverHintShown;
	int gunnerHintShown;
	int lastClipFlashTime;
	InvalidCmdHintType invalidCmdHintType;
	int invalidCmdHintTime;
	SuccessfulCmdHintType successfulCmdHintType;
	int successfulCmdHintTime;
	int lastHealthPulseTime;
	int lastHealthLerpDelay;
	int lastHealthClient;
	float lastHealth;
	float healthOverlayFromAlpha;
	float healthOverlayToAlpha;
	int healthOverlayPulseTime;
	int healthOverlayPulseDuration;
	int healthOverlayPulsePhase;
	bool healthOverlayHurt;
	int healthOverlayLastHitTime;
	float healthOverlayOldHealth;
	int healthOverlayPulseIndex;
	int proneBlockedEndTime;
	int lastStance;
	int lastStanceChangeTime;
	int lastStanceFlashTime;
	int voiceTime;
	Weapon weaponSelect;
	int weaponSelectTime;
	bool weaponForcedSelect;
	Weapon weaponLatestPrimary;
	Weapon lastWeaponForAlt[15];
	unsigned int viewModelFx;
	Weapon prevViewmodelWeapon;
	bool prevViewmodelWeaponInASD;
	Weapon equippedOffHand;
	viewDirectionalHitIndicator_t directionalHitIndicator[4];
	viewDamage_t viewDamage[8];
	int damageTime;
	float damageX;
	float damageY;
	float damageValue;
	float viewFade;
	int waterDropCount;
	int waterDropStartTime;
	int waterDropStopTime;
	int weaponIdleTime;
	int nomarks;
	int clearMarks;
	int newPlayerViewmodel;
	bool weaponLaserOff;
	int v_dmg_time;
	float v_dmg_pitch;
	float v_dmg_roll;
	float v_dmg_flash;
	float fBobCycle;
	float xyspeed;
	vec3_t kickAVel;
	vec3_t kickAngles;
	vec3_t offsetAngles;
	float gunPitch;
	float gunYaw;
	float gunXOfs;
	float gunYOfs;
	float gunZOfs;
	vec3_t flamethrowerKickOffset;
	float minigunSpinAngle;
	vec3_t viewModelAxis[4];
	float rumbleScale;
	float compassNorthYaw;
	vec2_t compassNorth;
	int *compassMapMaterial;
	int *compassMapScrambledMaterial;
	vec2_t compassMapUpperLeft;
	vec2_t compassMapWorldSize;
	int compassLastTime;
	float compassYaw;
	float compassSpeed;
	int compassFadeTime;
	int healthFadeTime;
	int ammoFadeTime;
	int stanceFadeTime;
	int sprintFadeTime;
	int offhandFadeTime;
	int offhandFlashTime;
	int waypointFadeTime;
	int vehicleControlsFadeTime;
	shellshock_t shellshock;
	$F6DFD6D87F75480A1EF1906639406DF5 testShock;
	int shellshockSoundActive;
	int holdBreathTime;
	int holdBreathInTime;
	int holdBreathDelay;
	float holdBreathFrac;
	float radarProgress;
	float satelliteProgress;
	int radarType;
	vec2_t selectedLocation;
	vec2_t selectedYaw;
	int typewriterStartTime;
	vec2_t selectedLocations[3];
	int lastTimeSelected;
	SprintState sprintStates;
	int adsViewErrorDone;
	int inKillCam;
	int wasInKillCam;
	bool killCamFirstFrameRan;
	int killCamEntity;
	int invalidKillCamEntity;
	KillCamEntityType killCamEntityType;
	int killCamLastEntityNum;
	vec3_t killCamLastEntityOrg;
	vec3_t killCamLastEntityAngles;
	KillCamEntityRestState killCamEntityRestState;
	int killCamLookAtEntity;
	vec3_t killCamLookAt;
	vec3_t killCamHelicopterOffset;
	short killCamLastVehicleDefIndex;
	int killCamStoppedTime;
	float killCamStoppedDecelTime;
	vec3_t killCamStoppedPos;
	vec3_t killCamStoppedVel;
	vec3_t killCamPrevBombOrigin;
	int killCamLerpEndTime;
	vec3_t killCamOldViewAngles;
	vec3_t killCamOldViewOrg;
	char bgs[0x12FD0];
	cpose_t viewModelPose;
	visionSetVars_t visionSetPreLoaded[8];
	char visionSetPreLoadedName[8][64];
	visionSetVars_t visionSetFrom[8];
	visionSetVars_t visionSetTo[8];
	visionSetVars_t visionSetCurrent[8];
	visionSetLerpData_t visionSetLerpData[8];
	char visionNameNaked[64];
	char visionNameNight[64];
	char visionNameLastStand[64];
	char visionNameFlare[64];
	char visionNameInfrared[64];
	char visionNameTvguided[64];
	char visionNameExtraCam[64];
	bool drewReticle;
	bitarray<64> extraButton_bits;
	bool breathPressedLastFrame;
	int lastActionSlotTime;
	bool playerTeleported;
	float flareRatioLastFrame;
	int stepViewStart;
	float stepViewChange;
	$BE9F66374A020A9809EEAF403416A176 lastFrame; //close
	int oldCommandTime;
	vec3_t oldOrigin;
	vec3_t oldViewangles;
	transPlayerState_t oldTransPlayerState;
	hudElemSoundInfo_t hudElemSound[32];
	int nextRippleTime;
	unsigned int impactEffectsNext;
	unsigned int impactEffects[256];
	float warDesiredMomentumProgress;
	float warCurrentMomentumProgress;
	int warMomentumMultiplier;
	int warMomentumBlitzkriegTime;
	int warMomentumFlashTime;
	float gunnerPitchOffset;
	unsigned int centInNextSnapshot[32];
	centity_t *slideFakeEnt;
	int cameraLinkedEntitiesCount;
	int cameraLinkedEntities[4];
	link_type_e cameraLinkedEntitiesType[4];
	vec3_t cameraLinkedEntitiesOffset[4];
	int groundTiltEntNum;
	int poisoned;
	int *genericMaterialMap[64];
	bool genericFilterPassEnabled[8][4];
	int *genericFilterPassMaterial[8][4];
	int genericFilterPassTarget[8][4];
	int genericFilterPassSampler0[8][4];
	int genericFilterPassSampler1[8][4];
	float genericFilterPassParam[8][4][16];
	int genericFilterPassQuads[8][4];
	int genericFilterBitFlag[8];
	bool genericOverlayEnabled[3];
	int *genericOverlayMaterial[3];
	float genericOverlayParam[3][16];
	int genericOverlaySortIndex[3];
	float genericOverlayParamADS[8];
	bool genericOverlayEnableADS;
	int swimming;
	int swimmingStartTime;
	int missileViewWobbleLastTime;
	vec3_t missileViewWobbleFreq;
	vec3_t missileViewWobbleAmp;
	int counterSpinTime;
	float counterSpinTarget;
	float counterSpinAngle;
	int extraCamEntity;
	int extraCamActive;
	int extraCamStatic;
	vec3_t extraCamOrigin;
	vec3_t extraCamAngles;
	int hasLocalRadar;
	vec2_t localRadarPos;
	float localRadarProgress;
	int globalScramblerActive;
	float scramblerEnemyAlpha;
	float scramblerFriendlyAlpha;
	int popUpSwayStartTime;
	float popupRotationAngle;
	float popUpAngleDelta;
	CompassScrambler compassScrambler[16];
	centity_t *closestEnemyScrambler;
	int alliesFlagAway;
	int axisFlagAway;
	int resetWeaponStateFlag;
	int delayedShieldHitEventsCount;
	ShieldHitDelayedEvent delayedShieldHitEvents[2];
	int recentKilledByClientNum;
	int recentKilledByTime;
	int recentVictimClientNums[8];
	int recentVictimTimes[8];
	int recentVictimIndex;
	bool talkingToEnemy;
	FogSettings serverFogSettings;
	bool forceInfraredMaterialsStreaming;
	bool sonarAttachmentOn;
	bool hudOutlineOn;
	bool sonarAttachmentFullscreenOn;
	DroppedWeaponDobjInfo droppedWeaponDobjInfo[64];
	vec3_t traceHitPos;
	int traceHitDistance;
	bool traceHitEnemy;
	int rangeFinderStartTime;
	bool rangeFinderTimerActive;
	bool rangeFinderPerformTrace;
	bool rangeFinderPerformFxVisTest;
	int playerVehicleEntity;
	bool clientCollisionLinked;
	float altScopeFrac;
	int lastAltScopeFracUpdateTime;
	bool useAlternateAimAssistParams;
	bool useFlashLight;
	int empStartTime;
	int lastEmpTime;
	footstepEvent_t footstepEvents[16];
	unsigned int numFootstepEvents;
	int movers[64];
	int moversCount;
	bullet_hit_info_t hit_infos[12];
	int num_hit_infos;
	int hit_charge;
	bool hit_possible;
	bool bClientNeedsConnectCallback;
	targetInfo_t targets[32];
	snd_ambient_script_data soundAmbientData[32];
	int numAmbientDataStructs;
	snd_ambient_script_data *defaultAmbientRoom;
	snd_ambient_collider soundAmbientColliderData[64];
	int currentAmbientRoom;
	int currentAmbientPackage;
	unsigned int ambientRoomOverride;
	unsigned int ambientPackageOverride;
	int shoutcastListenInBits;
	Weapon selectedClassWeapon;
	int gumpTransitionState;
	vec3_t gumpTransitionColor;
	float gumpTransitionAlpha;
	int gumpTransitionTime;
	int hudDpadShown;
	int resetLuiNeeded;
	int hostMigrationOccured;
	int safeSpectatorCamTime;
	vec3_t safeSpectatorCamPos;
	vec3_t safeSpectatorCamOffset;
	team_t team;
};

struct ClientArchiveData
{
	int serverTime;
	vec3_t origin;
	vec3_t velocity;
	int bobCycle;
	int movementDir;
	PlayerVehicleState playerVehStateClientArchive;
};

struct outPacket_t
{
	int p_cmdNumber;
	int p_serverTime;
	int p_realtime;
};

struct clSnapshot_t
{
	int valid;
	int snapFlags;
	int serverTime;
	int physicsTime;
	int messageNum;
	int deltaNum;
	int ping;
	int cmdNum;
	playerState_s ps;//6C
	int numEntities;
	int numClients;
	int numActors;
	int parseMatchStateIndex;
	int parseEntitiesIndex;
	int parseClientsIndex;
	int parseActorsIndex;
	int serverCommandNum;
};

#define FL_NONE 0
#define FL_CROUCH 0x4
#define FL_PRONE 0x8
#define FL_DEAD 0x40000
#define FL_ZOOM 0x80000
#define FL_FIRE 0x800000

enum StanceState
{
	CL_STANCE_STAND = 0x0,
	CL_STANCE_CROUCH = 0x1,
	CL_STANCE_PRONE = 0x2,
	CL_STANCE_DIVE_TO_PRONE = 0x3,
};

struct clientActive_t
{
	MatchState *parseMatchStatesBuf;
	int numParseMatchStates;
	int maxParseMatchStates;
	entityState_s *parseEntitiesBuf; //0x84
	int numParseEntities;
	int maxParseEntities;
	clientState_s *parseClientsBuf;
	int numParseClients;
	int maxParseClients;
	actorState_s *parseActorsBuf;
	int numParseActors;
	int maxParseActors;
	outPacket_t *outPackets;
	clSnapshot_t *snapshots;
	int packetBackupCount;
	int packetBackupMask;
	int gameStateMarker;
	bool usingAds;
	int timeoutcount;
	clSnapshot_t snap; //4C
	int snapServerTime;
	int oldSnapServerTime;
	bool alwaysFalse;
	int serverTime;
	int oldServerTime;
	int oldFrameServerTime;
	int serverTimeDelta;
	int extrapolatedSnapshot;
	int newSnapshots;
	int serverId;
	int forceNewSnapshots;
	int unpausedTimeBehind;
	int serverTimeErrorIndex;
	int serverTimeErrorCount;
	int serverTimeErrorCumul;
	int serverTimeErrorAvg;
	int serverTimeErrorPrev;
	int serverTimeError[20];
	int serverTimeError2[20];
	char mapname[64];
	int parseMatchStateIndex;
	int parseEntitiesIndex;
	int parseClientsIndex;
	int parseActorsIndex;
	bool stanceHeld;
	StanceState stance;
	StanceState stancePosition;
	int stanceTime;
	bool weapNextHeld;
	int weapNextTime;
	bool switchingToInventory;
	Weapon cgameUserCmdWeapon;
	Weapon cgameUserCmdOffHandWeapon;
	Weapon cgameUserCmdLastWeaponForAlt;
	float cgameFOVSensitivityScale;
	float cgameMaxPitchSpeed;
	float cgameMaxYawSpeed;
	vec3_t cgameKickAngles;
	vec3_t cgameOrigin;
	vec3_t cgameVelocity;
	PlayerVehicleState cgamePlayerVehState;
	int cgameBobCycle;
	int cgameMovementDir;
	bitarray<64> cgameExtraButton_bits;
	int cgamePredictedDataServerTime;
	vec3_t viewangles;
	int skelTimeStamp;
	volatile int skelMemPos;
	char skelMemory[262144];
	char *skelMemoryStart;
	bool allowedAllocSkel;
	usercmd_s cmds[128];
	int cmdNumber;
	ClientArchiveData clientArchive[256];
	int clientArchiveIndex;
	entityState_s entityBaselines[1024];
	int corruptedTranslationFile;
	char translationVersion[256];
	int lastFireTime;
	bool useHeld;
	int useTime;
	int useCount;
	int wasInVehicle;
	int serverFrameMS;
	int serverKbps;
	int serverKbpsAvg[2];
	int serverKbpsCount[2];
};

struct SonarAttachmentInfo
{
	vec3_t prevOrigin;
	float movementDistance[60];
	int nextMovementDistanceIndex;
};

struct animation_s
{
	char name[64];
	int initialLerp;
	int finalLerp;
	float forceAnimRate;
	float moveSpeed;
	float rotSpeed;
	int duration;
	int nameHash;
	int flags;
	int64_t movetype;
	int stance;
	int movestatus;
	int noteType;
};

struct lerpFrame_t
{
	float yawAngle;
	int yawing;
	float pitchAngle;
	int pitching;
	int animationNumber;
	animation_s *animation;
	int animationTime;
	vec3_t oldFramePos;
	float oldFrameYaw;
	float animSpeedScale;
	int oldFrameSnapshotTime;
};

struct clientInfo_t
{
	int infoValid;
	int nextValid;
	int clientNum;
	char name[32];
	team_t team;
	team_t oldteam;
	ffa_team_t ffaTeam;
	int clanAbbrev_IsEliteValidated;
	int64_t leagueTeamID;
	int leagueDivisionID;
	int64_t leagueSubdivisionID;
	int *hLeagueDivisionIcon;
	int leagueSubdivisionRank;
	int rank;
	union {
		int prestige;
		int lastDaysPlayed;
	} __u14;
	int needsRevive;
	unsigned int perks[2];
	int64_t xuid;
	char clanAbbrev[8];
	score_s score;
	int *hStatusIcon;
	int *hRankIcon;
	int location;
	int health;
	char model[64];
	char attachModelNames[6][64];
	char attachTagNames[6][64];
	unsigned int modelChecksum;
	unsigned int attachModelChecksums[6];
	unsigned int attachTagChecksums[6];
	lerpFrame_t legs;
	lerpFrame_t torso;
	float lerpMoveDir;
	float lerpLean;
	vec3_t playerAngles;
	int leftHandGun;
	int dobjDirty;
	clientControllers_t control;
	int lastDamageTime;
	int lastStandStartTime;
	int turnedHumanTime;
	int64_t moveType;
	int64_t eventType;
	int beingRevived;
	unsigned int clientConditions[25];
	int *pXAnimTree;
	Weapon DObjWeapon;
	char weaponModel;
	Weapon DObjOffhandWeapon;
	Weapon DObjMeleeWeapon;
	char meleeWeaponModel;
	int showReloadClipInHand;
	int hideWeaponClipModel;
	int dropWeaponClipTime;
	int stanceTransitionTime;
	int turnAnimEndTime;
	char turnAnimType;
	int attachedVehEntNum;
	int attachedVehSeat;
	bool hideWeapon;
	unsigned int weaponHideBits[5];
	bool usingKnife;
	bool usingGrenade;
	bool usingLaser;
	int nextHideWeaponTime;
	vec3_t vehAnimLastOrg;
	vec3_t vehAnimLastAngle;
	int vehAnimLastBone;
	int vehAnimLastTime;
	int vehAnimLerpStartTime;
	int vehAnimLerpEndTime;
	float weaponSpinLerp;
	float lastWeaponSpinLerp;
	float weaponSpin;
	bool wasFiring[5];
	int laseFXCentNum;
	unsigned int laseFXHandle;
	int clientUIVisibilityFlags;
	int teleportTime;
	bool teleportBit;
	int surfaceType;
	int movemcentityType;
	int footstepEventCount;
	SonarAttachmentInfo sonarAttachmentInfo;
	float infraredFadeOut;
	WeaponDobjInfo weaponDobjInfo;
	int offhandWeaponVisible;
};

struct trace__t
{
	struct hybrid_vector
	{
		__m128 vec;
	}normal; //0x0
	float fraction; //0x10
	int sflags; //0x14
	int cflags; //0x18
	TraceHitType hitType; //0x1C
	unsigned short hitId; //0x20
	unsigned short modelIndex; //0x22
	unsigned short partName; //0x24
	unsigned short boneIndex; //0x26
	unsigned short partGroup; //0x28
	bool allsolid; //0x2A
	bool startsolid; //0x2B
	bool walkable; //0x2C
	struct cStaticModel_s *staticModel; //0x30
	int hitPartition; //0x34
};

struct BulletFireParams_
{
	int worldEntNum;
	int skipNum;
	float damageMultiplier;
	int methodOfDeath; //bulletType?
	vec3_t origStart;
	vec3_t start;
	vec3_t end;
	vec3_t dir;
};

struct BulletTraceResults__
{
	trace1_t trace;
	int hitEnt;
	Vector3 hitPos;
	bool ignoreHitEnt;
	int depthSurfaceType; //0x4C
	char _0x50[0x4]; //0x50
	int hitSurfaceType; //0x54
};

struct BulletTraceResults_
{
	char data[0x2F4];
};

#pragma region Vehicle Def
/* 2747 */
struct VehicleDriveBySound
{
	int apex;
	const char *name;
	unsigned int alias;
};

/* 2748 */
struct VehicleEngineSound
{
	const char *name;
	unsigned int alias;
	float params[5];
};

/* 2749 */
struct VehicleGearData
{
	float minRPM;
	float maxRPM;
	float ratio;
};

/* 2750 */
struct VehicleEngine
{
	float idleRpms;
	float maxRpms;
	float maxTorque;
	float brakingCoeff;
	float loadFadeParams[4];
	float loadScale;
	float loadSmoothing;
	float throttleLag;
	float pitchScale;
	VehicleEngineSound onload[5];
	VehicleEngineSound offload[5];
	int numGears;
	int loopLastGear;
	VehicleGearData gears[10];
};

/* 2751 */
struct VehicleAntenna
{
	float springK;
	float damp;
	float length;
	float gravity;
};
struct view_limits_t
{
	float horizSpanLeft;
	float horizSpanRight;
	float vertSpanUp;
	float vertSpanDown;
	float horizResistLeft;
	float horizResistRight;
	float vertResistUp;
	float vertResistDown;
};
enum TractionType
{
	TRACTION_TYPE_FRONT = 0x0,
	TRACTION_TYPE_BACK = 0x1,
	TRACTION_TYPE_ALL_WD = 0x2,
	NUM_TRACTION_TYPES = 0x3,
};
struct VehicleParameter
{
	float m_speed_max;
	float m_accel_max;
	float m_reverse_scale;
	float m_steer_angle_max;
	float m_steer_angle_speed_scale;
	float m_steer_speed;
	float m_wheel_radius;
	float m_susp_spring_k;
	float m_susp_damp_k;
	float m_susp_adj;
	float m_susp_hard_limit;
	float m_susp_min_height;
	float m_tire_fric_fwd;
	float m_tire_fric_side;
	float m_tire_fric_brake;
	float m_tire_fric_hand_brake;
	float m_body_mass;
	float m_roll_stability;
	float m_pitch_stability;
	float m_pitch_roll_resistance;
	float m_yaw_resistance;
	float m_upright_strength;
	float m_tilt_fakey;
	float m_peel_out_max_speed;
	float m_tire_damp_coast;
	float m_tire_damp_brake;
	float m_tire_damp_hand;
	float m_auto_hand_brake_min_speed;
	TractionType m_traction_type;
	const char *m_name;
	vec3_t m_bbox_min;
	vec3_t m_bbox_max;
	vec3_t m_mass_center_offset;
	vec3_t m_buoyancybox_min;
	vec3_t m_buoyancybox_max;
	float m_water_speed_max;
	float m_water_accel_max;
	float m_water_turn_accel;
	float m_water_turn_speed_max;
	float m_water_ebrake_power;
	vec3_t m_boat_motor_offset;
	float m_boat_speed_rise;
	float m_boat_speed_tilt;
	float m_boat_side_fric_scale;
	float m_boat_forward_fric_scale;
	float m_boat_vertical_fric_scale;
	float m_jump_force;
	float m_tire_fric_side_max;
	bool m_drive_on_walls;
	float m_linear_drag_scale;
	float m_angular_drag_scale;
};
const struct VehicleDef
{
	const char *name;
	__int16 type;
	int remoteControl;
	int bulletDamage;
	int armorPiercingDamage;
	int grenadeDamage;
	int projectileDamage;
	int projectileSplashDamage;
	int heavyExplosiveDamage;
	__int16 cameraMode;
	int autoRecenterOnAccel;
	int thirdPersonDriver;
	int thirdPersonUseVehicleRoll;
	int thirdPersonCameraPitchVehicleRelative;
	int thirdPersonCameraHeightWorldRelative;
	float thirdPersonCameraRange;
	float thirdPersonCameraMinPitchClamp;
	float thirdPersonCameraMaxPitchClamp;
	float thirdPersonCameraHeight[2];
	float thirdPersonCameraPitch[2];
	int cameraAlwaysAutoCenter;
	float cameraAutoCenterLerpRate;
	float cameraAutoCenterMaxLerpRate;
	float thirdPersonCameraSpringDistance;
	float thirdPersonCameraSpringTime;
	float thirdPersonCameraHandbrakeTurnRateInc;
	float cameraFOV;
	float cameraRollFraction;
	vec3_t tagPlayerOffset;
	int killcamCollision;
	float killcamDist;
	float killcamZDist;
	float killcamMinDist;
	float killcamZTargetOffset;
	float killcamFOV;
	float killcamNearBlur;
	float killcamNearBlurStart;
	float killcamNearBlurEnd;
	float killcamFarBlur;
	float killcamFarBlurStart;
	float killcamFarBlurEnd;
	int isDrivable;
	int numberOfSeats;
	int numberOfGunners;
	int seatSwitchOrder[11];
	int driverControlledGunPos;
	float entryPointRadius[5];
	float texScrollScale;
	float wheelRotRate;
	float extraWheelRotScale;
	int wheelChildTakesSteerYaw;
	float maxSpeed;
	float maxSpeedVertical;
	float accel;
	float accelVertical;
	float rotRate;
	float rotAccel;
	float maxBodyPitch;
	float maxBodyRoll;
	float collisionDamage;
	float collisionSpeed;
	float suspensionTravel;
	float heliCollisionScalar;
	float viewPitchOffset;
	float viewInfluence;
	float tiltFromAcceleration[2];
	float tiltFromDeceleration[2];
	float tiltFromVelocity[2];
	float tiltSpeed[2];
	const char *turretWeapon;
	view_limits_t turretViewLimits;
	float turretRotRate;
	int turretClampPlayerView;
	int turretLockTurretToPlayerView;
	const char *gunnerWeapon[4];
	uint16_t gunnerWeaponIndex[4];
	float gunnerRotRate;
	vec2_t gunnerRestAngles[4];
	view_limits_t passengerViewLimits[6];
	const char *sndNames[2];
	unsigned int sndIndices[2];
	const char *sndMaterialNames[3];
	float skidSpeedMin;
	float skidSpeedMax;
	const char *futzName;
	float futzBlend;
	int animType;
	const char *animSet;
	int scriptedAnimationEntry;
	float mantleAngles[4];
	uint16_t extraWheelTags[4];
	uint16_t driverHideTag;
	void *attachmentModels[4];
	uint16_t attachmentTags[4];
	void *deathAttachmentModels[4];
	uint16_t deathAttachmentTags[4];
	float tracerOffset[2];
	void *model;
	void *viewModel;
	void *deathModel;
	void *enemyModel;
	float modelSwapDelay;
	void *exhaustFx;
	int oneExhaust;
	void *treadFx[32];
	void *deathFx;
	uint16_t deathFxTag;
	const char *deathFxSound;
	void *lightFx[4];
	uint16_t lightFxTag[4];
	void *friendlyLightFx;
	uint16_t friendlyLightFxTag;
	void *enemyLightFx;
	uint16_t enemyLightFxTag;
	float radiusDamageMin;
	float radiusDamageMax;
	float radiusDamageRadius;
	const char *shootShock;
	const char *shootRumble;
	float deathQuakeScale;
	float deathQuakeDuration;
	float deathQuakeRadius;
	const char *rumbleType;
	float rumbleScale;
	float rumbleDuration;
	float rumbleRadius;
	float rumbleBaseTime;
	float rumbleAdditionalTime;
	int healthDefault;
	int healthMin;
	int healthMax;
	int eTeam;
	int boostAccelMultiplier;
	float boostDuration;
	float boostSpeedIncrease;
	int addToCompass;
	int addToCompassEnemy;
	const char *compassIcon;
	pvoid *compassIconMaterial;
	const char *gasButtonName;
	int gasButton;
	const char *reverseBrakeButtonName;
	int reverseBrakeButton;
	const char *handBrakeButtonName;
	int handBrakeButton;
	const char *attackButtonName;
	int attackButton;
	const char *attackSecondaryButtonName;
	int attackSecondaryButton;
	const char *boostButtonName;
	int boostButton;
	const char *moveUpButtonName;
	int moveUpButton;
	const char *moveDownButtonName;
	int moveDownButton;
	const char *switchSeatButtonName;
	int switchSeatButton;
	const char *steerGraphName;
	void *steerGraph;
	const char *accelGraphName;
	void *accelGraph;
	int isNitrous;
	int isFourWheelSteering;
	int useCollmap;
	float radius;
	float minHeight;
	float maxHeight;
	float max_fric_tilt_angle;
	float max_fric_tilt;
	int noDirectionalDamage;
	int fakeBodyStabilizer;
	float vehHelicopterBoundsRadius;
	float vehHelicopterDecelerationFwd;
	float vehHelicopterDecelerationSide;
	float vehHelicopterDecelerationUp;
	float vehHelicopterTiltFromControllerAxes;
	float vehHelicopterTiltFromFwdAndYaw;
	float vehHelicopterTiltFromFwdAndYaw_VelAtMaxTilt;
	float vehHelicopterTiltMomentum;
	int vehHelicopterQuadRotor;
	int vehHelicopterAccelTwardsView;
	float maxRotorArmMovementAngle;
	float maxRotorArmRotationAngle;
	int vehHelicopterMaintainHeight;
	int vehHelicopterMaintainMaxHeight;
	float vehHelicopterMaintainHeightLimit;
	float vehHelicopterMaintainHeightAccel;
	float vehHelicopterMaintainHeightMinimum;
	float vehHelicopterMaintainHeightMaximum;
	float vehHelicopterMaintainCeilingMinimum;
	int joltVehicle;
	int joltVehicleDriver;
	float joltMaxTime;
	float joltTime;
	float joltWaves;
	float joltIntensity;
	VehicleParameter nitrousVehParams;
	float driveBySoundRadius[2];
	VehicleDriveBySound driveBySounds[40];
	int doFootSteps;
	int isSentient;
	VehicleEngine engine;
	VehicleAntenna antenna[2];
	char *csvInclude;
	float customFloat0;
	float customFloat1;
	float customFloat2;
	int customBool0;
	int customBool1;
	int customBool2;
};
#pragma endregion

/* 1265 */
struct GfxDrawSurfFields
{
	unsigned __int64 objectId : 16;
	unsigned __int64 fade : 4;
	unsigned __int64 customIndex : 5;
	unsigned __int64 reflectionProbeIndex : 3;
	unsigned __int64 hdrBits : 1;
	unsigned __int64 glightRender : 1;
	unsigned __int64 dlightRender : 1;
	unsigned __int64 materialSortedIndex : 12;
	unsigned __int64 primaryLightIndex : 8;
	unsigned __int64 surfType : 4;
	unsigned __int64 prepass : 2;
	unsigned __int64 noDynamicShadow : 1;
	unsigned __int64 primarySortKey : 6;
};

/* 1266 */
union GfxDrawSurf
{
	GfxDrawSurfFields fields;
	unsigned __int64 packed;
};

/* 1267 */
struct __declspec(align(8)) MaterialInfo
{
	const char *name;
	unsigned int gameFlags;
	char pad;
	char sortKey;
	char textureAtlasRowCount;
	char textureAtlasColumnCount;
	GfxDrawSurf drawSurf;
	unsigned int surfaceTypeBits;
	unsigned int layeredSurfaceTypes;
	unsigned __int16 hashIndex;
};

struct Material
{
	MaterialInfo info;
	char stateBitsEntry[130];
	char textureCount;
	char constantCount;
	char stateBitsCount;
	char stateFlags;
	char cameraRegion;
	char maxStreamedMips;
	int ___u8;
	int *textureTable;
	int ___u10;
	int *stateBitsTable;
};



enum eAttachment
{
	ATTACHMENT_NONE = 0x0,
	ATTACHMENT_ACOG = 0x1,
	ATTACHMENT_DUALCLIP = 0x2,
	ATTACHMENT_DUALOPTIC = 0x3,
	ATTACHMENT_DW = 0x4,
	ATTACHMENT_EXTBARREL = 0x5,
	ATTACHMENT_EXTCLIP = 0x6,
	ATTACHMENT_EXTRAMAGS = 0x7,
	ATTACHMENT_FASTADS = 0x8,
	ATTACHMENT_FASTRELOAD = 0x9,
	ATTACHMENT_FMJ = 0xA,
	ATTACHMENT_GL = 0xB,
	ATTACHMENT_GRIP = 0xC,
	ATTACHMENT_HOLO = 0xD,
	ATTACHMENT_IR = 0xE,
	ATTACHMENT_IRONSIGHTS = 0xF,
	ATTACHMENT_LONGBREATH = 0x10,
	ATTACHMENT_MK = 0x11,
	ATTACHMENT_MMS = 0x12,
	ATTACHMENT_RANGEFINDER = 0x13,
	ATTACHMENT_REFLEX = 0x14,
	ATTACHMENT_RF = 0x15,
	ATTACHMENT_SELECTFIRE = 0x16,
	ATTACHMENT_SILENCER = 0x17,
	ATTACHMENT_STACKFIRE = 0x18,
	ATTACHMENT_STALKER = 0x19,
	ATTACHMENT_STEADYAIM = 0x1A,
	ATTACHMENT_SWAYREDUC = 0x1B,
	ATTACHMENT_TACKNIFE = 0x1C,
	ATTACHMENT_VZOOM = 0x1D,
	ATTACHMENT_TYPE_COUNT = 0x1E,
	ATTACHMENT_INVALID = 0x1E,
};


enum eAttachmentPoint
{
	ATTACHMENT_POINT_NONE = 0x0,
	ATTACHMENT_POINT_TOP = 0x1,
	ATTACHMENT_POINT_FIRST = 0x1,
	ATTACHMENT_POINT_BOTTOM = 0x2,
	ATTACHMENT_POINT_TRIGGER = 0x3,
	ATTACHMENT_POINT_MUZZLE = 0x4,
	ATTACHMENT_POINT_GUNPERK = 0x5,
	ATTACHMENT_POINT_COUNT = 0x6,
	ATTACHMENT_POINT_INVALID = 0x6,
};


struct WeaponAttachment
{
	const char *szInternalName;
	const char *szDisplayName;
	eAttachment attachmentType;
	eAttachmentPoint attachmentPoint;
	PenetrateType penetrateType;
	weapFireType_t fireType;
	int firstRaisePriority;
	float fHipIdleAmount;
	bool bAltWeaponAdsOnly;
	bool bAltWeaponDisableSwitching;
	float altScopeADSTransInTime;
	float altScopeADSTransOutTime;
	bool bSilenced;
	bool bDualMag;
	bool laserSight;
	bool bInfraRed;
	bool bUseAsMelee;
	bool bDualWield;
	bool sharedAmmo;
	float fDamageRangeScale;
	float fAdsZoomFov1;
	float fAdsZoomFov2;
	float fAdsZoomFov3;
	float fAdsZoomInFrac;
	float fAdsZoomOutFrac;
	float fAdsTransInTimeScale;
	float fAdsTransOutTimeScale;
	float fAdsRecoilReductionRate;
	float fAdsRecoilReductionLimit;
	float fAdsViewKickCenterSpeedScale;
	float fAdsIdleAmountScale;
	bool swayOverride;
	float swayMaxAngle;
	float swayLerpSpeed;
	float swayPitchScale;
	float swayYawScale;
	float swayHorizScale;
	float swayVertScale;
	bool adsSwayOverride;
	float adsSwayMaxAngle;
	float adsSwayLerpSpeed;
	float adsSwayPitchScale;
	float adsSwayYawScale;
	float fAdsSwayHorizScale;
	float fAdsSwayVertScale;
	float adsMoveSpeedScale;
	float fHipSpreadMinScale;
	float fHipSpreadMaxScale;
	float strafeRotR;
	float standMoveF;
	vec3_t vStandRot;
	float fFireTimeScale;
	float fReloadTimeScale;
	float fReloadEmptyTimeScale;
	float fReloadAddTimeScale;
	float fReloadQuickTimeScale;
	float fReloadQuickEmptyTimeScale;
	float fReloadQuickAddTimeScale;
	bool mmsWeapon;
	bool mmsInScope;
	float mmsFOV;
	float mmsAspect;
	float mmsMaxDist;
	float clipSizeScale;
	int iClipSize;
	unsigned int stackFire;
	float stackFireSpread;
	float stackFireAccuracyDecay;
	unsigned int perks[2];
	float customFloat0;
	float customFloat1;
	float customFloat2;
	int customBool0;
	int customBool1;
	int customBool2;
};

#pragma region client active
struct outPacket_tt
{
	int p_cmdNumber;
	int p_serverTime;
	int p_realtime;
};
struct playerState_sss {
	int commandTime;				/// 0x0000 - 0x0004
	int pm_type;					/// 0x0004 - 0x0008
	int pm_flags;					/// 0x0008 - 0x000C
	long long weapFlags;			/// 0x000C - 0x0018
	int otherFlags;					/// 0x0018 - 0x001C
	int pm_time;					/// 0x001C - 0x0020
	unsigned int loopSoundId;		/// 0x0020 - 0x0024
	int loopSoundFade;				/// 0x0024 - 0x0028
	Vector3 origin;					/// 0x0028 - 0x0034
	Vector3 velocity;				/// 0x0034 - 0x0040
	char _0x000040[0x4C];			/// 0x0040 - 0x008C
	int gravity;					/// 0x008C - 0x0090
	float leanf;					/// 0x0090 - 0x0094
	int speed;						/// 0x0094 - 0x0098
	Vector3 delta_angles;			/// 0x0098 - 0x00A4
	int groundEntityNum;			/// 0x00A4 - 0x00A8
	int moverEntityNum;				/// 0x00A8 - 0x00AC
	int moverTimestamp;				/// 0x00AC - 0x00B0
	int groundType;					/// 0x00B0 - 0x00B4
	Vector3 vLadderVec;				/// 0x00B4 - 0x00C0
	int jumpTime;					/// 0x00C0 - 0x00C4
	float jumpOriginZ;				/// 0x00C4 - 0x00C8
	int slideTime;					/// 0x00C8 - 0x00CC
	int moveType;					/// 0x00CC - 0x00D0
	int legsTimer;					/// 0x00D0 - 0x00D4
	int torsoTimer;					/// 0x00D4 - 0x00D8
	int legsAnim;					/// 0x00D8 - 0x00E0
	int legsAnimDuration;			/// 0x00DC - 0x00E0
	int torsoAnimDuration;			/// 0x00E0 - 0x00E4
	int damageTimer;				/// 0x00E4 - 0x00E8
	int damageDuration;				/// 0x00E8 - 0x00EC
	int dmgDirection;				/// 0x00EC - 0x00F0
	int dmgType;					/// 0x00F0 - 0x00F4
	int corpseIndex;				/// 0x00F4 - 0x00F8
	int movementDir;				/// 0x00F8 - 0x00FC
	int eFlags;						/// 0x00FC - 0x0100
	int eFlags2;					/// 0x0100 - 0x0104
	char _0x000104[0xB4];			/// 0x0104 - 0x01B8
	int weapon;						/// 0x01B8 - 0x01BC
	char _0x0001BC[0x3C];			/// 0x01BC - 0x01F8
	Vector3 viewangles;				/// 0x01F8 - 0x0204
	char _0x002CAC[0x5604];			/// 0x0204 - 0x5808
};
struct clSnapshot_tt
{
	int valid;
	int snapFlags;
	int serverTime;
	int physicsTime;
	int messageNum;
	int deltaNum;
	int ping;
	int cmdNum;
	playerState_sss ps;
	int numEntities;
	int numClients;
	int numActors;
	int parseMatchStateIndex;
	int parseEntitiesIndex;
	int parseClientsIndex;
	int parseActorsIndex;
	int serverCommandNum;
};
struct usercmd_ss
{
	int time;
	int buttons;
	int Buf8;
	int viewAngles[3];
	int weapon;
	int offHandIndex;
	int Buf20;
	char fDir;
	char rDir;
	char Buf[0x16];
};
struct MatchStatee
{
	/// reverse oneday
};
struct entityState_ss {
	/// reverse later ?
};
struct clientState_ss
{
	int clientIndex;
	int team;
	int ffaTeam;
	int modelindex;
	int riotShieldNext;
	int attachModelIndex[6];
	int attachTagIndex[6];
	char name[32];
	float maxSprintTimeMultiplier;
	int rank;
};
struct actorState_ss {
	/// reverse later ( idc rn )
};
struct clientactive_tt {
	MatchState * parseMatchStatesBuf;		/// 0x00000 - 0x00004
	int numParseMatchStates;				/// 0x00004 - 0x00008
	int maxParseMatchStates;				/// 0x00008 - 0x0000C
	entityState_ss * parseEntitiesBuf;		/// 0x0000C - 0x00010
	int numParseEntities;					/// 0x00010 - 0x00014
	int maxParseEntities;					/// 0x00014 - 0x00018
	clientState_ss * parseClientsBuf;		/// 0x00018 - 0x0001C
	int numParseClients;					/// 0x0001C - 0x00020
	int maxParseClients;					/// 0x00020 - 0x00024
	actorState_ss * parseActorsBuf;			/// 0x00024 - 0x00028
	int numParseActors;						/// 0x00028 - 0x0002C
	int maxParseActors;						/// 0x0002C - 0x00030
	outPacket_tt * outPackets;				/// 0x00030 - 0x00034
	clSnapshot_tt * snapshot;				/// 0x00034 - 0x00038
	char _000000000038[0xC];				/// 0x00038 - 0x00044
	bool usingAds;							/// 0x00044 - 0x00045
	char _0x00108[0xC3];					///	0x00045 - 0x00108
	Vector3 delta_angles;                    /// 0x00108 - 0x00114
	char _0x02C94[0x2B80];					/// 0x00114 - 0x02C94
	Vector3 viewAngles;						/// 0x02C94 - 0x02C9C
	char padding03[0x40010];				//  0x02C9C - 0x42CB0
	usercmd_ss cmds[128];					///	0x42CB0 - 0x468B0
	int cmdNumber;							/// 0x468B0 - 0x468B4
};
#pragma endregion


#endif