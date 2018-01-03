#pragma once
#include "WindowInterface.h"
#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class SfmlWindow : public virtual IWindow {
public:
	explicit SfmlWindow(const size_t width, const size_t height, const std::string windowTitle);

	void Draw() override;
	bool IsOpen() override;
	void Close() override;
	void Display() final override;

	bool HandleEvent() override {
		sf::Event event;
		const auto result = m_renderWindow.pollEvent(event);
		HandleSfmlEvent(event);
		return result;
	}

protected:
	virtual bool HandleSfmlEvent(sf::Event e) = 0;
	sf::RenderWindow m_renderWindow;
};

