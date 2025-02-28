#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <optional>
using namespace std;
const int MAX_BOOKS = 100;


class Book
{
private:
    
public:
    string book_name, author_name, isbn, borrowed_by="None";
    bool available;
    vector<Book> current_books;
    Book(){}
    Book(string book_name, string author_name, string isbn, bool available=true, string borrowed_by = "None")
    {
        this->book_name=book_name; this->author_name=author_name; this->isbn=isbn;this->available = available;this->borrowed_by=borrowed_by;

    }
    void list_book() const
    {
        std::cout<<"Book Name: "<< book_name<<std::endl;
        std::cout<<"Book Author: "<< author_name<<std::endl;
        std::cout<<"Book ISBN: "<< isbn<<std::endl;
        if (available) std::cout<<"Book Avaiable: "<< "Yes"<<std::endl;
        else std::cout<<"Book Avaiable:"<< "No"<<std::endl;
        std::cout<<"Book borrowed by: "<<borrowed_by<<std::endl;
        std::cout<<"==================================="<<std::endl;
    }

};

class User
{
public:
    string name;
    string birth_date;
    string user_id;
    string password;
    int number_of_books = 0;
    User(){}
    

    string return_name(){
        return name;
    }

protected:

};


class Admin : public User{

    private:


    public:
        Admin(string name, string birth_date, string user_id, string password)
        {
            this->name=name; this->birth_date=birth_date; this->user_id=user_id; this->password=password;
        }
        Admin()
        {
            std::cout<<"Enter Name and Surname: "<<std::endl;
            std::cin>>name;

            std::cout<<"Enter Birthdate: "<<std::endl;
            std::cin>>birth_date;

            std::cout<<"Enter User ID: "<<std::endl;
            std::cin>>user_id;

            std::cout<<"Enter Password: "<<std::endl;
            std::cin>>password;



        }
        //Books can be deleted by admin
        bool delete_book_by_isbn(vector<Book> &current_books, string isbn_1) const
        {  
            for (int i = 0;i<current_books.size();i++)
            {  
                Book temp = current_books[i];
                if (temp.isbn==isbn_1)
                {
                    current_books.erase(current_books.begin() + i);
                    return true;
                }
            }
            return false;
        }
        //New books are registered by admin
        void enter_book(vector<Book> &current_books)
        {
            Book temp;
            std::cout<<"Enter book name: ";
            std::cin>>temp.book_name;
            std::cout<<std::endl;

            std::cout<<"Enter author name: ";
            std::cin>>temp.author_name;
            std::cout<<std::endl;

            std::cout<<"Enter book ISBN: ";
            std::cin>>temp.isbn;
            std::cout<<std::endl;

            std::cout<<"Book registered."<<std::endl;
            current_books.push_back(temp);
            if( !_kbhit() )
                    getch();


        }


};

class Student: public User
{
    public:
        Student(string name, string birth_date, string user_id, string password)
        {
            this->name=name; this->birth_date=birth_date; this->user_id=user_id; this->password=password;
        }
        Student()
        {
            std::cout<<"Enter Name and Surname: "<<std::endl;
            std::cin>>name;
    
            std::cout<<"Enter Birthdate: "<<std::endl;
            std::cin>>birth_date;
    
            std::cout<<"Enter User ID: "<<std::endl;
            std::cin>>user_id;
    
            std::cout<<"Enter Password: "<<std::endl;
            std::cin>>password;   
    
        }
};
//function for listing all books, as name suggests
void list_books(const vector<Book> current_books){

    for (const auto& book: current_books)
    {
        book.list_book();
    }
}
//cin breaks sometimes, i dont know why
string cin_doesnt_work()
{
    string user_id_entered;
    std::cin>>user_id_entered;
    return user_id_entered;

}

char cin_doesnt_work_char()
{
    char user_id_entered;
    std::cout<<"Enter: ";
    std::cin>>user_id_entered;
    return user_id_entered;

}

optional<string> control_admin_return(const string admin_id_entered, vector<Admin> admin_vector)
{
    for(auto const admin: admin_vector)
    {
        if(admin.user_id == admin_id_entered) return admin.user_id;
    }

    return {};
}

optional<string> control_student_return(string user_id_entered, vector<Student> student_vector)
{
    for(auto std: student_vector)
    {
        if(std.user_id == user_id_entered) return std.user_id;
    }

    return{};
}
bool control_book(vector<Book> &books, string isbn_required)
{
    for(auto const book: books)
    {
        if (book.isbn == isbn_required) return true;
    }
    return false;

}

void borrow_book(vector<Book> &books, Book book_required, User student_in_process)
{
    for(auto book: books)
    {
        if (book.isbn == book_required.isbn)
        {
            book.available = false;
            book.borrowed_by = student_in_process.user_id;
        }
    }
    cout<<"Invalid ID!"<<endl;
    std::cout<<( "Press any key to continue..." )<<std::endl;
    if( !_kbhit() )
        getch();

}

