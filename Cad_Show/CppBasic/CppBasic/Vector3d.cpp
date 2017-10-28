
#include <math.h>
#include "Vector3d.h"

using namespace std;

Vector3d::Vector3d() {
	
}

Vector3d::Vector3d(float x, float y, float z) {
	v[0] = x;
	v[1] = y;
	v[2] = z;
}

float &Vector3d::operator[](int index) {
	return v[index];
}

float Vector3d::operator[](int index) const {
	return v[index];
}

Vector3d Vector3d::operator*(float scale) const {
	return Vector3d(v[0] * scale, v[1] * scale, v[2] * scale);
}

Vector3d Vector3d::operator/(float scale) const {
	return Vector3d(v[0] / scale, v[1] / scale, v[2] / scale);
}

Vector3d Vector3d::operator+(const Vector3d &other) const {
	return Vector3d(v[0] + other.v[0], v[1] + other.v[1], v[2] + other.v[2]);
}

Vector3d Vector3d::operator-(const Vector3d &other) const {
	return Vector3d(v[0] - other.v[0], v[1] - other.v[1], v[2] - other.v[2]);
}

Vector3d Vector3d::operator-() const {
	return Vector3d(-v[0], -v[1], -v[2]);
}

const Vector3d &Vector3d::operator*=(float scale) {
	v[0] *= scale;
	v[1] *= scale;
	v[2] *= scale;
	return *this;
}

const Vector3d &Vector3d::operator/=(float scale) {
	v[0] /= scale;
	v[1] /= scale;
	v[2] /= scale;
	return *this;
}

const Vector3d &Vector3d::operator+=(const Vector3d &other) {
	v[0] += other.v[0];
	v[1] += other.v[1];
	v[2] += other.v[2];
	return *this;
}

const Vector3d &Vector3d::operator-=(const Vector3d &other) {
	v[0] -= other.v[0];
	v[1] -= other.v[1];
	v[2] -= other.v[2];
	return *this;
}

float Vector3d::magnitude() const {
	return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

float Vector3d::magnitudeSquared() const {
	return v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
}

Vector3d Vector3d::normalize() const {
	float m = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	return Vector3d(v[0] / m, v[1] / m, v[2] / m);
}

float Vector3d::dot(const Vector3d &other) const {
	return v[0] * other.v[0] + v[1] * other.v[1] + v[2] * other.v[2];
}

Vector3d Vector3d::cross(const Vector3d &other) const {
	return Vector3d(v[1] * other.v[2] - v[2] * other.v[1],
				 v[2] * other.v[0] - v[0] * other.v[2],
				 v[0] * other.v[1] - v[1] * other.v[0]);
}

Vector3d operator*(float scale, const Vector3d &v) {
	return v * scale;
}

ostream &operator<<(ostream &output, const Vector3d &v) {
	cout << '(' << v[0] << ", " << v[1] << ", " << v[2] << ')';
	return output;
}









