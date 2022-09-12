#pragma once

#include "Shape.h"
#include "Model/Entity/Component.h"

class GeomComponent : public Component
{
public:
    GeomComponent(Shape* shape = nullptr) : m_shape(shape) {}
    ~GeomComponent() override { delete m_shape; }

    GeomComponent(const GeomComponent& other)                = default;
    GeomComponent(GeomComponent&& other) noexcept            = default;
    GeomComponent& operator=(const GeomComponent& other)     = default;
    GeomComponent& operator=(GeomComponent&& other) noexcept = default;

    [[nodiscard]] Shape* getShape() const
    {
        return m_shape;
    }

    void setShape(Shape* shape)
    {
        m_shape = shape;
    }

private:
    Shape* m_shape;
};