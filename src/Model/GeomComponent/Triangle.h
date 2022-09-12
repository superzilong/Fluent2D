#pragma once
#include <array>
#include <QPoint>

#include "Shape.h"

class Triangle : public Shape
{
public:

	Triangle() : Shape(Type::triangle) {}
	Triangle(const std::array<QPointF, 3>& points) : Shape(Type::triangle), m_p1(points.at(0)), m_p2(points.at(1)), m_p3(points.at(2)) {}

	virtual ~Triangle() {}

    Triangle(const Triangle& other)                = default;
    Triangle(Triangle&& other) noexcept            = default;
    Triangle& operator=(const Triangle& other)     = default;
    Triangle& operator=(Triangle&& other) noexcept = default;

    QPointF getCenter() { return QPointF((m_p1.x() + m_p2.x() + m_p3.x()) / 3., (m_p1.y() + m_p2.y() + m_p3.y()) / 3.); }

	void setEndPoint1(const QPointF& p1) { this->m_p1 = p1; }
	void setEndPoint2(const QPointF& p2) { this->m_p2 = p2; }
	void setEndPoint3(const QPointF& p3) { this->m_p3 = p3; }
	void setPoints(double x1, double y1, double x2, double y2, double x3, double y3)
	{
		m_p1.setX(x1);
		m_p1.setY(y1);
		m_p2.setX(x2);
		m_p2.setY(y2);
		m_p3.setX(x3);
		m_p3.setY(y3);
	}
	
	QPointF getEndPoint1() { return m_p1; }
	QPointF getEndPoint2() { return m_p2; }
	QPointF getEndPoint3() { return m_p3; }

private:
	QPointF m_p1;
	QPointF m_p2;
	QPointF m_p3;
};
