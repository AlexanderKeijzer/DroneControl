#include "simulation/Motor.hpp"

namespace DroneControl {
    Motor::Motor(WorldObject &parent, Vec3 relPos, double mass, double maxLift) : SubWorldObject(parent, relPos, mass), maxLift(maxLift) {

    };

    void Motor::update() {
        addForce(Vec3(0, 0, maxLift));
        SubWorldObject::update();
    }
}