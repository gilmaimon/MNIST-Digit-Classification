#pragma once
#include "WindowInterface.h"
#include "FlatternToPixelsInterface.h"

struct IInteractiveDataDrawingWindow : public virtual IWindow, public IFlatternToPixels {
	virtual ~IInteractiveDataDrawingWindow() = default;
	virtual void SetBrushSize(const size_t brushSize) = 0;
};