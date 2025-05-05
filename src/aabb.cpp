#include "aabb.h"
#include "raylib.h"

AABB::AABB(float min_x, float min_y, float max_x, float max_y):
_x1(min_x), _y1(min_y), _x2(max_x), _y2(max_y) {
}

bool AABB::contain_point(Vector2 point) const {
    return _x1 <= point.x && point.x <= _x2 &&
           _y1 <= point.y && point.y <= _y2;
}

Vector2 AABB::min_point() const {
    return { _x1, _y1 };
}

Vector2 AABB::max_point() const {
    return { _x2, _y2 };
}

void AABB::draw() const {
    Vector2 points[] = {
        {_x1,_y1},
        {_x2,_y1},
        {_x2,_y2},
        {_x1,_y2},
        {_x1,_y1}
    };
    DrawLineStrip(points, sizeof(points)/sizeof(*points), RED);
}
