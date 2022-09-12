#pragma once
#include <QPointF>

#include "Shape.h"

class Rect : public Shape
{
public:

	Rect() : Shape(Type::rect) {}
	Rect(const QPointF& lefttop, double w, double h) : Shape(Type::rect), m_left(lefttop.x()), m_top(lefttop.y()), m_width(w), m_height(h) {}

	virtual ~Rect() {}

    Rect(const Rect& other)                = default;
    Rect(Rect&& other) noexcept            = default;
    Rect& operator=(const Rect& other)     = default;
    Rect& operator=(Rect&& other) noexcept = default;

    double getLeft() const
	{
		return m_left;
	}

	void setLeft(double left)
	{
		m_left = left;
	}

	double getTop() const
	{
		return m_top;
	}

	void setTop(double top)
	{
		this->m_top = top;
	}

	double getWidth() const
	{
		return m_width;
	}

	void setWidth(double width)
	{
		this->m_width = width;
	}

	double getHeight() const
	{
		return m_height;
	}

	void setHeight(double height)
	{
		this->m_height = height;
	}

	QPointF getCenter() const
	{
		return { m_left + m_width / 2, m_top - m_height / 2 };
	}

private:
	double m_left = 0.;
	double m_top = 0.;
	double m_width = 0.;
	double m_height = 0.;

};
