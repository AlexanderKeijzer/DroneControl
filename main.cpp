#include "simulation.hpp"
#include <thread>
#include <mutex>

namespace DroneControl {
    extern void startVisualization(int argc, char** argv);
}

std::mutex objectMutex;

int main(int argc, char** argv) {
    std::thread simulationThread(DroneControl::run);
    std::thread visualizationThread(DroneControl::startVisualization, argc, argv);

    visualizationThread.join();
    DroneControl::kill();
    simulationThread.join();
    return 0;
}