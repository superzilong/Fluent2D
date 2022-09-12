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
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
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
    QGraphicsView::keyPressEvent(event);
}

void GraphicWidget::mousePressEvent(QMouseEvent* event)
{
    if (m_operator)
    {
        m_operator->mousePressEvent(event);
    }
    QGraphicsView::mousePressEvent(event);
}

void GraphicWidget::mouseMoveEvent(QMouseEvent* event)
{
    if (m_operator)
    {
        m_operator->mouseMoveEvent(event);
    }
    QGraphicsView::mouseMoveEvent(event);

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
    QGraphicsView::mouseReleaseEvent(event);
}

void GraphicWidget::init()
{
	setBackgroundBrush(QBrush(QColor(0x3C3C3C)));
    updateSceneRect();
}

void GraphicWidget::tick()
{
}

void GraphicWidget::logViewportSize(const char* funcName)
{
    QWidget* vp = viewport();
    int      w = vp->width();
    int      h = vp->height();
    LOG_TRACE("{0} Viewport size is {1} * {2}", funcName, w, h);
}

void GraphicWidget::drawBackground(QPainter* painter, const QRectF& rect)
{
    QGraphicsView::drawBackground(painter, rect);

    painter->save();

    painter->drawRect(0, 0, 200, 100);
    QWidget* vp = viewport();

    int w = vp->width();
    int h = vp->height();

    QPointF tl = mapToScene(0, 0);
    QPointF br = mapToScene(w, h);

    QColor red(0xa44453);
    QColor green(0x638532);
    QColor gray(0x4F4F4F);

    int leftIndex = static_cast<int>(std::ceil(tl.x() / 50));
    int rightIndex = static_cast<int>(std::floor(br.x() / 50));
    for (int i = leftIndex; i <= rightIndex; ++i)
    {
        QColor             c = i == 0 ? green : gray;
        painter->setPen(QPen(c));
        painter->drawLine(i * GRID_SIZE, tl.y(), i * GRID_SIZE, br.y());
    }

    int topIndex = static_cast<int>(std::ceil(tl.y() / 50));
    int bottomIndex = static_cast<int>(std::floor(br.y() / 50));
    for (int j = topIndex; j <= bottomIndex; ++j)
    {
        QColor             c = j == 0 ? red : gray;
        painter->setPen(QPen(c));
        painter->drawLine(tl.x(), j * GRID_SIZE, br.x(), j * GRID_SIZE);
    }
    painter->restore();
}

void GraphicWidget::resizeEvent(QResizeEvent* event)
{
    logViewportSize(__FUNCTION__);
	QGraphicsView::resizeEvent(event);
}

void GraphicWidget::showEvent(QShowEvent* event)
{
    logViewportSize(__FUNCTION__);
	init();
	QGraphicsView::showEvent(event);
}

void GraphicWidget::wheelEvent(QWheelEvent* event)
{
	auto delta = event->angleDelta();
	LOG_DEBUG("{0} wheel angle y delta: {1}", __FUNCTION__, delta.y());
	if (delta.y() > 0)
	{
		scale(1.1, 1.1);
	}
	else if (delta.y() < 0)
	{
		scale(10. / 11., 10. / 11.);
	}
    updateSceneRect();
    QGraphicsView::wheelEvent(event);
}

void GraphicWidget::updateSceneRect()
{
    QWidget* vp = viewport();
    int      w  = vp->width();
    int      h  = vp->height();
    QPointF  tl = mapToScene(0, 0);
    QPointF  br = mapToScene(w, h);
    QRectF   vpRect(tl, br);
    QRectF   bbRect    = m_scene.itemsBoundingRect();
    QRectF   finalRect = vpRect.united(bbRect);
    QRectF   rect      = m_scene.sceneRect();
    if (rect != finalRect)
    {
        m_scene.setSceneRect(finalRect);
        LOG_DEBUG("Scene rect is at {0},{1}, w {2}, h{3}", finalRect.left(), finalRect.top(), finalRect.width(), finalRect.height());
    }
}

void GraphicWidget::paintEvent(QPaintEvent* event)
{
    logViewportSize(__FUNCTION__);
    QGraphicsView::paintEvent(event);

}
