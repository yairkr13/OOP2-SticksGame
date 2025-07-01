#include <vector>
#include <SFML/Graphics.hpp>
#include "Stick.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <memory>

Stick::Stick(const sf::Color color) : m_originalColor(color) {
    int x = 110 + rand() % 1060;
    int y = 110 + rand() % 300;
    int size_x = 150 + rand() % 50;
    int size_y = 10;
    float angle = static_cast<float>(rand() % 90);
    if (rand() % 2) angle *= -1;
    m_stick.setSize(sf::Vector2f(static_cast<float>(size_x), static_cast<float>(size_y)));
    m_stick.setRotation(angle);
    m_stick.setPosition(sf::Vector2f(static_cast<float>(x), static_cast<float>(y)));
    m_stick.setFillColor(color);
    m_stick.setOutlineThickness(1.5f);
    m_stick.setOutlineColor(sf::Color::White);
    m_stick.setOrigin(sf::Vector2f(m_stick.getSize().x / 2, m_stick.getSize().y / 2));
}

void Stick::draw(sf::RenderWindow& window)
{
    window.draw(m_stick);
}

bool Stick::hit(sf::Vector2f pos) const
{
    sf::Transform transform = m_stick.getTransform();
    sf::Transform i_transform = transform.getInverse();
    sf::Vector2f local_point = i_transform.transformPoint(pos);
    sf::FloatRect local_bounds = m_stick.getLocalBounds();
    return local_bounds.contains(local_point);
}

static Point toPoint(const sf::Vector2f& vec) {
    return { static_cast<int>(vec.x), static_cast<int>(vec.y) };
}

bool Stick::isOverlapping(const Stick& other) const {
    // Get the edges of both sticks
    auto edges1 = getEdges();
    auto edges2 = other.getEdges();

    // Iterate through each edge of the first rectangle
    for (size_t i = 0; i < edges1.size(); ++i) {
        sf::Vector2f p1 = edges1[i];
        sf::Vector2f q1 = edges1[(i + 1) % edges1.size()];

        // Iterate through each edge of the second rectangle
        for (size_t j = 0; j < edges2.size(); ++j) {
            sf::Vector2f p2 = edges2[j];
            sf::Vector2f q2 = edges2[(j + 1) % edges2.size()];

            // Check if the edges intersect
            if (doIntersect(
                toPoint(p1), toPoint(q1),
                toPoint(p2), toPoint(q2))) {
                return true;
            }
        }
    }

    return false;
}

std::vector<sf::Vector2f> Stick::getEdges() const {
    std::vector<sf::Vector2f> edges;

    sf::FloatRect bounds = m_stick.getLocalBounds();
    sf::Vector2f topLeft(bounds.left, bounds.top);
    sf::Vector2f topRight(bounds.left + bounds.width, bounds.top);
    sf::Vector2f bottomRight(bounds.left + bounds.width, bounds.top + bounds.height);
    sf::Vector2f bottomLeft(bounds.left, bounds.top + bounds.height);

    // Apply the transformation to get the actual edge points
    sf::Transform transform = m_stick.getTransform();
    edges.push_back(transform.transformPoint(topLeft));
    edges.push_back(transform.transformPoint(topRight));
    edges.push_back(transform.transformPoint(bottomRight));
    edges.push_back(transform.transformPoint(bottomLeft));

    return edges;
}

void Stick::highlight(sf::Color color)
{
    m_stick.setFillColor(color);
}

void Stick::resetColor()
{
    m_stick.setFillColor(m_originalColor);
}   

sf::Color Stick::getFillColor() const
{
    return m_stick.getFillColor();
}

void Stick::addOverlappingStick(const std::shared_ptr<Stick>& stick)
{
    m_overlappingSticks.push_back(stick);
}

void Stick::removeOverlappingStick(const std::shared_ptr<Stick>& stick)
{
    m_overlappingSticks.erase(std::remove(m_overlappingSticks.begin(), m_overlappingSticks.end(), stick), m_overlappingSticks.end());
}

bool Stick::canBePickedUp() const {
    // If there are no overlapping sticks, it can be picked up
    if (m_overlappingSticks.empty())
    {
        return true;
    }
    return false;
}

const std::vector<std::shared_ptr<Stick>>& Stick::getOverlappingSticks() const
{
    return m_overlappingSticks;
}

const sf::Vector2f& Stick::getPosition()  {
    return m_stick.getPosition();
}

void Stick::setPosition(const sf::Vector2f& position) {
    m_stick.setPosition(position);
}

float Stick::getRotation()  {
    return m_stick.getRotation();
}

void Stick::setRotation(float rotation) {
    m_stick.setRotation(rotation);
}
