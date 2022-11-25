#pragma once

#include <iostream>

struct Vector3
{
	float x, y, z;

	// 
	// Constructors
	// 

	Vector3()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	Vector3(const Vector3& vec)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
	}

	template <typename T>
	Vector3(const T val_x, const T val_y, const T val_z)
	{
		x = val_x;
		y = val_y;
		z = val_z;
	}

	//
	// Functions
	//

	Vector3 to(const Vector3& vec)
	{
		return Vector3(vec.x - x, vec.y - y, vec.z - z);
	}

	float mag()
	{
		return static_cast<float>(std::sqrt(x * x + y * y + z * z));
	}

	//
	// Operators
	//

	Vector3& operator=(const Vector3& vec)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
		return *this;
	}

	Vector3 operator+(const Vector3& vec)
	{
		return Vector3(x + vec.x, y + vec.y, z + vec.z);
	}

	Vector3& operator+=(const Vector3& vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;
		return *this;
	}

	Vector3 operator-(const Vector3& vec)
	{
		return Vector3(x - vec.x, y - vec.y, z - vec.z);
	}

	Vector3& operator-=(const Vector3& vec)
	{
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		return *this;
	}

	template <typename T>
	Vector3 operator*(const T val)
	{
		return Vector3(x * val, y * val, z * val);
	}

	template <typename T>
	Vector3& operator*=(const T val)
	{
		x *= val;
		y *= val;
		z *= val;
		return *this;
	}

	template <typename T>
	Vector3 operator/(const T val)
	{
		return Vector3(x / val, y / val, z / val);
	}

	template <typename T>
	Vector3& operator/=(const T val)
	{
		x /= val;
		y /= val;
		z /= val;
		return *this;
	}
};