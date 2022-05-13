// #ifndef OPENCTMAT_WIDGET_H
// #define OPENCTMAT_WIDGET_H

// #include <chrono>
// #include <functional>
// #include <memory>
// #include <ratio>
// #include <vector>
// #include <string>

// #include "imgui.h"
// // #include "gl3w.h"

// #include "ImGuiWidget.h"

// using namespace std::chrono;
// using namespace std::chrono_literals;

// // typedef std::function<cv::Mat*()> CVMatProviderFunc;

// namespace matrixui {

// class OpenCVMatWidget : public ImGuiWidget {
// public:
// 	OpenCVMatWidget(int width, int height) 
// 		: ImGuiWidget("OpenCVMat", ImGuiWindowFlags_AlwaysAutoResize), 
// 		canvasWidth_(width), canvasHeight_(height)
// 		{};

// protected:
// 	// override
// 	void init() override;
// 	void internalRender() override;
// private:
// 	void renderCvMat();
// 	const int canvasWidth_;
// 	const int canvasHeight_;
// 	// CVMatProviderFunc matProviderPtr_;
	
// 	// GLuint
// 	unsigned int cvImgTextureId_ = -1;
// }; // class OpenCVMatWidget


// } // namespace matrixui

// #endif // OPENCVMAT_WIDGET_H