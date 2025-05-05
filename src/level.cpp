#include "level.h"

Level::Level() {
    _cached_obj = nullptr;
    _objs.push_back(Object({{200, 200}, {240, 240}, {180, 270}}));
    _objs.push_back(Object({{200, 200}, {240, 240}, {180, 270}}));
    _rays.push_back(LightRay({200, 200}, 0));
    _rays.push_back(LightRay({200, 205}, 0));
    _rays.push_back(LightRay({200, 210}, 0));
    _rays.push_back(LightRay({200, 215}, 0));
    _rays.push_back(LightRay({200, 220}, 0));
}

void Level::update() {
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
        _cached_obj = nullptr;
    }
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 cursor = GetMousePosition();
        for (auto &o: _objs) {
            if (o.contain_point(cursor)) {
                _cached_obj = &o;
                _cached_obj->set_origin(cursor);
            }
        }
    }
    if (_cached_obj) {
        _cached_obj->set_position(GetMousePosition());
        _cached_obj->rotate(0.005);
        for (auto &r: _rays) {
            r.update(_objs);
        }
    }
}

void Level::draw() const {
    for (const auto &o: _objs) {
        o.draw();
    }
    for (const auto &r: _rays) {
        r.draw();
    }
}
