#pragma once
#include <iostream>
#include <fstream>
using namespace std;

class Account {
    string username;
    string password;
public:
    Account () {
        this -> username = "DEFAULT";
        this -> password = "12345";
    }
    Account (string username, string password) {
        this -> username = username;
        this -> password = password;
    }
    void readDataBase () {}; // đọc tất cả tài khoản và mật khẩu đã lưu
    void saveDataBase () {}: // ghi thêm tài khoản và mật khẩu mới tạo
    void createNewAccount () {
        string username, password;
        cout << "PLease sign up your Username: ";
        cin >> username;
        this -> username = username;
        cout << "Please sign up your Password: ";
        string temp;
        getline(cin, temp);
        getline(cin, password);
        while (checkpassword(password) == false) {
            cout << "Inappropriate Passwords!" << endl << "Please sign up your password again: ";
            getline(cin, password);
        }
        this -> password = password;
    }
    bool checkpassword (string password) {
        if (password.length() > 10) {
            return false;
        } else {
            int dem = 0;
            for (int i = 0; i < password.length(); i++) {
                if (isblank(password[i])) {
                    return false;
                } else if (!islower(password[i]) && !isupper(password[i]) && !isdigit(password[i])) {
                    dem++;
                }
            }
            if (dem == 0) {
                return false;
            }
        }
        return true;
    }
    void login() {}; // đăng nhập
    void setPassword (string password) {
        this -> password = password;
    }
};
