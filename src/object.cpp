#include "object.h"

#include <algorithm>
#include <cmath>

Object::Object(std::vector<Vector2> points):
_points(points), _aabb(AABB(0, 0, 0, 0)) {
    _points.push_back(_points.front());
    _origin = _points.front();
    update_aabb();
}

void Object::draw() const {
    DrawLineStrip((Vector2 *)_points.data(), _points.size(), BLACK);
    DrawCircle(_origin.x, _origin.y, 3, GREEN);
    // _aabb.draw();
}

const AABB& Object::aabb() const {
    return _aabb;
}

void Object::set_origin(Vector2 origin) {
    _origin = origin;
}

void Object::set_position(Vector2 pos) {
    Vector2 delta = { pos.x - _origin.x, pos.y - _origin.y };
    for (auto &p : _points) {
        p.x += delta.x;
        p.y += delta.y;
    }
    _origin.x += delta.x;
    _origin.y += delta.y;
    update_aabb();
}

bool Object::contain_point(Vector2 point) {
    if (!_aabb.contain_point(point)) {
        return false;
    }

    bool is_inside = true;
    for (int i = 0; i < _points.size() - 1; i++) {
        Vector2 a =_points[i];
        Vector2 b =_points[i + 1];
        is_inside = is_inside && (b.x - a.x)*(point.y - a.y) - (b.y - a.y)*(point.x - a.x) > 0;
    }
    return is_inside;
}

std::tuple<bool, Vector2, float, float> Object::ray_line_collision(
    Vector2 r, float angle_rad, Vector2 a, Vector2 b
) const {
    float sin_a = std::sin(angle_rad);
    float cos_a = std::cos(angle_rad);
    float delimiter = ((a.x - b.x) * sin_a + (b.y - a.y) * cos_a);
    float t1 = ((b.x - a.x) * (r.y - a.y) - (b.y - a.y) * (r.x - a.x)) / delimiter;
    float t2 = ((a.x - r.x) * sin_a + (r.y - a.y) * cos_a) / delimiter;
    if (!(t1 > 0 && t2 >= 0 && t2 <= 1)) {
        return std::make_tuple(false, Vector2 { 0, 0 }, 0, 0);
    }
    float ix = r.x + t1 * cos_a;
    float iy = r.y + t1 * sin_a;
    if (std::fabs(ix - r.x) < 0.001 && std::fabs(iy - r.y) < 0.001) {
        return std::make_tuple(false, Vector2 { 0, 0 }, 0, 0);
    }

    float n_len = std::sqrt((b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y));
    float nx = (a.y - b.y) / n_len;
    float ny = (b.x - a.x) / n_len;

    float angle = std::acos(cos_a * nx + sin_a * ny);
    if (((ix - r.x) * (a.x - b.x) + (iy - r.y) * (a.y - b.y)) < 0) {
        angle = -angle;
    }
    return std::make_tuple(true, Vector2 { ix, iy }, angle, t1);
}

std::tuple<bool, Vector2, float, float> Object::ray_lines_collision(
    Vector2 from, float angle_rad, std::vector<Vector2> points
) const {
    auto rrc = std::make_tuple<bool, Vector2>(false, {0, 0}, 0.0, 0.0);
    float min_t = std::numeric_limits<float>::max();
    for (int i = 0; i < points.size() - 1; i++) {
        Vector2 a = points[i];
        Vector2 b = points[i + 1];
        auto rc = ray_line_collision(from, angle_rad, a, b);
        if (std::get<0>(rc) && min_t >= std::get<3>(rc)) {
            min_t = std::get<3>(rc);
            rrc = rc;
        }
    }
    if (min_t > 0) {
        return rrc;
    }
    return std::make_tuple<bool, Vector2>(false, {0, 0}, 0.0, 0.0);
}

std::tuple<bool, Vector2, float, float> Object::collision_with_ray(Vector2 from, float angle_rad) const {
    Vector2 aabb_min = _aabb.min_point();
    Vector2 aabb_max = _aabb.max_point();
    std::vector<Vector2> aabb_points = {
        aabb_min,
        { aabb_max.x, aabb_min.y },
        aabb_max,
        { aabb_min.x, aabb_max.y },
        aabb_min
    };
    if (!std::get<0>(ray_lines_collision(from, angle_rad, aabb_points))) {
        return std::make_tuple<bool, Vector2>(false, {0, 0}, 0, 0);
    }
    return ray_lines_collision(from, angle_rad, _points);
}

void Object::rotate(float angle_rad) {
    float sin = std::sin(angle_rad);
    float cos = std::cos(angle_rad);
    for (auto &p : _points) {
        p.x -= _origin.x;
        p.y -= _origin.y;
        p.x = p.x * cos - p.y * sin;
        p.y = p.x * sin + p.y * cos;
        p.x += _origin.x;
        p.y += _origin.y;
    }
}

void Object::update_aabb() {
    float min_x = _points[0].x;
    float min_y = _points[0].y;
    float max_x = min_x;
    float max_y = min_y;
    for (const auto &p : _points) {
        min_x = std::min(min_x, p.x);
        min_y = std::min(min_y, p.y);
        max_x = std::max(max_x, p.x);
        max_y = std::max(max_y, p.y);
    }
    _aabb = AABB(min_x, min_y, max_x, max_y);
}
