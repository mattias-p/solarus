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
#include "solarus/entities/MapEntityState.h"

namespace Solarus {

/**
 * \brief Creates a state.
 *
 * This constructor can be called only from the subclasses.
 *
 * \param hero The hero to control with this state.
 * \param state_name A name describing this state.
 */
MapEntityState::MapEntityState(MapEntity& entity, const std::string& state_name):
  entity(entity),
  name(state_name) {
}

/**
 * \brief Destructor.
 *
 * The state is destroyed once it is not the current state of the entity anymore.
 */
MapEntityState::~MapEntityState() {
}

/**
 * \brief Returns the entity linked to this state.
 * \return The entity linked to this state.
 */
MapEntity& MapEntityState::get_entity() {
  return entity;
}

/**
 * \brief Returns the entity linked to this state.
 * \return The entity linked to this state.
 */
const MapEntity& MapEntityState::get_entity() const {
  return entity;
}

/**
 * \brief Returns a name describing this state.
 * \return A name describing this state.
 */
const std::string& MapEntityState::get_name() const {
  return name;
}

}
