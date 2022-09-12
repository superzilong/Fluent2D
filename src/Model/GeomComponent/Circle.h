#pragma once
#include <QPointF>
#include <cmath>
#include "Shape.h"

class Circle : public Shape
{
public:

	Circle() : Shape(Type::circle) {}
	Circle(const QPointF& center, double r) : Shape(Type::circle), m_center(center), m_radius(r) {}

	virtual ~Circle() {}

    Circle(const Circle& other)                = default;
    Circle(Circle&& other) noexcept            = default;
    Circle& operator=(const Circle& other)     = default;
    Circle& operator=(Circle&& other) noexcept = default;

    QPointF getCenter() const
	{
		return m_center;
	}

	void setCenter(const QPointF& center)
	{
		this->m_center = center;
	}

	void setCenter(double x, double y)
	{
		this->m_center.setX(x);
		this->m_center.setY(y);
	}

	double getRadius() const
	{
		return m_radius;
	}

	void setRadius(double radius)
	{
		this->m_radius = radius;
	}

	void setPointInCircle(double x, double y)
	{
		this->m_radius = sqrt(std::pow(x - m_center.x(), 2) + std::pow(y - m_center.y(), 2));
	}

private:

	QPointF m_center;
	double m_radius;
};
