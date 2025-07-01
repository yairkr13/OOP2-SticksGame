#include "ButtonManager.h"

ButtonManager::ButtonManager()
{
    m_font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
}

void ButtonManager::initializeUI(sf::RenderWindow& window) 
{
    m_bottomBar.setSize(sf::Vector2f(1280, 150)); 
    m_bottomBar.setPosition(0, 570); 
    m_bottomBar.setFillColor(sf::Color(0, 100, 255, 180)); 
}

void ButtonManager::initMenuButton(sf::RenderWindow& window) {
    m_menuButton.setSize(sf::Vector2f(150, 50));
    m_menuButton.setFillColor(sf::Color::Cyan);
    m_menuButton.setPosition(window.getSize().x - 160, window.getSize().y - 60);

    m_menuButtonText.setFont(m_font);
    m_menuButtonText.setString("Menu");
    m_menuButtonText.setCharacterSize(20);
    m_menuButtonText.setFillColor(sf::Color::Black);
    m_menuButtonText.setPosition(m_menuButton.getPosition().x + 10, m_menuButton.getPosition().y + 10);
}

void ButtonManager::initHelpButton(sf::RenderWindow& window) {
    m_helpButton.setSize(sf::Vector2f(150, 50));
    m_helpButton.setFillColor(sf::Color::Green);
    m_helpButton.setPosition(window.getSize().x - 160, window.getSize().y - 120);

    m_helpButtonText.setFont(m_font);
    m_helpButtonText.setString("Help");
    m_helpButtonText.setCharacterSize(20);
    m_helpButtonText.setFillColor(sf::Color::Black);
    m_helpButtonText.setPosition(m_helpButton.getPosition().x + 10, m_helpButton.getPosition().y + 10);
}

void ButtonManager::initSaveButton(sf::RenderWindow& window) {
    m_saveButton.setSize(sf::Vector2f(150, 50));
    m_saveButton.setFillColor(sf::Color::Yellow);
    m_saveButton.setPosition(window.getSize().x - 320, window.getSize().y - 60);

    m_saveButtonText.setFont(m_font);
    m_saveButtonText.setString("Save Game");
    m_saveButtonText.setCharacterSize(20);
    m_saveButtonText.setFillColor(sf::Color::Black);
    m_saveButtonText.setPosition(m_saveButton.getPosition().x + 10, m_saveButton.getPosition().y + 10);
}

bool ButtonManager::isSaveButtonClicked(const sf::Vector2f& pos) const {
    return m_saveButton.getGlobalBounds().contains(pos);
}

void ButtonManager::drawButtons(sf::RenderWindow& window) {
    window.draw(m_bottomBar);
    window.draw(m_menuButton);
    window.draw(m_menuButtonText);
    window.draw(m_helpButton);
    window.draw(m_helpButtonText);
    window.draw(m_saveButton);
    window.draw(m_saveButtonText);
}

bool ButtonManager::isMenuButtonClicked(const sf::Vector2f& pos) const {
    return m_menuButton.getGlobalBounds().contains(pos);
}

bool ButtonManager::isHelpButtonClicked(const sf::Vector2f& pos) const {
    return m_helpButton.getGlobalBounds().contains(pos);
}

//Run Time of HELP button--> O(k) - k is the availableSticks
void ButtonManager::highlightAvailableSticks(std::vector<std::shared_ptr<Stick>>& availableSticks) 
{
    for (auto& stick : availableSticks) {
        stick->highlight(sf::Color::Magenta); 
    }
}
