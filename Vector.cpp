#include "Vector.h"

#include <cmath>

Vector::Vector()
{
	x_ = 0;
	y_ = 0;
	z_ = 0;
}

Vector::Vector(float x, float y, float z)
{
	x_ = x;
	y_ = y;
	z_ = z;
}

Vector::Vector(Point p1, Point p2)
{
	x_ = p2.x() - p1.x();
	y_ = p2.y() - p1.y();
	z_ = p2.z() - p1.z();
}

float Vector::x() const
{
	return x_;
}

float Vector::y() const
{
	return y_;
}

float Vector::z() const
{
	return z_;
}

float Vector::sqr_length() const
{
	return std::pow(x_, 2) + std::pow(y_, 2) + std::pow(z_, 2);
}

float Vector::length() const
{
	return std::sqrt(sqr_length());
}

Vector Vector::operator+(Vector other) const
{
	float x = x_ + other.x();
	float y = y_ + other.y();
	float z = z_ + other.z();
	return Vector(x, y, z);
}

Vector  Vector::operator-(Vector other) const
{
	float x = x_ - other.x();
	float y = y_ - other.y();
	float z = z_ - other.z();
	return Vector(x, y, z);
}

float dot(Vector v1, Vector v2)
{
	float result = (v1.x() * v2.x()) + (v1.y() * v2.y()) + (v1.z() * v2.z());
	return result;
}

Vector Vector::cross(Vector other)
{
	float vx = (y_ * other.z()) - (other.y() * z_);
	float vy = (z_ * other.x()) - (other.z() * x_);
	float vz = (x_ * other.y()) - (other.x() * y_);
	return Vector(vx, vy, vz);
}

Vector Vector::operator*(float alpha) const
{
	float x = x_ * alpha;
	float y = y_ * alpha;
	float z = z_ * alpha;
	return Vector(x, y, z);
}

Point Vector::point()
{
	return Point(x_,y_,z_);
}

Vector unit(Vector vector)
{
	return (vector / vector.length());
}

Vector operator-(Vector vector)
{
	float x = -vector.x();
	float y = -vector.y();
	float z = -vector.z();
	return Vector(x, y, z);
}

Vector operator/(const Vector vector, float alpha)
{
	float x = vector.x() / alpha;
	float y = vector.y() / alpha;
	float z = vector.z() / alpha;
	return Vector(x, y, z);
}

Vector operator*(float alpha, const Vector vector)
{
	float x = vector.x() * alpha;
	float y = vector.y() * alpha;
	float z = vector.z() * alpha;
	return Vector(x, y, z);
}

Point operator+(Point point, Vector vector)
{
	float x = vector.x() + point.x();
	float y = vector.y() + point.y();
	float z = vector.z() + point.z();
	return Point(x, y, z);
}

std::ostream& operator<<(std::ostream& os, const Vector& vector)
{
	os << "Vector(" << vector.x() << ", " << vector.y() << ", " << vector.z() << ")";
	return os;
}

std::istream& operator>>(std::istream& is, Vector& vector)
{
	char chToken;
	float x;
	float y;
	float z;

	is >> chToken;       // Read the <
	is >> x >> chToken;  // Read point coordinates and commas
	is >> y >> chToken;
	is >> z >> chToken;  // Reads the last coordinate and >

	vector = Vector(x, y, z);   // Make the vector
	return is;
}

