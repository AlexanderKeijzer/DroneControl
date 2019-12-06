#include "simulation.hpp"
#include "Drone.hpp"
#include <vector>
#include <chrono>
#include <thread>
#include <mutex>
#include <iostream>

extern std::mutex objectMutex;

namespace DroneControl {

    std::mutex stepMutex;

    std::vector<Object*> objects;
    double timestep = 0.01;
    int runtime = 10000;
    bool modeStep;
    bool killSim = false;
    bool doStep = false;

    void run(bool stepMode) {
        modeStep = stepMode;

        std::cout << "Simulation initializing..." << std::endl << stepMode << std::endl;

        Drone* d = new Drone(Vec3(), 0.5, Vec3(0, 0, 0), Vec3(0.00081, 0.00081, 0.00142)); //1.571
        objects.push_back(d);

        if (stepMode) {
            runStepMode();
        } else {
            runTimeMode();
        }

        // Clear objects cleanly
        for (Object* obj : objects) {
            delete obj;
        }
        objects.clear();
    }

    void runStepMode() {
        while (!killSim) {
            //std::cout << "check" << std::endl;
            if (doStep) {
                update();
                std::lock_guard<std::mutex> guard(stepMutex);
                doStep = false;
                std::cout << "doStep" << std::endl;
            }
        }
    }

    void step() {
        if (!modeStep) {
            std::cout << "Trying to step while not in step mode! Ignoring." << std::endl;
            return;
        }
        //Read is not locked and it should be in some way
        {
            std::lock_guard<std::mutex> guard(stepMutex);
            doStep = true;
            std::cout << "stepin" << std::endl;
        }
        while (doStep) {
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(1ms);
        }
        std::cout << "stepout" << std::endl;
    }

    void runTimeMode() {
        using namespace std::this_thread;
        using namespace std::chrono;

        system_clock::time_point endTime = system_clock::now() + seconds(runtime);
        while(system_clock::now() < endTime && !killSim) {
            system_clock::time_point t = system_clock::now() + milliseconds((int)(timestep*1000));
            update();
            sleep_until(t);
        }
    }

    void update() {
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

    void kill() {
        killSim = true;
    }
}