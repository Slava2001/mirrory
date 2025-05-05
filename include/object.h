#pragma once
#include <vector>
#include <tuple>
#include "raylib.h"

#include "aabb.h"

class Object {
public:
    Object(std::vector<Vector2> points);
    void draw() const;
    const AABB& aabb() const;
    void set_origin(Vector2 origin);
    void set_position(Vector2 pos);
    void rotate(float angle_rad);
    bool contain_point(Vector2 point);
    std::tuple<bool, Vector2, float, float> collision_with_ray(Vector2 from, float angle_rad) const;
private:
    std::vector<Vector2> _points;
    Vector2 _origin;

    AABB _aabb;
    void update_aabb();
    std::tuple<bool, Vector2, float, float> ray_line_collision(
        Vector2 r, float angle_rad, Vector2 a, Vector2 b
    ) const;
    std::tuple<bool, Vector2, float, float> ray_lines_collision(
        Vector2 from, float angle_rad, std::vector<Vector2> points
    ) const;
};
