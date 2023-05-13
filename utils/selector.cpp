#include "selector.h"

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	EnumWindowsData *data = reinterpret_cast<EnumWindowsData *>(lParam);
	CHAR window_name[256];
	GetWindowTextA(hwnd, window_name, 256);
	if (strstr(window_name, data->substring))
	{
		data->window_names->push_back(window_name);
	}

	return TRUE;
}

std::vector<std::string> filter_windows(char *substring)
{
	EnumWindowsData data;
	data.substring = substring;
	data.window_names = new std::vector<std::string>;
	EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(&data));

	return *data.window_names;
}

void print_options(int selected_index, std::vector<std::string> options)
{
	for (int i = 0; i < options.size(); i++)
	{
		if (i == selected_index)
		{
			std::cout << " > " << options[i] << std::endl;
		}
		else
		{
			std::cout << "   " << options[i] << std::endl;
		}
	}
}

char *select_windows(char *filter_by)
{
	std::vector<std::string> options = filter_windows(filter_by);
	int selected_index = 0;
	while (true)
	{
		system("cls");
		print_options(selected_index, options);

		char ch = _getch();
		if (ch == 72 && selected_index > 0)
		{ // up arrow
			selected_index--;
		}
		else if (ch == 80 && selected_index < options.size() - 1)
		{ // down arrow
			selected_index++;
		}
		else if (ch == 13)
		{ // enter key
			std::cout << "Selected" << std::endl;
			return (char *)options[selected_index].c_str();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}