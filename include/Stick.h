#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

struct Point {
    int x;
    int y;
};

class Stick {
public:
    Stick(const sf::Color color);
    void draw(sf::RenderWindow& window);
    bool hit(sf::Vector2f pos) const;
    std::vector<sf::Vector2f> getEdges() const;
    bool isOverlapping(const Stick& other) const;
    void highlight(sf::Color color);
    void resetColor();
    sf::Color getFillColor() const;

    void addOverlappingStick(const std::shared_ptr<Stick>& stick);
    void removeOverlappingStick(const std::shared_ptr<Stick>& stick);
    bool canBePickedUp() const;
    const std::vector<std::shared_ptr<Stick>>& getOverlappingSticks() const;

    const sf::Vector2f& getPosition() ;
    void setPosition(const sf::Vector2f& position);

    float getRotation() ;
    void setRotation(float rotation);

private:
    sf::RectangleShape m_stick;
    sf::Color m_originalColor;

    std::vector<std::shared_ptr<Stick>> m_overlappingSticks; 
};

static bool onSegment(Point p, Point q, Point r)
{
    if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
        q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y))
        return true;
    return false;
}

static int orientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
}

static bool doIntersect(Point p1, Point q1, Point p2, Point q2)
{
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    if (o1 != o2 && o3 != o4) return true;
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false;
}