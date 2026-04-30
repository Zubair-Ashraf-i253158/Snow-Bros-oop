#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>

class AuthSystem
{
private:
    std::string loggedInUser;

    // simple hash - har character ki value add karo
    int hashPassword(std::string password)
    {
        int hash = 0;
        for (int i = 0; i < password.size(); i++)
            hash += password[i] * (i + 1);
        return hash;
    }

public:
    std::string getUser() { return loggedInUser; }

    bool signup(std::string username, std::string password)
    {
        // check karo user already exist karta hai
        std::ifstream checkFile("data/users.txt");
        std::string u, p;
        while (checkFile >> u >> p)
            if (u == username) return false; // already exists
        checkFile.close();

        // save karo
        std::ofstream file("data/users.txt", std::ios::app);
        file << username << " " << hashPassword(password) << "\n";
        file.close();
        loggedInUser = username;
        return true;
    }

    bool login(std::string username, std::string password)
    {
        std::ifstream file("data/users.txt");
        std::string u;
        int p;
        while (file >> u >> p)
        {
            if (u == username && p == hashPassword(password))
            {
                loggedInUser = username;
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }
};