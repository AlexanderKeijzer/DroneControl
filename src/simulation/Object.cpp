#include "simulation/Object.hpp"
#include <iostream>

namespace DroneControl {
    WorldObject::WorldObject(Vec3 pos, double mass) : pos(pos), mass(mass) {
    };

    WorldObject::WorldObject(Vec3 pos, double mass, Vec3 rot, Vec3 a_mass) : pos(pos), mass(mass), rot(rot), a_mass(a_mass) {
    };

    void WorldObject::update() {
        addForce(Vec3(0, -0.001, 0), Vec3(0, 0, 1));
        addForce(Vec3(0, -0.001, 0), Vec3(1, 0, 0));
        std::cout << rot.getX() << ":" << rot.getY() << ":" << rot.getZ() << std::endl;
    }

    void WorldObject::step(const double &dt) {
        //TODO: Better integration
        vel += forces/mass*dt;
        pos += vel*dt;
        forces.zero();

        //Everything is descibed in global coordinate system, except for inertia.
        //Intertia is rotated to global CS from rot.

        //TODO: This is incorrect! Rotation doesn't only happen here!
        a_vel += moments/a_mass.rotate(rot)*dt;
        rot += a_vel*dt;
        moments.zero();
    }

    void WorldObject::addForce(const Vec3 &force) {
        forces += force;
    }

    void WorldObject::addForce(const Vec3 &force, const Vec3 &pos) {
        addForce(force);
        addMoment(Vec3::crossProduct(pos, force));
    }

    void WorldObject::addMoment(const Vec3 &moment) {
        moments += moment;
    }

    void Object::update() {
    }

    void Object::step(const double &dt) {
    }
}