void student_main(Student &student_user, vector<Book> &books)
{
    bool while_run = true;
    // Removed the line that sets number_of_books to 100
    while (while_run)
    {
        char key = 0;
        std::cout << "1 -- Account Info: " << std::endl;
        std::cout << "2 -- Borrow Book: " << std::endl;
        std::cout << "3 -- Return Book: " << std::endl;
        std::cout << "4 -- Borrowed books: " << std::endl;
        std::cout << "Q -- Quit" << std::endl;
        std::cout << "Press key" << std::endl;
        key = cin_doesnt_work_char();
        switch (key)
        {
        case '1':
        {
            std::cout << "Name: " << student_user.name << std::endl;
            std::cout << "ID: " << student_user.user_id << std::endl;
            std::cout << "Birth Date: " << student_user.birth_date << std::endl;
            std::cout << "Borrowed books: " << student_user.number_of_books << std::endl;
            std::cout << "Press any key to continue..."<<std::endl;
            if (!_kbhit())
                getch();
            break;
        }
        case '2':
        {
            string isbn_obtained;
            std::cout << "Enter book's ISBN: ";
            std::cin >> isbn_obtained;
            if (control_book(books, isbn_obtained) == false)
                cout << "Invalid ISBN!" << endl;
                std::cout << "Press any key to continue..."<<std::endl;
                if (!_kbhit())
                    getch();
                break;
                
            for (int i = 0; i < books.size(); i++)
            {
                Book *temp = &books[i];
                if (isbn_obtained == temp->isbn)
                {
                    temp->available = false;
                    temp->borrowed_by = student_user.user_id;
                    std::cout << "Book borrowed!" << std::endl;
                    student_user.number_of_books += 1;
                    std::cout << "Press any key to continue..."<<std::endl;
                    if (!_kbhit())
                        getch();
                    break;
                }
            }
            break;
        }
        case '3':
        {
            string isbn_obtained;
            std::cout << "Enter book's ISBN: ";
            std::cin >> isbn_obtained;
            if (control_book(books, isbn_obtained) == false)
            {
                cout << "Invalid ISBN!" << endl;
                std::cout << "Press any key to continue..."<<std::endl;
                if (!_kbhit())
                    getch();
                break;
            }
            for (int i = 0; i < books.size(); i++)
            {
                Book *temp = &books[i];
                if (isbn_obtained == temp->isbn)
                {
                    temp->available = true;
                    temp->borrowed_by = "None";
                    std::cout << "Book returned!" << std::endl;
                    student_user.number_of_books -= 1;
                    std::cout << "Press any key to continue..."<<std::endl;
                    if (!_kbhit())
                        getch();
                    break;
                }
            }
            break;
        }
        case '4':
        {
            std::cout << "#################" << std::endl;
            for (const auto &book_search : books)
            {
                if (book_search.borrowed_by == student_user.user_id)
                {
                    std::cout << "Book name: " << book_search.book_name << " Book author: " << book_search.author_name << " Book ISBN: " << book_search.isbn << std::endl;
                }
            }
            std::cout << "#################" << std::endl;
            std::cout << "Press any key to continue..."<<std::endl;
            if (!_kbhit())
                getch();
            break;
        }
        case 'q':
        case 'Q':
        {
            while_run = false;
            break;
        }
        default:
        {
            std::cout << "Invalid input!" << std::endl;
            std::cout << "Press any key to continue..."<<std::endl;
            if (!_kbhit())
                getch();
        }
        }
    }
}

