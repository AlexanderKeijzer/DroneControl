#include <vector>
#include "simulation/Motor.hpp"

namespace DroneControl {
    class Drone : public WorldObject {
    private:
        int nMotors;
        double dMotors;
        std::vector<Motor*> motors;

    public:
        Drone(Vec3 pos, double mass, Vec3 rot, Vec3 a_mass);
        ~Drone();
        virtual void update() override;
    };
}