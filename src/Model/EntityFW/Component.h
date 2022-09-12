#pragma once

class Component
{
public:
    Component() = default;
    virtual ~Component() {}

    Component(const Component& other)                = default;
    Component(Component&& other) noexcept            = default;
    Component& operator=(const Component& other)     = default;
    Component& operator=(Component&& other) noexcept = default;
};

