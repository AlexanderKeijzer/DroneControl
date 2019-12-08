#include "main.hpp"
#include "simulation.hpp"
#include <thread>
#include <mutex>
#include <iostream>

#ifdef USE_VISULATIZATION
namespace DroneControl {
    extern void startVisualization(int argc, char** argv);
}
#endif

std::mutex objectMutex;

int main(int argc, char* argv[]) {

    std::cout << "Starting..." << std::endl;
    bool stepMode = false;
    if (argc >= 2 && strcmp(argv[1], "step") == 0) {
        stepMode = true;
    }

    std::thread simulationThread(DroneControl::run, stepMode);
    std::cout << "Created simulation thread" << std::endl;

    #ifdef USE_VISULATIZATION
    std::thread visualizationThread(DroneControl::startVisualization, argc, argv);

    visualizationThread.join();
    DroneControl::kill();
    #endif

    simulationThread.join();
    return 0;
}