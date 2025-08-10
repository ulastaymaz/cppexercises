#include "LibrarySystem.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
using namespace std;

LibrarySystem::LibrarySystem() {
    data_handler.reload_books(books);
    data_handler.reload_students(students);
    data_handler.reload_admins(admins);
}

void LibrarySystem::run() {
	login_menu();
    data_handler.save_books(books);
    data_handler.save_students(students);
    data_handler.save_admins(admins);
}

void LibrarySystem::signup_student() {
	file_handler.signup_student(students);
}

void LibrarySystem::admin_login() {
    optional<Admin> admin_request = file_handler.admin_login_request(admins);
    if (!admin_request.has_value()) {
        return;
	}

	Admin admin_user = admin_request.value();
	handle_admin_menu(admin_user);
}

void LibrarySystem::student_login() {
    optional<Student> student_request = file_handler.student_login_request(students);
    if (!student_request.has_value()) {
        return;
    }
	Student student_user = student_request.value();
	this->handle_student_menu(student_user);
}

void LibrarySystem::login_menu() {
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
			this->student_login();
            break;
        }
        case '2':
        {

            this->signup_student();
            break;

        }
        case '3':
        {
			this->admin_login();
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
            std::cout << ("Press any key to continue...") << std::endl;
            if (!_kbhit())
                _getch();
            break;
        }
        }
    }
}

void LibrarySystem::handle_admin_menu(Admin admin_user) {
    bool while_run = true;
    while (while_run)
    {
        cout << "\033[2J\033[1;1H";
        char key = 0;
        std::cout << "1 -- Account Info: " << std::endl;
        std::cout << "2 -- Borrow Book: " << std::endl;
        std::cout << "3 -- Return Book: " << std::endl;
        std::cout << "4 -- Borrowed books: " << std::endl;
        std::cout << "5 -- Delete book: " << std::endl;
        std::cout << "6 -- Enter new book: " << std::endl;
        std::cout << "7 -- List books: " << std::endl;
        std::cout << "Q -- Quit" << std::endl;
        std::cout << "Press key: ";
        cin >> key;
        switch (key)
        {
        case '1':
        {
			file_handler.user_info(admin_user);
            break;

        }
        case '2':
        {
            file_handler.borrow_book(books, admin_user);
            break;
        }
        case '3':
        {
			file_handler.return_book(admin_user, books);
            break;
        }
        case '4':
        {
			file_handler.borrowed_books(books, admin_user);
            break;
        }
        case '5':
        {
			admin_user.delete_book_by_isbn(books, students, admins);
            break;
        }
        case '6':
        {
            admin_user.enter_book(books);
            break;
        }
        case '7':
        {
			file_handler.list_books(books);
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
            std::cout << ("Press any key to continue...");
            if (!_kbhit())
                _getch();
            break;

        }

        }

    }

}

void LibrarySystem::handle_student_menu(Student student_user) {
    bool while_run = true;
    while (while_run)
    {
        char key = 0;
        std::cout << "1 -- Account Info: " << std::endl;
        std::cout << "2 -- Borrow Book: " << std::endl;
        std::cout << "3 -- Return Book: " << std::endl;
        std::cout << "4 -- Borrowed books: " << std::endl;
		std::cout << "5 -- List available books: " << std::endl;
        std::cout << "Q -- Quit" << std::endl;
        std::cout << "Press key: ";
        cin >> key;
        switch (key)
        {
        case '1':
        {
			file_handler.user_info(student_user);
            break;
        }
        case '2':
        {
            file_handler.borrow_book(books, student_user);
            break;
        }
        case '3':
        {
			file_handler.return_book(student_user, books);
            break;
        }
        case '4':
        {
            
			file_handler.borrowed_books(books, student_user);
            break;
        }
        case '5':
        {

            file_handler.available_books(books);
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
            std::cout << "Press any key to continue..." << std::endl;
            if (!_kbhit()) {
                _getch();
            }
        }
        }
    }
}