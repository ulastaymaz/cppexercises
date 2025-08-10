#pragma once
#include <vector>
#include <string>
#include "Book.hpp"
#include "User.hpp"
#include "Utility.hpp"
#include "DataHandler.hpp"
class LibrarySystem
{
private:
	std::vector<Book> books;
	std::vector<Student> students;
	std::vector<Admin> admins;
	Utility file_handler;
	DataHandler data_handler;
public:
	LibrarySystem();
	void run();
	void login_menu();
	void admin_login();
	void student_login();
	void signup_student();

private:
	void handle_admin_menu(Admin admin_user);
	void handle_student_menu(Student student_user);

};


