#ifndef POINT_H_
#define POINT_H_

#include <iostream>
#include <cmath>

#define PI			3.1415926535897932384626433832795
#define HALF_PI		1.5707963267948966192313216916398
#define TWO_PI		6.283185307179586476925286766559
#define DEG_TO_RAD	0.017453292519943295769236907684886
#define RAD_TO_DEG	57.295779513082320876798154814105

template <class T>
class Vector_t {

public:
	
	Vector_t<T>();
	Vector_t<T>(T xx, T yy);
	Vector_t<T>(T xx, T yy, T zz);
	
	const T calculateDirection(const Vector_t<T>& other) const;
	const T calculateDistance(const Vector_t<T>& other) const;

	virtual ~Vector_t<T>();


	T x;
	T y;
	T z;


	Vector_t<T>& operator+=(const Vector_t<T>& rhs);
	Vector_t<T> operator+(const Vector_t<T>& rhs) const;
	Vector_t<T>& operator-=(const Vector_t<T>& rhs);
	Vector_t<T> operator-(const Vector_t<T>& rhs) const;
	Vector_t<T>& operator*=(const Vector_t<T>& rhs);
	Vector_t<T> operator*(const Vector_t<T>& rhs) const;
	Vector_t<T>& operator/=(const Vector_t<T>& rhs);
	Vector_t<T> operator/(const Vector_t<T>& rhs) const;

	Vector_t<T>& operator+=(const T rhs);
	Vector_t<T> operator+(const T rhs) const;
	Vector_t<T>& operator-=(const T rhs);
	Vector_t<T> operator-(const T rhs) const;
	Vector_t<T>& operator*=(const T rhs);
	Vector_t<T> operator*(const T rhs) const;
	Vector_t<T>& operator/=(const T rhs);
	Vector_t<T> operator/(const T rhs) const;

	bool operator==(const Vector_t<T>& other) const;
	bool operator!=(const Vector_t<T>& other) const;
};

typedef Vector_t<int> VectorI;
typedef Vector_t<float> VectorF;
typedef Vector_t<double> VectorD;

typedef VectorF Vector;

typedef Vector_t<int> Vector2I;
typedef Vector_t<float> Vector2F;
typedef Vector_t<double> Vector2D;

typedef Vector2F Vector2;

typedef Vector_t<int> Vector3I;
typedef Vector_t<float> Vector3F;
typedef Vector_t<double> Vector3D;

typedef Vector3F Vector3;


template <class T>
Vector_t<T>::Vector_t() {
	x = 0;
	y = 0;
	z = 0;
}

template <class T>
Vector_t<T>::Vector_t(T xx, T yy) {
	x = xx;
	y = yy;
	z = 0;
}

template <class T>
Vector_t<T>::Vector_t(T xx, T yy, T zz) {
	x = xx;
	y = yy;
	z = zz;
}

template <class T>
const T Vector_t<T>::calculateDirection(const Vector_t<T>& other) const {
	
	Vector_t<T> direction = *this - other;
	Vector_t<T> distance = sqrt(direction.x * direction.x + direction.y * direction.y);
	direction /= distance; 

	return direction;
}

template <class T>
const T Vector_t<T>::calculateDistance(const Vector_t<T>& other) const {

	Vector_t<T> direction = *this - other;
	Vector_t<T> distance = sqrt(direction.x * direction.x + direction.y * direction.y);

	return distance;
}

template <class T>
Vector_t<T>::~Vector_t() {

}

template <class T>
Vector_t<T>& Vector_t<T>::operator+=(const Vector_t<T>& rhs) {
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

template <class T>
Vector_t<T> Vector_t<T>::operator+(const Vector_t<T>& rhs) const {
	return Vector_t<T>(x + rhs.x, y + rhs.y, z + rhs.z);
}

template <class T>
Vector_t<T>& Vector_t<T>::operator-=(const Vector_t<T>& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

template <class T>
Vector_t<T> Vector_t<T>::operator-(const Vector_t<T>& rhs) const {
	return Vector_t<T>(x + -rhs.x, y - rhs.y, z - rhs.z);
}

template <class T>
Vector_t<T>& Vector_t<T>::operator*=(const Vector_t<T>& rhs) {
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;
	return *this;
}

template <class T>
Vector_t<T> Vector_t<T>::operator*(const Vector_t<T>& rhs) const {
	return Vector_t<T>(x * rhs.x, y * rhs.y, z * rhs.z);
}

template <class T>
Vector_t<T>& Vector_t<T>::operator/=(const Vector_t<T>& rhs)
{
	// TODO: check for division by 0?
	x /= rhs.x;
	y /= rhs.y;
	z /= rhs.z;
	return *this;
}

template <class T>
Vector_t<T> Vector_t<T>::operator/(const Vector_t<T>& rhs) const {
	// TODO: check for division by 0?
	return Vector_t<T>(x / rhs.x, y / rhs.y, z / rhs.z);
}

template <class T>
Vector_t<T>& Vector_t<T>::operator+=(const T rhs) {
	x += rhs;
	y += rhs;
	z += rhs;
	return *this;
}

template <class T>
Vector_t<T> Vector_t<T>::operator+(const T rhs) const {
	return Vector_t<T>(x + rhs, y + rhs, z + rhs);
}

template <class T>
Vector_t<T>& Vector_t<T>::operator-=(const T rhs) {
	x -= rhs;
	y -= rhs;
	z -= rhs;
	return *this;
}

template <class T>
Vector_t<T> Vector_t<T>::operator-(const T rhs) const {
	return Vector_t<T>(x - rhs, y - rhs, z - rhs);
}

template <class T>
Vector_t<T>& Vector_t<T>::operator*=(const T rhs) {
	x *= rhs;
	y *= rhs;
	z *= rhs;
	return *this;
}

template <class T>
Vector_t<T> Vector_t<T>::operator*(const T rhs) const {
	return Vector_t<T>(x * rhs, y * rhs, z * rhs);
}

template <class T>
Vector_t<T>& Vector_t<T>::operator/=(const T rhs) {
	// TODO: check for division by 0?
	x /= rhs;
	y /= rhs;
	z /= rhs;
	return *this;
}

template <class T>
Vector_t<T> Vector_t<T>::operator/(const T rhs) const {
	// TODO: check for division by 0?
	return Vector_t<T>(x / rhs, y / rhs, z / rhs);
}

template <class T>
bool Vector_t<T>::operator==(const Vector_t<T>& other) const {
	return (x == other.x && y == other.y && z == other.z);
}

template <class T>
bool Vector_t<T>::operator!=(const Vector_t<T>& other) const {
	return !(*this == other);
}


template <class T>
std::ostream& operator<<(std::ostream& stream, Vector_t<T> ob) {
	stream << "(" << ob.x << ", " << ob.y << ", " << ob.z << ")";
	return stream;
}

template <class T>
std::istream& operator>>(std::istream& stream, Vector_t<T>& ob) {
	stream >> ob.x >> ob.y >> ob.z;
	return stream;
}

#endif
