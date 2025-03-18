#pragma once

#include <vector>
#include <SFML/System/Vector2.hpp>

struct Cell {
    std::vector<int> indices;
};

class Grid {
public:
    // Note: make sure both window_size x and y components are divisible by grid_size
    Grid() {
        width = conf::window_size.x / conf::grid_size;
        height = conf::window_size.y / conf::grid_size;
        clear();
    }

    [[nodiscard]]
    Cell& getCell(const uint32_t x, const uint32_t y) {
        return cells[x][y];
    }

    [[nodiscard]]
    sf::Vector2u size() const {
        return {width, height};
    }

    void clear() {
        cells.clear();
        cells.resize(width, std::vector<Cell>(height));
    }

    void placeParticle(const sf::Vector2f position, const int index) {
        const auto x = static_cast<uint32_t>(position.x / conf::grid_size);
        const auto y = static_cast<uint32_t>(position.y / conf::grid_size);
        cells[x][y].indices.push_back(index);
    }

private:
    std::vector<std::vector<Cell>> cells;
    uint32_t width, height;
};

