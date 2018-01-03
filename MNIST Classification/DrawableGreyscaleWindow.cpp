#include "DrawableGreyscaleWindow.h"

const float DrawableGreyscaleWindow::WindowSize = 500.0;

DrawableGreyscaleWindow::DrawableGreyscaleWindow():
	m_mouseDown(MouseDownState_None),
	SfmlWindow(WindowSize, WindowSize, "Draw Something!"),
	m_gridWindow(WindowSize / g_mnistImageSize, WindowSize / g_mnistImageSize, g_mnistImageSize, g_mnistImageSize) { }

void DrawableGreyscaleWindow::Draw() {
	SfmlWindow::Draw();
	m_gridWindow.Draw(m_renderWindow);
}

PixelsVector DrawableGreyscaleWindow::FlatternToPixels() const {
	PixelsVector result;
	for (size_t iRow = 0; iRow < g_mnistImageSize; iRow++) {
		for (size_t iCol = 0; iCol < g_mnistImageSize; iCol++) {
			float greyScaleValue = m_gridWindow(iRow, iCol).getFillColor().r;
			result.push_back(greyScaleValue);
		}
	}
	return result;
}

bool DrawableGreyscaleWindow::HandleSfmlEvent(const sf::Event coughtEvent) {
	UpdateMouseStateFromEvent(coughtEvent);

	if (m_mouseDown == MouseDownState_None) return false;
	
	const auto mousePosition = sf::Mouse::getPosition(m_renderWindow);
	const auto mappedGridPosition = MapWindowPositionToGridIndex({ mousePosition.y, mousePosition.x });	
	PaintCircleOnGridIndex(mappedGridPosition, 2);

	return true;
}

void DrawableGreyscaleWindow::OnCellClicked(const size_t rowIndex, const size_t colIndex) {
	double greyscaleColor = m_gridWindow.GetColor(rowIndex, colIndex).r;
	static const size_t LeftClickColorIncrement = 5;
	static const size_t RightClickColorDecrement = 10;

	switch (m_mouseDown) {
	case MouseDownState_Left:
		//In case of left click on a cell, brighten the color up to the max value which is 255
		greyscaleColor = std::min(greyscaleColor + LeftClickColorIncrement, 255.0);
		m_gridWindow.SetColor(
			rowIndex,
			colIndex,
			sf::Color(greyscaleColor, greyscaleColor, greyscaleColor)
		);
		break;

	case MouseDownState_Right:
		//In case of right click on a cell, darken the color up to the minimum value which is 0
		greyscaleColor = std::max(greyscaleColor - RightClickColorDecrement, 0.0);
		m_gridWindow.SetColor(
			rowIndex,
			colIndex,
			sf::Color(greyscaleColor, greyscaleColor, greyscaleColor)
		);
		break;

	default: 
		// Last state is None, in which we dont want to do anything
		// because it does not mean any change in that cell's state
		break;
	}

}

DrawableGreyscaleWindow::MouseDownState DrawableGreyscaleWindow::UpdateMouseStateFromEvent(const sf::Event event) {
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Button::Left) {
			m_mouseDown = MouseDownState_Left;
		}
		else {
			m_mouseDown = MouseDownState_Right;
		}
	}
	else if (event.type == sf::Event::MouseButtonReleased) {
		m_mouseDown = MouseDownState_None;
	}
	return m_mouseDown;
}

DrawableGreyscaleWindow::TablePosition DrawableGreyscaleWindow::MapWindowPositionToGridIndex(TablePosition screenPosition)
{
	const float distanceDelta = WindowSize / g_mnistImageSize;

	const int rowIndex = screenPosition.row / distanceDelta;
	const int colIndex = screenPosition.col / distanceDelta;
	return { rowIndex, colIndex };
}

void DrawableGreyscaleWindow::PaintCircleOnGridIndex(TablePosition paintTargetPosition, size_t brushSize)
{
	const size_t brushStartRow = std::max(0, paintTargetPosition.row - static_cast<int>(brushSize));
	const size_t brushEndRow = std::min(g_mnistImageSize - 1, paintTargetPosition.row + static_cast<int>(brushSize));

	const int brushStartCol = paintTargetPosition.col - brushSize;
	const int brushEndCol = paintTargetPosition.col + brushSize;

	for (int iCol = brushStartCol; iCol <= brushEndCol; iCol++) {
		const int rowsIncrement = abs(paintTargetPosition.col - iCol);
		for (int iRow = brushStartRow + rowsIncrement; iRow <= brushEndRow - rowsIncrement; iRow++) {
			if (iRow < 0 || iRow > g_mnistImageSize - 1 || iCol < 0 || iCol > g_mnistImageSize - 1) continue;
			OnCellClicked(iRow, iCol);
		}
	}
}
