#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class SfmlGridWindow {
public:
	float CellHeigh() const;
	float CellWidth() const;
	SfmlGridWindow(const float width, const float height, const int numHorizontal, const int numVertical);
	sf::RectangleShape& operator()(const int row, const int col);
	const sf::RectangleShape& operator()(const int row, const int col) const;
	void SetColor(const int row, const int col, const sf::Color color);
	sf::Color GetColor(const int row, const int col) const;
	void Draw(sf::RenderWindow& window);

	~SfmlGridWindow() {}
private:
	SfmlGridWindow() = delete;

	typedef std::vector<std::vector<sf::RectangleShape>> Grid;
	Grid m_grid;

	int m_countRows;
	int m_countCols;

	float m_totalWidth;
	float m_totalHeight;
};

