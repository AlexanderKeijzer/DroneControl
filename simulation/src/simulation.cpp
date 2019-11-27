#include "simulation.hpp"
#include "Drone.hpp"
#include <vector>
#include <chrono>
#include <thread>
#include <mutex>

extern std::mutex objectMutex;

namespace DroneControl {
    std::vector<Object*> objects;
    double timestep = 0.01;
    int runtime = 10;

    void run() {
        using namespace std::this_thread;
        using namespace std::chrono;
        Drone* d = new Drone(Vec3(), 0.5, Vec3(0, 0, 0), Vec3(0.00081, 0.00081, 0.00142)); //1.571
        objects.push_back(d);

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
        std::lock_guard<std::mutex> guard(objectMutex);
        for (Object* obj : objects) {
            obj->step(timestep);
            //dynamic_cast<WorldObject*>(obj)->getPos().display();
        }
    }

    const std::vector<Object*> &getObjects() {
        return objects;
    }
}