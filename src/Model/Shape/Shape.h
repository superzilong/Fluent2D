#pragma once

class Shape
{
public:	
	enum class Type
	{
		unknown,
		rect,
		circle,
		triangle
	};

	Shape(Type t) : m_type(t) {}

	virtual ~Shape() {}

    Shape(const Shape& other)                = default;
    Shape(Shape&& other) noexcept            = default;
    Shape& operator=(const Shape& other)     = default;
    Shape& operator=(Shape&& other) noexcept = default;


    Type getType() const
	{
		return m_type;
	}

	void setType(Type type)
	{
		m_type = type;
	}

protected:
	Type m_type = Type::unknown;
};
