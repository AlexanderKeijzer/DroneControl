#include "main.hpp"
#include "simulation.hpp"
#include <thread>
#include <mutex>

namespace DroneControl {
    extern void startVisualization(int argc, char** argv);
}

std::mutex objectMutex;

int main(int argc, char* argv[]) {

    bool stepMode = false;
    if (argc >= 2 && strcmp(argv[1], "step") == 0) {
        stepMode = true;
    }

    std::thread simulationThread(DroneControl::run, stepMode);
    std::thread visualizationThread(DroneControl::startVisualization, argc, argv);

    visualizationThread.join();
    DroneControl::kill();
    simulationThread.join();
    return 0;
}