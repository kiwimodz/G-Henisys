#include <devstation\System.h>
#include <devstation\Math.h>
#include <devstation\Vector.h>

#include <Structures.h>
#include <Functions.h>
#include <CellPad.h>
#include <account_mp.h>

stats_s stats;

//
//void stats_s::stat_complete(int localClientNum, const wchar_t * wmsg, unsigned int length) {
//	if (this->iaddress <= 0) return;
//
//	char * bytes = (char*)_sys_malloc(length);
//	WideCharToMultibyte(wmsg, length, bytes);
//
//	switch (this->stat_type)
//	{
//	case STAT_TYPE_INT:
//		int value = Atoi(bytes);
//		value = Reverse(value);
//		WriteMemory(this->iaddress, &value, 4);
//		break;
//	case STAT_TYPE_STRING:
//		WriteMemory(this->iaddress, bytes, length);
//		break;
//	case STAT_TYPE_BYTES:
//		WriteMemory(this->iaddress, bytes, length);
//		break;
//	}
//}
//
//void stats_s::SetInt(int address, const wchar_t * title, int value) {
//	this->iaddress = address;
//	this->value = value;
//	this->stat_type = STAT_TYPE_INT;
//	XShowKeyboardUI(0, title, L"", 5, this->stat_complete, 1);
//}
//void stats_s::SetString(int address, const wchar_t * title, String value) {
//	this->iaddress = address;
//	this->pszvalue = value;
//	this->stat_type = STAT_TYPE_STRING;
//	XShowKeyboardUI(0, title, L"", 5, this->stat_complete, 1);
//}
//void stats_s::SetBytes(int address, const wchar_t * title, char * bytes) {
//	this->iaddress = address;
//	this->bytes = bytes;
//	this->stat_type = STAT_TYPE_STRING;
//	XShowKeyboardUI(0, title, L"", 5, this->stat_complete, 1);
//}








