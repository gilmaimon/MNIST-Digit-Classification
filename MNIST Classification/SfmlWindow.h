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

	float GetWidth() const {
		return m_renderWindow.getSize().x;
	}

	float GetHeight() const {
		return m_renderWindow.getSize().y;
	}

	bool HandleEvent() override {
		sf::Event event;
		const auto result = m_renderWindow.pollEvent(event);
		
		if (event.type != sf::Event::Closed) {
			HandleSfmlEvent(event);
		}
		else {
			m_renderWindow.close();
		}
		
		return result;
	}

protected:
	virtual bool HandleSfmlEvent(sf::Event e) = 0;
	sf::RenderWindow m_renderWindow;
};

