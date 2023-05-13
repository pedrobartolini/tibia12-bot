#include <chrono>
#include <thread>

#include "utils/selector.h"
#include "utils/process.h"
// #include "opencv/pixel.h"
#include "bot/bot.h"

int main()
{
	// Simple terminal window selector. Filter windows by "Tibia"
	char *selected_window = select_windows("Tibia");

	// Module responsible for loading process and exporting core methods
	Process process(selected_window);
	auto find_module = std::bind(&Process::find_module, &process, std::placeholders::_1);
	auto read_address = std::bind(&Process::read_address, &process, std::placeholders::_1);
	auto write_address = std::bind(&Process::write_address, &process, std::placeholders::_1, std::placeholders::_2);
	auto send_key = std::bind(&Process::send_key, &process, std::placeholders::_1);

	// Module responsible for updating addresses and values (uses core methods from process)
	Offsets offsets(find_module, read_address, write_address);

	// Module responsible for values and key sends
	Bot bot(&offsets, send_key);

	// Start bot thread
	std::thread memory_bot(std::bind(&Bot::tick, &bot));

	// THREAD PARA MUDAR CONFIGS
	while (true)
	{
		std::cout << "bot rodando" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(120000));
	}

	return 1;
}
