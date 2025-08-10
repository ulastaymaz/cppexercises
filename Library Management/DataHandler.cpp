
#include "DataHandler.hpp"
using namespace std;

DataHandler::DataHandler() {};

void DataHandler::save_students(const vector<Student>& students) {
    string line;
    ofstream myfile3("students_text.txt");

    if (myfile3.is_open())
    {
        for (auto student : students)
        {
            myfile3 << student.name << "|" << student.birth_date << "|" << student.user_id << "|" << student.password << "|" << to_string(student.number_of_books) << "\n";
        }
        myfile3.close();
    }

}

void DataHandler::save_admins(const vector<Admin>& admins) {
    string line;
    ofstream myfile5("admins_text.txt");

    if (myfile5.is_open())
    {
        for (auto admin : admins)
        {
            myfile5 << admin.name << "|" << admin.birth_date << "|" << admin.user_id << "|" << admin.password << "|" << to_string(admin.number_of_books) << "\n";
        }
        myfile5.close();
    }

}

void DataHandler::save_books(const vector<Book>& books)
{
    string line;
    ofstream myfile2("books_text.txt");

    if (myfile2.is_open())
    {
        for (auto book : books)
        {
            string temp_availability;
            if (book.available) temp_availability = "true";
            else temp_availability = "false";
            myfile2 << book.book_name << "|" << book.author_name << "|" << book.isbn << "|" << temp_availability << "|" << book.borrowed_by << "\n";

        }
        myfile2.close();
    }

}

void DataHandler::reload_students(vector<Student>& students) {

    this->reload_user("students_text.txt", students);
}

void DataHandler::reload_admins(vector<Admin>& admins) {

	this->reload_user("admins_text.txt", admins);
}

void DataHandler::reload_books(vector<Book>& books)
{
    string line;
    ifstream myfile1("books_text.txt");

    if (myfile1.is_open())
    {
        while (std::getline(myfile1, line))
        {
            Book temp;
            //cout << line << '\n';
            stringstream ss(line);
            string word;
            int i = 0;
            while (getline(ss, word, '|'))
            {
                switch (i)
                {
                case 0:
                {
                    temp.book_name = word;
                    break;
                }
                case 1:
                {
                    temp.author_name = word;
                    break;
                }
                case 2:
                {
                    temp.isbn = word;
                    break;
                }
                case 3:
                {
                    if (word == "true") temp.available = true;
                    else temp.available = false;
                    break;
                }
                case 4:
                {
                    if (word == "None") temp.borrowed_by = "None";
                    else temp.borrowed_by = word;
                    break;
                }
                default:
                    break;
                }
                i++;
            }
            books.push_back(temp);

        }
        myfile1.close();
    }

    else cout << "Unable to open file";

}
