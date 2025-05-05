#pragma once

#include "raylib.h"

#include "object.h"

struct LightRayPart {
    Vector2 from;
    Vector2 to;
    float angle_rad;
};

class LightRay {
public:
    LightRay(Vector2 pos, float angle_rad);
    void update(const std::vector<Object> &objs);
    void draw() const;
private:
    std::vector<LightRayPart> _parts;
};
