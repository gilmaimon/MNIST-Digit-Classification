#pragma once
#include <SFML/Graphics/Color.hpp>
#include <algorithm>
#include "GridWindow.h"
#include "MnistWindow.h"
#include "InteractiveDrawingWindowInterface.h"

class DrawableGreyscaleWindow : public IInteractiveDataDrawingWindow, public SfmlWindow {
public:
	DrawableGreyscaleWindow();

	virtual void Draw() override;

	PixelsVector FlatternToPixels() const;

	virtual ~DrawableGreyscaleWindow() override = default;
protected:
	virtual bool HandleSfmlEvent(const sf::Event e) override;

private:
	enum MouseDownState {
		MouseDownState_Left,
		MouseDownState_Right,
		MouseDownState_None
	};

	static const float WindowSize;
	GridWindow m_gridWindow;
	MouseDownState m_mouseDown = MouseDownState_None;

	void OnCellClicked(const size_t rowIndex, const size_t colIndex);
	MouseDownState UpdateMouseStateFromEvent(const sf::Event event);

	struct TablePosition {
		int row;
		int col;
	};
	TablePosition MapWindowPositionToGridIndex(TablePosition screenPosition);
	void PaintCircleOnGridIndex(TablePosition paintTargetPosition, size_t brushSize);
};