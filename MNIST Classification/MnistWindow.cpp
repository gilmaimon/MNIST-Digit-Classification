#include "MnistWindow.h"
#include <cassert>
#include <SFML/Graphics.hpp>
#include "SfmlGridWindow.h"

MnistWindow::MnistWindow(const float width, const float height,
	const std::string windowTitle, MnistDataItem item) : 
	SfmlWindow(width, height, windowTitle), m_dataItem(std::move(item)), m_width(width), m_height(height) {
}

void MnistWindow::SetDataItem(MnistDataItem item) {
	m_dataItem = std::move(item);
}

void MnistWindow::Draw() {
	SfmlWindow::Draw();
	DrawMnistImage();
	DrawLabel();
}

void MnistWindow::DrawMnistImage() {
	assert(m_dataItem.imageData.size() == g_mnistImageSize * g_mnistImageSize);

	SfmlGridWindow gridWindow{ m_width, m_height, g_mnistImageSize, g_mnistImageSize };
	for (size_t row = 0; row < g_mnistImageSize; row++) {
		for (size_t col = 0; col < g_mnistImageSize; col++) {
			const uint8_t alphaColor = m_dataItem.imageData[row * g_mnistImageSize + col];
			const sf::Color greyScaleColor{ alphaColor, alphaColor , alphaColor };
			gridWindow.SetColor(row, col, greyScaleColor);
		}
	}

	gridWindow.Draw(m_renderWindow);
}

void MnistWindow::DrawLabel() {
	std::string textToShow = "Correct: ";
	textToShow += static_cast<char>(m_dataItem.label + '0');

	sf::Font font;
	font.loadFromFile("arial.ttf");
	// Create a text
	sf::Text correctLabel(textToShow, font);
	correctLabel.setCharacterSize(25);
	correctLabel.setStyle(sf::Text::Bold);
	//correctLabel.setColor(sf::Color::Red);
	correctLabel.setPosition(10, 5);

	// Draw it
	m_renderWindow.draw(correctLabel);
}
