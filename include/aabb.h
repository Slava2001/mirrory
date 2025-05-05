#pragma once

#include "raylib.h"

class AABB {
public:
    AABB(float min_x, float min_y, float max_x, float max_y);
    bool contain_point(Vector2 point) const;
    void draw() const;
    Vector2 min_point() const;
    Vector2 max_point() const;
private:
    float _x1;
    float _y1;
    float _x2;
    float _y2;
};
