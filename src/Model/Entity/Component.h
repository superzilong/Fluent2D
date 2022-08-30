#pragma once
#include <atomic>

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

typedef std::size_t TypeId;

class TypeIdGenerator
{
public:

    template <typename T>
    static TypeId GetTypeId()
    {
        static const TypeId id = m_nextTypeId++;
        return id;
    }

private:

    static std::atomic<TypeId> m_nextTypeId;
};

std::atomic<TypeId> TypeIdGenerator::m_nextTypeId{ 0 };

template <class T>
TypeId GetTypeId()
{
    return TypeIdGenerator::GetTypeId<T>();
}