#ifndef hook_h
#define hook_h



typedef uint32_t handle_t;

enum handleCall_t {
	CALL_NONE = 0x0,
	CALL_START = 0x1,
	CALL_EXECUTE = 0x2,
	CALL_TEMP = 0x3,
	CALL_STOP = 0x4,
	CALL_FREE = 0x5,
};

typedef void(*handleCallback)(handle_t* handle, handleCall_t type, int32_t arg);
typedef void(*handleCallback_2)(handle_t* handle, handleCall_t type, int32_t arg, int32_t arg1);

#define HANDLE_COUNT		0x100
#define INVALID_HANDLE		((handle_t)-1)

#define TIME_NOW			clock()
#define TIME_NOW_OFF(x)		(clock() + (x * (CLOCKS_PER_SEC / 1000)))

struct handle_s {
	int arg;
	int arg1;
	bool dualArgs;
	handleCallback function;
	handleCallback_2 function1;
	handleCall_t type;
	handle_t* handle;
	clock_t interval;
	clock_t time;
	clock_t startTime;
};


void handleHookAlloc(handle_t* handle, handleCallback function, clock_t interval, clock_t start_time, int32_t arg);
handle_t handleHookAllocTemp(handleCallback function, clock_t start_time, int32_t arg);
handle_t handleHookAllocTemp_2(handleCallback_2 function, clock_t start_time, int32_t arg, int32_t arg1);
bool handleHookStop(handle_t* handle);
bool doesHandleHookExist(handle_t* handle);
bool handleHookFree(handle_t* handle);
bool handleHookClear(handle_t* handle);
void handleHookExecute();
void handleHookStopAll();
void handleHookClearAll();

#endif