#ifndef DRONECONTROL_SIMULATION_HPP
#define DRONECONTROL_SIMULATION_HPP
#include "Object.hpp"

namespace DroneControl {
    void run();
    void step();
    const std::vector<Object*> &getObjects();
};

#endif