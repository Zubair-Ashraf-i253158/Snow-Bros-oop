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
        // check if already exists
        std::ifstream checkFile("users.txt"); // data/ hatao
        std::string u;
        int p;
        while (checkFile >> u >> p)
            if (u == username) return false;
        checkFile.close();

        // save karo
        std::ofstream file("users.txt", std::ios::app); // data/ hatao
        file << username << " " << hashPassword(password) << "\n";
        file.close();
        loggedInUser = username;
        return true;
    }

    bool login(std::string username, std::string password)
    {
        std::ifstream file("users.txt"); // data/ hatao
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