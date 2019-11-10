#include "simulation/World.hpp"

namespace DroneControl {
    Vec3::Vec3() : x(0), y(0), z(0){
    };

    Vec3::Vec3(double x, double y, double z) : x(x), y(y), z(z) {
    };

    Vec3::Vec3(const Vec3 &vec) : x(vec.x), y(vec.y), z(vec.z) {
    };

    void Vec3::set(const double &xValue, const double &yValue, const double &zValue)
    {
        x = xValue;
        y = yValue;
        z = zValue;
    }

    double Vec3::getX() const { return x; }
    double Vec3::getY() const { return y; }
    double Vec3::getZ() const { return z; }

    void Vec3::setX(const double &xValue) { x = xValue; }
    void Vec3::setY(const double &yValue) { y = yValue; }
    void Vec3::setZ(const double &zValue) { z = zValue; }

    void Vec3::zero()
    {
        x = y = z = 0;
    }

    void Vec3::addX(const double &value) { x += value; }
    void Vec3::addY(const double &value) { y += value; }
    void Vec3::addZ(const double &value) { z += value; }

    Vec3 Vec3::operator+(const Vec3 &vector) const
    {
        return Vec3(x + vector.x, y + vector.y, z + vector.z);
    }

    void Vec3::operator+=(const Vec3 &vector)
    {
        x += vector.x;
        y += vector.y;
        z += vector.z;
    }

    Vec3 Vec3::operator-(const Vec3 &vector) const
    {
        return Vec3(x - vector.x, y - vector.y, z - vector.z);
    }

    void Vec3::operator-=(const Vec3 &vector)
    {
        x -= vector.x;
        y -= vector.y;
        z -= vector.z;
    }

    Vec3 Vec3::operator*(const Vec3 &vector) const
    {
        return Vec3(x * vector.x, y * vector.y, z * vector.z);
    }

    Vec3 Vec3::operator*(const double &value) const
    {
        return Vec3(x * value, y * value, z * value);
    }

    void Vec3::operator*=(const double &value)
    {
        x *= value;
        y *= value;
        z *= value;
    }

    Vec3 Vec3::operator/(const double &value) const
    {
        return Vec3(x / value, y / value, z / value);
    }

    void Vec3::operator/=(const double &value)
    {
        x /= value;
        y /= value;
        z /= value;
    }
}