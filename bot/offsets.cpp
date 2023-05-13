#include "offsets.h"

Offsets::Offsets(std::function<DWORD(char *)> find_module, std::function<DWORD(DWORD)> reader, std::function<void(DWORD, DWORD)> writter)
	: find_module(find_module), reader(reader), writter(writter)
{
	refresh_addresses();
	refresh_values();
}

void Offsets::refresh_values()
{
	values.current_health = reader(addresses.current_health);
	values.current_mana = reader(addresses.current_mana);
	values.total_health = reader(addresses.total_health);
	values.total_mana = reader(addresses.total_mana);
	values.heal_cooldown = reader(addresses.heal_cooldown);
	values.paralyze = reader(addresses.paralyze);
}

void Offsets::refresh_addresses()
{
	addresses.clientexe = find_module("client.exe");

	addresses.base = reader(addresses.clientexe + 0x10BAD24);
	addresses.player = reader(addresses.base + 0x6C);

	addresses.current_health = addresses.player + 0xC;
	addresses.current_mana = addresses.player + 0x58;

	addresses.total_health = addresses.player + 0x10;
	addresses.total_mana = addresses.player + 0x5C;

	addresses.heal_cooldown = reader(addresses.clientexe + 0x10F9D68);
	addresses.heal_cooldown = reader(addresses.heal_cooldown + 0x8);
	addresses.heal_cooldown = reader(addresses.heal_cooldown + 0x0);
	addresses.heal_cooldown = reader(addresses.heal_cooldown + 0x10);
	addresses.heal_cooldown = reader(addresses.heal_cooldown + 0x34);
	addresses.heal_cooldown = reader(addresses.heal_cooldown + 0x44);
	addresses.heal_cooldown = reader(addresses.heal_cooldown + 0x20);
	addresses.heal_cooldown = reader(addresses.heal_cooldown + 0x8);
	addresses.heal_cooldown = reader(addresses.heal_cooldown + 0x44);
	addresses.heal_cooldown = reader(addresses.heal_cooldown + 0x208);
	addresses.heal_cooldown = addresses.heal_cooldown + 0x18;

	addresses.paralyze = reader(addresses.clientexe + 0x10BAD24);
	addresses.paralyze = reader(addresses.paralyze + 0x2E4);
	addresses.paralyze = reader(addresses.paralyze + 0x10);
	addresses.paralyze = reader(addresses.paralyze + 0x24);
	addresses.paralyze = reader(addresses.paralyze + 0x0);
	addresses.paralyze = reader(addresses.paralyze + 0x34);
	addresses.paralyze = reader(addresses.paralyze + 0x4);
	addresses.paralyze = reader(addresses.paralyze + 0x100);
	addresses.paralyze = reader(addresses.paralyze + 0x78);
	addresses.paralyze = reader(addresses.paralyze + 0x30);
	addresses.paralyze = addresses.paralyze + 0x18;
}
