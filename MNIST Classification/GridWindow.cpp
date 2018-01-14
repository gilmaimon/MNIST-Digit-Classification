#include "GridWindow.h"

GridWindow::
GridWindow(const float width, const float height, const int numHorizontal, const int numVertical):
	m_numVertical(numVertical), m_numHorizontal(numHorizontal), m_width(width), m_height(height) {
	m_grid = Grid(numVertical, std::vector<sf::RectangleShape>(numHorizontal));
	for (auto row = 0; row < numVertical; row++) {
		for (auto col = 0; col < numHorizontal; col++) {
			m_grid[row][col] = sf::RectangleShape({width, height});

			const auto posRow = row * height;
			const auto posCol = col * width;

			m_grid[row][col].setPosition(posCol, posRow);
			m_grid[row][col].setFillColor(sf::Color::Black);
		}
	}
}

sf::RectangleShape& GridWindow::operator()(const int row, const int col) {
	return m_grid[row][col];
}

const sf::RectangleShape& GridWindow::operator()(const int row, const int col) const {
	return m_grid[row][col];
}

void GridWindow::SetColor(const int row, const int col, const sf::Color color) {
	m_grid[row][col].setFillColor(color);
}

sf::Color GridWindow::GetColor(const int row, const int col) const {
	return m_grid[row][col].getFillColor();
}

void GridWindow::Draw(sf::RenderWindow& window) {
	for (auto row = 0; row < m_numVertical; row++) {
		for (auto col = 0; col < m_numHorizontal; col++) {
			window.draw(m_grid[row][col]);
		}
	}
}
