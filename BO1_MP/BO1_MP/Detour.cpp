#include <devstation\System.h>
#include <devstation\Detour.h>

#define EXECUTABLE_SECTION __attribute__((section(".text"))) // Cant Execute Data Segment
unsigned char STUB_ADDRESS_BLOCK[0x5000] EXECUTABLE_SECTION;

void DetourFunction(int address, int hookFunc, int stubFunc) {
	int StubData[8], FuncData[4];

	int hook_address = hookFunc != NULL ? *(int*)hookFunc : 0;
	int stub_address = stubFunc != NULL ? *(int*)stubFunc : 0;

	if (stub_address) {
		int branchAddr = address + 0x10;
		StubData[0] = 0x3D600000 + ((branchAddr >> 16) & 0xFFFF) + (branchAddr & 0x8000 ? 1 : 0);
		StubData[1] = 0x396B0000 + (branchAddr & 0xFFFF);
		StubData[2] = 0x7D6903A6;
		StubData[7] = 0x4E800420;
		ReadMemory(address, &StubData[3], 0x10);
		MemCopy((pvoid)stub_address, StubData, 0x20);
	}

	if (hook_address) {
		FuncData[0] = 0x3D600000 + ((hook_address >> 16) & 0xFFFF) + (hook_address & 0x8000 ? 1 : 0);
		FuncData[1] = 0x396B0000 + (hook_address & 0xFFFF);
		FuncData[2] = 0x7D6903A6;
		FuncData[3] = 0x4E800420;
		MemCopy((pvoid)address, FuncData, 0x10);
	}
}

unsigned int PRX_TOC_ADDRESS = 0;
unsigned char* Detour::HookSection = STUB_ADDRESS_BLOCK;
unsigned int Detour::HookCount = 0;

void Detour::Restore() {
	if (this->isHooked)
		MemCopy((pvoid)this->Address, this->RestoreInstructions, 0x10);
	this->isHooked = false;
}

Detour::~Detour() {
	this->Restore();

	/*delete[] this->stubTOC;*/
	
	_sys_free(this->stubTOC);

	MemCopy(this, 0, sizeof(Detour));
}

Detour::Detour() {
	MemCopy(this, 0, sizeof(Detour));
}
#define MALLOC_(struct_data) ((struct_data*)(_sys_malloc(sizeof(struct_data))))
unsigned int Detour::AllocateStub() {
	

	/*this->stubTOC = new int[2];*/
	this->stubTOC = (int*)_sys_malloc(sizeof((int*)this->stubTOC));

	unsigned int stubInstructions = (unsigned int)((int)&this->HookSection[0] + (this->HookCount * 0x20));
	this->HookCount++;

	this->stubTOC[0] = stubInstructions;
	this->stubTOC[1] = TOC;

	return (unsigned int)&this->stubTOC[0];
}

void Detour::Hook(int address, void(*hookFunc)) {
	this->Address = address;
	this->hookFunction = (int)hookFunc;
	this->Stub = (void*(*)(...))this->AllocateStub();

	MemCopy((pvoid)this->Address, this->RestoreInstructions, 0x10);

	DetourFunction(this->Address, this->hookFunction, (int)this->Stub);

	this->isHooked = true;
}