#ifndef MATRIX_PLOT_H
#define MATRIX_PLOT_H

#include <math.h>
#include <string>
#include <vector>

#include <implot.h>

namespace matrixui {

// utility structure for realtime plot
template <class T>
struct ScrollingBuffer {
	int MaxSize;
	int Offset;
	ImVector<std::pair<float, T>> Data;
	ScrollingBuffer(int max_size = 2000) {
		MaxSize = max_size;
		Offset  = 0;
		Data.reserve(MaxSize);
	}
	void AddPoint(float x, T y) {
		if (Data.size() < MaxSize)
			Data.push_back(std::pair(x,y));
		else {
			Data[Offset] = std::pair(x,y);
			Offset =  (Offset + 1) % MaxSize;
		}
	}
	void Erase() {
		if (Data.size() > 0) {
			Data.shrink(0);
			Offset = 0;
		}
	}
};

// utility structure for realtime plot
template <class T>
struct RollingBuffer {
	float Span;
	ImVector<std::pair<float, T>> Data;
	RollingBuffer() {
		Span = 10.0f;
		Data.reserve(2000);
	}
	void AddPoint(float x, T y) {
		float xmod = fmodf(x, Span);
		if (!Data.empty() && xmod < Data.back().first) Data.shrink(0);
		Data.push_back(std::pair(xmod, y));
	}
};

enum SimplePlotType {
	Line,
	Stairs,
	Shaded,
	Bar,
	HBar,
	// These aren't so simple, but are types of plots
	// Scatter,
	// BarGroups,
	// HBarGroups,
	// ErrorBars
	// ErrorHBars,
	// Stems,
	// VLines,
	// HLines,
	// PieChart,
	// Heatmap,
	//
};

template <class T>
class MatrixTimeSeriesPlot {
public:
	static void plotSimpleData(SimplePlotType plotType, std::string label, float * timeDelta, T * datapoint, int count, int offset = 0) {
		switch(plotType) {
		default: // default to Line
		case SimplePlotType::Line:
			ImPlot::PlotLine(label.c_str(), timeDelta, datapoint, count, offset, 2 * sizeof(T));
			break;
		case SimplePlotType::Stairs:
			ImPlot::PlotStairs(label.c_str(), timeDelta, datapoint, count, offset, 2 * sizeof(T));
			break;
		case SimplePlotType::Shaded:
			ImPlot::PlotShaded(label.c_str(), timeDelta, datapoint, count, -INFINITY, offset, 2 * sizeof(T));
			break;
		case SimplePlotType::Bar:
			ImPlot::PlotBars(label.c_str(), timeDelta, datapoint, count, -INFINITY, offset, 2 * sizeof(T));
			break;
		case SimplePlotType::HBar:
			ImPlot::PlotBarsH(label.c_str(), timeDelta, datapoint, count, -INFINITY, offset, 2 * sizeof(T));
			break;
	}
	}
};

template <class T>
class MatrixPlot {
	MatrixPlot();

	void addDataPoint(float time, T dataPoint);

private:
	ScrollingBuffer<T> _scrollBuf;
	RollingBuffer<T> _rollBuf;
	// std::vector<ScrollingBuffer<T>> _scrollBufs;
	// std::vector<RollingBuffer<T>> _rollBufs;
	// ScrollingBuffer
}; // class MatrixPlot



} // namespace matrixui

#endif // MATRIX_PLOT_H