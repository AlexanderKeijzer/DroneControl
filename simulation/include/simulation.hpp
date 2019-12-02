#ifndef DRONECONTROL_SIMULATION_HPP
#define DRONECONTROL_SIMULATION_HPP
#include "Object.hpp"

namespace DroneControl {
    void run(bool stepMode);
    void runStepMode();
    void step();
    void runTimeMode();
    void update();
    const std::vector<Object*> &getObjects();
    void kill();
};

#endif