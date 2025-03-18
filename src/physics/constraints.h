#pragma once

#include <SFML/System/Vector2.hpp>
#include <cmath>

struct ConstraintLine {
    sf::Vector2f p1;
    sf::Vector2f p2;

    ConstraintLine(const sf::Vector2f p1, const sf::Vector2f p2) : p1(p1), p2(p2) {}

    [[nodiscard]]
    float distanceToPoint(const sf::Vector2f& other) const {
        const float distance = std::abs((p2.y-p1.y)*other.x-(p2.x-p1.x)*other.y+p2.x*p1.y-p2.y*p1.x)
        / sqrtf(pow(p2.y-p1.y,2)+pow(p2.x-p1.x,2)); // NOLINT(*-narrowing-conversions)
        return distance;
    }
    [[nodiscard]]
    sf::Vector2f getNormal() const {
        const float magnitude = sqrtf( pow(p2.y-p1.y,2) + pow(p2.x-p1.x,2) ); // NOLINT(*-narrowing-conversions)
        return {(p2.y-p1.y)/magnitude, (p1.x-p2.x)/magnitude};
    }
};

struct ConstraintRectangle {
    sf::Vector2f p1, p2, p3, p4;

    ConstraintRectangle(const sf::Vector2f p1, const sf::Vector2f p2, const sf::Vector2f p3, const sf::Vector2f p4) : p1(p1), p2(p2), p3(p3), p4(p4) {}
    ConstraintRectangle(const sf::Vector2f size, const sf::Vector2f position) {
        p1 = position;  // Top left
        p2 = position + sf::Vector2f(0.0f, size.y); // Bottom left
        p3 = position + size;  // Bottom right
        p4 = position + sf::Vector2f(size.x, 0.0f); // Top right
    }

    [[nodiscard]]
    bool isInside(const sf::Vector2f& point) const {
        const float cross_product = (point.x-p1.x)*(p2.y-p1.y)-(point.y-p1.y)*(p2.x-p1.x);
        if (cross_product < 0) return false;
        if ((point.x-p2.x)*(p3.y-p2.y)-(point.y-p2.y)*(p3.x-p2.x) < 0) return false;
        if ((point.x-p3.x)*(p4.y-p3.y)-(point.y-p3.y)*(p4.x-p3.x) < 0) return false;
        if ((point.x-p4.x)*(p1.y-p4.y)-(point.y-p4.y)*(p1.x-p4.x) < 0) return false;
        return true;
    }

    [[nodiscard]]
    ConstraintLine getClosestLine(const sf::Vector2f& point) const {
        ConstraintLine l1 = ConstraintLine(p1, p2);
        ConstraintLine l2 = ConstraintLine(p2, p3);
        ConstraintLine l3 = ConstraintLine(p3, p4);
        ConstraintLine l4 = ConstraintLine(p4, p1);
        float d1 = l1.distanceToPoint(point);
        float d2 = l2.distanceToPoint(point);
        float d3 = l3.distanceToPoint(point);
        float d4 = l4.distanceToPoint(point);
        if (d1 < d2 && d1 < d3 && d1 < d4) return l1;
        if (d2 < d1 && d2 < d3 && d2 < d4) return l2;
        if (d3 < d1 && d3 < d2 && d3 < d4) return l3;
        return l4;
    }

    [[nodiscard]]
    std::vector<ConstraintLine> getLines() const {
        return {ConstraintLine(p1, p2), ConstraintLine(p2, p3), ConstraintLine(p3, p4), ConstraintLine(p4, p1)};
    }
};

struct ConstraintSphere {
    sf::Vector2f center;
    float radius;

    ConstraintSphere(const sf::Vector2f center, const float radius) : center(center), radius(radius) {}

    [[nodiscard]]
    bool isInside(const sf::Vector2f& point) const {
         return distanceToPoint(point)< radius;
    }

    [[nodiscard]]
    float distanceToPoint(const sf::Vector2f& point) const {
        return sqrtf( pow(center.x-point.x,2) + pow(center.y-point.y,2) ); // NOLINT(*-narrowing-conversions)
    }

    [[nodiscard]]
    sf::Vector2f getNormal(const sf::Vector2f& point) const {
        const sf::Vector2f delta = point - center;
        return delta / distanceToPoint(point);
    }
};