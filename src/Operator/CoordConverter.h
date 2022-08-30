#pragma	once
#include <QTransform>

class CoordConverter
{
public:
	CoordConverter(QTransform* viewTrans, QTransform* projTrans) : m_viewTrans(viewTrans), m_projTrans(projTrans) {}
	
	std::pair<double, double> worldToViewport(double x, double y)
	{
		QPointF p = (*m_viewTrans * *m_projTrans).map(QPointF(x, y));
		return { p.x(), p.y() };
	}
	
	std::pair<double, double> viewportToWorld(double x, double y)
	{
		QPointF p = (*m_viewTrans * *m_projTrans).inverted().map(QPointF(x, y));
		return { p.x(), p.y() };
	}

private:
	QTransform* m_viewTrans;
	QTransform* m_projTrans;
};
