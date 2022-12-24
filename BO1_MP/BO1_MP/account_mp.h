#ifndef account_mp_h
#define account_mp_h

enum statindex_t : int
{
	prestige = 0x26fd014,
	deaths = 0x26FC940, 
	kills = 0x26FCB70,
	headshots = 0x26FCA44,
};
enum stat_type_t
{
	STAT_TYPE_INT,
	STAT_TYPE_STRING,
	STAT_TYPE_BYTES,
};
struct stats_s
{
private :
	int iaddress;
	char * bytes;
	int value;
	String pszvalue;
	stat_type_t stat_type;
	void stat_complete(int localClientNum, const wchar_t * wmsg, unsigned int length);
public:
	void SetInt(int address, const wchar_t * title, int value);
	void SetString(int address, const wchar_t * title, String value);
	void SetBytes(int address, const wchar_t * title, char * bytes);
};


extern stats_s stats;

#endif