#include "MatrixPlot.h"

namespace matrixui {

template <class T>
MatrixPlot<T>::MatrixPlot() {
	_rollBuf.Span = 10.0f;
}

template <class T>
void MatrixPlot<T>::addDataPoint(float time, T dataPoint) {
	_scrollBuf.AddPoint(time, dataPoint);
	_rollBuf.AddPoint(time, dataPoint);
}

} // namespace matrixui
