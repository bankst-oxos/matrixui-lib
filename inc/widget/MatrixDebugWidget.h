#ifndef MATRIX_DEBUG_WIDGET_H
#define MATRIX_DEBUG_WIDGET_H

#include <chrono>
#include <vector>

#include "imgui.h"
#include "implot.h"

#include "ImGuiWidget.h"
#include "MatrixPlot.h"

namespace matrixui {

class MatrixDebugWidget : public ImGuiWidget {
public:
	MatrixDebugWidget() : ImGuiWidget("Matrix Debug") {}

	void shouldShowImGuiDemo(bool showDemo);

protected:
	// override
	void internalRender();

private:
	bool _showDemo = false;

	// Junk data for plot test
	ScrollingBuffer<float> sdata1, sdata2;
	RollingBuffer<float>   rdata1, rdata2;
	float plot_t = 0;
	long microsSinceLast = 0;

}; // class MatrixDebugWidget


} // namespace matrixui

#endif // MATRIX_DEBUG_WIDGET_H