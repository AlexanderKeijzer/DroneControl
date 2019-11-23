#ifndef DRONECONTROL_OBJECT_HPP
#define DRONECONTROL_OBJECT_HPP

#include "Object.hpp"
#include "Vec3.hpp"
#include <iostream>
#include <vector>

namespace DroneControl {
    class Object {
    public:
        virtual void update();

        virtual void step(const double &dt);
    };

    class SubWorldObject;

    class WorldObject : public Object {
    protected:
        Vec3 pos;
        Vec3 vel;
        Vec3 forces;
        double mass;

        Vec3 rot;
        Vec3 a_vel;
        Vec3 moments;
        Vec3 a_mass;
        std::vector<SubWorldObject*> children;


    public:
        WorldObject(Vec3 pos, double mass);
        WorldObject(Vec3 pos, double mass, Vec3 rot, Vec3 a_mass);
        virtual ~WorldObject();
        virtual void update() override;
        virtual void step(const double &dt) override;
        virtual void addChild(SubWorldObject* child);
        virtual const Vec3& getPos();
        virtual const Vec3& getRot();
        virtual void addForce(const Vec3 &force);
        virtual void addForce(const Vec3 &force, const Vec3 &pos);
        virtual void addMoment(const Vec3 & moment);
    };

    class SubWorldObject : public WorldObject {
    protected:
        WorldObject &parent;
        Vec3 relPos;
        //TODO: relRot?

    public:
        SubWorldObject(WorldObject &parent, Vec3 relPos, double mass);
        virtual void update() override;
        virtual void step(const double &dt) override;
        virtual const Vec3& getRelPos();
    };
}


#endif