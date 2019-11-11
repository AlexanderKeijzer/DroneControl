#ifndef DRONECONTROL_OBJECT_HPP
#define DRONECONTROL_OBJECT_HPP

#include <iostream>
#include "simulation/World.hpp"

namespace DroneControl {
    class Object {
    public:
        virtual void update();

        virtual void step(const double &dt);
    };

    class WorldObject : public Object {
    private:
        Vec3 pos;
        Vec3 vel;
        Vec3 forces;
        double mass;

        Vec3 rot;
        Vec3 a_vel;
        Vec3 moments;
        Vec3 a_mass;


    public:
        WorldObject(Vec3 pos, double mass);
        WorldObject(Vec3 pos, double mass, Vec3 rot, Vec3 a_mass);
        virtual void update() override;
        virtual void step(const double &dt) override;
        virtual void addForce(const Vec3 &force);
        virtual void addForce(const Vec3 &force, const Vec3 &pos);
        virtual void addMoment(const Vec3 & moment);
    };
}


#endif