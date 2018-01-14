#pragma once
#include "SfmlWindow.h"
#include "MnistCommon.h"

const int g_mnistImageSize = 28;

class MnistWindow : public SfmlWindow {
public:
	explicit MnistWindow(const float width, const float height, const std::string windowTitle, MnistDataItem item);

	void SetDataItem(MnistDataItem item);

	void Draw() override;
	virtual ~MnistWindow() = default;

protected:
	bool HandleSfmlEvent(const sf::Event e) override {
		if(e.type == sf::Event::Closed) {
			Close();
		}
		return true;
	}
private:
	MnistDataItem m_dataItem;
	const float m_width, m_height;

	void DrawMnistImage();
	void DrawLabel();
};

