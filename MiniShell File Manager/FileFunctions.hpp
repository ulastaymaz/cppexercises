#pragma once
//#include "Utility.hpp"
#include <iostream>
#include <filesystem>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <locale>
#include <codecvt>
class FileFunctions
{
private:
	std::filesystem::path copy_path;
	std::filesystem::path paste_path;
public:
	FileFunctions();


	std::filesystem::path string_to_path(std::string& path_str);
	void search_file(const std::filesystem::path& the_path, const std::string& the_file) const;
	void display_files(std::filesystem::path& the_path) const;
	void display_dirs(std::filesystem::path& the_path) const;
	void delete_file(std::filesystem::path& the_path, const std::string file_to_delete) const;
	void delete_folder(std::filesystem::path& the_path, const std::string file_to_delete) const;
	void parent_directory(std::filesystem::path& the_path) const;
	void rename_file(const std::filesystem::path& the_path, const std::string& old_name, const std::string& new_name) const;
	void enter_directory_path(std::filesystem::path& the_path, std::string& directory_name);
	void create_directory(std::filesystem::path& the_path, const std::string& directory_name) const;
	void enter_directory(std::filesystem::path& the_path, const std::string& directory_name) const;
	void remove_file_or_dir(const std::filesystem::path& the_path, const std::string delete_name) const;
	void copy_file(const std::filesystem::path& the_path, const std::string& file_to_copy);
	void paste_file(const std::filesystem::path& the_path) const;
};

