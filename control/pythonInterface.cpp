//#include "main.hpp"
#include <pybind11/pybind11.h>

namespace py = pybind11;

extern int main(int argc, char* argv[]);

void start() {
    char *inputs[] = {"DroneControl", "step"};
    main(2, inputs);
}

int add(int i, int j)
{
    return i + j;
}

int subtract(int i, int j)
{
    return i - j;
}

PYBIND11_MODULE(DroneControlControl, m)
{
    m.def("start", &start);
    m.def("subtract", &subtract);
}