void admin_main(Admin &admin_user, vector<Book> &books, vector<Student> &students, vector<Admin> &admins)
{
    bool while_run = true;
    while (while_run)
    {
        cout << "\033[2J\033[1;1H";
        char key = 0;
        std::cout<<"1 -- Account Info: "<<std::endl;
        std::cout<<"2 -- Borrow Book: "<<std::endl;
        std::cout<<"3 -- Return Book: "<<std::endl;
        std::cout<<"4 -- Borrowed books: "<<std::endl;
        std::cout<<"5 -- Delete book: "<<std::endl;
        std::cout<<"6 -- Enter new book: "<<std::endl;
        std::cout<<"Q -- Quit"<<std::endl;
        std::cout<<"Press key"<<std::endl;
        key = cin_doesnt_work_char();
        switch(key)
        {
            case '1':
            {

                std::cout<<admin_user.name<<std::endl;
                std::cout<<admin_user.user_id<<std::endl;
                std::cout<<admin_user.birth_date<<std::endl;
                std::cout<<( "Press any key to continue..." );
                if( !_kbhit() )
                    getch();
                break;

            }
            case '2':
            {
                string isbn_obtained;
                std::cout<<"Enter book's ISBN: ";
                std::cin>>isbn_obtained;
                if(control_book(books, isbn_obtained) == false) cout<<"Invalid ISBN!"<<endl;
                for(int i = 0; i<books.size();i++)
                {   
                    Book *temp = &books[i];
                    if(isbn_obtained==temp->isbn)
                    {
                        temp->available = false;
                        temp->borrowed_by = admin_user.user_id;
                        admin_user.number_of_books+=1;
                        break;
                    } 

                }
                break;
            }
            case '3':
            {
                {
                    string isbn_obtained;
                    std::cout<<"Enter book's ISBN: ";
                    std::cin>>isbn_obtained;
                    if(control_book(books, isbn_obtained) == false)
                    {
                        cout<<"Invalid ISBN!"<<endl;
                        break;
                    }
                    for(int i = 0; i<books.size();i++)
                    {   
                        Book *temp = &books[i];
                        if(isbn_obtained==temp->isbn)
                        {
                            temp->available = true;
                            temp->borrowed_by = "None";
                            admin_user.number_of_books-=1;
                            break;
                        } 

                    }
                    break;
                }
            }
            case '4':
            {   
                std::cout<<"#################"<<std::endl;
                for(const auto book_search : books)
                {
                    
                    if (book_search.borrowed_by == admin_user.user_id)
                    {
                        std::cout<<"Book name: "<<book_search.book_name<<" Book author: "<<book_search.author_name<<" Book ISBN: "<<book_search.isbn<<std::endl;
                    }
                }
                std::cout<<"#################"<<std::endl;
                std::cout<<( "Press any key to continue..." );
                        if( !_kbhit() )
                            getch();
                        break;
                break;
            }
            case '5':
            {
                std::cout<<"Enter ISBN: "<<std::endl;
                string isbn_1 = cin_doesnt_work();
                bool is_isbn_correct = false;
                for(auto book_search : books)
                {
                    if (book_search.isbn == isbn_1)
                    {
                        if(admin_user.delete_book_by_isbn(books, isbn_1))
                        {
                            for(auto student : students)
                            {
                                if(student.user_id == book_search.isbn)
                                {
                                    student.number_of_books -=1;
                                    break;
                                }
                            }
                            for(auto admin : admins)
                            {
                                if(admin.user_id == book_search.isbn)
                                {
                                    admin.number_of_books -=1;
                                    break;
                                }
                            }
                            std::cout<<"Book deleted!"<<std::endl;
                            std::cout<<( "Press any key to continue..." );
                            is_isbn_correct=true;
                            if( !_kbhit() )
                                getch();
                            break;
                        }

                    }
                }
                if (is_isbn_correct == false)
                {
                    std::cout<<"Incorrect ISBN!"<<std::endl;
                    if( !_kbhit() )
                                getch();
                    break;
                }
            }
            case '6':
            {
                admin_user.enter_book(books);
                break;
            }
            case 'q':            
            case 'Q':
            {
                while_run=false;
                break;
            }
            default : 
            {
                std::cout<<"Invalid input!"<<std::endl;
                std::cout<<( "Press any key to continue..." );
                        if( !_kbhit() )
                            getch();
                            break;
                break;
            }
            
        }
        //break;
    }
    


}

