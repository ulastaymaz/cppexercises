#include <iostream>
#include <filesystem>
#include <string>
#include <sstream>
#include <vector>
#include <queue>



namespace fs = std::filesystem;
using namespace std;
void cleanscr() {
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


//File searching with BFS, it is really slow...
void search_file(fs::path the_path, const string &the_file) {
    queue<fs::path> directories;
    directories.push(the_path);

    while (!directories.empty()) {
        fs::path current_path = directories.front();
        directories.pop();

        try {
            for (const auto &entry : fs::directory_iterator{current_path}) {
                if (entry.path().filename().string() == the_file) {
                    cout << entry.path() << endl;
                }

                if (is_directory(entry) && !is_symlink(entry)) {
                    directories.push(entry.path());
                }
            }
        } catch (fs::filesystem_error const &e) {
            //cout << "ERROR: " << e.what() << endl;
            //I'll just skip this part, maybe i just exclude try-catch
        }
    }
}


//Display all the files in the current folder
void display_files(fs::path &the_path) {

    cleanscr();
    std::cout << "In directory: " << the_path << std::endl;
    try {
        for (const auto &dirs : fs::directory_iterator{the_path}) {
            std::cout << dirs.path().filename().string()<< std::endl;
        }
    } catch (fs::filesystem_error const &e) {
        std::cout << "ERROR1: " << e.what() << std::endl;
    }
}


//Display all the directories in the current folder
void display_dirs(fs::path &the_path) {
    cleanscr();
    cout << "In directory: " << the_path << endl;
    try {
        for(const auto &dirs : fs::directory_iterator{the_path}) {
            if(is_directory(dirs)) cout << dirs.path().filename().string() << endl;
        }
    } catch(fs::filesystem_error const &e) {
        cout << "ERROR2: " << e.what() << endl;
    }


}

//Split string, can be easier
vector<string> split_comd(const std::string &s) {
    std::stringstream ss(s);
    std::string word;
    std::vector<string> words;
    while (getline(ss, word, ' ')) {
        words.push_back(word);
    }
    return words;
}

void take_command(fs::path &path1, const std::string &comd, fs::path &copy_path) {
    if (comd.empty()) return;

    fs::path temp = path1;
    vector<string> command_vec = split_comd(comd);
    //cleanscr();

    //DELETE FILE
    if (command_vec[0] == "-delete" || command_vec[0] == "-d") {
        if (command_vec.size()==1) {
            cout << "Only -delete command is taken, please use command as -delete filename."<<endl;
            return;
        }
        path1 /= command_vec[1];
        try {
            fs::remove(path1);
        } catch (fs::filesystem_error const &e) {
            std::cout << "ERROR IN COMMAND: " << e.what() << std::endl;
        }
        path1 = temp;
    } 
    //////////////////////////////////////////////////////////
    //Enter folder in the current folder
    else if (command_vec[0] == "-enter" || command_vec[0] == "-e") {
        if (command_vec.size()==1) {
            cout << "Only -enter command is taken, please use command as -enter filename."<<endl;
            return;
        }
        try{
            for (auto &dirs : fs::directory_iterator{path1}) {
                if(dirs.path().filename().string() == command_vec[1]) {
                    if(fs::is_directory(dirs.path())){   
                        path1 /= command_vec[1];
                        return;
                    }
                }
            }
        } catch(fs::filesystem_error const &e) {
            cout << "ERROR: " << e.what() << endl;
        }
            std::cout << "ERROR: Folder does not exists in the current folder." << std::endl;
            //path1 = temp;
    } 
    //////////////////////////////////////////////////////////
    //Go to parent folder
    else if (command_vec[0] == "-up" || command_vec[0] == "-u") {
        if (path1 != path1.root_directory()) {
            path1 = path1.parent_path();
        }
    } 
    //////////////////////////////////////////////////////////
    //List all files in the folder
    else if(command_vec[0] == "-list" || command_vec[0] == "-l") {
        display_files(path1);
        
    } 
    //////////////////////////////////////////////////////////
    //List all directories in the folder
    else if(command_vec[0] == "-listdir" || command_vec[0] == "-ld") {
        display_dirs(path1);
        
    } 
    //////////////////////////////////////////////////////////
    //Rename the file
    else if(command_vec[0] == "-rename" || command_vec[0] == "-rm") {
        if(command_vec.size()<3){
            cout << "Invalid input. Enter as -rename filename1 filename2" << endl;
            return;
        } 
        try {
                for(auto &dirs : fs::directory_iterator{path1}){
                    if(dirs.path().filename().string() == command_vec[1]) {
                        cout << "DEGISTI" << endl;
                        fs::rename(path1 / command_vec[1], path1 / command_vec[2]);
                        return;
                    }
                }
                cout << "File couldn't found" << endl;
                /* DOESN'T WORK
                if(fs::exists(command_vec[1])) {
                    cout <<"dogru"<<endl;
                    fs::rename(path1 / command_vec[1], path1 / command_vec[2]);
                }
                */
        } catch(fs::filesystem_error const &e) {
            cout << "ERROR: " << e.what() << endl;
        }
    }
    //////////////////////////////////////////////////////////
    //Create folder
    else if (command_vec[0] == "-create" || command_vec[0] == "-cr") {
        if (command_vec.size()<2){
            cout << "Invalid input. Enter as -create filename" << endl;
            return;
        } 
        else if (fs::exists(path1/command_vec[1])) {
            cout << "Folder already exists." << endl;
            return;
        }
        try {
                fs::create_directory(command_vec[1]);
        } catch(fs::filesystem_error const &e) {
            cout << "ERROR: " << e.what() << endl;
        }
    }
    //////////////////////////////////////////////////////////
    //Copy file or folder
    else if (command_vec[0] == "-copy" || command_vec[0] == "-cd") {
        if (command_vec.size()<2){
            cout << "Invalid input. Enter as -copy filename" << endl;
            return;
        } 
        else if (!fs::exists(path1/command_vec[1])) {
            cout << "Folder does not exists." << endl;
            return;
        }
        try {
                copy_path = path1 / command_vec[1];
        } catch(fs::filesystem_error const &e) {
            cout << "ERROR: " << e.what() << endl;
        }
    }
    //////////////////////////////////////////////////////////
    //Paste file or folder
    else if (command_vec[0] == "-paste" || command_vec[0] == "-pd") {

        try {
                fs::path destination = path1 / copy_path.filename();                
                if (fs::exists(destination)) {
                    fs::remove_all(destination); // Remove the existing directory
                }
                fs::create_directory(copy_path.filename());
                fs::copy(copy_path, destination, fs::copy_options::overwrite_existing | fs::copy_options::recursive);
                copy_path.clear();
        } catch(fs::filesystem_error const &e) {
            cout << "ERROR: " << e.what() << endl;
        }
    }
    //////////////////////////////////////////////////////////
    //Search given file/folder
    else if (command_vec[0] == "-search" || command_vec[0] == "-sr") {
        try {
                fs::path the_path = path1;
                while( the_path != the_path.root_directory() ) {
                    if (the_path == the_path.parent_path()) break;
                    the_path = the_path.parent_path();
                }
                search_file(the_path, command_vec[1]);
                
        } catch(fs::filesystem_error const &e) {
            
            cout << "ERROR: " << e.what() << endl;
        }
    }
}

int main() {

    fs::path path1 = fs::current_path();
    fs::path copy_path;

    while (true) {

        cout << path1.string() << "> " ;
        string comm_s;
        getline(cin, comm_s);
        take_command(path1, comm_s, copy_path);

    }
    return 0;
}