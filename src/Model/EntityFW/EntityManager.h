#pragma once


#include <vector>
#include <type_traits>
#include <utility>
#include "EntityIdPool.h"
#include "Entity.h"

namespace anax
{
    class EntityManager
    {

    public:

        /// Describes an array of Entities
        using EntityArray = std::vector<Entity>;

        /// Default Constructor
        EntityManager();

        /// Constructs the world with a custom entity pool size
        /// \param entityPoolSize The amount of entities you wish to have pooled ready to use by default
        explicit EntityManager(std::size_t entityPoolSize);

        EntityManager(const EntityManager& world) = delete;
        EntityManager(EntityManager&& world) = delete;
        EntityManager& operator=(const EntityManager&) = delete;
        EntityManager& operator=(EntityManager&&) = delete;

        Entity createEntity();

        /// Creates an entity and applies an entity template to the entity
        /// \tparam EntityTemplateFn The type of template function you wish to apply
        ///
        /// \param fn The function you wish to apply to this entity
        /// \param args The corresponding arguments to the entity template function
        template <typename EntityTemplateFn, typename... Args>
        Entity createEntity(EntityTemplateFn fn, Args&&... args)
        {
            Entity e = createEntity();
            fn(e, std::forward<Args>(args)...);
            return e;
        }

        EntityArray createEntities(std::size_t amount);

        void removeEntity(Entity& entity);

        void removeEntities(std::vector<Entity>& entities);

        void clear();

        std::size_t getEntityCount() const;

        const EntityArray& getEntities() const;

        Entity getEntity(std::size_t index);

    private:


        /// A pool storage of the IDs for the entities within the world
        EntityIdPool m_entityIdPool;


        void checkForResize(std::size_t amountOfEntitiesToBeAllocated);
        void resize(std::size_t amount);

    };
}
