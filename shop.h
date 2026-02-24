#ifndef SHOP_H
#define SHOP_H

#include <vector>
#include <string>
using namespace std;

struct UserRegister
{
  string username;
  string password;
  string confirmPassword;
  string role;
};

struct SalesData
{
  int quantity;
  double totalPrice;
};

void registerFunction(vector<UserRegister> &allUser);
void loadUserData(vector<UserRegister> &allUser);
UserRegister loginFunction(vector<UserRegister> &allUser);
bool validateWelcomePageInput(int choice);
int WelcomePage();
void ownerDashboard(const UserRegister &currentUser);
void adminDashboard(const UserRegister &currentUser);

void sellReport();
void restock();
void viewInventory();
void userManagement();
void sell();

#endif
