#include "DisplayManager.h"

#include <qgraphicsitem.h>
#include "GraphicWidget.h"

#include "Core/Log/Log.h"

static int s_viewport_index = 0;

std::pair<int, QWidget*> DisplayManager::createGraphicsWidget(QWidget* parent)
{
    auto gw = new GraphicWidget(parent);
    auto p = gw->sizeAdjustPolicy();
    ++s_viewport_index;
    m_vp2GraphicsWidget[s_viewport_index] = gw;
    return std::make_pair(s_viewport_index, gw);
}

QWidget* DisplayManager::getGraphicsWidgetByViewportID(const int vp) const
{
    return m_vp2GraphicsWidget.value(vp, nullptr);
}

int DisplayManager::getViewportIDByGraphicsWidget(QWidget* w) const
{
    return m_vp2GraphicsWidget.key(w, -1);
}

void DisplayManager::setCurrentOperator(const int vp, const std::shared_ptr<BaseOperator>& op)
{
    if (m_vp2GraphicsWidget.contains(vp))
    {
        dynamic_cast<GraphicWidget*>(m_vp2GraphicsWidget.value(vp))->setCurrentOperator(op);
    }
}

std::uintptr_t DisplayManager::addLine(const int vp, const QPointF& p1, const QPointF& p2)
{
    if (m_vp2GraphicsWidget.contains(vp))
    {
        auto                  graphicsWidget = dynamic_cast<GraphicWidget*>(m_vp2GraphicsWidget.value(vp));
        QGraphicsScene* scene = graphicsWidget->scene();
        QGraphicsLineItem* item = scene->addLine(QLineF(p1, p2), QColor(0xA2A3A4));
        uintptr_t key = reinterpret_cast<std::uintptr_t>(item);
        m_vp2items[vp].push_back(key);
        return key;
    }
    return 0;
}

void DisplayManager::modifyLine(const int vp, const std::uintptr_t key, const QPointF& p1, const QPointF& p2)
{
    if (m_vp2GraphicsWidget.contains(vp) && m_vp2items.contains(vp))
    {
        if (m_vp2items[vp].contains(key))
        {
            auto item = reinterpret_cast<QGraphicsLineItem*>(key);
            item->setLine(QLineF(p1, p2));
        }
    }
}

std::uintptr_t DisplayManager::addCircle(const int vp, const QPointF& p, const double r)
{
    if (m_vp2GraphicsWidget.contains(vp))
    {
        auto                  graphicsWidget = dynamic_cast<GraphicWidget*>(m_vp2GraphicsWidget.value(vp));
        QGraphicsScene*       scene             = graphicsWidget->scene();
        QGraphicsEllipseItem* item              = scene->addEllipse(p.x() - r, p.y() - r, 2*r, 2*r, Qt::NoPen, QColor(0xA2A3A4));
        uintptr_t key = reinterpret_cast<std::uintptr_t>(item);
        m_vp2items[vp].push_back(key);
        return key;
    }
    return 0;
}

void DisplayManager::modifyCircle(const int vp, const std::uintptr_t key, const QPointF& p, const double r)
{
    if (m_vp2GraphicsWidget.contains(vp) && m_vp2items.contains(vp))
    {
        if (m_vp2items[vp].contains(key))
        {
            auto item = reinterpret_cast<QGraphicsEllipseItem*>(key);
            item->setRect(p.x() - r, p.y() - r, 2 * r, 2 * r);
        }
    }
}

std::uintptr_t DisplayManager::addRect(const int vp, const QPointF& topLeft, const double w, const double h)
{
    if (m_vp2GraphicsWidget.contains(vp))
    {
        auto               graphicsWidget = dynamic_cast<GraphicWidget*>(m_vp2GraphicsWidget.value(vp));
        QGraphicsScene*    scene          = graphicsWidget->scene();
        QGraphicsRectItem* item           = scene->addRect(QRectF(topLeft, QSizeF(w, h)), Qt::NoPen, QColor(0xA2A3A4));
        uintptr_t          key            = reinterpret_cast<std::uintptr_t>(item);
        m_vp2items[vp].push_back(key);
        return key;
    }
    return 0;
}

void DisplayManager::modifyRect(const int vp, const std::uintptr_t key, const QPointF& topLeft, const double w, const double h)
{
    if (m_vp2GraphicsWidget.contains(vp) && m_vp2items.contains(vp))
    {
        if (m_vp2items[vp].contains(key))
        {
            auto item = reinterpret_cast<QGraphicsRectItem*>(key);
            item->setRect(QRectF(topLeft, QSizeF(w, h)));
        }
    }
}

std::uintptr_t DisplayManager::addPolygon(const int vp, const QVector<QPointF>& pts)
{
    if (m_vp2GraphicsWidget.contains(vp))
    {
        auto                  graphicsWidget = dynamic_cast<GraphicWidget*>(m_vp2GraphicsWidget.value(vp));
        QGraphicsScene*       scene          = graphicsWidget->scene();
        QGraphicsPolygonItem* item           = scene->addPolygon(QPolygonF(pts), Qt::NoPen, QColor(0xA2A3A4));
        uintptr_t             key            = reinterpret_cast<std::uintptr_t>(item);
        m_vp2items[vp].push_back(key);
        return key;
    }
    return 0;
}

void DisplayManager::modifyPolygon(const int vp, const std::uintptr_t key, const QVector<QPointF>& pts)
{
    if (m_vp2GraphicsWidget.contains(vp) && m_vp2items.contains(vp))
    {
        if (m_vp2items[vp].contains(key))
        {
            auto item = reinterpret_cast<QGraphicsPolygonItem*>(key);
            item->setPolygon(QPolygonF(pts));
        }
    }
}

void DisplayManager::deleteItem(const int vp, const std::uintptr_t key)
{
    if (m_vp2GraphicsWidget.contains(vp) && m_vp2items.contains(vp))
    {
        if (m_vp2items[vp].contains(key))
        {
            auto item = reinterpret_cast<QGraphicsItem*>(key);
            auto graphicsScene = dynamic_cast<GraphicWidget*>(m_vp2GraphicsWidget.value(vp))->scene();
            graphicsScene->removeItem(item);
            m_vp2items[vp].removeAll(key);
        }
    }
}

QPointF DisplayManager::worldToViewport(const int vp, const QPointF& p) const
{
    if (m_vp2GraphicsWidget.contains(vp))
    {
        auto w = dynamic_cast<GraphicWidget*>(m_vp2GraphicsWidget.value(vp));
        return w->worldToViewport(p);
    }
    return QPointF();
}

QPointF DisplayManager::viewportToWorld(const int vp, const QPointF& p) const
{
    if (m_vp2GraphicsWidget.contains(vp))
    {
        auto w = dynamic_cast<GraphicWidget*>(m_vp2GraphicsWidget.value(vp));
        return w->viewportToWorld(p);
    }
    return QPointF();
}

QPointF DisplayManager::getMousePointInWorld(const int vp) const
{
    if (m_vp2GraphicsWidget.contains(vp))
    {
        auto w = dynamic_cast<GraphicWidget*>(m_vp2GraphicsWidget.value(vp));
        return w->viewportToWorld(w->viewport()->mapFromGlobal(QCursor::pos()));
    }
    return QPointF();
}
