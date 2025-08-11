#include "FileFunctions.hpp"
namespace fs = std::filesystem;

FileFunctions::FileFunctions() = default;

std::filesystem::path FileFunctions::string_to_path(std::string& path_str) {
    return std::filesystem::path(path_str);
}


void FileFunctions::search_file(const std::filesystem::path& the_path, const std::string& the_file) const {
    std::queue<fs::path> directories;
    directories.push(the_path);

    while (!directories.empty()) {
        fs::path current_path = directories.front();
        directories.pop();

        try {
            for (const auto& entry : fs::directory_iterator{ current_path }) {
                if (entry.path().filename().string() == the_file) {
                    std::cout << entry.path() << std::endl;
                }

                if (is_directory(entry) && !is_symlink(entry)) {
                    directories.push(entry.path());
                }
            }
        }
        catch (fs::filesystem_error const e) {
            //cout << "ERROR: " << e.what() << endl;
            //I'll just skip this part, maybe i just exclude try-catch
        }
    }

}

void FileFunctions::display_files(std::filesystem::path& the_path) const {
    //utility.cleanscr();
    std::cout << "In directory: " << the_path << std::endl;
    try {
        for (const auto& dirs : fs::directory_iterator{ the_path }) {
            //std::cout << dirs.path().filename().string() << std::endl;
            std::cout << reinterpret_cast<const char*>(dirs.path().filename().u8string().c_str()) << std::endl;
        }
    }
    catch (fs::filesystem_error const& e) {
        std::cout << "ERROR1: " << e.what() << std::endl;
    }


}

void FileFunctions::display_dirs(std::filesystem::path& the_path) const {
    //utility.cleanscr();
    std::cout << "In directory: " << the_path << std::endl;
    try {
        for (const auto& dirs : fs::directory_iterator{ the_path }) {
            if (is_directory(dirs)) std::cout << dirs.path().filename() << std::endl;
            //std::cout << dirs.path().filename() << std::endl;
        }
    }
    catch (fs::filesystem_error const& e) {
        std::cout << "ERROR2: " << e.what() << std::endl;
    }
}

void FileFunctions::delete_folder(std::filesystem::path& the_path, const std::string file_to_delete) const {
    //utility.cleanscr();
    try {
        for (auto& dirs : fs::directory_iterator{the_path}) {
            if (dirs.path().filename().string() == file_to_delete) {
                if (fs::is_directory(dirs.path())) {
                    fs::remove_all(the_path/file_to_delete);
                    return;
                }
            }
        }
    }
    catch (fs::filesystem_error const e) {
        std::cout << "ERROR: " << e.what() << std::endl;
    }
    //std::cout << "ERROR: Folder does not exists in the current folder." << std::endl;
}

void FileFunctions::delete_file(std::filesystem::path& the_path, const std::string file_to_delete) const {
    //utility.cleanscr();
    try {
        for (auto& dirs : fs::directory_iterator{ the_path }) {
            if (dirs.path().filename().string() == file_to_delete) {
                if (fs::is_regular_file(fs::status(the_path / file_to_delete))) {
                    fs::remove(the_path / file_to_delete);
                    return;
                }
                    
            }
        }
    }
    catch (fs::filesystem_error const e) {
        std::cout << "ERROR: " << e.what() << std::endl;
    }
    //std::cout << "ERROR: Folder does not exists in the current folder." << std::endl;
}

void FileFunctions::parent_directory(std::filesystem::path& the_path) const {
    //utility.cleanscr();
    if(the_path != the_path.root_directory()) {
	    the_path = the_path.parent_path();
    }
}

void FileFunctions::create_directory(std::filesystem::path& the_path, const std::string& directory_name) const {
    //utility.cleanscr();
    if (fs::exists(the_path / directory_name) ) {
        std::cout << "Folder already exists." << std::endl;
        return;
    }
    try {
        fs::create_directory(the_path / directory_name);
    }
    catch (fs::filesystem_error const e) {
        std::cout << "ERROR: " << e.what() << std::endl;
    }
}

void FileFunctions::enter_directory(std::filesystem::path& the_path, const std::string& directory_name) const {
    if(fs::is_directory(fs::status(the_path / directory_name)) && !fs::is_block_file(fs::status(the_path / directory_name))) {
        the_path = the_path / directory_name;
        return;
	}
    /*
    for (auto& dirs : fs::directory_iterator{ the_path }) {
        if (dirs.path().filename().string() == directory_name) {
            if (fs::is_directory(fs::status(the_path / directory_name))) {
				the_path = the_path / directory_name;
                return;
            }
        }
    }
    */
	std::cout << "ERROR: Directory does not exist in the current folder." << std::endl;
}

void FileFunctions::rename_file(const std::filesystem::path& the_path, const std::string& old_name, const std::string& new_name) const {
    //utility.cleanscr();
    try {
        fs::rename(the_path / old_name, the_path / new_name);
    }
    catch (fs::filesystem_error const e) {
        std::cout << "ERROR: " << e.what() << std::endl;
    }
}

void FileFunctions::copy_file(const std::filesystem::path& the_path, const std::string& file_to_copy) {
    try{
        if (fs::exists(the_path / file_to_copy)) {
			copy_path = the_path / file_to_copy;
        } else {
            std::cout << "ERROR: File does not exist." << std::endl;
        }
    }
    catch (fs::filesystem_error const e) {
        std::cout << "ERROR: " << e.what() << std::endl;
	}
}

void FileFunctions::paste_file(const std::filesystem::path& the_path) const {
    try {
        if (fs::exists(copy_path)) {
            fs::copy(copy_path, the_path / copy_path.filename());
        } else {
            std::cout << "ERROR: No file to paste." << std::endl;
        }
    }
    catch (fs::filesystem_error const e) {
        std::cout << "ERROR: " << e.what() << std::endl;
    }
}


//doesnt work, i dont know why
void FileFunctions::enter_directory_path(std::filesystem::path& the_path, std::string& directory_name) {
    std::filesystem::path new_path = directory_name; //= string_to_path(directory_name);
    if(std::filesystem::is_directory(new_path)) {
        //std::filesystem::current_path(new_path);
		the_path = new_path;
    } else {
        std::cout << "ERROR: The specified path is not a directory." << std::endl;
	}
}


//no need for this
void FileFunctions::remove_file_or_dir(const std::filesystem::path& the_path, const std::string delete_name) const {
    //utility.cleanscr();
    try {
        if (fs::is_directory(fs::status(the_path/ delete_name))) {
            fs::remove_all(the_path/delete_name);
        }
        else if (fs::is_regular_file(fs::status(the_path/ delete_name))) {
            fs::remove(the_path/delete_name);
        }
        else {
            std::cout << "ERROR: The path is neither a file nor a directory." << std::endl;
        }
    }
    catch (fs::filesystem_error const e) {
        std::cout << "ERROR: " << e.what() << std::endl;
    }
}

