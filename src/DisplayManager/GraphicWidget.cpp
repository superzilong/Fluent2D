#include "GraphicWidget.h"
#include <QMouseEvent>
#include "Operator/CADOperatorMgr.h"
#include <QGraphicsLineItem>
#include <QScrollBar>
#include <QWheelEvent>

#include "BaseOperator.h"
#include "DisplayManager.h"

#include "Core/Log/Log.h"


const static int GRID_SIZE = 50;

GraphicWidget::GraphicWidget(QWidget* parent) : QGraphicsView(parent)
{
	setMouseTracking(true);
	setScene(&m_scene);

	//QOpenGLWidget* gl = new QOpenGLWidget();
	//QSurfaceFormat format;
	//format.setSamples(4);
	//gl->setFormat(format);
	//setViewport(gl);
}

QPointF GraphicWidget::worldToViewport(const QPointF& p) const
{
	return mapFromScene(p);
}

QPointF GraphicWidget::viewportToWorld(const QPointF& p) const
{
	return mapToScene(QPoint(static_cast<int>(p.x()), static_cast<int>(p.y())));
}

void GraphicWidget::keyPressEvent(QKeyEvent* event)
{
	if (m_operator)
	{
	    m_operator->keyPressEvent(event);
	}
}

void GraphicWidget::mousePressEvent(QMouseEvent* event)
{
    if (m_operator)
    {
        m_operator->mousePressEvent(event);
    }
}

void GraphicWidget::mouseMoveEvent(QMouseEvent* event)
{
    if (m_operator)
    {
        m_operator->mouseMoveEvent(event);
    }

	auto& dm = DisplayManager::instance();
	auto vp = dm.getViewportIDByGraphicsWidget(this);
	emit dm.signal_mousePos(vp, mapToScene(event->pos()));
}

void GraphicWidget::mouseReleaseEvent(QMouseEvent* event)
{
	auto mgr = CADOperatorMgr::instance();
	auto pOp = mgr->getCurrentOp();
	if (pOp)
	{
		pOp->mouseReleaseEvent(event);
	}
}

void GraphicWidget::init()
{
	setBackgroundBrush(QBrush(QColor(0x3C3C3C)));

	m_scene.addRect(-1000.0, 100.0, 900.0, 100.0, Qt::NoPen, QBrush(Qt::yellow));
	m_scene.addRect(0.0, 0.0, 1000.0, 100.0, Qt::NoPen, QBrush(Qt::blue));
	QRectF bbRect = m_scene.itemsBoundingRect();
	LOG_DEBUG("bounding rect is at {0},{1}, w {2}, h{3}", bbRect.left(), bbRect.top(), bbRect.width(), bbRect.height());
	m_scene.setSceneRect(bbRect);

	QWidget* vp = viewport();

	int w = vp->width();
	int h = vp->height();
	LOG_TRACE("Viewport size is {0} * {1}", w, h);

	QPointF tl = mapToScene(0, 0);
	QPointF br = mapToScene(w, h);
	//m_scene.setSceneRect(QRectF(tl, br));

	QColor red(0xa44453);
	QColor green(0x638532);
	QColor gray(0x4F4F4F);

	//int leftIndex = int(tl.x() / 50);
	//int rightIndex = int(br.x() / 50);
 //   for (int i = leftIndex; i <= rightIndex; ++i)
 //   {
	//	QColor             c    = i == 0 ? green : gray;
 //       QGraphicsLineItem* line = m_scene.addLine(i * GRID_SIZE, tl.y(), i * GRID_SIZE, br.y(), c);
	//	line->setZValue(-1);

 //   }

	//int topIndex = int(tl.y() / 50);
	//int bottomIndex = int(br.y() / 50);
	//for (int j = topIndex; j <= bottomIndex; ++j)
	//{
	//	QColor             c    = j == 0 ? red : gray;
 //       QGraphicsLineItem* line = m_scene.addLine(tl.x(), j * GRID_SIZE, br.x(), j * GRID_SIZE, c);
	//	line->setZValue(-1);
	//}
}

void GraphicWidget::tick()
{
}

void GraphicWidget::resizeEvent(QResizeEvent* event)
{
	QWidget* vp = viewport();

	int w = vp->width();
	int h = vp->height();
	LOG_TRACE("Viewport size is {0} * {1}", w, h);
	QGraphicsView::resizeEvent(event);
}

void GraphicWidget::showEvent(QShowEvent* event)
{
	QWidget* vp = viewport();

	int w = vp->width();
	int h = vp->height();
	LOG_TRACE("Viewport size is {0} * {1}", w, h);
	init();
	QGraphicsView::showEvent(event);
}

void GraphicWidget::wheelEvent(QWheelEvent* event)
{
	auto delta = event->angleDelta();
	LOG_DEBUG("wheel angle y delta: {0}", delta.y());
	if (delta.y() > 0)
	{
		scale(1.1, 1.1);
	}
	else if (delta.y() < 0)
	{
		scale(10. / 11., 10. / 11.);
	}

    QGraphicsView::wheelEvent(event);
}

void GraphicWidget::paintEvent(QPaintEvent* event)
{
	QRectF bbRect = m_scene.itemsBoundingRect();
	LOG_DEBUG("bounding rect is at {0},{1}, w {2}, h{3}", bbRect.left(), bbRect.top(), bbRect.width(), bbRect.height());
	std::for_each(m_bgGrid.begin(), m_bgGrid.end(), [this](QGraphicsLineItem* line)
    {
		m_scene.removeItem(line);
	});
	m_bgGrid.clear();

	QWidget* vp = viewport();

	int w = vp->width();
	int h = vp->height();

	QPointF tl = mapToScene(0, 0);
	QPointF br = mapToScene(w, h);

	QColor red(0xa44453);
	QColor green(0x638532);
	QColor gray(0x4F4F4F);

	int leftIndex = int(tl.x() / 50);
	int rightIndex = int(br.x() / 50);
    for (int i = leftIndex; i <= rightIndex; ++i)
    {
		QColor             c    = i == 0 ? green : gray;
        QGraphicsLineItem* line = m_scene.addLine(i * GRID_SIZE, tl.y(), i * GRID_SIZE, br.y(), c);
		line->setZValue(-1);
		m_bgGrid.push_back(line);
    }

	int topIndex = int(tl.y() / 50);
	int bottomIndex = int(br.y() / 50);
	for (int j = topIndex; j <= bottomIndex; ++j)
	{
		QColor             c    = j == 0 ? red : gray;
        QGraphicsLineItem* line = m_scene.addLine(tl.x(), j * GRID_SIZE, br.x(), j * GRID_SIZE, c);
		line->setZValue(-1);
		m_bgGrid.push_back(line);
	}

    QGraphicsView::paintEvent(event);
}
