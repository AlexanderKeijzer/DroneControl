#ifndef DRONECONTROL_WORLD_HPP
#define DRONECONTROL_WORLD_HPP

namespace DroneControl {
    class Vec3 {
    private:
        double x, y, z;

    public:
        Vec3();
        Vec3(double x, double y, double z);
        Vec3(const Vec3 &vec);

        void clear();

        void set(const double &xValue, const double &yValue, const double &zValue);

        double getX() const;
        double getY() const;
        double getZ() const;

        void setX(const double &xValue);
        void setY(const double &yValue);
        void setZ(const double &zValue);

        void zero();

        void addX(const double &value);
        void addY(const double &value);
        void addZ(const double &value);

        Vec3 operator+(const Vec3 &vector) const;
        void Vec3::operator+=(const Vec3 &vector);
        Vec3 Vec3::operator-(const Vec3 &vector) const;
        void Vec3::operator-=(const Vec3 &vector);
        Vec3 Vec3::operator*(const Vec3 &vector) const;
        Vec3 Vec3::operator*(const double &value) const;
        void Vec3::operator*=(const double &value);
        Vec3 Vec3::operator/(const double &value) const;
        void Vec3::operator/=(const double &value);
    };
}

#endif