#include "light_ray.h"
#include <cmath>
#include <tuple>

LightRay::LightRay(Vector2 pos, float angle_rad) {
    _parts.push_back(LightRayPart {
        .from = pos,
        .to = { pos.x + 1000 * std::cos(angle_rad),
                pos.y + 1000 * std::sin(angle_rad) },
        .angle_rad = angle_rad
    });
}

void LightRay::update(const std::vector<Object> &objs) {
    Vector2 pos = _parts.front().from;
    float angle_rad = _parts.front().angle_rad;
    _parts.clear();
    _parts.push_back(LightRayPart {
        .from = pos,
        .to = { pos.x + 1000 * std::cos(angle_rad),
                pos.y + 1000 * std::sin(angle_rad) },
        .angle_rad = angle_rad
    });

    int i = 0;
    do {
        auto ray = &_parts[i];
        for (const auto &o: objs) {
            auto rc = o.collision_with_ray(ray->from, ray->angle_rad);
            if (std::get<0>(rc)) {
                Vector2 point = std::get<1>(rc);
                float angle_rad = ray->angle_rad + PI - std::get<2>(rc) * 2;
                ray->to = std::get<1>(rc);
                if (_parts.size() < 30) {
                    _parts.push_back(LightRayPart {
                        .from = point,
                        .to = { point.x + 1000 * std::cos(angle_rad),
                                point.y + 1000 * std::sin(angle_rad) },
                        .angle_rad = angle_rad
                    });
                }
                break;
            }
        }
        i++;
    } while (i < _parts.size());
}

void LightRay::draw() const {
    DrawCircle(_parts.front().from.x, _parts.front().from.y, 3, BLUE);
    for (const auto &p: _parts) {
        DrawLineV(p.from, p.to, BLUE);
    }
}
