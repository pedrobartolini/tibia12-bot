#include <chrono>
#include <thread>
#include <conio.h>
#include <vector>
#include <windows.h>
#include <iostream>

struct EnumWindowsData
{
	std::vector<std::string> *window_names;
	char *substring;
};

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);

std::vector<std::string> filter_windows(char *substring);

void print_options(int selected_index, std::vector<std::string> options);

char *select_windows(char *filter_by);
