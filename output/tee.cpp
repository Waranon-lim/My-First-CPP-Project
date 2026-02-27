#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct UserRegistration
{
    string userName;
    string password;
    string role;
};

struct UserProfile
{
    string userName;
    string role;
};

UserProfile currentUser;

void Register()
{
    UserRegistration user;

    cout << "Input User Name: ";
    cin >> user.userName;

    cout << "Input Password: ";
    cin >> user.password;

    cout << "Input Role: ";
    cin >> user.role;

    cout << "User Registered: " << user.userName << " " << user.password
         << " (" << user.role << ")";

    ofstream MyFile("user.txt");
    MyFile << user.userName << " " << user.password << " " << user.role;

    MyFile.close();
}

void Login()
{
    UserRegistration user;

    cout << "Input User Name: ";
    cin >> user.userName;

    cout << "Input Password: ";
    cin >> user.password;

    string myText;
    string userName, password, role;

    ifstream MyReadFile("user.txt");
    while (getline(MyReadFile, myText))
    {
        stringstream ss(myText);
        ss >> userName >> password >> role;

        if (user.userName == userName && user.password == password)
        {
            currentUser.userName = userName;
            currentUser.role = role;
            // cout << "Welcome";
            break;
        }
    }
}

int main()
{
    int choice;
    do
    {
        cout << "\n1.Register\n2.Login\n3.Exit\n";
        cin >> choice;

        if (choice == 1)
            Register();
        else if (choice == 2)
        {
            Login();
            if (currentUser.role == "Staff")
            {
                cout << "Go to staff page";
            }
            else if (currentUser.role == "Customer")
            {
                cout << "Go to customer page";
            }
            // cout << currentUser.userName << currentUser.role;
        }
        else if (choice == 3)
            break;
        else
            cout << "Invalid Input, Pls try again";
    } while (true);

    return 0;
}

// while
// for
// do-while