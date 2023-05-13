#include <windows.h>
#include <psapi.h>
#include <iostream>

struct Modules
{
	HMODULE array[1024];
	DWORD modules_length;
};

class Process
{
private:
	HANDLE handle;
	Modules modules;
	HWND hwnd;
	DWORD id;
	char *name;

	void get_handle();
	void get_hwnd();
	void get_id();
	void load_module_list();
	void error(char *message);

public:
	DWORD find_module(char *target_module_name);
	DWORD read_address(DWORD address);
	void write_address(DWORD address, DWORD buffer);
	void send_key(WPARAM key);

	Process(char *name);
};