void available_books(const vector<Book> books)
{
    for(const auto the_book : books)
    {
        if (the_book.available==true) std::cout<<the_book.book_name<<std::endl;
    }

}
void reload_books(vector<Book> &books)
{
    string line;
    ifstream myfile1 ("books_text.txt");

    if (myfile1.is_open())
    {   
        while (std::getline(myfile1,line))
        {
            Book temp; 
          //cout << line << '\n';
            stringstream ss(line);
            string word;
            int i=0;
          while(getline(ss, word, '|'))
          {
            switch(i)
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
                    if(word=="true") temp.available = true;
                    else temp.available = false;
                    break;
                }
                case 4:
                {
                    if(word=="None") temp.borrowed_by = "None";
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
void save_books(vector<Book> books)
{
    string line;
    ofstream myfile2 ("books_text.txt");

    if (myfile2.is_open())
    {
        for(auto book: books)
        {
            string temp_availability;
            if (book.available) temp_availability = "true";
            else temp_availability="false";
            myfile2<<book.book_name<<"|"<<book.author_name<<"|"<<book.isbn<<"|"<<temp_availability<<"|"<<book.borrowed_by<<"\n";
            
        }
        myfile2.close();
    }

}
void save_students(vector<Student> students)
{
    string line;
    ofstream myfile3 ("students_text.txt");

    if (myfile3.is_open())
    {
        for(auto student: students)
        {
            myfile3<<student.name<<"|"<<student.birth_date<<"|"<<student.user_id<<"|"<<student.password<<"|"<<to_string(student.number_of_books)<<"\n"; 
        }
        myfile3.close();
    }

}
void reload_students(vector<Student> &students)
{
    string line;
    ifstream myfile4 ("students_text.txt");

    if (myfile4.is_open())
    {   
        while (std::getline(myfile4,line))
        {
            Student temp(" ", " "," "," "); 
          //cout << line << '\n';
            stringstream ss(line);
            string word;
            int i=0;
            while (getline(ss, word, '|'))
            {
                switch(i)
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
          students.push_back(temp);

        }
        myfile4.close();
    }
    
    else cout << "Unable to open file";

}
void save_admins(vector<Admin> admins)
{
    string line;
    ofstream myfile5 ("admins_text.txt");

    if (myfile5.is_open())
    {
        for(auto admin: admins)
        {
            myfile5<<admin.name<<"|"<<admin.birth_date<<"|"<<admin.user_id<<"|"<<admin.password<<"|"<<to_string(admin.number_of_books)<<"\n"; 
        }
        myfile5.close();
    }

}
void reload_admins(vector<Admin> &admins)
{
    string line;
    ifstream myfile6 ("admins_text.txt");

    if (myfile6.is_open())
    {   
        while (std::getline(myfile6,line))
        {
            Admin temp(" ", " "," "," "); 
          //cout << line << '\n';
            stringstream ss(line);
            string word;
            int i=0;
            while (getline(ss, word, '|'))
            {
                switch(i)
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
          admins.push_back(temp);

        }
        myfile6.close();
    }
    
    else cout << "Unable to open file";

}
int main()
{
    vector<Student> current_students;
    vector<Admin> current_admins;
    vector<Book> current_books;

    reload_books(current_books);
    reload_students(current_students);
    reload_admins(current_admins);

    char key;
    bool run_while = true;

    while (run_while)
    {
        cout << "\033[2J\033[1;1H";
        std::cout << "###############" << std::endl;
        std::cout << "1 -- Login User" << std::endl;
        std::cout << "2 -- Signup User" << std::endl;
        std::cout << "3 -- Login Admin" << std::endl;
        std::cout << "Q -- Quit" << std::endl;
        std::cout << "Press key:  ";
        std::cin >> key;
        cout << "\033[2J\033[1;1H";
        switch (key)
        {
            case '1':
            {
                std::cout<<"Enter ID: ";
                string user_id_entered = cin_doesnt_work();
                optional<string> the_id = (control_student_return(user_id_entered, current_students));
                if (the_id.has_value()==false)
                {
                    std::cout << "Invalid ID!"<<std::endl;
                    std::cout<<( "Press any key to continue..." )<<std::endl;
                    if( !_kbhit() )
                        getch();
                    break;
                }
                for (auto &student_search : current_students)
                {
                    if (student_search.user_id == the_id)
                    {
                        string temp_password;
                        cout << "Enter Password: ";
                        cin >> temp_password;
                        if (temp_password != student_search.password)
                        {
                            cout << "Password is incorrect!" << endl;
                            break;
                        }
                        student_main(student_search, current_books);
                        break;
                    }
                }
                break;
            }
            case '2':
            {
                Student new_student;
                current_students.push_back(new_student);
                std::cout << current_students.size() << endl;
                cout << "\033[2J\033[1;1H";
                break;
            }
            case '3':
            {
                std::cout<<"Enter ID: ";
                string admin_id_entered = cin_doesnt_work();
                optional<string> the_id = (control_admin_return(admin_id_entered, current_admins));
                if (the_id.has_value()==false)
                {
                    std::cout << "Invalid ID!"<<std::endl;
                    std::cout<<( "Press any key to continue..." )<<std::endl;
                    if( !_kbhit() )
                        getch();
                    break;
                }
                for (auto &admin_search : current_admins)
                {
                    if (admin_search.user_id == the_id)
                    {
                        string temp_password;
                        cout << "Enter Password: ";
                        cin >> temp_password;
                        if (temp_password != admin_search.password)
                        {
                            cout << "Password is incorrect!" << endl;
                            std::cout<<( "Press any key to continue..." )<<std::endl;
                            if( !_kbhit() )
                                getch();
                            break;
                            cout << "\033[2J\033[1;1H";
                            break;
                        }
                        admin_main(admin_search, current_books, current_students, current_admins);
                        break;
                    }
                }
                break;
            }
            case 'q':
            case 'Q':
            {
                run_while = false;
                break;
            }
            default:
            {
                cout << "Invalid option!" << endl;
                std::cout<<( "Press any key to continue..." )<<std::endl;
                if( !_kbhit() )
                    getch();
                break;
            }
        }
    }

    save_books(current_books);
    save_students(current_students);
    save_admins(current_admins);
    return 0;
}