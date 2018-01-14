#include "SfmlWindow.h"

SfmlWindow::SfmlWindow(const size_t width, const size_t height, const std::string windowTitle): m_renderWindow(
	sf::VideoMode(width, height), windowTitle) { }

void SfmlWindow::Draw() {
	m_renderWindow.clear();
}

void SfmlWindow::Display() {
	m_renderWindow.display();
}

bool SfmlWindow::IsOpen() {
	return m_renderWindow.isOpen();
}

void SfmlWindow::Close() {
	m_renderWindow.close();
}
