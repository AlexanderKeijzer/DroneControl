#define _USE_MATH_DEFINES

#include "simulation/Drone.hpp"
#include <cmath>

namespace DroneControl {

    Drone::Drone(Vec3 pos, double frame_mass, Vec3 rot, Vec3 a_mass) : WorldObject(pos, mass, rot, a_mass), nMotors(4), dMotors(0.21) {
        double radMotor = 2*M_PI/nMotors;
        for (int i = 0; i < nMotors; i++) {
            Vec3 relPos(sin(radMotor*i)*dMotors, cos(radMotor*i)*dMotors, 0);
            motors.push_back(new Motor(*this, relPos, 0.15, 5));
            //TODO: Subobjects should add inertia and mass
        }
    };

    Drone::~Drone() {
        for (Object* motor : motors) {
            delete motor;
        }
        motors.clear();
    }

    void Drone::update() {
        WorldObject::update();
    };
}