#include "OpenCVMatWidget.h"
#include <imgui_impl_glfw.h>
#include "GL/glcorearb.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_opengl3_loader.h"
#include <imgui_internal.h>
#include <GLFW/glfw3.h>

using namespace std::chrono;
using namespace std::chrono_literals;

namespace matrixui {
	
	void OpenCVMatWidget::init() {
		// nothing ig
	}
	
	void OpenCVMatWidget::renderCvMat() {
		cv::Mat * mat = matProviderPtr_();
		uint width = mat->cols;
		uint height = mat->rows;
		
		auto imageConvertBeginTime = steady_clock::now();
		
		if (cvImgTextureId_ == -1) glGenTextures( 1, &cvImgTextureId_ );
		
		glBindTexture( GL_TEXTURE_2D, cvImgTextureId_ );
		glPixelStorei(GL_UNPACK_ALIGNMENT, (mat->step & 3) ? 1 : 4);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, mat->ptr() );
		
		auto imageConvertElapsedTime = std::chrono::duration_cast<std::chrono::nanoseconds>(steady_clock::now() - imageConvertBeginTime);
		
		if (_showDebugInfo) {
			double millis = imageConvertElapsedTime.count() / 1000000.0;
			ImGui::Text("cv::Mat conversion time: %.5fms", millis);
			ImGui::Text("Image Size: (%d, %d)",  width, height);
		}
		
		ImGui::Image( reinterpret_cast<void*>( static_cast<intptr_t>( cvImgTextureId_ ) ), ImVec2( width, height ) );
	}
	
	void OpenCVMatWidget::internalRender() {
		renderCvMat();
	}
}