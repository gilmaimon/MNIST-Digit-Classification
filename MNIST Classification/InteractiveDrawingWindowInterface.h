#pragma once
#include "WindowInterface.h"
#include "FlatternToPixelsInterface.h"

struct IInteractiveDataDrawingWindow : public virtual IWindow, public IFlatternToPixels {
	virtual ~IInteractiveDataDrawingWindow() = default;
};