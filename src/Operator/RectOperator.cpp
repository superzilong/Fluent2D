#include "RectOperator.h"

#include <QMouseEvent>

#include "CoordConverter.h"
#include "Core/Log/Log.h"

RectOperator::RectOperator()
{
	m_action.setText("create rectangle");
}

void RectOperator::keyPressEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_Escape)
	{
		//if (m_rectPoint1Created)
		//{
		//	m_rectPoint1Created = false;
		//	GraphicItemManager::instance()->deleteItem(m_previewRect);
		//	delete m_previewRect;
		//	m_rectPoint1 = QPointF();
		//	m_previewRect = nullptr;
		//}
		//else
		//{
		//	emit signal_exit(this);
	 //	}
	}
}

void RectOperator::mousePressEvent(QMouseEvent* event)
{
	if (m_rectPoint1Created)
	{
		//GraphicItemManager::instance()->deleteItem(m_previewRect);
		//delete m_previewRect;
		//m_previewRect = nullptr;

		//QPoint mousePoint = event->pos();
		//auto[x, y] = m_converter->viewportToWorld(mousePoint.x(), mousePoint.y());
		//auto [startX, endX] = std::minmax(m_rectPoint1.x(), x);
		//auto [startY, endY] = std::minmax(m_rectPoint1.y(), y);

		//// Create rectangle graphic.
		//auto rect = new GraphicRect();
		//rect->setColor(0xFF, 0xB3, 0x44);
		//rect->setLeft(startX);
		//rect->setBottom(startY);
		//rect->setWidth(endX - startX);
		//rect->setHeight(endY - startY);
		//GraphicItemManager::instance()->addItem(rect);
		//m_rectPoint1Created = false;
		//LOG_INFO(fmt::format("Create rect with center: ({0}, {1}), width: {2}, height: {3}",
		//	rect->getCenter().x(),
		//	rect->getCenter().y(),
		//	rect->getWidth(),
		//	rect->getHeight()
		//));

		//// Create rectangle physical model.
		//auto pe = PhysicalEngine::instance();
		//b2Body* body = pe->createDynamicBox(rect);

	}
	else
	{
		//auto[x, y] = m_converter->viewportToWorld(event->pos().x(), event->pos().y());
		//m_rectPoint1.setX(x);
		//m_rectPoint1.setY(y);
		//m_rectPoint1Created = true;
	}
}

void RectOperator::mouseMoveEvent(QMouseEvent* event)
{
	if (m_rectPoint1Created)
	{
		//QPoint mousePoint = event->pos();
		//auto[x, y] = m_converter->viewportToWorld(mousePoint.x(), mousePoint.y());
		//auto [startX, endX] = std::minmax(m_rectPoint1.x(), x);
		//auto [startY, endY] = std::minmax(m_rectPoint1.y(), y);

	/*	if (!m_previewRect)
		{
			m_previewRect = new GraphicRect();
			m_previewRect->setColor(0xFF, 0xB3, 0x44);
			m_previewRect->setLeft(startX);
			m_previewRect->setBottom(startY);
			m_previewRect->setWidth(endX - startX);
			m_previewRect->setHeight(endY - startY);
			GraphicItemManager::instance()->addItem(m_previewRect);
		}
		else
		{
			m_previewRect->setLeft(startX);
			m_previewRect->setBottom(startY);
			m_previewRect->setWidth(endX - startX);
			m_previewRect->setHeight(endY - startY);
		}*/
	}
}

void RectOperator::mouseReleaseEvent(QMouseEvent* event)
{
}

void RectOperator::reset()
{
	//if (m_previewRect)
	//{
	//	GraphicItemManager::instance()->deleteItem(m_previewRect);
	//	delete m_previewRect;
	//	m_previewRect = nullptr;
	//}
	m_rectPoint1 = QPointF();
	m_rectPoint1Created = false;
}
