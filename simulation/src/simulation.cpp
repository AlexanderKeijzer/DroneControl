#include "simulation.hpp"
#include "Drone.hpp"
#include <vector>
#include <chrono>
#include <thread>
#include <mutex>
#include <iostream>
#include <condition_variable>

extern std::mutex objectMutex;

namespace DroneControl {

    std::mutex stepMutex;
    std::condition_variable stepCond; 
    bool doStep = false;

    std::vector<Object*> objects;
    double timestep = 0.01;
    int runtime = 10000;
    bool modeStep;
    bool killSim = false;

    void run(bool stepMode) {
        modeStep = stepMode;

        std::cout << "Simulation initializing..." << std::endl << (stepMode ? "Running in step mode" : "Running in time mode") << std::endl;

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
            {
                std::unique_lock<std::mutex> lck(stepMutex);
                stepCond.wait(lck, []{ return doStep || killSim; });
                if (killSim)
                    return;
                update();
                doStep = false;
            }
            stepCond.notify_one();
        }
    }

    void step() {
        if (!modeStep) {
            std::cout << "Trying to step while not in step mode! Ignoring." << std::endl;
            return;
        }
        //Read is not locked and it should be in some way
        {
            std::unique_lock<std::mutex> lck(stepMutex);
            stepCond.wait(lck, []{ return !doStep; });
            doStep = true;
        }
        stepCond.notify_one();
    }

    /**
     * Simple 1D step which returns next state from input lift target.
     **/
    const Vec3& step(double lift) {
        Object* obj = objects[0];
        Drone* drone = dynamic_cast<Drone*>(obj);
        {
            //Wait for a step still finishing
            std::unique_lock<std::mutex> lck(stepMutex);
            stepCond.wait(lck, []{ return !doStep; });

            //Set lift on motors
            int nMotors = drone->getNumMotors();
            std::lock_guard<std::mutex> guard(objectMutex);
            for(auto i = 0; i < nMotors; i++) {
                drone->setLift(i, lift/nMotors);
                //std::cout << lift/nMotors << std::endl;
            }

            doStep = true;
        }
        //Step with other thread
        stepCond.notify_one();

        //Wait untill step is finished and return new position
        std::unique_lock<std::mutex> lck(stepMutex);
        stepCond.wait(lck, []{ return !doStep; });
        return drone->getPos();
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

    const Vec3& reset() {
        for (Object* obj : objects) {
            obj->reset();
        }
        WorldObject* wo =  dynamic_cast<WorldObject*>(objects[0]);
        return wo->getPos();
    }

    void kill() {
        killSim = true;
        stepCond.notify_one();
    }
}