#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <fstream>
#include "Textbox.h"
#include "Button.h"

using namespace std;

class Account {

private:
	string username;
	string password;
public:
	Account();

	Account(string Username, string Password);

	string getUserName();

	void setUserName(string user);

	void saveDataBase(vector<vector<string>> &All_Account);

	bool checkPassword(string Password);

	void setPassword(string Password);

	bool signIn(vector<vector<string>>& All_Account, string User, string Pass);

	void readDataBase(vector<vector<string>>& All_Account);

	int signUp(vector<vector<string>>& All_Account, string User, string Pass1, string Pass2);

	bool Save_Todo_List(vector<vector<string>>& All_Account, vector<Textbox> &todo_list, vector<Button> &check, int &count);

	void saveTask(vector<vector<string>>& All_Account);

	void readTask(vector<vector<string>>& All_Account, vector<Textbox> &todo_list, vector<Button> &check, int& count);

	void deleteTask(vector<vector<string>>& All_Account, vector<Textbox>& todo_list, vector<Button> &check, int& count);
};

