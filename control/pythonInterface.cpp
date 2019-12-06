//#include "main.hpp"
#include <pybind11/pybind11.h>
#include <iostream>
#include <thread>
#include <chrono>

namespace py = pybind11;
std::thread mainThread;

extern int main(int argc, char* argv[]);
namespace DroneControl {
    extern void step();
    extern void kill();
}

void start() {
    char *inputs[] = {"DroneControl", "step"};
    using namespace std::chrono_literals;
    mainThread = std::thread(main, 2, inputs);
    std::this_thread::sleep_for(1s);
}

void step() {
    DroneControl::step();
    std::cout << "step" << std::endl;
}

void kill() {
    DroneControl::kill();
    std::cout << "Killed simulation" << std::endl;
}

int run(int argc, char* argv[]) {
    using namespace std::chrono_literals;
    mainThread = std::thread(main, argc, argv);
    std::this_thread::sleep_for(1s);
}

PYBIND11_MODULE(DroneControlControl, m)
{
    m.def("start", &start);
    m.def("step", &step);
    m.def("kill", &kill);
}