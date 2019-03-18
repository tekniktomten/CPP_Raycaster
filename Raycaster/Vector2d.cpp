#include "Vector2d.hpp"
#include <stdio.h>
#include <cmath>

Vector2d::Vector2d(double x_, double y_) {
    x = x_;
    y = y_;
}

double Vector2d::getX() const {
    return x;
};

double Vector2d::getY() const {
    return y;
};

void Vector2d::operator += (const Vector2d b) {
    x += b.getX();
    y += b.getY();
}

void Vector2d::operator -= (const Vector2d b) {
    x -= b.getX();
    y -= b.getY();
}

void Vector2d::operator *= (const double b) {
    x *= b;
    y *= b;
}

void Vector2d::operator /= (const double b) {
    x /= b;
    y /= b;
}

void Vector2d::rotateThis(const double b) {
    double xTemp = x;
    x = cos(b) * x - sin(b) * y;
    y =  sin(b) * xTemp + cos(b) * y;
}

Vector2d Vector2d::rotate(const double b) {
    double xNew;
    double yNew;
    xNew = cos(b) * x - sin(b) * y;
    yNew =  sin(b) * x + cos(b) * y;
    return Vector2d(xNew, yNew);
}

Vector2d Vector2d::operator + (const Vector2d b) {
    return Vector2d(x + b.getX(), y + b.getY());
}

Vector2d Vector2d::operator - (const Vector2d b) {
    return Vector2d(x - b.getX(), y - b.getY());
}

Vector2d Vector2d::operator * (const double b) {
    return Vector2d(x * b, y * b);
}

Vector2d Vector2d::operator / (const double b) {
    return Vector2d(x / b, y / b);
}

double Vector2d::dot(const Vector2d b) {
    return x * b.getX() + y * b.getY();
}

double Vector2d::mag() {
    return sqrt(x*x+y*y);
}

Vector2d Vector2d::copy() {
    return Vector2d(x, y);
}

Vector2d Vector2d::norm() {
    return copy() / mag();
}
