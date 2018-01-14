#pragma once
#include <SFML/Graphics/Color.hpp>
#include <algorithm>
#include "GridWindow.h"
#include "MnistWindow.h"

class DrawableGreyscaleWindow : public SfmlWindow {
public:
	DrawableGreyscaleWindow();

	virtual void Draw() override;

	PixelsVector FlatternImage() const;

	virtual ~DrawableGreyscaleWindow() override = default;
protected:
	virtual bool HandleSfmlEvent(const sf::Event e) override;

private:
	enum MouseDown {
		MouseDown_Left,
		MouseDown_Right,
		MouseDown_None
	};

	static const float WindowSize;
	GridWindow m_gridWindow;
	MouseDown m_mouseDown = MouseDown_None;

	void OnCellClicked(const size_t rowIndex, const size_t colIndex);
};