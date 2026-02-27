#include "shop.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <iomanip>

void registerFunction(vector<UserRegister> &allUser)
{

    UserRegister userAccount;
    ofstream outfile("user.csv", ios::app);
    // std::ios::app it's a syntax and it add the data to the end
    if (!outfile)
    {
        cout << "Error: Cannot open file.\n";
        return;
    }

    cout << "--- Register ---" << endl;

    bool isDuplicate;
    do
    {
        isDuplicate = false;

        cout << "username: ";
        cin >> userAccount.username;

        for (const auto &member : allUser)
        {
            if (userAccount.username == member.username)
            {
                cout << "this name already exist" << endl;
                isDuplicate = true;
                break;
            }
        }
    } while (isDuplicate);

    do
    {
        cout << "password: ";
        cin >> userAccount.password;
        cout << "confirm password: ";
        cin >> userAccount.confirmPassword;

        if (userAccount.password != userAccount.confirmPassword)
        {
            cout << "passwords do not match\n";
        }
    } while (userAccount.password != userAccount.confirmPassword);

    cout << "role: ";
    cin >> userAccount.role;

    outfile << userAccount.username << "," << userAccount.password << "," << userAccount.role << endl;

    allUser.push_back(userAccount); // vector_name.push_back(variable that want to store) writen by lim not AI

    cout
        << "Registration successful!\n"
        << endl;
}

void loadUserData(vector<UserRegister> &allUser)
{
    ifstream readFile("user.csv");

    string line;
    while (getline(readFile, line)) // getline(input_stream, string_variable)
    {
        stringstream ss(line); // stringstream ชื่อตัวแปร (แหล่งข้อมูลที่จะแยก)
        UserRegister tempUser;

        getline(ss, tempUser.username, ',');
        getline(ss, tempUser.password, ',');
        getline(ss, tempUser.role, ',');

        allUser.push_back(tempUser);
    }

    readFile.close();
}

UserRegister loginFunction(vector<UserRegister> &allUser)
{

    UserRegister userAccount;
    string username, password;
    cout << "username: ";
    cin >> userAccount.username;

    cout << "password: ";
    cin >> userAccount.password;
    bool isfound = false;
    for (const auto &member : allUser)
    {
        if (userAccount.username == member.username && userAccount.password == member.password)
        {
            cout << "Login Success Welcome " << member.username << endl;
            isfound = true;
            return member;
        }
    }
    cout << "username or password incorrect" << endl;
    return UserRegister();
}

bool validateWelcomePageInput(int choice)
{
    if (choice == 1 || choice == 2 || choice == 3)
        return true;
    return false;
}

int WelcomePage()
{
    int choice;
    cout << "1.register\n2.login\n3.exit\n"
         << endl;
    cin >> choice;

    while (!validateWelcomePageInput(choice))
    {
        cout << "Invalid option, please try again: ";
        cin >> choice;
    }
    return choice;
}

//-------------------- owner and admin dashboard --------------------//

void ownerDashboard(const UserRegister &currentUser)
{
    while (true)
    {
        cout << "--- OWNER DASHBOARD --- " << endl;
        cout << "1. Sell report" << endl;
        cout << "2. Restock" << endl;
        cout << "3. View inventory" << endl;
        cout << "4. User management" << endl;
        cout << "5. Logout" << endl;

        int choice;
        cin >> choice;

        if (choice == 1)
        {
            sellReport();
        }
        else if (choice == 2)
        {
            restock();
        }
        else if (choice == 3)
        {
            viewInventory();
        }
        else if (choice == 4)
        {
            userManagement();
        }
        else if (choice == 5)
        {
            break;
        }
    }
}

void adminDashboard(const UserRegister &currentUser)
{
    while (true)
    {

        cout << "--- ADMIN DASHBOARD --- " << endl;
        cout << "1.sell" << endl;
        cout << "2.restock" << endl;
        cout << "3.logout" << endl;

        int choice;
        cin >> choice;
        if (choice == 1)
        {
            sell();
        }
        else if (choice == 2)
        {
            restock();
        }
        else if (choice == 3)
        {
            break;
        }
    }
}

