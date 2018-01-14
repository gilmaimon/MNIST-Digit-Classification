#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class GridWindow {
private:
	GridWindow() = delete;

	typedef std::vector<std::vector<sf::RectangleShape>> Grid;
	Grid m_grid;

	int m_numVertical;
	int m_numHorizontal;

	float m_width;
	float m_height;
public:
	GridWindow(const float width, const float height, const int numHorizontal, const int numVertical);
	sf::RectangleShape& operator()(const int row, const int col);
	const sf::RectangleShape& operator()(const int row, const int col) const;
	void SetColor(const int row, const int col, const sf::Color color);
	sf::Color GetColor(const int row, const int col) const;
	void Draw(sf::RenderWindow& window);

	~GridWindow() {}
};

