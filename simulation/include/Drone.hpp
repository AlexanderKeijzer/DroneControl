#ifndef DRONECONTROL_DRONE_HPP
#define DRONECONTROL_DRONE_HPP

#include <vector>
#include "Motor.hpp"

namespace DroneControl {
    class Drone : public WorldObject {
    private:
        int nMotors;
        double dMotors;

    public:
        Drone(Vec3 pos, double mass, Vec3 rot, Vec3 a_mass);
        virtual void update() override;
        bool setLift(int motor, double lift);
        double getLift(int motor);
        const int getNumMotors();
    };
}

#endif