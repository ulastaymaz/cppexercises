#include <iostream>
#include <filesystem>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include "FileFunctions.hpp"
#include "ShellManager.hpp"

namespace fs = std::filesystem;
using namespace std;



int main() {
	ShellManager run_program;
	run_program.run_shell();
	//FileFunctions file_functions;
	//std::filesystem::path current_path = std::filesystem::current_path();
	//file_functions.display_files(current_path);

	//std::cout << "Welcome to MiniShell!" << std::endl;
}