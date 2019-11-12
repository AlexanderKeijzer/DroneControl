#include "simulation/Vec3.hpp"
#include <cmath>

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

    double Vec3::dotProduct(const Vec3 &vec1, const Vec3 &vec2)
    {
        return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
    }

    double Vec3::dotProduct(const Vec3 &vec) const
    {
        return x * vec.x + y * vec.y + z * vec.z;
    }

    Vec3 Vec3::crossProduct(const Vec3 &vec1, const Vec3 &vec2)
    {
        return Vec3(vec1.y * vec2.z - vec1.z * vec2.y, vec1.z * vec2.x - vec1.x * vec2.z, vec1.x * vec2.y - vec1.y * vec2.x);
    }

    Vec3 Vec3::rotate(const Vec3 &rotation) const {
        double s, c, x_temp, y_temp, z_temp;

        Vec3 r(x, y, z);
        s = std::sin(rotation.z);
        c = std::cos(rotation.z);
        x_temp = r.x*c - r.y*s;
        y_temp = r.x*s + r.y*c;
        z_temp = r.z;
        r.set(x_temp, y_temp, z_temp);

        s = std::sin(rotation.y);
        c = std::cos(rotation.y);
        x_temp = r.x*c + r.z*s;
        y_temp = r.y;
        z_temp = -r.x*s + r.z*c;
        r.set(x_temp, y_temp, z_temp);

        s = std::sin(rotation.x);
        c = std::cos(rotation.x);
        x_temp = r.x;
        y_temp = r.y*c - r.z*s;
        z_temp = r.y*s + r.z*c;
        r.set(x_temp, y_temp, z_temp);
        return r;
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

    Vec3 Vec3::operator/(const Vec3 &vector) const
    {
        return Vec3(x / vector.x, y / vector.y, z / vector.z);
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