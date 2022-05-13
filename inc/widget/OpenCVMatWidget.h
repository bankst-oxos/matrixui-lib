#ifndef OPENCTMAT_WIDGET_H
#define OPENCTMAT_WIDGET_H

#include <chrono>
#include <functional>
#include <memory>
#include <ratio>
#include <vector>
#include <string>

#include "opencv2/core.hpp"

#include "imgui.h"
#include "imgui_impl_opengl3.h"

#include "ImGuiWidget.h"

using namespace std::chrono;
using namespace std::chrono_literals;

typedef std::function<cv::Mat*()> CVMatProviderFunc;

namespace matrixui {

class OpenCVMatWidget : public ImGuiWidget {
public:
	OpenCVMatWidget(CVMatProviderFunc matProviderPtr) 
		: ImGuiWidget("OpenCVMat", ImGuiWindowFlags_AlwaysAutoResize), 
		matProviderPtr_(matProviderPtr) {};

protected:
	// override
	void init() override;
	void internalRender() override;
private:
	void renderCvMat();
	CVMatProviderFunc matProviderPtr_;
	
	// GLuint
	unsigned int cvImgTextureId_ = -1;
}; // class OpenCVMatWidget


} // namespace matrixui

#endif // OPENCVMAT_WIDGET_H