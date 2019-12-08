#include "main.hpp"
#include "Vec3.hpp"
#include "simulation.hpp"
#include <pybind11/pybind11.h>
#include <iostream>
#include <thread>
#include <chrono>

namespace py = pybind11;
std::thread mainThread;

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

const DroneControl::Vec3& stepState(double lift) {
    return DroneControl::step(lift);
}

const DroneControl::Vec3& reset() {
    return DroneControl::reset();
}

void kill() {
    DroneControl::kill();
    mainThread.join();
    std::cout << "Killed simulation" << std::endl;
}

PYBIND11_MODULE(DroneControlControl, m)
{
    py::class_<DroneControl::Vec3>(m, "Vec3")
        .def(py::init<double, double, double>())
        .def("getX", &DroneControl::Vec3::getX)
        .def("getY", &DroneControl::Vec3::getY)
        .def("getZ", &DroneControl::Vec3::getZ);

    m.def("start", &start);
    m.def("step", &step);
    m.def("step_state", &stepState);
    m.def("reset", &reset);
    m.def("kill", &kill);
}