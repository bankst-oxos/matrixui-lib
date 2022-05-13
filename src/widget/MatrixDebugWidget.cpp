#include "MatrixDebugWidget.h"
#include "MatrixPlot.h"
#include "imgui.h"
#include "implot.h"
#include <chrono>

namespace matrixui {

using namespace std::chrono;

// override
void MatrixDebugWidget::internalRender() {
	ImGui::Checkbox("Show ImGui Demo", &_showDemo);

	// generate plot data
	ImVec2 mouse = ImGui::GetMousePos();
	plot_t += ImGui::GetIO().DeltaTime;
	sdata1.AddPoint(plot_t, mouse.x * 0.0005f);
	rdata1.AddPoint(plot_t, mouse.x * 0.0005f);
	sdata2.AddPoint(plot_t, mouse.y * 0.0005f);
	rdata2.AddPoint(plot_t, mouse.y * 0.0005f);

	static float history = 10.0f;
	static ImPlotAxisFlags flags = ImPlotAxisFlags_NoTickLabels;

	// show plot
	if (ImGui::BeginChild("Plot Test", ImVec2{500, 300}, true)) {
		if (ImPlot::BeginPlot("Scrolling", ImVec2(-1,150))) {
			ImPlot::SetupAxes(NULL, NULL, flags, flags);
			ImPlot::SetupAxisLimits(ImAxis_X1, plot_t - history, plot_t, ImGuiCond_Always);
			ImPlot::SetupAxisLimits(ImAxis_Y1,0,1);
			ImPlot::SetNextFillStyle(IMPLOT_AUTO_COL,0.5f);

			MatrixTimeSeriesPlot<float>::plotSimpleData(
				SimplePlotType::Line, "Mouse X",
				&sdata1.Data[0].first, &sdata1.Data[0].second,
				sdata1.Data.size(), sdata1.Offset
			);

			// ImPlot::PlotShaded("Mouse X", &sdata1.Data[0].first, &sdata1.Data[0].second, sdata1.Data.size(), -INFINITY, sdata1.Offset, 2 * sizeof(float));
			ImPlot::PlotLine("Mouse Y", &sdata2.Data[0].first, &sdata2.Data[0].second, sdata2.Data.size(), sdata2.Offset, 2*sizeof(float));
			ImPlot::EndPlot();
		}
		if (ImPlot::BeginPlot("Rolling", ImVec2(-1,150))) {
			ImPlot::SetupAxes(NULL, NULL, flags, flags);
			ImPlot::SetupAxisLimits(ImAxis_X1,0,history, ImGuiCond_Always);
			ImPlot::SetupAxisLimits(ImAxis_Y1,0,1);
			ImPlot::PlotLine("Mouse X", &rdata1.Data[0].first, &rdata1.Data[0].second, rdata1.Data.size(), 0, 2 * sizeof(float));
			ImPlot::PlotLine("Mouse Y", &rdata2.Data[0].first, &rdata2.Data[0].second, rdata2.Data.size(), 0, 2 * sizeof(float));
			ImPlot::EndPlot();
		}
		ImGui::EndChild();
	}

	if (_showDemo) {
		ImGui::ShowDemoWindow(&_showDemo);
	}
}

void MatrixDebugWidget::shouldShowImGuiDemo(bool showDemo) {
	_showDemo = showDemo;
}

} // namespace matrixui
