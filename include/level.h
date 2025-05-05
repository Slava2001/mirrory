#pragma once

#include <vector>
#include "object.h"
#include "light_ray.h"

class Level {
public:
    Level();
    void update();
    void draw() const;
private:
    std::vector<Object> _objs;
    std::vector<LightRay> _rays;
    Object* _cached_obj;
};
