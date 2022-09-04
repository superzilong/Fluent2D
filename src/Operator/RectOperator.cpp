#include "RectOperator.h"

#include <QMouseEvent>

#include "Core/Log/Log.h"

#include "DisplayManager/DisplayManager.h"

RectOperator::RectOperator()
{
	m_action.setText("create rectangle");
}

void RectOperator::keyPressEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_Escape)
	{
		if (m_rectPoint1Created)
		{
			m_rectPoint1Created = false;
			DisplayManager::instance().deleteItem(m_vp, m_previewRect);
			m_rectPoint1 = QPointF();
			m_previewRect = 0;
		}
		else
		{
			emit signal_exit(this);
	 	}
	}
}

void RectOperator::mousePressEvent(QMouseEvent* event)
{
	if (m_rectPoint1Created)
	{
		QPointF mousePoint = DisplayManager::instance().viewportToWorld(m_vp, event->pos());
		auto [startX, endX] = std::minmax(m_rectPoint1.x(), mousePoint.x());
		auto [startY, endY] = std::minmax(m_rectPoint1.y(), mousePoint.y());
		// Create rectangle graphic.
		DisplayManager::instance().addRect(m_vp, QPointF(startX, startY), endX - startX, endY - startY);
		LOG_INFO("Create rect with topleft: ({0}, {1}), width: {2}, height: {3}", startX, startY, endX - startX, endY - startY);

		reset();
	}
	else
	{
		m_rectPoint1 = DisplayManager::instance().viewportToWorld(m_vp, event->pos());
		m_rectPoint1Created = true;
	}
}

void RectOperator::mouseMoveEvent(QMouseEvent* event)
{
	if (m_rectPoint1Created)
	{
		QPointF mousePoint = DisplayManager::instance().viewportToWorld(m_vp, event->pos());
		auto [startX, endX] = std::minmax(m_rectPoint1.x(), mousePoint.x());
		auto [startY, endY] = std::minmax(m_rectPoint1.y(), mousePoint.y());

		if (!m_previewRect)
		{
			m_previewRect = DisplayManager::instance().addRect(m_vp, QPointF(startX, startY), endX - startX, endY - startY);
		}
		else
		{
			DisplayManager::instance().modifyRect(m_vp, m_previewRect, QPointF(startX, startY), endX - startX, endY - startY);
		}
	}
}

void RectOperator::mouseReleaseEvent(QMouseEvent* event)
{
}

void RectOperator::reset()
{
	if (m_previewRect)
	{
		DisplayManager::instance().deleteItem(m_vp, m_previewRect);
		m_previewRect = 0;
	}
	m_rectPoint1 = QPointF();
	m_rectPoint1Created = false;
}
