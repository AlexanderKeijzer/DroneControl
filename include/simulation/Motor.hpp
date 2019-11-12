#include "simulation/Object.hpp"

namespace DroneControl {
    class Motor : public SubWorldObject {
    private:
        double maxLift;
    public:
        Motor(WorldObject &parent, Vec3 relPos, double mass, double maxLift);
        virtual void update();
    };
}