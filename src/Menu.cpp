#include "Menu.h"
#include <iostream>
#include <string>
#include <fstream>

Menu::Menu()
    : m_isGameOpen(false), m_gameManager(nullptr)
{
    if (!m_font.loadFromFile("C:/Windows/Fonts/Arial.ttf")) 
    {
        std::cerr << "Error opening Fonts"<< std::endl;
        return;
    }

    m_titleButton.setFont(m_font);
    m_titleButton.setString("Hit The Sticks");
    m_titleButton.setCharacterSize(60);
    m_titleButton.setPosition(440, 80);

    m_startGameButton.setSize(sf::Vector2f(250, 100));
    m_startGameButton.setPosition(515, 240);
    m_startGameButton.setFillColor(sf::Color::Green);

    m_exitButton.setSize(sf::Vector2f(250, 100));
    m_exitButton.setPosition(515, 480);
    m_exitButton.setFillColor(sf::Color::Red);

    m_continueGameButton.setSize(sf::Vector2f(250, 100));
    m_continueGameButton.setPosition(515, 360);
    if (checkIfSavedGameExists()) {
        m_continueGameButton.setFillColor(sf::Color::Blue);
    }
    else {
        m_continueGameButton.setFillColor(sf::Color(100, 100, 100)); 
    }

    // Continue game button text
    m_continueGameButtonText.setFont(m_font);
    m_continueGameButtonText.setString("Continue Game");
    m_continueGameButtonText.setCharacterSize(30);
    m_continueGameButtonText.setFillColor(sf::Color::White);
    m_continueGameButtonText.setPosition(
        m_continueGameButton.getPosition().x + 20,
        m_continueGameButton.getPosition().y + 30);
}

void Menu::show() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Hit The Sticks", sf::Style::Close | sf::Style::Titlebar);

    while (window.isOpen()) {
        sf::Event event;
        window.clear();

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (!m_isGameOpen) {
                handleClick(event, window);
            }
            else {
                if (m_gameManager) {
                    m_gameManager->play(); // Run the game
                    m_isGameOpen = false;  // When the game is over, return to the menu
                    delete m_gameManager;  // Clean up
                    m_gameManager = nullptr;
                }
            }
        }
        if (!m_isGameOpen) {
            drawMenu(window);
        }
        window.display();
    }
}

void Menu::drawMenu(sf::RenderWindow& window) const {
    window.draw(m_titleButton);
    window.draw(m_startGameButton);
    window.draw(m_continueGameButton);
    window.draw(m_continueGameButtonText);
    window.draw(m_exitButton);
}

void Menu::handleClick(sf::Event event, sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f pos = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });

            if (m_startGameButton.getGlobalBounds().contains(pos)) {
                m_isGameOpen = true;
                m_gameManager = new GameManager();
            }
            //
            if (m_continueGameButton.getGlobalBounds().contains(pos) && checkIfSavedGameExists()) {
                m_isGameOpen = true;
                m_gameManager = new GameManager();
                try {
                    m_gameManager->loadGame("savefile.txt");
                }
                catch (const std::exception& e) {
                    std::cerr << "Error loading game: " << e.what() << std::endl;
                    delete m_gameManager;
                    m_gameManager = nullptr;
                    m_isGameOpen = false;
                }
            }

            if (m_exitButton.getGlobalBounds().contains(pos)) {
                window.close();
            }
        }
    }
}

bool Menu::checkIfSavedGameExists() const {
    std::ifstream file("savefile.txt");
    return file.good();
}
