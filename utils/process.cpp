#include "process.h"

Process::Process(char *name) : name(name)
{
	get_hwnd();
	get_id();
	get_handle();
	load_module_list();
}

void Process::get_hwnd()
{
	hwnd = FindWindowA(nullptr, reinterpret_cast<const char *>(name));
	if (hwnd == nullptr)
	{
		error("Could not find window with this name");
	}
}

void Process::get_id()
{
	if (!GetWindowThreadProcessId(hwnd, &id))
	{
		error("Could not find PID");
	}
}

void Process::get_handle()
{
	handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, id);
	if (!handle)
	{
		error("Could not load handle.");
	}
}

void Process::load_module_list()
{
	if (!EnumProcessModulesEx(handle, modules.array, sizeof(modules.array), &modules.modules_length, LIST_MODULES_ALL))
	{
		error("Could not load module list.");
	}
	modules.modules_length /= sizeof(HMODULE);
}

void Process::error(char *message)
{
	char err_tpl[512] = "Process: ";
	char msg_tpl[512] = " -> ";
	strcat(err_tpl, (const char *)name);
	strcat(msg_tpl, message);
	strcat(err_tpl, msg_tpl);
	throw std::runtime_error(err_tpl);
}

void Process::send_key(WPARAM key)
{
	SendMessage(hwnd, WM_KEYDOWN, key, 0);
	SendMessage(hwnd, WM_KEYUP, key, 0);
}

DWORD Process::find_module(char *target_module_name)
{
	char module_name[256];
	for (short i = 0; i < modules.modules_length; ++i)
	{
		if (!GetModuleBaseNameA(handle, modules.array[i], module_name, 256))
		{
			continue;
		}
		if (strcmp(module_name, target_module_name) == 0)
		{
			return static_cast<DWORD>(reinterpret_cast<DWORD_PTR>(modules.array[i]));
		}
	}

	char err_msg[] = "Could not find module ";
	strcat(err_msg, target_module_name);
	error(err_msg);
}

DWORD Process::read_address(DWORD address)
{
	if (!address)
	{
		error("Address is undefined");
	}

	DWORD buffer;
	if (!ReadProcessMemory(handle, (void *)address, &buffer, sizeof(DWORD), NULL))
	{
		return 404;
	}
	return buffer;
}

void Process::write_address(DWORD address, DWORD buffer)
{
	if (!address)
	{
		error("Address is undefined");
	}

	if (!WriteProcessMemory(handle, (void *)address, (void *)&buffer, 8, NULL))
	{
		error("Could not write address");
	}
}