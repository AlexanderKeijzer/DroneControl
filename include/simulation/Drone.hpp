#include <vector>
#include "simulation/Motor.hpp"

namespace DroneControl {
    class Drone : public WorldObject {
    private:
        int nMotors;
        double dMotors;

    public:
        Drone(Vec3 pos, double mass, Vec3 rot, Vec3 a_mass);
        virtual void update() override;
    };
}