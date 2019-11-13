#include "simulation/Object.hpp"
#include <iostream>

namespace DroneControl {

    void Object::update() {
    }

    void Object::step(const double &dt) {
    }

    WorldObject::WorldObject(Vec3 pos, double mass) : pos(pos), mass(mass) {
    };

    WorldObject::WorldObject(Vec3 pos, double mass, Vec3 rot, Vec3 a_mass) : pos(pos), mass(mass), rot(rot), a_mass(a_mass) {
    };

    WorldObject::~WorldObject() {
        for(SubWorldObject *child : children) {
            delete child;
        }
        children.empty();
    }

    void WorldObject::update() {
        for(SubWorldObject *child : children) {
            child->update();
        }
        addForce(Vec3(0, 0, -9.81*mass));
        //addForce(Vec3(0, -0.001, 0), Vec3(0, 0, 1));
        //addForce(Vec3(0, -0.001, 0), Vec3(1, 0, 0));
        std::cout << rot.getX() << ":" << rot.getY() << ":" << rot.getZ() << std::endl;
    }

    void WorldObject::step(const double &dt) {
        for(SubWorldObject *child : children) {
            child->step(dt);
        }
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

    const Vec3& WorldObject::getPos() {
        return pos;
    }

    const Vec3& WorldObject::getRot() {
        return rot;
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

    SubWorldObject::SubWorldObject(WorldObject &parent, Vec3 relPos, double mass) 
        : WorldObject(parent.getPos()+relPos, mass, parent.getRot(), Vec3()), parent(parent), relPos(relPos) {
    };

    void SubWorldObject::update() {
        //Forces can be added to a subobject externally. If they update after this subobject,
        //this means the effect of that force on its parent could be delayed by one tick.
        //However, if the update order is constant we should not see double addition of forces from one source.
        addForce(Vec3(0, 0, -mass*9.81));
        parent.addForce(forces, relPos);
        forces.zero();
        parent.addMoment(moments);
        moments.zero();
    }

    void SubWorldObject::step(const double &dt) {
        //For now we don't care abuot velocities.
        pos = parent.getPos() + relPos;
        rot = parent.getRot();
    }
}