#include "InputHandler.hpp"
#include "FileFunctions.hpp"
#include <sstream>

InputHandler::InputHandler() {};

bool InputHandler::control_command(const std::string& command) {
	if(commands.contains(command)) return true;
	else {
		std::cerr << "Invalid command: " << command << std::endl;
		return false;
	}
}

void InputHandler::cleanscr() const {
#if defined _WIN32
    system("cls");
    //clrscr(); // including header file : conio.h
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
    //std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
#elif defined (__APPLE__)
    system("clear");
#endif
}


bool InputHandler::check_command(std::string command) {
    if (commands.contains(command)) return true;
    else {
        //std::cerr << "Invalid command!" << std::endl;
        return false;
    }
}


std::optional<std::vector<std::string>> InputHandler::parse_input(const std::string& input) {
	std::vector<std::string> commands;
	std::string command;
	std::istringstream stream(input);
	while (std::getline(stream, command, ' ')) {
		if (!command.empty()) {
			commands.push_back(command);
		}
	}
	if (!commands.empty() && control_command(commands[0]))	return commands;
	else return {};
}