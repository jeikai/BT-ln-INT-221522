#pragma once
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

vector<string> username;
vector<string> password;

bool findAcc(vector<string> check, string temp) {
    for (auto x : check) {
        if (x == temp) {
            return true;
        }
    }
    return false;
}

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
        ofstream Username ("D:/Project/Account/Username.txt", ios::app);
        Username << this -> username << "\n";
        Username.close();
        ofstream Password ("D:/Project/Account/Password.txt", ios::app);
        Password << this -> password << "\n";
        Password.close();
    }
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
    void setPassword (string password) {
        this -> password = password;
    }
};


void readDataBase () { // đọc tất cả tài khoản và mật khẩu đã lưu
    ifstream Username;
    Username.open("D:/Project/Account/Username.txt");
    ifstream Password;
    Password.open("D:/Project/Account/Password.txt");
    string temp1;
    while (!Username.eof()) {
        Username >> temp1;
        if (temp1 != "\n") username.push_back(temp1);
    }
    Username.close();
    string temp2;
    while (!Password.eof()) {
        Password >> temp2;
        if (temp2 != "\n") password.push_back(temp2);
    }
    Password.close();
}

void login() {
    readDataBase();
    string user, pass;
    bool check = false;
    do {
        cout << "Username: ";
        cin >> user;
        cout << "Password: ";
        cin >> pass;
        if (findAcc(username, user) && findAcc(password, pass)) {
            check = true;
            cout << "Welcome back " << user << "!" << endl;
        } else {
            cout << "Invalid username or password!" << endl << "Please renter!" << endl;
        }
    } while (check == false);
}
