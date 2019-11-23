#ifndef DRONECONTROL_MOTOR_HPP
#define DRONECONTROL_MOTOR_HPP

#include "Object.hpp"

namespace DroneControl {
    class Motor : public SubWorldObject {
    private:
        const double maxLift;
        double lift;
    public:
        Motor(WorldObject &parent, Vec3 relPos, double mass, double maxLift);
        virtual void update();
        void setLift(double lift);
        double getLift();
    };
}

#endif