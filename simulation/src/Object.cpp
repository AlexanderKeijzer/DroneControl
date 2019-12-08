#include "Object.hpp"
#include <iostream>

namespace DroneControl {

    void Object::update() {
    }

    void Object::step(const double &dt) {
    }

    void Object::reset() {
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
        //std::cout << rot.getX() << ":" << rot.getY() << ":" << rot.getZ() << std::endl;
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

    void WorldObject::addChild(SubWorldObject* child) {
        if (child != nullptr) {
            // TODO: This is not correct. The centre of mass will move. Currently the position
            // of an object is the centre of mass position. To fix this problem we need
            // to split those.
            mass += child->mass;
            Vec3 chilRelPos = child->getRelPos();
            a_mass += Vec3(chilRelPos*chilRelPos*child->mass);
            children.push_back(child);
        }
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

    void WorldObject::reset() {
        pos = Vec3();
        vel = Vec3();
        forces = Vec3();
        rot = Vec3();
        a_vel = Vec3();
        moments = Vec3();
        for (SubWorldObject* child : children) {
            child->reset();
        }
    }

    SubWorldObject::SubWorldObject(WorldObject &parent, Vec3 relPos, double mass) 
        : WorldObject(parent.getPos()+relPos, mass, parent.getRot(), Vec3()), parent(parent), relPos(relPos) {
    };

    void SubWorldObject::update() {
        //Forces can be added to a subobject externally. If they update after this subobject,
        //this means the effect of that force on its parent could be delayed by one tick.
        //However, if the update order is constant we should not see double addition of forces from one source.
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

    const Vec3& SubWorldObject::getRelPos() {
        return relPos;
    }

    void SubWorldObject::reset() {
        pos = relPos;
        forces = Vec3();
        rot = Vec3();
        moments = Vec3();
    }
}