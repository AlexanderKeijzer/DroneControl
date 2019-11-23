#define _USE_MATH_DEFINES

#include "Drone.hpp"
#include <cmath>

namespace DroneControl {

    Drone::Drone(Vec3 pos, double frame_mass, Vec3 rot, Vec3 a_mass) : WorldObject(pos, frame_mass, rot, a_mass), nMotors(4), dMotors(0.21) {
        double radMotor = 2*M_PI/nMotors;
        for (int i = 0; i < nMotors; i++) {
            Vec3 relPos(sin(radMotor*i)*dMotors, cos(radMotor*i)*dMotors, 0);
            addChild(new Motor(*this, relPos, 0.15, 5));
        }
    };

    void Drone::update() {
        for (SubWorldObject* child : children) {
            dynamic_cast<Motor*>(child)->setLift(-getPos().getZ());
        }
        WorldObject::update();
        forces.display();
    };

    bool Drone::setLift(int motor, double lift) {
        if (children.size() >= motor) {
            return false;
        }
        dynamic_cast<Motor*>(children[motor])->setLift(lift);
        return true;
    }

    double Drone::getLift(int motor) {
        if (children.size() >= motor) {
            return 0;
        }
        return dynamic_cast<Motor*>(children[motor])->getLift();
    }
}