#include <windows.h>
#include <chrono>
#include <thread>
#include <functional>
#include <cstdlib>
#include "offsets.h"

struct Heal
{
	bool enabled;
	WPARAM hotkey;
	DWORD min_mana;
	DWORD percentage;
	bool is_spell;
};

struct Mana
{
	bool enabled;
	WPARAM hotkey;
	DWORD percentage;
};

struct Waste_mana
{
	bool enabled;
	WPARAM hotkey;
	DWORD percentage;
};

struct Paralyze
{
	bool enabled;
	WPARAM hotkey;
};

struct Haste
{
	bool enabled;
	WPARAM hotkey;
	DWORD min_mana;
};

class Bot
{
private:
	Offsets *offsets;
	Props *values;

	std::function<void(WPARAM)> send_key;
	DWORD string_to_dword(char *string);

	float percentage_value(DWORD value, DWORD percentage);

	void heal(Heal heal);
	void restore_mana();
	void cure_paralyze();
	void auto_haste();
	void waste_mana();

public:
	Heal low_heal;
	Heal med_heal;
	Heal high_heal;

	Mana mana;
	Paralyze paralyze;
	Haste haste;
	Waste_mana waste;

	void tick();

	Bot(Offsets *offsets, std::function<void(WPARAM)> send_key);
};