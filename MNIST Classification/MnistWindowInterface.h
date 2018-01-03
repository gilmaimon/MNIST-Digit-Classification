#pragma once
#include "MnistCommon.h"
#include "WindowInterface.h"

struct IMnistWindow : public virtual IWindow {
	virtual void SetDataItem(MnistDataItem item) = 0;
};
