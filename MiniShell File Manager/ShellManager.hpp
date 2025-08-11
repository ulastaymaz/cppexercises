#pragma once
#include "InputHandler.hpp"
#include "FileFunctions.hpp"
#include <iostream>
#include <optional>
#include <map>
#include <vector>
#include <string>
#include <functional>
#include <filesystem>
class ShellManager
{
public:
	ShellManager();
	
	void run_shell();
	
	std::optional<std::vector<std::string>> parse_input(const std::string& input);
private:

	InputHandler input_handler;
	FileFunctions file_handler;

	void handle_command(const std::string& command);
	std::filesystem::path path = std::filesystem::current_path();
	std::map<std::string, std::function<void(const std::vector<std::string>&)>> commandMap = {
		//{"-l", [this](const std::vector<std::string>& cmd) { file_handler.display_files(path); }},
		//{"-list", [this](const std::vector<std::string>& cmd) { file_handler.display_files(path); }},
		{"-l", [this](const std::vector<std::string>& cmd) {
			if (cmd.size() > 1) {
				std::cerr << "Error: '-l' does not take any input." << std::endl;
				return;
			}
			file_handler.display_files(path);
		}},
		{"-list", [this](const std::vector<std::string>& cmd) {
			if (cmd.size() < 2) {
				std::cerr << "Error: '-list' does not take any input." << std::endl;
				return;
			}
			file_handler.display_files(path);
		}},

		//{"-ld", [this](const std::vector<std::string>& cmd) { file_handler.display_dirs(path); }},
		//{"-list_dir", [this](const std::vector<std::string>& cmd) { file_handler.display_dirs(path); }},

		{"-ld", [this](const std::vector<std::string>& cmd) {
			if (cmd.size() > 1) {
				std::cerr << "Error: '-ld' does not take any input." << std::endl;
				return;
			}
			file_handler.display_dirs(path);
		}},
		{"-list_dir", [this](const std::vector<std::string>& cmd) {
			if (cmd.size() < 2) {
				std::cerr << "Error: '-list_dir' does not take any input." << std::endl;
				return;
			}
			file_handler.display_dirs(path);
		}},

		//{"-u", [this](const std::vector<std::string>& cmd) { file_handler.parent_directory(path); }},
		//{"-up", [this](const std::vector<std::string>& cmd) { file_handler.parent_directory(path); }},

		{"-u", [this](const std::vector<std::string>& cmd) {
			if (cmd.size() > 1) {
				std::cerr << "Error: '-u' does not take any input." << std::endl;
				return;
			}
			file_handler.parent_directory(path);
		}},
		{"-up", [this](const std::vector<std::string>& cmd) {
			if (cmd.size() < 2) {
				std::cerr << "Error: '-up' does not take any input." << std::endl;
				return;
			}
			file_handler.parent_directory(path);
		}},

		{"-dr", [this](const std::vector<std::string>& cmd) {
			if (cmd.size() < 2) {
				std::cerr << "Error: '-dr' requires a filename." << std::endl;
				return;
			}
			else if (cmd.size() > 2) {
				std::cerr << "Error: Too many arguments for '-dr'." << std::endl;
				return;
			}
			file_handler.delete_folder(path, cmd[1]);
		}},
		{"-delete_dir", [this](const std::vector<std::string>& cmd) {
			if (cmd.size() < 2) {
				std::cerr << "Error: '-delete_dir' requires a filename." << std::endl;
				return;
			}
			else if (cmd.size() > 2) {
				std::cerr << "Error: Too many arguments for '-delete_dir'." << std::endl;
				return;
			}
			file_handler.delete_folder(path, cmd[1]);
		}},

		//{"-dr", [this](const std::vector<std::string>& cmd) { file_handler.delete_folder(path, cmd[1]); }},
		//{"-delete_dir", [this](const std::vector<std::string>& cmd) { file_handler.delete_folder(path, cmd[1]); }},

		{"-d", [this](const std::vector<std::string>& cmd) {
			if (cmd.size() < 2) {
				std::cerr << "Error: '-d' requires a filename." << std::endl;
				return;
			}
			else if (cmd.size() > 2) {
				std::cerr << "Error: Too many arguments for '-d'." << std::endl;
				return;
			}
			file_handler.delete_file(path, cmd[1]);
		}},
		{"-delete", [this](const std::vector<std::string>& cmd) {
			if (cmd.size() < 2) {
				std::cerr << "Error: '-delete' requires a filename." << std::endl;
				return;
			}
			else if (cmd.size() > 2) {
				std::cerr << "Error: Too many arguments for '-delete'." << std::endl;
				return;
			}
			file_handler.delete_file(path, cmd[1]);
		}},

		//{"-cr", [this](const std::vector<std::string>& cmd) { file_handler.create_directory(path, cmd[1]); }},
		//{"-create", [this](const std::vector<std::string>& cmd) { file_handler.create_directory(path, cmd[1]); }},

		{"-cr", [this](const std::vector<std::string>& cmd) {
			if (cmd.size() < 2) {
				std::cerr << "Error: '-cr' requires a filename." << std::endl;
				return;
			}
			else if (cmd.size() > 2) {
				std::cerr << "Error: Too many arguments for '-cr'." << std::endl;
				return;
			}
			file_handler.create_directory(path, cmd[1]);
		}},
		{"-create", [this](const std::vector<std::string>& cmd) {
			if (cmd.size() < 2) {
				std::cerr << "Error: '-create' requires a filename." << std::endl;
				return;
			}
			else if (cmd.size() > 2) {
				std::cerr << "Error: Too many arguments for '-create'." << std::endl;
				return;
			}
			file_handler.create_directory(path, cmd[1]);
		}},

		//{"-e", [this](const std::vector<std::string>& cmd) { file_handler.enter_directory(path, cmd[1]); }},
		//{"-enter", [this](const std::vector<std::string>& cmd) { file_handler.enter_directory(path, cmd[1]); }},

		{"-e", [this](const std::vector<std::string>& cmd) {
			if (cmd.size() < 2) {
				std::cerr << "Error: '-e' requires a filename." << std::endl;
				return;
			}
			else if (cmd.size() > 2) {
				std::cerr << "Error: Too many arguments for '-e'." << std::endl;
				return;
			}
			file_handler.enter_directory(path, cmd[1]);//////
		}},
		{"-enter", [this](const std::vector<std::string>& cmd) {
			if (cmd.size() < 2) {
				std::cerr << "Error: '-enter' requires a filename." << std::endl;
				return;
			}
			else if (cmd.size() > 2) {
				std::cerr << "Error: Too many arguments for '-enter'." << std::endl;
				return;
			}
			file_handler.enter_directory(path, cmd[1]);
		}},


		//{"-rn", [this](const std::vector<std::string>& cmd) { file_handler.rename_file(path, cmd[1], cmd[2]); }},
		//{"-rename", [this](const std::vector<std::string>& cmd) { file_handler.rename_file(path, cmd[1], cmd[2]); }},

		{ "-rn", [this](const std::vector<std::string>& cmd) {
			if (cmd.size() < 2) {
				std::cerr << "Error: '-rn' requires a filename." << std::endl;
				return;
			}
			else if (cmd.size() > 2) {
				std::cerr << "Error: Too many arguments for '-rn'." << std::endl;
				return;
			}
			file_handler.rename_file(path, cmd[1], cmd[2]);
		} },
		{ "-rename", [this](const std::vector<std::string>& cmd) {
			if (cmd.size() < 2) {
				std::cerr << "Error: '-rename' requires a filename." << std::endl;
				return;
			}
			else if (cmd.size() > 2) {
				std::cerr << "Error: Too many arguments for '-rename'." << std::endl;
				return;
			}
			file_handler.rename_file(path, cmd[1], cmd[2]);
		} },


		{ "-cp", [this](const std::vector<std::string>& cmd) {
			if (cmd.size() < 2) {
				std::cerr << "Error: '-cp' requires a filename." << std::endl;
				return;
			}
			else if (cmd.size() > 2) {
				std::cerr << "Error: Too many arguments for '-cp'." << std::endl;
				return;
			}
			file_handler.copy_file(path, cmd[1]);
		} },
		{ "-copy", [this](const std::vector<std::string>& cmd) {
			if (cmd.size() < 2) {
				std::cerr << "Error: '-copy' requires a filename." << std::endl;
				return;
			}
			else if (cmd.size() > 2) {
				std::cerr << "Error: Too many arguments for '-copy'." << std::endl;
				return;
			}
			file_handler.copy_file(path, cmd[1]);
		} },

		{ "-pt", [this](const std::vector<std::string>& cmd) {
			if (cmd.size() > 1) {
				std::cerr << "Error: Too many arguments for '-pt." << std::endl;
				return;
			}
			file_handler.paste_file(path);
		} },
		{ "-paste", [this](const std::vector<std::string>& cmd) {
			if (cmd.size() > 1) {
				std::cerr << "Error: Too many arguments for '-paste'." << std::endl;
				return;
			}
			file_handler.paste_file(path);
		} },


		{"-rm", [this](const std::vector<std::string>& cmd) { file_handler.remove_file_or_dir(path, cmd[1]); }}
	};

};

