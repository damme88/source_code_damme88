
#ifndef PASSION_VECTOR3D_H_INCLUDED
#define PASSION_VECTOR3D_H_INCLUDED

#include <iostream>

class  Vector3d {
	private:
		float v[3];
	public:
		Vector3d();
		Vector3d(float x, float y, float z);
		
		float &operator[](int index);
		float operator[](int index) const;
		
		Vector3d operator*(float scale) const;
		Vector3d operator/(float scale) const;
		Vector3d operator+(const Vector3d &other) const;
		Vector3d operator-(const Vector3d &other) const;
		Vector3d operator-() const;
		
		const Vector3d &operator*=(float scale);
		const Vector3d &operator/=(float scale);
		const Vector3d &operator+=(const Vector3d &other);
		const Vector3d &operator-=(const Vector3d &other);
		
		float magnitude() const;
		float magnitudeSquared() const;
		Vector3d normalize() const;
		float dot(const Vector3d &other) const;
		Vector3d cross(const Vector3d &other) const;
};

Vector3d operator*(float scale, const Vector3d &v);
std::ostream &operator<<(std::ostream &output, const Vector3d &v);

#endif // PASSION_VECTOR3D_H_INCLUDED
