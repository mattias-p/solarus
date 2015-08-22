/*
 * Copyright (C) 2006-2015 Christopho, Solarus - http://www.solarus-games.org
 *
 * Solarus is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Solarus is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef SOLARUS_ENTITY_STATE_H
#define SOLARUS_ENTITY_STATE_H

#include <string>

namespace Solarus {

class Entity;

/**
 * \brief Abstract base class for a state of the entity.
 *
 * This class contains all entity-related functions that depend on his state
 * and provide a default implementation for them.
 * Most of them are almost empty here because they depend on the state.
 * Redefine for each state the functions that you need to implement or change.
 */
class MapEntityState {

  public:

    // creation and destruction
    virtual ~MapEntityState();

    virtual Entity& get_entity();
    virtual const Entity& get_entity() const;
    const std::string& get_name() const;

  protected:
    MapEntityState(Entity& entity, const std::string& state_name);

  private:
    Entity& entity;           /**< The entity controlled by this state. */
    const std::string name;   /**< Name describing this state. */
};

}

#endif

