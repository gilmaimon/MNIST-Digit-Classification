#pragma once
class Window {
public:
	virtual void Draw() = 0;
	virtual bool IsOpen() = 0;
	virtual void Close() = 0;
	virtual void Display() = 0;
	virtual bool HandleEvent() = 0;

	virtual ~Window() = default;
};