#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <fstream>
using namespace std;
static vector<string> All_Username;
static vector<string> All_Password;

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
    void saveDataBase () { // ghi thêm tài khoản và mật khẩu mới tạo
        ofstream Username ("D:/MyProject/Account/Username.txt", ios::app);
        Username << this -> username << "\n";
        Username.close();
        ofstream Password ("D:/MyProject/Account/Password.txt", ios::app);
        Password << this -> password << "\n";
        Password.close();
    }
    bool checkpassword (string password) {
        if (password.length() > 20 || password.length() < 5) {
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
    void setPassword (string password) {
        this -> password = password;
    }
    bool findUser(string User, int& pos) {
        for (int i = 0; i < All_Username.size(); i++) {
            if (All_Username[i] == User) {
                pos = i;
                this->username = User;
                return true;
            }
        }
        return false;
    }
    bool findPass(string Pass, int& pos) {
        if (All_Password[pos] == Pass) {
            this->password = Pass;
            return true;
        }
        return false;
    }
    bool findUser(string User) {
        for (int i = 0; i < All_Username.size(); i++) {
            if (All_Username[i] == User) {
                return true;
            }
        }
        return false;
    }
    bool signin(string User, string Pass) {
        if (All_Username.size() == 0 && All_Password.size() == 0) {
            readDataBase();
        }
        int pos;
        if (findUser(User, pos) == true) {
            if (findPass(Pass, pos) == true) {
                cout << "Welcome!" << endl;
                return true;
            }
            else {
                cout << "Incorrect Password!" << endl;
            }
        }
        else {
            cout << "Incorrect Username!" << endl;
        }
        return false;
    }
    void readDataBase() { // đọc tất cả tài khoản và mật khẩu đã lưu
        ifstream Username;
        Username.open("D:/MyProject/Account/Username.txt");
        ifstream Password;
        Password.open("D:/MyProject/Account/Password.txt");
        string temp1;
        while (!Username.eof()) {
            Username >> temp1;
            if (temp1 != "\n") All_Username.push_back(temp1);
        }
        Username.close();
        string temp2;
        while (!Password.eof()) {
            Password >> temp2;
            if (temp2 != "\n") All_Password.push_back(temp2);
        }
        Password.close();
    }
    int signup(string User, string Pass1, string Pass2) {
        if (All_Username.size() == 0 && All_Password.size() == 0) {
            readDataBase();
        }
        if (findUser(User) == true) {
            cout << "Username already exits!" << endl;
            return 1;
        }
        else {
            if (Pass1 == Pass2) {
                if (checkpassword(Pass1)) {
                    this->username = User;
                    this->password = Pass1;
                    saveDataBase();
                }
                else {
                    cout << "Password doesn't meet requirements!" << endl;
                    return 2;
                }
            }
            else {
                cout << "Password doesn't match!" << endl;
                return 3;
            }
        }
        return 0;
    }
};

// hinh nen
// 1 la tu render 
// man hinh chinh co 2 nut sign in va sign up
// sign in no se render ra man hinh dang nhap va goi ham login() trong thu vien Account.cpp
// sign up se render ra man hinh tao tai khoan, tao mot bien Account và goi ham Account.createNewAccount, sau khi create xong thi goi lai ham sign in
// sign in ok thi render ra man hinh chinh
// man hinh dang nhap va tao tk: 2 ô text box để lấy dữ liệu

//render hinh ô sờ kê
//tao button và mouse event, render text
//tao text box va lay du lieu tu ban phim