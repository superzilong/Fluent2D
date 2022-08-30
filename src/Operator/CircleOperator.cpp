#include "CircleOperator.h"
#include <QMouseEvent>

#include "CoordConverter.h"

#include "DisplayManager/DisplayManager.h"

CircleOperator::CircleOperator()
{
	m_action.setText("create circle");
}

void CircleOperator::keyPressEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_Escape)
	{
		if (m_centerPoint1Created)
		{
			if (m_previewCircle)
			{
				DisplayManager::instance().deleteItem(m_vp, m_previewCircle);
				m_previewCircle = 0;
			}
			m_centerPoint1 = QPointF();
			m_centerPoint1Created = false;
		}
		else
		{
			emit signal_exit(this);
	 	}
	}
}

void CircleOperator::mousePressEvent(QMouseEvent* event)
{
	if (m_centerPoint1Created)
	{
		DisplayManager::instance().deleteItem(m_vp, m_previewCircle);
		m_previewCircle = 0;

		QPoint mousePoint = event->pos();
		QPointF p = DisplayManager::instance().viewportToWorld(m_vp, event->pos());
		QLineF line(m_centerPoint1, p);
		DisplayManager::instance().addCircle(m_vp, m_centerPoint1, line.length());
		m_centerPoint1Created = false;
	}
	else
	{
		m_centerPoint1 = DisplayManager::instance().viewportToWorld(m_vp, event->pos());
		m_centerPoint1Created = true;
	}
}

void CircleOperator::mouseMoveEvent(QMouseEvent* event)
{
	if (m_centerPoint1Created)
	{
		QPoint mousePoint = event->pos();
		QPointF p = DisplayManager::instance().viewportToWorld(m_vp, event->pos());


		if (!m_previewCircle)
		{
			m_previewCircle = DisplayManager::instance().addCircle(m_vp, m_centerPoint1, QLineF(p, m_centerPoint1).length());
		}
		else
		{
			DisplayManager::instance().modifyCircle(m_vp, m_previewCircle, m_centerPoint1, QLineF(p, m_centerPoint1).length());
		}
	}
}

void CircleOperator::mouseReleaseEvent(QMouseEvent* event)
{
}

void CircleOperator::reset()
{
	if (m_previewCircle)
	{
		DisplayManager::instance().deleteItem(m_vp, m_previewCircle);
		m_previewCircle = 0;
	}
	m_centerPoint1 = QPointF();
	m_centerPoint1Created = false;
	m_vp = -1;
}
