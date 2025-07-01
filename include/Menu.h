#pragma once
#include "GameManager.h" 
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Menu {
public:
    Menu();
    void show();

private:
    void drawMenu(sf::RenderWindow& window) const;
    void handleClick(sf::Event event, sf::RenderWindow& window);

    bool checkIfSavedGameExists() const;
    bool m_isGameOpen;

    GameManager* m_gameManager;

    sf::RectangleShape m_startGameButton;
    sf::RectangleShape m_exitButton;
    sf::RectangleShape m_continueGameButton;

    sf::Font m_font;  

    sf::Text m_titleButton;
    sf::Text m_continueGameButtonText;

};
