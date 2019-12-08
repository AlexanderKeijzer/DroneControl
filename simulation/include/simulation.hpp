#ifndef DRONECONTROL_SIMULATION_HPP
#define DRONECONTROL_SIMULATION_HPP
#include "Object.hpp"

namespace DroneControl {
    void run(bool stepMode);
    void runStepMode();
    void step();
    const Vec3& step(double lift);
    void runTimeMode();
    void update();
    const std::vector<Object*> &getObjects();
    const Vec3& reset();
    void kill();
};

#endif