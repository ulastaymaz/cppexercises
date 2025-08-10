#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <optional>
#include "Utility.hpp"
//namespace view = std::views;
using namespace std;

Utility::Utility() {};

void Utility::borrow_book(vector<Book> &books, User &user_in_process)
{
	string isbn_obtained;
	cout << "Enter book's ISBN: ";
	cin >> isbn_obtained;
    if (control_book(books, string_view{ isbn_obtained }) == false) cout << "Invalid ISBN!" << endl;
    for(auto& book: books)
    {
        if (book.isbn == isbn_obtained)
        {
            if(book.available == false) {
                cout << "This book is already borrowed!" << endl;
                cout << "Press any key to continue..." << endl;
                if (!_kbhit()) {
                    _getch();
                }
                return;
			}
            book.available = false;
            book.borrowed_by = user_in_process.user_id;
			user_in_process.number_of_books += 1;
			cout << "Book borrowed successfully!" << endl;
            if (!_kbhit()) {
                _getch();
            }
            return;
        }
    }
    cout<<"Invalid ID!"<<endl;
    std::cout<<( "Press any key to continue..." )<<std::endl;
    if( !_kbhit() )
        _getch();

}

void Utility::borrowed_books(const vector<Book>& books, const User& user_in_process) {
    if (user_in_process.number_of_books == 0) {
        cout << "You have no borrowed books." << endl;
        if (!_kbhit()) {
            _getch();
        }
        return;
    }
    cout << "Borrowed books:" << std::endl;
    for (const auto& book_search : books) {
        if (book_search.borrowed_by == user_in_process.user_id) {
            cout << "Book name: " << book_search.book_name << endl;
        }
    }
    if (!_kbhit()) {
        _getch();
        return;
    }
}

void Utility::return_book(User & user, vector<Book>&books) {

    optional<size_t> book_idx = find_book_by_isbn(books);
    if(book_idx.has_value() == false)
    {
        cout << "Invalid ISBN!" << endl;
        std::cout << ("Press any key to continue...") << std::endl;
        if (!_kbhit()) {
            _getch();
            return;
        }
	}
	//Book* book_ptr = &books[book_idx.value()];
    if(books[book_idx.value()].available == true) {
        cout << "This book is already available!" << endl;
        std::cout << ("Press any key to continue...") << std::endl;
        if (!_kbhit()) {
            _getch();
            return;
        }
	}
	books[book_idx.value()].borrowed_by = "None";
	books[book_idx.value()].available = true;
	user.number_of_books -= 1;
	cout << "Book returned successfully!" << endl;
    if (!_kbhit()) {
        _getch();
	}
    return;
}

void Utility::available_books(const vector<Book>& books) const
{
    cout << "\033[2J\033[1;1H";
    for(const auto& book_available : books | std::views::filter(&Book::available))  {
        
        cout << std::format("Name: {:<30} | Author: {:<20} | ISBN: {:<15}\n",
            book_available.book_name,
            book_available.author_name,
            book_available.isbn);
	}
    cout << "##############################" << endl;

}

optional<size_t> Utility::find_book_by_isbn(std::vector<Book>& books) {
    string isbn;
	cout << "Enter ISBN: ";
	cin >> isbn;
    for (int i = 0; i < books.size(); i++) {
        if (books[i].isbn == isbn) {
            return i;
        }
    }
    return {}; // Return nullptr if no book is found
}

optional<Admin> Utility::control_admin_return(string_view admin_id_entered, string_view admin_password_entered, const vector<Admin>& admin_vector)
{
    for (auto const admin : admin_vector)
    {
        if(admin.user_id == admin_id_entered && admin.password == admin_password_entered) return admin;
    }

    return {};
}

optional<Student> Utility::control_student_return(string_view user_id_entered, string_view user_password_entered, const vector<Student>& student_vector)
{
    for (auto std : student_vector)
    {
        if (std.user_id ==  user_id_entered && std.password == user_password_entered) return std;
    }

    return{};
}

bool Utility::control_book(vector<Book> &books, string_view isbn_required)
{
    for(auto const& book: books)
    {
        if (book.isbn == isbn_required) return true;
    }
    return false;

}

void Utility::user_info(const User& user_in_process)
{
    std::cout << "Name: " << user_in_process.name << std::endl;
    std::cout << "ID: " << user_in_process.user_id << std::endl;
    std::cout << "Birth Date: " << user_in_process.birth_date << std::endl;
    std::cout << "Borrowed books: " << user_in_process.number_of_books << std::endl;
    std::cout << ("Press any key to continue...") << std::endl;
    if (!_kbhit()) {
        _getch();
    }
}

optional<Student> Utility::student_login_request(vector<Student>& students) {
    std::cout << "Enter ID: ";
    string user_id_entered;
    cin >> user_id_entered;

    std::cout << "Enter password: ";
    string user_password_entered;
    cin >> user_password_entered;
    optional<Student> student_request = (this->control_student_return(string_view{ user_id_entered }, string_view{ user_password_entered }, students));
    if (student_request.has_value() == false)
    {
        std::cout << "Invalid ID or password!" << std::endl;
        std::cout << ("Press any key to continue...") << std::endl;
		_getch(); // Wait for user input
        return {};
    }
    return student_request.value();
}

optional<Admin> Utility::admin_login_request(vector<Admin>& admins) {
    std::cout << "Enter ID: ";
    string admin_id_entered;
	cin >> admin_id_entered;

    std::cout << "Enter password: ";
    string admin_password_entered;
    cin >> admin_password_entered;
    optional<Admin> admin_request = (this->control_admin_return(string_view{ admin_id_entered }, string_view{ admin_password_entered }, admins));
    if (admin_request.has_value() == false)
    {
        std::cout << "Invalid ID or password!" << std::endl;
        std::cout << ("Press any key to continue...") << std::endl;
		_getch(); // Wait for user input
		return {};
    }
	return admin_request.value();

}

void Utility::signup_student(vector<Student>& students) {

    Student new_student;
    students.push_back(new_student);
    std::cout << students.size() << endl;
    cout << "\033[2J\033[1;1H";
}

void Utility::list_books(const vector<Book>& books) const {
    if(books.empty()) {
        cout << "No books available." << endl;
        std::cout << ("Press any key to continue...");
        if (!_kbhit())
            _getch();
        return;
	}
    cout << "List of books: " << endl;
    for (const auto& book_search : books) {
        cout << std::format("Name: {:<30} | Author: {:<20} | ISBN: {:<15} | Available: {}\n",
            book_search.book_name,
            book_search.author_name,
            book_search.isbn,
            book_search.available ? "Yes" : "No");
    }
    std::cout << ("Press any key to continue...");
    if (!_kbhit())
        _getch();
    return;
}