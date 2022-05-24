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

void Account::saveDataBase (vector<vector<string>> &All_Account) { // ghi thêm tài khoản và mật khẩu mới tạo
    vector<string> new_user;
    new_user.push_back(username);
    new_user.push_back(password);
    All_Account.push_back(new_user);
    ofstream Accounts ("Account/Accounts.txt", ios::ate);
    for (int i = 0; i < All_Account.size(); i++) {
        for (int j = 0; j < All_Account[i].size(); j++) {
            Accounts << All_Account[i][j] << "/";
        }
        if (i < All_Account.size() - 1) Accounts << '\n';
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

bool Account::signIn(vector<vector<string>>& All_Account, string User, string Pass) {
    bool check = false;
    if (All_Account.size() == 0) {
        readDataBase(All_Account);
    }
    for (int i = 0; i < All_Account.size(); i++) {
        if (All_Account[i][0] == User) {
            if (All_Account[i][1] == Pass) {
                username = User;
                password = Pass;
                check = true;
                break;
            }
            else {
                check = false;
            }
        }
        else {
            check = false;
        }
    }
    return check;
}

void Account::readDataBase(vector<vector<string>>& All_Account) { // đọc tất cả tài khoản và mật khẩu đã lưu
    ifstream Accounts;
    Accounts.open("Account/Accounts.txt");
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

int Account::signUp(vector<vector<string>>& All_Account, string User, string Pass1, string Pass2) {
    if (All_Account.size() == 0) {
        readDataBase(All_Account);
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
                    saveDataBase(All_Account);
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

bool Account::Save_Todo_List(vector<vector<string>>& All_Account, vector<Textbox> &todo_list, vector<Button>& check, int &count) {
    if (All_Account.size() == 0) {
        readDataBase(All_Account);
    }
    for (int i = 0; i < All_Account.size(); i++) {
        if (username == All_Account[i][0]) {
            for (long j = 0; j < count; j++) {
                string temp = "";
                if (check[j].getState() == BUTTON_STATE_MOUSE_OVER_MOTION) {
                    temp = todo_list[j].getInputText() + '1';
                }
                else {
                    temp = todo_list[j].getInputText() + '0';
                }
                if (j + 2 < All_Account[i].size()) {
                    All_Account[i][j + 2] = temp;
                }
                else {
                    All_Account[i].push_back(temp);
                }
            }
            saveTask(All_Account);
            return true;
        }
    }
    return false;
}

void Account::saveTask(vector<vector<string>>& All_Account) {
    ofstream Accounts("Account/Accounts.txt", ios::ate);
    for (int i = 0; i < All_Account.size(); i++) {
        for (int j = 0; j < All_Account[i].size(); j++) {
            Accounts << All_Account[i][j] << "/";
        }
        if (i < All_Account.size() - 1) Accounts << "\n";
    }
    Accounts.close();
}

void Account::readTask(vector<vector<string>>& All_Account, vector<Textbox> &todo_list, vector<Button> &check, int &count) {
    for (int i = 0; i < All_Account.size(); i++) {
        if (All_Account[i].at(0) == username) {
            if (All_Account[i].size() >= 3) {
                for (int j = 2; j < All_Account[i].size(); j++) {
                    string temp = All_Account[i][j];
                    if (temp[temp.length() - 1] == '1') {
                        check[count].setState(BUTTON_STATE_MOUSE_OVER_MOTION);
                    }
                    temp.pop_back();
                    todo_list[count].setInputText(temp);
                    count++;
                }
            }
        }
    }
}

void Account::deleteTask(vector<vector<string>>& All_Account, vector<Textbox>& todo_list, vector<Button> &check, int& count) {
    for (int i = 0; i < count; i++) {
        if (todo_list[i].getState() == true) {
            for (int j = i; j <= count; j++) {
                todo_list[j] = todo_list[j + 1];
                check[j].setState(check[j + 1].getState());
            }
            count--;
            for (int x = 0; x < All_Account.size(); x++) {
                if (username == All_Account[x][0]) {
                    for (int y = i + 2; y < count + 2; y++) {
                        All_Account[x][y] = All_Account[x][y + 1];
                    }
                    All_Account[x].pop_back();
                    break;
                }
            }
            break;
        }
    }
    saveTask(All_Account);
    cout << "deleted" << endl;
}

