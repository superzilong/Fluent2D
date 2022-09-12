#pragma once

#include <vector>
#include "Entity.h"

/// \brief A pool of entity IDs
///
/// Used to pool entity IDs, so they can be re-used.
///
/// \author Miguel Martin
///
class EntityIdPool
{
public:

    explicit EntityIdPool(std::size_t poolSize);

    EntityIdPool(const EntityIdPool&) = delete;
    EntityIdPool(EntityIdPool&&) = delete;
    EntityIdPool& operator=(const EntityIdPool&) = delete;
    EntityIdPool& operator=(EntityIdPool&&) = delete;


    /// Creates an Entity ID
    /// \return The newly created Entity ID
    EntityId create();

    /// Removes an ID from the pool
    /// \param id The ID you wish to remove
    /// \note
    /// The ID will be invalidated automatically
    /// once the entity ID is removed.
    void remove(EntityId id);

    /// \param The index you wish to access the Entity::Id at
    /// \return An Entity::Id at index
    EntityId get(std::size_t index) const;

    /// Determines if an Entity ID is valid
    /// \return true if the ID is valid
    bool isValid(EntityId id) const;

    /// \return The amount of entities that this pool can store
    std::size_t getSize() const;

    /// Resizes the pool
    /// \param amount The amount you wish to resize
    void resize(std::size_t amount);

    /// Clears the pool
    /// \note This will invalidate every entity ID given out
    void clear();

private:

    /// The default pool size
    std::size_t m_defaultPoolSize;

    /// The next ID to be used (if there is no IDs in the freelist)
    EntityId m_nextId;

    /// The entities ids that are available to be used
    std::vector<EntityId> m_freeList;
};

