#pragma once
#include <cstdint>
#include <unordered_map>

class Component;

class Entity
{
public:
    Entity(uint32_t id) : m_id(id) {}

    template<typename C, typename... Args>
    C& assign(Args&&... args)
    {
        
    }

    template<typename C>
    bool has()
    {
        
    }

    template<typename C>
    C& get()
    {

    }

    template<typename C>
    void remove()
    {

    }




private:
    uint32_t m_id;
    std::unordered_map<uint32_t, Component*> m_comps;
};
