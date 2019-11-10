#include "simulation/Object.hpp"
#include <iostream>

namespace DroneControl {
    WorldObject::WorldObject(Vec3 pos, double mass) : pos(pos), mass(mass) {
    };

    void WorldObject::update() {
        forces.addZ(-9.81*mass);
    }

    void WorldObject::step(const double &dt) {
        //TODO: Better integration
        vel += forces/mass*dt;
        pos += vel*dt;
        forces.zero();
    }

    void WorldObject::addForce(const Vec3 &force) {
        forces += force;
    }

    void Object::update() {
    }

    void Object::step(const double &dt) {
    }
}