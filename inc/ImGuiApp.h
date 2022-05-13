#ifndef IMGUI_APP_H
#define IMGUI_APP_H

#include <map>
#include <memory>
#include <string>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui_internal.h>
#include <GLFW/glfw3.h>

#include <implot.h>

#include "ImGuiWidget.h"

namespace matrixui {

class ImGuiApp {
public:
	ImGuiApp(int windowWidth, int windowHeight, std::string windowName);
	int init();
	void serviceLoop();
	void close();

	int addWidget(std::shared_ptr<ImGuiWidget> & widget);

	bool wantsToClose() const;

protected:
	void beginFrame();

	/** @brief Override to render things below widgets (i.e. menubar, background image) */
	virtual void renderFrame() {};

  void displayFrame();

	bool _wantsToClose;

	int _widgetCounter;
	std::map<int, std::shared_ptr<ImGuiWidget>> _widgets;
private:
  GLFWwindow* _window;
	int _windowWidth, _windowHeight;
	std::string _windowName;
  const ImVec4 _clearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	void renderWidgets();
}; // class ImGuiApp

} // namespace matrixui

#endif // IMGUI_APP_H
