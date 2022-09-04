#include "TriangleOperator.h"
#include <QMouseEvent>
#include "CoordConverter.h"

#include "Core/Log/Log.h"

#include "DisplayManager/DisplayManager.h"

TriangleOperator::TriangleOperator()
{

	m_action.setText("create triangle");
}

void TriangleOperator::keyPressEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_Escape)
	{
		if (m_point2Created)
		{
			if (m_previewTri)
			{
				DisplayManager::instance().deleteItem(m_vp, m_previewTri);
				m_previewTri = 0;

				if (!m_previewLine)
				{
					QPointF mousePoint = DisplayManager::instance().getMousePointInWorld(m_vp);
					m_previewLine = DisplayManager::instance().addLine(m_vp, m_point1, mousePoint);
				}
				
				m_point2 = QPointF();
				m_point2Created = false;
			}
		}
		else if (m_point1Created)
		{
			if (m_previewLine)
			{
				DisplayManager::instance().deleteItem(m_vp, m_previewLine);
				m_previewLine = 0;
			}
			m_point1 = QPointF();
			m_point1Created = false;
		}
		else
		{
			emit signal_exit(this);
	 	}
	}
}

void TriangleOperator::mousePressEvent(QMouseEvent* event)
{
	QPointF mousePoint = DisplayManager::instance().viewportToWorld(m_vp, event->pos());

	if (m_point2Created)
	{
		DisplayManager::instance().addPolygon(m_vp, { m_point1, m_point2, mousePoint });
		LOG_INFO("Create triangle with ({0}, {1}), ({2}, {3}), ({4}, {5})", m_point1.x(), m_point1.y(), m_point2.x(), m_point2.y(), mousePoint.x(), mousePoint.y());
		reset();
	}
	else if (m_point1Created)
	{
		m_point2 = mousePoint;
		m_point2Created = true;

	}
	else if (!m_point1Created)
	{
		m_point1 = mousePoint;
		m_point1Created = true;
	}
}

void TriangleOperator::mouseMoveEvent(QMouseEvent* event)
{
	QPointF mousePoint = DisplayManager::instance().viewportToWorld(m_vp, event->pos());

	if (m_point2Created)
	{
		if (!m_previewTri)
		{		
			m_previewTri = DisplayManager::instance().addPolygon(m_vp, { m_point1, m_point2, mousePoint });

			if (m_previewLine)
			{
				DisplayManager::instance().deleteItem(m_vp, m_previewLine);
				m_previewLine = 0;
			}
		}
		else
		{
			DisplayManager::instance().modifyPolygon(m_vp, m_previewTri, { m_point1, m_point2, mousePoint });
		}
	}
	else if (m_point1Created)
	{
		if (!m_previewLine)
		{
			m_previewLine = DisplayManager::instance().addLine(m_vp, m_point1, mousePoint);
		}
		else
		{
			DisplayManager::instance().modifyLine(m_vp, m_previewLine, m_point1, mousePoint);
		}
	}
}

void TriangleOperator::mouseReleaseEvent(QMouseEvent* event)
{
}

void TriangleOperator::reset()
{
	m_point1 = QPointF();
	m_point2 = QPointF();
	m_point1Created = false;
	m_point2Created = false;
	if (m_previewLine)
	{
		DisplayManager::instance().deleteItem(m_vp, m_previewLine);
		m_previewLine = 0;
	}
	if (m_previewTri)
	{
		DisplayManager::instance().deleteItem(m_vp, m_previewTri);
		m_previewTri = 0;
	}
}
