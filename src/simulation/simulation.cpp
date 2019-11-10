#include "simulation/Object.hpp"
#include "simulation/simulation.hpp"
#include <vector>
#include <chrono>
#include <thread>

namespace DroneControl {

    std::vector<Object*> objects;
    double timestep = 0.01;
    int runtime = 10;

    void run() {
        using namespace std::this_thread;
        using namespace std::chrono;
        objects.push_back(new WorldObject(Vec3(1.1, 1.2, 1.4), 5));
        objects.push_back(new WorldObject(Vec3(1.1, 1.2, 1.4), 500));

        system_clock::time_point endTime = system_clock::now() + seconds(runtime);
        while(system_clock::now() < endTime) {
            system_clock::time_point t = system_clock::now() + milliseconds((int)(timestep*1000));
            step();
            sleep_until(t);
        }

        // Clear objects cleanly
        for (Object* obj : objects) {
            delete obj;
        }
        objects.clear();
    }

    void step() {
        for (Object* obj : objects) {
            obj->update();
        }
        for (Object* obj : objects) {
            obj->step(timestep);
        }
    }
}