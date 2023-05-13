#include "bot.h"
#include <iostream>

Bot::Bot(Offsets *offsets, std::function<void(WPARAM)> send_key) : offsets(offsets), send_key(send_key)
{
	values = &offsets->values;

	low_heal.enabled = true;
	low_heal.hotkey = VK_F1;
	low_heal.percentage = 97;
	low_heal.is_spell = true;
	low_heal.min_mana = 20;

	med_heal.enabled = true;
	med_heal.hotkey = VK_F11;
	med_heal.percentage = 70;
	med_heal.is_spell = true;
	med_heal.min_mana = 100;

	high_heal.enabled = true;
	high_heal.hotkey = VK_F12;
	high_heal.percentage = 45;
	high_heal.is_spell = true;
	high_heal.min_mana = 160;

	mana.enabled = true;
	mana.hotkey = VK_F2;
	mana.percentage = 35;

	waste.enabled = true;
	waste.hotkey = VK_F1;
	waste.percentage = 99;

	haste.enabled = true;
	haste.hotkey = VK_F6;
	haste.min_mana = 100;

	paralyze.enabled = true;
	paralyze.hotkey = VK_F1;
};

DWORD Bot::string_to_dword(char *string)
{
	long int value = std::strtol(string, nullptr, 10);
	return static_cast<DWORD>(value);
}

float Bot::percentage_value(DWORD value, DWORD percentage)
{
	return (float)value / 100 * (float)percentage;
}

void Bot::tick()
{
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		offsets->refresh_values();

		heal(high_heal);
		heal(med_heal);
		heal(low_heal);

		restore_mana();

		cure_paralyze();

		auto_haste();

		waste_mana();
	}
}

void Bot::heal(Heal heal)
{
	if (heal.enabled != true)
	{
		return;
	}

	if (values->current_health > percentage_value(values->total_health, heal.percentage))
	{
		return;
	}

	if (heal.is_spell && values->current_mana < heal.min_mana)
	{
		return;
	}

	send_key(heal.hotkey);
}

void Bot::restore_mana()
{
	if (mana.enabled != true)
	{
		return;
	}

	if (values->current_mana < percentage_value(values->total_mana, mana.percentage))
	{
		send_key(mana.hotkey);
	}
}

void Bot::cure_paralyze()
{
	if (paralyze.enabled != true)
	{
		return;
	}

	if (values->paralyze == 2)
	{
		send_key(paralyze.hotkey);
	}
}

void Bot::waste_mana()
{
	if (waste.enabled != true)
	{
		return;
	}

	if (values->current_mana > percentage_value(values->total_mana, waste.percentage))
	{
		send_key(waste.hotkey);
	}
}

void Bot::auto_haste()
{
	if (haste.enabled != true)
	{
		return;
	}

	if (values->paralyze != 0)
	{
		return;
	}

	if (values->current_mana > haste.min_mana)
	{
		send_key(haste.hotkey);
	}
}
