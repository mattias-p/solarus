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
#ifndef SOLARUS_DYNAMIC_TILE_H
#define SOLARUS_DYNAMIC_TILE_H

#include "solarus/Common.h"
#include "solarus/entities/Entity.h"
#include <string>

namespace Solarus {

class TilePattern;
class Tileset;

/**
 * \brief A special tile that can be enabled or disabled.
 *
 * A dynamic tile is a tile placed on the map
 * that can be enabled or disabled by the script,
 * contrary to the Tile instances that are totally static for performance reasons.
 * An enabled dynamic tile behaves like a normal tile and may be an obstacle or any ground.
 * A disabled dynamic tile is invisible and can be traversed.
 */
class DynamicTile: public Entity {

  public:

    DynamicTile(
        const std::string& name,
        Layer layer,
        const Point& xy,
        const Size& size,
        Tileset& tileset,
        const std::string& tile_pattern_id,
        bool enabled
    );

    virtual EntityType get_type() const override;
    virtual bool is_ground_modifier() const override;
    virtual Ground get_modified_ground() const override;
    virtual void draw_on_map() override;

  private:

    const std::string tile_pattern_id; /**< Id of the tile pattern. */
    TilePattern& tile_pattern;         /**< Pattern of the tile. */

};

}

#endif

