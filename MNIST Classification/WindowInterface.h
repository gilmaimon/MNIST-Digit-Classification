#pragma once
struct IWindow {
	virtual void Draw() = 0;
	virtual bool IsOpen() = 0;
	virtual void Close() = 0;
	virtual void Display() = 0;
	virtual bool HandleEvent() = 0;

	virtual ~IWindow() = default;
};