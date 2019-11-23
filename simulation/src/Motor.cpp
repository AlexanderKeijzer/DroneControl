#include "Motor.hpp"
#include <algorithm>

namespace DroneControl {
    Motor::Motor(WorldObject &parent, Vec3 relPos, double mass, double maxLift) : SubWorldObject(parent, relPos, mass), maxLift(maxLift), lift(0){

    };

    void Motor::update() {
        addForce(Vec3(0, 0, lift).rotate(rot));
        SubWorldObject::update();
    }

    void Motor::setLift(double liftForce) {
        lift = std::max(std::min(liftForce, maxLift), 0.0);
    }

    double Motor::getLift() {
        return lift;
    }
}