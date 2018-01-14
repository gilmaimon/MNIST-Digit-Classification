#include "DrawableGreyscaleWindow.h"

const float DrawableGreyscaleWindow::WindowSize = 500.0;

DrawableGreyscaleWindow::DrawableGreyscaleWindow():
	SfmlWindow(WindowSize, WindowSize, "Draw Something!"),
	m_gridWindow(WindowSize / g_mnistImageSize, WindowSize / g_mnistImageSize, g_mnistImageSize, g_mnistImageSize) { }

void DrawableGreyscaleWindow::Draw() {
	SfmlWindow::Draw();
	m_gridWindow.Draw(m_renderWindow);
}

PixelsVector DrawableGreyscaleWindow::FlatternImage() const {
	PixelsVector result;
	for (size_t iRow = 0; iRow < g_mnistImageSize; iRow++) {
		for (size_t iCol = 0; iCol < g_mnistImageSize; iCol++) {
			float greyScaleValue = m_gridWindow(iRow, iCol).getFillColor().r;
			result.push_back(greyScaleValue);
		}
	}
	return result;
}

bool DrawableGreyscaleWindow::HandleSfmlEvent(const sf::Event e) {
	if (e.type == sf::Event::MouseButtonPressed) {
		if (e.mouseButton.button == sf::Mouse::Button::Left) m_mouseDown = MouseDown_Left;
		else m_mouseDown = MouseDown_Right;
	}
	else if (e.type == sf::Event::MouseButtonReleased) {
		m_mouseDown = MouseDown_None;
	}

	if (m_mouseDown != MouseDown_None) {
		const float xPosition = sf::Mouse::getPosition(m_renderWindow).x;
		const float yPosition = sf::Mouse::getPosition(m_renderWindow).y;

		const float distanceDelta = WindowSize / g_mnistImageSize;
		const int rowIndex = yPosition / distanceDelta;
		const int colIndex = xPosition / distanceDelta;

		const int brushSize = 2;

		const size_t brushStartRow = std::max(0, rowIndex - brushSize);
		const size_t brushEndRow = std::min<size_t>(g_mnistImageSize - 1, rowIndex + brushSize);

		const int brushStartCol = colIndex - brushSize;
		const int brushEndCol = colIndex + brushSize;

		for (int iCol = brushStartCol; iCol <= brushEndCol; iCol++) {
			const int rowsIncrement = abs(colIndex - iCol);
			for (int iRow = brushStartRow + rowsIncrement; iRow <= brushEndRow - rowsIncrement; iRow++) {
				if (iRow < 0 || iRow > g_mnistImageSize - 1 || iCol < 0 || iCol > g_mnistImageSize - 1) continue;
				OnCellClicked(iRow, iCol);
			}
		}

	}
	return false;
}

void DrawableGreyscaleWindow::OnCellClicked(const size_t rowIndex, const size_t colIndex) {
	double greyscaleColor = m_gridWindow.GetColor(rowIndex, colIndex).r;

	switch (m_mouseDown) {
	case MouseDown_Left:
		greyscaleColor = std::min(greyscaleColor + 5, 255.0);
		m_gridWindow.SetColor(
			rowIndex,
			colIndex,
			sf::Color(greyscaleColor, greyscaleColor, greyscaleColor)
		);

		break;

	case MouseDown_Right:
		greyscaleColor = std::max(greyscaleColor - 10, 0.0);
		m_gridWindow.SetColor(
			rowIndex,
			colIndex,
			sf::Color(greyscaleColor, greyscaleColor, greyscaleColor)
		);
		break;
	default: ;
	}

}
