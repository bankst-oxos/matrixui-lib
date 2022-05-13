#include "ImGuiApp.h"

namespace matrixui {

ImGuiApp::ImGuiApp(int windowWidth, int windowHeight, std::string windowName)
	: _windowWidth(windowWidth), _windowHeight(windowHeight), _windowName(windowName) {}

int ImGuiApp::init() {
	if (!glfwInit()) {
		return -1;
	}

	#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
	#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
	#endif

	_window = glfwCreateWindow(_windowWidth, _windowHeight, _windowName.c_str(), NULL, NULL);
	if (_window == NULL) {
		// log_err("GLFW window create FAIL");
		return -2;
	}
	// log_info("GLFW window create OK");

	glfwMakeContextCurrent(_window);
	glfwSwapInterval(0);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImPlot::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(_window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	return 0;
}

void ImGuiApp::serviceLoop() {
	_wantsToClose = glfwWindowShouldClose(_window);
	if (_wantsToClose) return;

	// Poll GLFW events
	glfwPollEvents();

	beginFrame();
	renderFrame();
	renderWidgets();
	displayFrame();
}

void ImGuiApp::close() {
	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImPlot::DestroyContext();
	ImGui::DestroyContext();
	glfwTerminate();
}

int ImGuiApp::addWidget(std::shared_ptr<ImGuiWidget> &widget) {
	int thisWidgetID = _widgetCounter++;

	auto ret =_widgets.insert({thisWidgetID, widget});
	widget->init();
	return thisWidgetID;
}

bool ImGuiApp::wantsToClose() const {
	return _wantsToClose;
}

void ImGuiApp::beginFrame() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void ImGuiApp::renderWidgets() {
	for (auto it = _widgets.begin(); it != _widgets.end(); it++) {
		if (!it->second) {
			std::cout << "Null widget detected! Skipping." << std::endl;
			continue;
		}

		std::string widgetName = it->second->getWidgetName();
		if(it->second->getVisibility()) {
			it->second->render();
		} else {
			// do nothing!
		}
	}

	ImGui::EndFrame();
}

void ImGuiApp::displayFrame() {
	ImGui::Render();

	int display_w, display_h;
	glfwGetFramebufferSize(_window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClearColor(_clearColor.x * _clearColor.w, _clearColor.y * _clearColor.w, _clearColor.z * _clearColor.w, _clearColor.w);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(_window);
}

} // namespace matrixui
