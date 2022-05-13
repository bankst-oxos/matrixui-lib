#include "ImGuiWidget.h"
#include "imgui.h"

namespace matrixui {

using namespace std::chrono;

ImGuiWidget::ImGuiWidget(
	std::string windowName,
	ImGuiWindowFlags windowFlags)
 : _windowName(windowName) {
	 _windowFlags |= windowFlags;
 }

void ImGuiWidget::render() {
	if (_visibility) {
		auto start = high_resolution_clock::now();

		if (ImGui::Begin(_windowName.c_str(), &_visibility, _windowFlags)) {
			// debug toggle and render profiling
			ImGui::Checkbox("Show Debug Info", &_showDebugInfo);
			if (_showDebugInfo)	ImGui::Text("Last render took %.2f ms", getRenderTime());

			internalRender();
		}
		ImGui::End();
		_renderTime = high_resolution_clock::now() - start;
	} else {
		_renderTime = 0ms;
	}
}

double ImGuiWidget::getRenderTime() {
	return _renderTime.count();
}

std::string ImGuiWidget::getWidgetName() {
	return _windowName;
}

void ImGuiWidget::setVisibility(bool visibility) {
	_visibility = visibility;
}

bool ImGuiWidget::getVisibility() {
	return _visibility;
}

} // namespace matrixui
