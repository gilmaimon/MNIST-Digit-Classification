#pragma once
#include "SfmlGridWindow.h"
#include "MnistWindow.h"
#include "InteractiveDrawingWindowInterface.h"

class DrawableGreyscaleWindow : public IInteractiveDataDrawingWindow, public SfmlWindow {
public:
	typedef float DimentionType;

	DrawableGreyscaleWindow(const DimentionType width, const DimentionType height,
		const std::string windowTitle, const size_t numRows, const size_t numCols);

	virtual void Draw() override;
	PixelsVector FlatternToPixels() const override;
	void SetBrushSize(const size_t brushSize) override;

	virtual ~DrawableGreyscaleWindow() override = default;
protected:
	virtual bool HandleSfmlEvent(const sf::Event e) override;

private:
	enum MouseDownState {
		MouseDownState_Left,
		MouseDownState_Right,
		MouseDownState_None
	};

	SfmlGridWindow m_gridWindow;
	MouseDownState m_mouseDownState = MouseDownState_None;
	size_t m_countCols, m_countRows;
	size_t m_brushSize;

	void OnCellClicked(const size_t rowIndex, const size_t colIndex);
	MouseDownState UpdateMouseStateFromEvent(const sf::Event event);

	struct TablePosition {
		int row;
		int col;
	};
	TablePosition MapWindowPositionToGridIndex(TablePosition screenPosition) const;
	void PaintCircleOnGridIndex(TablePosition paintTargetPosition);
};