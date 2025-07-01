#pragma once
#include <SFML/Graphics.hpp>
#include "Stick.h"

class ButtonManager {
public:
    ButtonManager();
    void initializeUI(sf::RenderWindow& window);
    void initMenuButton(sf::RenderWindow& window);
    void initHelpButton(sf::RenderWindow& window);
    void drawButtons(sf::RenderWindow& window);

    bool isMenuButtonClicked(const sf::Vector2f& pos) const;
    bool isHelpButtonClicked(const sf::Vector2f& pos) const;
    bool isSaveButtonClicked(const sf::Vector2f& pos) const;

    void highlightAvailableSticks(std::vector<std::shared_ptr<Stick>>& sticks);
    void initSaveButton(sf::RenderWindow& window);

private:
    sf::RectangleShape m_menuButton;
    sf::RectangleShape m_helpButton;
    sf::RectangleShape m_bottomBar;
    sf::RectangleShape m_saveButton;

    sf::Text m_menuButtonText;
    sf::Text m_helpButtonText;
    sf::Text m_saveButtonText;

    sf::Font m_font;
};
