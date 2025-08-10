#include "Book.hpp"
#include "User.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <optional>
#include <sstream>
//#include <filesystem>

class DataHandler
{
	
public:
    template<typename T>
    void reload_user(const std::string& file_name, std::vector<T>& data_vector) {
        std::ifstream file(file_name);
		std::string line;
		//::filesystem::path file_path(file_name);
        if (file.is_open()) {
            while (std::getline(file, line))
            {
                T temp(" ", " ", " ", " ");
                std::stringstream ss(line);
                std::string word;
                int i = 0;
                while (getline(ss, word, '|'))
                {
                    switch (i)
                    {
                    case 0:
                    {
                        temp.name = word;
                        break;
                    }
                    case 1:
                    {
                        temp.birth_date = word;
                        break;
                    }
                    case 2:
                    {
                        temp.user_id = word;
                        break;
                    }
                    case 3:
                    {
                        temp.password = word;
                        break;
                    }
                    case 4:
                    {
                        temp.number_of_books = stoi(word);
                        break;
                    }
                    default:
                        break;
                    }
                    i++;
                }
                data_vector.push_back(temp);

            }
            file.close();
        }
        else {
            std::cerr << "Error: Unable to open file " << file_name << std::endl;
        }
}
	DataHandler();
	void reload_books(std::vector<Book>& books);
	void save_students(const std::vector<Student>& students);
	void save_admins(const std::vector<Admin>& admins);
	void save_books(const std::vector<Book>& books);
	void reload_students(std::vector<Student>& students);
	void reload_admins(std::vector<Admin>& admins);
};