void sellReport()
{
    ifstream file("sales.csv");

    if (!file)
    {
        cout << "file does not exists\n";
        return;
    }

    string readLine;
    double totalRevenue = 0;

    /* map<string,int> myMap อันนี้คือ เหมือน vector ช่องแรกมันจะหาตัวแปรที่เป็น string แล้ว จะหา int ที่ควบคู่ กับ string myMap คือตัวแปรที่ใช้เก็บข้อมูลในข้อนี้ */
    map<string, SalesData> totalSell;

    while (getline(file, readLine))
    {
        stringstream parseSellData(readLine);
        string name;
        int quantity;
        double price;

        getline(parseSellData, name, ','); // getline(istream& input, string& str, char delim);
        parseSellData >> quantity;
        parseSellData.ignore();
        parseSellData >> price;

        totalSell[name].quantity += quantity;
        totalSell[name].totalPrice += price;

        totalRevenue += price;
    }

    cout << left << setw(15) << "Product"
         << setw(10) << "Pieces"
         << setw(15) << "Total"
         << endl;

    cout << "----------------------------------------" << endl;
    for (const auto &data : totalSell)
    {
        cout << left << setw(15) << data.first
             << setw(10) << data.second.quantity
             << setw(15) << data.second.totalPrice
             << endl;
    }
    cout << "----------------------------------------" << endl;
    cout << "Total" << totalRevenue << "$";
}

void restock()
{
    ifstream file("inventory.csv");
    map<string, int> inventory;
    string readFile;

    if (!file)
    {
        cout << "file does not exist" << endl;
        return;
    }

    while (getline(file, readFile))
    {
        stringstream ss(readFile);
        string name;
        int quantity;

        getline(ss, name, ',');
        ss >> quantity;
        inventory[name] = quantity;
    }
    string product;
    int addQuantity;

    cout << "name of product" << endl;
    cin >> product;

    cout << "amount to add" << endl;
    cin >> addQuantity;

    inventory[product] += addQuantity;

    ofstream restockFile("inventory.csv");
    for (const auto &item : inventory)
    {
        restockFile << item.first << "," << item.second << endl;
    }
    cout << "Restock completed!\n";
}

void viewInventory()
{
    ifstream file("inventory.csv");
    string readLine;

    cout << "Current Inventory\n"
         << endl;
    cout << "------------------------------\n"
         << endl;
    cout << left << setw(20) << "Product" << left << setw(10) << "Quantity" << endl;

    while (getline(file, readLine))
    {
        stringstream ss(readLine);
        string name;
        int quantity;
        getline(file, name, ',');
        ss >> quantity;

        cout << name << left << setw(15) << quantity << endl;
    }
    cout << "------------------------------\n"
         << endl;
}

void userManagement()
{
    ifstream userFile("user.csv");
            cout
        << "Current User\n"
        << endl;
    cout << "------------------------------\n"
         << endl;
    string readLine;
    while (getline(userFile, readLine))
        
    {
        string name, role, password;

        stringstream ss(readLine);
        getline(ss, name, ',');
        getline(ss, password, ',');
        getline(ss, role, ',');
    

    for(const auto &item : readLine)
    {
        cout << left << setw(15) << name << left << setw(10) << role << endl;
    }
    }
    cout << "------------------------------\n"
         << endl;
}
void sell()
{
    ifstream inFile("inventory.csv");
    map<string, int> inventory;
    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string name;
        int qty;
        if (getline(ss, name, ',')) {
            ss >> qty;
            inventory[name] = qty;
        }
    }
    inFile.close();

    string productName;
    int sellQty;
    double pricePerUnit; 

    cout << "Enter product name to sell: ";
    cin >> productName;

    if (inventory.find(productName) == inventory.end()) {
        cout << "Error: Product not found!" << endl;
        return;
    }

    cout << "Enter quantity to sell: ";
    cin >> sellQty;

    while (true) {
    cout << "Enter quantity to sell: ";
    cin >> sellQty;

    if (inventory[productName] >= sellQty) {
        break; 
    } else {
        cout << "Not enough! We only have " << inventory[productName] << ". Try again." << endl;
    }
}

    cout << "Enter price per unit: ";
    cin >> pricePerUnit;

    inventory[productName] -= sellQty; 
    double totalSalesPrice = sellQty * pricePerUnit;

    ofstream salesFile("sales.csv", ios::app);
    if (salesFile.is_open()) {
        salesFile << productName << "," << sellQty << "," << totalSalesPrice << endl;
        salesFile.close();
    }

    ofstream outInv("inventory.csv");
    for (const auto &item : inventory) {
        outInv << item.first << "," << item.second << endl;
    }
    outInv.close();

    cout << "Sale completed! Total: " << totalSalesPrice << "$" << endl;
}