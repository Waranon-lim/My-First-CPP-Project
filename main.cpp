#include "shop.h"
#include <iostream>
using namespace std;

int main()
{
    vector<UserRegister> allUser;
    loadUserData(allUser);

    while (true)
    {
        int choice = WelcomePage();

        if (choice == 1)
        {
            registerFunction(allUser);
        }
        else if (choice == 2)
        {

            while (true)
            {
                UserRegister currentUser = loginFunction(allUser);

                if (!currentUser.username.empty())
                {
                    if (currentUser.role == "owner")
                    {
                        ownerDashboard(currentUser);
                        break;
                    }
                    else if (currentUser.role == "admin")
                    {
                        adminDashboard(currentUser);
                        break;
                    }
                }
            }
            break;
        }
        else if (choice == 3)
        {
            break;
        }
    }

    return 0;
}