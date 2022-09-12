#pragma once
#include <atomic>
#include <cstdint>
#include <unordered_map>

using TypeId = std::uint32_t;

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

class Component;

using EntityId = std::uint32_t;

class Entity
{
public:
    Entity(EntityId id) : m_id(id) {}

    template<typename C, typename... Args>
    C& assign(Args&&... args)
    {
        static_assert(std::is_base_of<Component, C>(), "C is not a component, cannot add C to entity");
        auto component = new C{ std::forward<Args>(args)... };
        m_comps.insert(GetTypeId<C>(), component);
        return *component;
    }

    template<typename C>
    bool has()
    {
        static_assert(std::is_base_of<Component, C>(), "C is not a component, cannot add C to entity");
        return m_comps.count(GetTypeId<C>()) != 0;
    }

    template<typename C>
    C& get()
    {
        static_assert(std::is_base_of<Component, C>(), "C is not a component, cannot add C to entity");
        return static_cast<C&>(*m_comps.at(GetTypeId<C>()));
    }

    template<typename C>
    void remove()
    {
        static_assert(std::is_base_of<Component, C>(), "C is not a component, cannot add C to entity");
        if (has<C>())
        {
            delete m_comps.at(GetTypeId<C>());
            m_comps.erase(GetTypeId<C>());
        }
    }

private:
    EntityId m_id;
    std::unordered_map<TypeId, Component*> m_comps;
};
