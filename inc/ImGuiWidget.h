#ifndef IMGUI_WIDGET_H
#define IMGUI_WIDGET_H

#include <chrono>
#include <iostream>
#include <memory>
#include <string>

#include <imgui.h>

namespace matrixui {
using namespace std::chrono_literals;

#define DEFAULT_WIDGET_FLAGS ImGuiWindowFlags_

class ImGuiWidget {
public:
	ImGuiWidget(std::string windowName, ImGuiWindowFlags windowFlags = 0);
	/** called once to prepare widget */
	virtual void init() {};
	void render();

	double getRenderTime();

	std::string getWidgetName();

	void setVisibility(bool visibility);
	bool getVisibility();
protected:
	virtual void internalRender() = 0;

	bool _showDebugInfo = false;
private:
	std::string _windowName;
	ImGuiWindowFlags _windowFlags = 0;

	bool _visibility = true;

	std::chrono::duration<double, std::milli> _renderTime = 0ms;
}; // class ImGuiWidget

typedef std::shared_ptr<ImGuiWidget> ImGuiWidgetPtr;

} // namespace matrixui

#endif // IMGUI_WIDGET_H