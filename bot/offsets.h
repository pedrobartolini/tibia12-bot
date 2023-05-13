#include <windows.h>
#include <functional>

struct Props
{
	DWORD clientexe;

	DWORD base;
	DWORD player;

	DWORD current_health;
	DWORD total_health;

	DWORD current_mana;
	DWORD total_mana;

	DWORD paralyze;

	DWORD haste;
	DWORD heal_cooldown;
};

class Offsets
{
private:
	void find_heal_cooldown();
	std::function<DWORD(char *)> find_module;
	std::function<DWORD(DWORD)> reader;
	std::function<void(DWORD, DWORD)> writter;

public:
	Props addresses;
	Props values;

	void refresh_addresses();
	void refresh_values();

	Offsets(std::function<DWORD(char *)> find_module, std::function<DWORD(DWORD)> reader, std::function<void(DWORD, DWORD)> writter);
};