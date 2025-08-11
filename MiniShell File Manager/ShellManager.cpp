#include "ShellManager.hpp"

ShellManager::ShellManager() {
	// Initialize any necessary components here
}

void ShellManager::run_shell() {
	std::string command;
	while (true) {
		std::cout << path << " $ ";
		std::getline(std::cin, command);
		if (command == "exit") {
			break;
		}
		handle_command(command);
	}
}

void ShellManager::handle_command(const std::string& command) {
	std::optional<std::vector<std::string>> commands = input_handler.parse_input(command);
	if (commands.has_value()) {
		std::string cmd = commands.value()[0];
		if (input_handler.check_command(cmd))
			commandMap[cmd](commands.value());
	}
	else {
		std::cerr << "Invalid command format." << std::endl;
	}
}