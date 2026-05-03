#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>

class Leaderboard
{
private:
    sf::Font font;
    sf::Text title;
    sf::Text entries[10];
    sf::Text backBtn;

    struct Entry {
        std::string name;
        int score;
    };
    Entry board[10];
    int entryCount = 0;

    void loadFromFile()
    {
        entryCount = 0;
        std::ifstream file("leaderboard.txt");
        while (file >> board[entryCount].name >> board[entryCount].score
            && entryCount < 10)
            entryCount++;
        file.close();

        //SORTIN
        for (int i = 0; i < entryCount - 1; i++)
            for (int j = 0; j < entryCount - i - 1; j++)
                if (board[j].score < board[j + 1].score)
                {
                    Entry temp = board[j];
                    board[j] = board[j + 1];
                    board[j + 1] = temp;
                }
    }

public:
    Leaderboard()
    {
        font.loadFromFile("assets/FONT/font.ttf");

        title.setFont(font);
        title.setString("LEADERBOARD");
        title.setCharacterSize(45);
        title.setFillColor(sf::Color::Cyan);
        title.setPosition(230, 30);

        backBtn.setFont(font);
        backBtn.setString("[ BACK ]");
        backBtn.setCharacterSize(28);
        backBtn.setFillColor(sf::Color::Yellow);
        backBtn.setPosition(330, 530);

        for (int i = 0; i < 10; i++)
        {
            entries[i].setFont(font);
            entries[i].setCharacterSize(24);
            entries[i].setFillColor(sf::Color::White);
            entries[i].setPosition(150, 100 + i * 42);
        }
    }

    //score update 
    void updateScore(std::string username, int score)
    {
        //file mein dhundo
        std::ifstream inFile("leaderboard.txt");
        std::string data = "";
        std::string u;
        int s;
        bool found = false;

        while (inFile >> u >> s)
        {
            if (u == username)
            {
                //agar naya score zyada hai to update karo
                data += u + " " + std::to_string(score > s ? score : s) + "\n";
                found = true;
            }
            else
                data += u + " " + std::to_string(s) + "\n";
        }
        inFile.close();

        if (!found)
            data += username + " " + std::to_string(score) + "\n";

        std::ofstream outFile("leaderboard.txt");
        outFile << data;
        outFile.close();
    }

    //returns 1 if back pressed
    int update(sf::Event& event)
    {
        loadFromFile(); //load
        if (event.type == sf::Event::MouseButtonPressed)
        {
            sf::Vector2f click(event.mouseButton.x, event.mouseButton.y);
            if (backBtn.getGlobalBounds().contains(click))
                return 1;
        }
        return 0;
    }

    void draw(sf::RenderWindow& window)
    {
        window.clear(sf::Color(10, 10, 40));
        window.draw(title);

        for (int i = 0; i < entryCount; i++)
        {
            std::string rank = std::to_string(i + 1) + ".  " +
                board[i].name + "  -  " +
                std::to_string(board[i].score);
            entries[i].setString(rank);

			//top3 ka color alag karo
            if (i == 0) entries[i].setFillColor(sf::Color(255, 215, 0));
            else if (i == 1) entries[i].setFillColor(sf::Color(192, 192, 192));
            else if (i == 2) entries[i].setFillColor(sf::Color(205, 127, 50));
            else entries[i].setFillColor(sf::Color::White);

            window.draw(entries[i]);
        }
        window.draw(backBtn);
    }
};