#include "Account.h"

Account::Account () {
    username = "";
    password = "";
}

Account::Account (string Username, string Password) {
    username = Username;
    password = Password;
}

string Account::getUserName() {
    return username;
}

void Account::setUserName(string user) {
    username = user;
}

void Account::saveDataBase () { // ghi thêm tài khoản và mật khẩu mới tạo
    vector<string> new_user;
    new_user.push_back(username);
    new_user.push_back(password);
    All_Account.push_back(new_user);
    ofstream Accounts ("D:/MyProject/Account/Accounts.txt", ios::ate);
    for (int i = 0; i < All_Account.size(); i++) {
        for (int j = 0; j < All_Account[i].size(); j++) {
            Accounts << All_Account[i][j] << "/";
        }
        Accounts << "\n";
    }
    Accounts.close();
}

bool Account::checkPassword (string Password) {
    if (Password.length() > 20 || Password.length() < 5) {
        return false;
    } else {
        int dem = 0;
        for (int i = 0; i < Password.length(); i++) {
            if (isblank(Password[i])) {
                return false;
            } else if (!islower(Password[i]) && !isupper(Password[i]) && !isdigit(Password[i])) {
                dem++;
            }
        }
        if (dem == 0) {
            return false;
        }
    }
    return true;
}

void Account::setPassword (string Password) {
    password = Password;
}

bool Account::signIn(string User, string Pass) {
    if (All_Account.size() == 0) {
        readDataBase();
    }
    for (int i = 0; i < All_Account.size(); i++) {
        if (User == All_Account[i][0]) {
            if (Pass == All_Account[i][1]) {
                username = User;
                password = Pass;
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
    }
    return false;
}

void Account::readDataBase() { // đọc tất cả tài khoản và mật khẩu đã lưu
    ifstream Accounts;
    Accounts.open("D:/MyProject/Account/Accounts.txt");
    if (Accounts) {
        while (Accounts.eof() == false) {
            string temp;
            getline(Accounts, temp);
            vector<string> user;
            int pos = 0;
            for (int i = 0; i < temp.size(); i++) {
                if (temp[i] == '/') {
                    string res = temp.substr(pos, i - pos);
                    user.push_back(res);
                    pos = i + 1;
                }
            }
            All_Account.push_back(user);
        }
    }
    else {
        cout << "Cannot open file" << endl;
    }
    Accounts.close();
}

int Account::signUp(string User, string Pass1, string Pass2) {
    if (All_Account.size() == 0) {
        readDataBase();
    }
    for (int i = 0; i < All_Account.size(); i++) {
        if (User == All_Account[i][0]) {
            cout << "Username already exits!" << endl;
            return 1;
        }
        else {
            if (Pass1 == Pass2) {
                if (checkPassword(Pass1)) {
                    username = User;
                    password = Pass1;
                    saveDataBase();
                    break;
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
    }
    return 0;
}

bool Account::Save_Todo_List(Account User, vector<Textbox> todo_list, int &count) {
    if (All_Account.size() == 0) {
        readDataBase();
    }
    for (int i = 0; i < All_Account.size(); i++) {
        if (User.getUserName() == All_Account[i][0]) {
            for (int j = 0; j < count; j++) {
                All_Account[i].push_back(todo_list[j].getInputText());
            }
            saveTask();
            return true;
        }
    }
    return false;
}

void Account::saveTask() {
    ofstream Accounts("D:/MyProject/Account/Accounts.txt", ios::ate);
    for (int i = 0; i < All_Account.size(); i++) {
        for (int j = 0; j < All_Account[i].size(); j++) {
            Accounts << All_Account[i][j] << "/";
        }
        Accounts << "\n";
    }
    Accounts.close();
}

void Account::readTask(Account User, vector<Textbox> todo_list, int &count) {
    for (int i = 0; i < All_Account.size(); i++) {
        if (User.getUserName() == All_Account[i][0]) {
            if (All_Account[i].size() >= 3) {
                for (int j = 2; j < All_Account[i].size(); j++) {
                    todo_list[count].setInputText(All_Account[i][j]);
                    count++;
                }
            }
        }
    }
}

