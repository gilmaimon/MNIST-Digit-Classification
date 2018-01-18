#include "DrawableGreyscaleWindow.h"

DrawableGreyscaleWindow::DrawableGreyscaleWindow(const DimentionType width, const DimentionType height,
	const std::string windowTitle, const size_t numRows, const size_t numCols) :
	SfmlWindow(width, height, windowTitle),
	m_gridWindow(width, height, numCols, numRows),
	m_mouseDownState(MouseDownState_None),
	m_countCols(numCols), m_countRows(numRows), m_brushSize(2) { }

void DrawableGreyscaleWindow::Draw() {
	SfmlWindow::Draw();
	m_gridWindow.Draw(m_renderWindow);
}

PixelsVector DrawableGreyscaleWindow::FlatternToPixels() const {
	PixelsVector result;
	for (size_t iRow = 0; iRow < m_countRows; iRow++) {
		for (size_t iCol = 0; iCol < m_countCols; iCol++) {
			float greyScaleValue = m_gridWindow(iRow, iCol).getFillColor().r;
			result.push_back(greyScaleValue);
		}
	}
	return result;
}

void DrawableGreyscaleWindow::SetBrushSize(const size_t brushSize) {
	m_brushSize = brushSize;
}

bool DrawableGreyscaleWindow::HandleSfmlEvent(const sf::Event coughtEvent) {
	UpdateMouseStateFromEvent(coughtEvent);

	if (m_mouseDownState == MouseDownState_None) return false;
	
	const auto mousePosition = sf::Mouse::getPosition(m_renderWindow);
	const auto mappedGridPosition = MapWindowPositionToGridIndex({ mousePosition.y, mousePosition.x });	
	PaintCircleOnGridIndex(mappedGridPosition);

	return true;
}

void DrawableGreyscaleWindow::OnCellClicked(const size_t rowIndex, const size_t colIndex) {
	double greyscaleColor = m_gridWindow.GetColor(rowIndex, colIndex).r;
	static const size_t LeftClickColorIncrement = 5;
	static const size_t RightClickColorDecrement = 10;

	switch (m_mouseDownState) {
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
			m_mouseDownState = MouseDownState_Left;
		}
		else {
			m_mouseDownState = MouseDownState_Right;
		}
	}
	else if (event.type == sf::Event::MouseButtonReleased) {
		m_mouseDownState = MouseDownState_None;
	}
	return m_mouseDownState;
}

DrawableGreyscaleWindow::TablePosition DrawableGreyscaleWindow::MapWindowPositionToGridIndex(const TablePosition screenPosition) const {
	const auto colsDistanceDelta = GetWidth() / g_mnistImageSize;
	const int colIndex = screenPosition.col / colsDistanceDelta;

	const auto rowsDistanceDelta = GetHeight() / g_mnistImageSize;
	const int rowIndex = screenPosition.row / rowsDistanceDelta;

	return { rowIndex, colIndex };
}

void DrawableGreyscaleWindow::PaintCircleOnGridIndex(const TablePosition centerPosition)
{
	//Comupte brush starting row, without going out of bounds
	const int brushStartRow = centerPosition.row - static_cast<int>(m_brushSize);
	const int brushEndRow = centerPosition.row + static_cast<int>(m_brushSize);

	const int brushStartCol = centerPosition.col - static_cast<int>(m_brushSize);
	const int brushEndCol = centerPosition.col + static_cast<int>(m_brushSize);

	for (int iCol = brushStartCol; iCol <= brushEndCol; iCol++) {
		const int rowsIncrement = abs(centerPosition.col - iCol);
		for (int iRow = brushStartRow + rowsIncrement; iRow <= brushEndRow - rowsIncrement; iRow++) {
			if (iRow < 0 || iRow > g_mnistImageSize - 1 || iCol < 0 || iCol > g_mnistImageSize - 1) continue;
			OnCellClicked(iRow, iCol);
		}
	}
}
