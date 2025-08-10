#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <optional>
#include <string_view>
#include <ranges>
#include <format>
#include "Book.hpp"
#include "User.hpp"



class Utility {
    public:
    Utility();
    void borrow_book(std::vector<Book> &books, User &user_in_process);
    void return_book(User& user, std::vector<Book>& books);
    void available_books(const std::vector<Book>& books) const;
	void borrowed_books(const std::vector<Book>& books, const User& user_in_process);
    void list_books(const std::vector<Book>& books) const;
    bool control_book(std::vector<Book> &books, std::string_view isbn_required);
	void user_info(const User& user_in_process);
    std::optional<Student> student_login_request(std::vector<Student>& students);
    std::optional<Admin> admin_login_request(std::vector<Admin>& admins);
	void signup_student(std::vector<Student>& students);
    std::optional<Admin> control_admin_return(std::string_view admin_id_entered, const std::string_view admin_password_entered, const std::vector<Admin>& admin_vector);
    std::optional<Student> control_student_return(std::string_view user_id_entered, std::string_view user_password_entered, const std::vector<Student>& student_vector);
    std::optional<size_t> find_book_by_isbn(std::vector<Book>& books);
};
