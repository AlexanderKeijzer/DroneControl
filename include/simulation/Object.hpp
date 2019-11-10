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

    public:
        WorldObject(Vec3 pos, double mass);
        void update() override;
        void step(const double &dt) override;
        void addForce(const Vec3 &force);
    };
}


#endif