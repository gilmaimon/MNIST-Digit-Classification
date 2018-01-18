#include "SfmlGridWindow.h"

SfmlGridWindow::
SfmlGridWindow(const float width, const float height, const int numHorizontal, const int numVertical):
	m_countRows(numVertical), m_countCols(numHorizontal), m_totalWidth(width), m_totalHeight(height) {
	m_grid = Grid(numVertical, std::vector<sf::RectangleShape>(numHorizontal));
	for (auto row = 0; row < numVertical; row++) {
		for (auto col = 0; col < numHorizontal; col++) {
			m_grid[row][col] = sf::RectangleShape({width, height});

			const auto posRow = row * CellHeigh();
			const auto posCol = col * CellWidth();

			m_grid[row][col].setPosition(posCol, posRow);
			m_grid[row][col].setFillColor(sf::Color::Black);
		}
	}
}

sf::RectangleShape& SfmlGridWindow::operator()(const int row, const int col) {
	return m_grid[row][col];
}

const sf::RectangleShape& SfmlGridWindow::operator()(const int row, const int col) const {
	return m_grid[row][col];
}

void SfmlGridWindow::SetColor(const int row, const int col, const sf::Color color) {
	m_grid[row][col].setFillColor(color);
}

sf::Color SfmlGridWindow::GetColor(const int row, const int col) const {
	return m_grid[row][col].getFillColor();
}

void SfmlGridWindow::Draw(sf::RenderWindow& window) {
	for (auto row = 0; row < m_countRows; row++) {
		for (auto col = 0; col < m_countCols; col++) {
			window.draw(m_grid[row][col]);
		}
	}
}

float SfmlGridWindow::CellHeigh() const {
	return m_totalHeight / m_countRows;
}

float SfmlGridWindow::CellWidth() const {
	return m_totalWidth / m_countCols;
}
