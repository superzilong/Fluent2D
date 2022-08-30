#include "TriangleOperator.h"
#include <QMouseEvent>
#include "CoordConverter.h"

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
			//if (m_previewTri)
			//{
				//if (!m_previewLine)
				//{
				//	m_previewLine = new GraphicLine();
				//	m_previewLine->setPoints(m_point1.x(), m_point1.y(), m_previewTri->getEndPoint3().x(), m_previewTri->getEndPoint3().y());
				//	GraphicItemManager::instance()->addItem(m_previewLine);
				//}
				//
				//GraphicItemManager::instance()->deleteItem(m_previewTri);
				//delete m_previewTri;
				//m_previewTri = nullptr;
			//}

			m_point2 = QPointF();
			m_point2Created = false;
		}
		else if (m_point1Created)
		{
			//if (m_previewLine)
			//{
				//GraphicItemManager::instance()->deleteItem(m_previewLine);
				//delete m_previewLine;
				//m_previewLine = nullptr;
			//}
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
	QPoint mousePoint = event->pos();
	//auto[x, y] = m_converter->viewportToWorld(mousePoint.x(), mousePoint.y());

	if (m_point2Created)
	{
		//auto tri = new GraphicTriangle();
		//tri->setColor(0xFF, 0xB3, 0x44);
		//tri->setPoints(m_point1.x(), m_point1.y(), m_point2.x(), m_point2.y(), x, y);
		//GraphicItemManager::instance()->addItem(tri);
		//reset();

		//PhysicalEngine::instance()->createDynamicTriangle(tri);
	}
	else if (m_point1Created)
	{
		//m_point2 = { x, y };
		m_point2Created = true;

	}
	else if (!m_point1Created)
	{
		//m_point1 = { x, y };
		m_point1Created = true;
	}
}

void TriangleOperator::mouseMoveEvent(QMouseEvent* event)
{
	QPoint mousePoint = event->pos();
	//auto[x, y] = m_converter->viewportToWorld(mousePoint.x(), mousePoint.y());

	//if (m_point2Created)
	//{
	//	if (!m_previewTri)
	//	{		
	//		m_previewTri = new GraphicTriangle();
	//		m_previewTri->setColor(0xFF, 0xB3, 0x44);
	//		m_previewTri->setPoints(m_point1.x(), m_point1.y(), m_point2.x(), m_point2.y(), x, y);
	//		GraphicItemManager::instance()->addItem(m_previewTri);

	//		if (m_previewLine)
	//		{
	//			GraphicItemManager::instance()->deleteItem(m_previewLine);
	//			delete m_previewLine;
	//			m_previewLine = nullptr;
	//		}
	//	}
	//	else
	//	{
	//		m_previewTri->setEndPoint3({ x, y });
	//	}
	//}
	//else if (m_point1Created)
	//{
	//	if (!m_previewLine)
	//	{
	//		m_previewLine = new GraphicLine();
	//		m_previewLine->setPoints(m_point1.x(), m_point1.y(), x, y);
	//		GraphicItemManager::instance()->addItem(m_previewLine);
	//	}
	//	else
	//	{
	//		m_previewLine->setEndPoint2({ x, y });
	//	}
	//}

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
	//if (m_previewLine)
	//{
	//	GraphicItemManager::instance()->deleteItem(m_previewLine);
	//	delete m_previewLine;
	//	m_previewLine = nullptr;
	//}
	//if (m_previewTri)
	//{
	//	GraphicItemManager::instance()->deleteItem(m_previewTri);
	//	delete m_previewTri;
	//	m_previewTri = nullptr;
	//}
}
