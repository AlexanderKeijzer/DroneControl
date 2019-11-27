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
    
    simulationThread.join();
    visualizationThread.join();
    return 0;
}