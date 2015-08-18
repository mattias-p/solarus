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
#ifndef SOLARUS_CAMERA_H
#define SOLARUS_CAMERA_H

#include "solarus/Common.h"
#include "solarus/entities/MapEntity.h"
#include "solarus/entities/MapEntityPtr.h"
#include "solarus/lowlevel/Rectangle.h"
#include <memory>

namespace Solarus {

class Map;
class Separator;
class TargetMovement;

/**
 * \brief Manages the visible area of the map.
 *
 * The camera determines the visible area of the map.
 * Most of the time, the camera is centered on the hero movements,
 * blocking on the map borders and on separators.
 *
 * Occasionally, it can also be moved towards a point and then restored
 * towards the hero.
 */
class Camera : public MapEntity {

  public:

    Camera(Map& map);

    virtual EntityType get_type() const override;

    virtual void update() override;

    bool is_moving() const;
    void set_speed(int speed);
    void move(int target_x, int target_y);
    void move(const Point& target);
    void move(MapEntity& entity);
    void restore();
    void traverse_separator(Separator* separator);

    Rectangle apply_map_bounds(const Rectangle& area);
    Rectangle apply_separators(const Rectangle& area);
    Rectangle apply_separators_and_map_bounds(const Rectangle& area);

  private:

    void update_fixed_on();
    void update_moving();

    // Camera centered on the hero.
    MapEntityPtr fixed_on;                  /**< \c true if the camera is fixed on the hero. */
    Rectangle separator_scrolling_position; /**< Current camera position while crossing a separator. */
    Rectangle separator_target_position;    /**< Target camera position when crossing a separator. */
    int separator_scrolling_dx;             /**< X increment to the camera position when crossing a separator. */
    int separator_scrolling_dy;             /**< Y increment to the camera position when crossing a separator. */
    uint32_t separator_next_scrolling_date; /**< Next camera position change when crossing a separator. */
    int separator_scrolling_direction4;     /**< Direction when scrolling. */
    std::shared_ptr<Separator>
        separator_traversed;                /**< Separator currently being traversed or nullptr. */

    // Camera being moved toward a point or back to the hero.
    bool restoring;                         /**< \c true if the camera is moving back to the hero. */
    int speed;                              /**< Speed of the next movement. */
};

}

#endif

