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
#ifndef SOLARUS_MAP_H
#define SOLARUS_MAP_H

#include "solarus/Common.h"
#include "solarus/entities/Ground.h"
#include "solarus/entities/Layer.h"
#include "solarus/lowlevel/Debug.h"
#include "solarus/lowlevel/Rectangle.h"
#include "solarus/lowlevel/SurfacePtr.h"
#include "solarus/lua/ExportableToLua.h"
#include "solarus/Camera.h"
#include "solarus/MapData.h"
#include "solarus/Transition.h"
#include <memory>
#include <string>

namespace Solarus {

class Destination;
class Detector;
class InputEvent;
class LuaContext;
class MapEntities;
class MapLoader;
class Tileset;
class Sprite;

/**
 * \brief Represents a map where the game can take place.
 *
 * A map is a game scene. It contains various information, including:
 * - its dimensions,
 * - the tileset,
 * - the tiles and the other entities placed on the map,
 * - the ground of each 8x8 square,
 * - the background music,
 * - the position of the camera.
 */
class SOLARUS_API Map: public ExportableToLua {

  public:

    // creation and destruction
    Map(const std::string& id);

    // map properties
    const std::string& get_id() const;
    Tileset& get_tileset();
    const std::string& get_tileset_id() const;
    void set_tileset(const std::string& tileset_id);
    const std::string& get_music_id() const;
    bool has_world() const;
    const std::string& get_world() const;
    void set_world(const std::string& world);
    bool has_floor() const;
    int get_floor() const;
    void set_floor(int floor);
    const Rectangle& get_location() const;

    Size get_size() const;
    int get_width() const;
    int get_height() const;
    int get_width8() const;
    int get_height8() const;

    // camera
    const SurfacePtr& get_visible_surface();
    const Rectangle& get_camera_position() const;
    void move_camera(int x, int y, int speed);
    void restore_camera();
    bool is_camera_moving() const;
    void traverse_separator(Separator* separator);

    // loading
    bool is_loaded() const;
    void load(Game& game);
    void unload();
    Game& get_game();
    LuaContext& get_lua_context();
    virtual const std::string& get_lua_type_name() const override;

    void notify_opening_transition_finished();

    // entities
    MapEntities& get_entities();
    const MapEntities& get_entities() const;

    // presence of the hero
    bool is_started() const;
    void start();
    void leave();

    // current destination point
    void set_destination(const std::string& destination_name);
    const std::string& get_destination_name() const;
    Destination* get_destination();
    int get_destination_side() const;

    // collisions with obstacles (checked before a move)
    bool test_collision_with_border(int x, int y) const;
    bool test_collision_with_border(const Point& point) const;
    bool test_collision_with_border(const Rectangle& collision_box) const;
    bool test_collision_with_ground(
        Layer layer,
        int x,
        int y,
        const Entity& entity_to_check,
        bool& found_diagonal_wall
    ) const;
    bool test_collision_with_entities(
        Layer layer,
        const Rectangle& collision_box,
        Entity& entity_to_check
    ) const;
    bool test_collision_with_obstacles(
        Layer layer,
        const Rectangle& collision_box,
        Entity& entity_to_check
    ) const;
    bool test_collision_with_obstacles(
        Layer layer,
        int x,
        int y,
        Entity& entity_to_check
    ) const;
    bool test_collision_with_obstacles(
        Layer layer,
        const Point& point,
        Entity& entity_to_check
    ) const;
    bool has_empty_ground(
        Layer layer,
        const Rectangle& collision_box
    ) const;

    Ground get_ground(Layer layer, int x, int y) const;
    Ground get_ground(Layer layer, const Point& xy) const;

    // collisions with detectors (checked after a move)
    void check_collision_with_detectors(Entity& entity);
    void check_collision_with_detectors(Entity& entity, Sprite& sprite);
    void check_collision_from_detector(Detector& detector);

    // main loop
    bool notify_input(const InputEvent& event);
    void update();
    bool is_suspended() const;
    void check_suspended();
    void draw();
    void draw_sprite(Sprite& sprite, const Point& xy);
    void draw_sprite(Sprite& sprite, int x, int y);
    void draw_sprite(Sprite& sprite, int x, int y,
        const Rectangle& clipping_area);

  private:

    friend class MapLoader; // the map loader modifies the private fields of Map

    void set_suspended(bool suspended);
    void build_background_surface();
    void build_foreground_surface();
    void draw_background();
    void draw_foreground();

    static MapLoader map_loader;  /**< The map file parser. */

    // map properties

    Game* game;                   /**< The game this map was started in. */
    std::string id;               /**< Id of this map. */

    int width8;                   /**< Map width in 8x8 squares (width8 = get_width() / 8). */
    int height8;                  /**< Map height in 8x8 squares (height8 = get_height() / 8). */

    std::string tileset_id;       /**< Id of the current tileset. */
    std::unique_ptr<Tileset>
        tileset;                  /**< Tileset of the map: every tile of this map
                                   * is extracted from this tileset. */

    std::string music_id;         /**< Id of the current music of the map:
                                   * can be a valid music, Music::none or Music::unchanged. */

    std::string world;            /**< Name of the context where this map is. When changing context,
                                   * the savegame starting position is set and crystal switches are reset. */

    int floor;                    /**< The floor where this map is (possibly MapData::NO_FLOOR). */

    Rectangle location;           /**< Location of the map in its context: the width and height fields
                                   * indicate the map size in pixel, and the x and y field indicate the position.
                                   * This is used to correctly scroll between adjacent maps. */

    // screen

    std::unique_ptr<Camera>
        camera;                   /**< The visible area of the map. */
    SurfacePtr visible_surface;   /**< Surface where the map is displayed. This is only the visible part
                                   * of the map, so the coordinates on this surface are relative to the screen,
                                   * not to the map. */
    SurfacePtr
        background_surface;       /**< A surface filled with the background color of the tileset. */
    SurfacePtr
        foreground_surface;       /**< A surface with black bars when the map is smaller than the screen. */

    // map state
    bool loaded;                  /**< Whether the loading phase is done. */
    bool started;                 /**< Whether this map is the current map. */
    std::string destination_name; /**< Current destination point on the map,
                                   * or "_same" to keep the hero's coordinates,
                                   * or "_side0", "_side1", "_side2" or "_side3"
                                   * to place the hero on a side of the map,
                                   * or an empty string to use the one saved. */

    std::unique_ptr<MapEntities>
        entities;                 /**< The entities on the map. */
    bool suspended;               /**< Whether the game is suspended. */
};

/**
 * \brief Tests whether a point is outside the map area.
 * \param x x of the point to check.
 * \param y y of the point to check.
 * \return true if this point is outside the map area.
 */
inline bool Map::test_collision_with_border(int x, int y) const {

  return (x < 0 || y < 0 || x >= location.get_width() || y >= location.get_height());
}

/**
 * \brief Tests whether a point is outside the map area.
 * \param point point to check.
 * \return true if this point is outside the map area.
 */
inline bool Map::test_collision_with_border(const Point& point) const {

  return test_collision_with_border(point.x, point.y);
}

/**
 * \brief Returns the position of the visible area, relative to the map
 * top-left corner.
 * \return The rectangle of the visible area.
 */
inline const Rectangle& Map::get_camera_position() const {
  SOLARUS_ASSERT(camera != nullptr, "Missing camera");
  return camera->get_bounding_box();
}

}

#endif

