#pragma once
#include <vector>
#include <string>
#include <filesystem>
#include <string_view>
#include <map>
#include <functional>
#include <set>
#include <optional>
//#include "FileFunctions.hpp"

class InputHandler
{
public:
	InputHandler();
	bool control_command(const std::string& command);
	void cleanscr() const;
	
	bool check_command(std::string command);
	std::optional<std::vector<std::string>> parse_input(const std::string& input);
	
private:
	//FileFunctions file_handler;
	std::set<std::string> commands = {
	"-u", "-up", // go parent directory
	"-e", "-enter", // enter directory
	"-e" ,"-enter", // enter directory
	"-dr", "-delete_dir", // delete folder
	"-d", "-delete", // delete file
	"-l", "-list", // list files and directories
	"-ld", "-list_dir", // list directories
	"-rn" ,"-rename", // rename file or directory
	"-cr" ,"-create", // create directory
	"-cp" ,"-copy", // copy file or directory
	"-pt" ,"-paste" }; // paste file or directory
	

};

