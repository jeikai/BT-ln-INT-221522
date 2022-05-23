#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <fstream>
#include "Textbox.h"

using namespace std;

static vector<vector<string>> All_Account;

class Account {

private:
	string username;
	string password;
public:
	Account();

	Account(string Username, string Password);

	string getUserName();

	void setUserName(string user);

	void saveDataBase();

	bool checkPassword(string Password);

	void setPassword(string Password);

	bool signIn(string User, string Pass);

	void readDataBase();

	int signUp(string User, string Pass1, string Pass2);

	bool Save_Todo_List(Account User, vector<Textbox> todo_list, int &count);

	void saveTask();

	void readTask(Account User, vector<Textbox> todo_list, int& count);
};

