#ifndef POINT_H
#define POINT_H

#include<ostream>
#include<iostream>

// Represents a point in three-dimensional space
class Point
{
private:
    // Object variables
    float x_;
    float y_;
    float z_;

public:
    // Constructor that creates a point at 0, 0, 0
    Point();

    // Constructor that creates a point at the given x, y, z
    Point(float x, float y, float z);

    // Get methods for object variables
    float x() const;

    float y() const;

    float z() const;
};

// Overloaded output operator for printing the point's information
std::ostream& operator<<(std::ostream& os, const Point& point);

// Overloaded input operator for reading a point from a file
// Format: <10, 0, -50>
std::istream& operator>>(std::istream& is, Point& point);

#endif /* POINT_H */
