#pragma once

struct Vector2
{
	float x, y;

	// 
	// Constructors
	// 

	Vector2()
	{
		x = 0.0f;
		y = 0.0f;
	}

	Vector2(const Vector2& vec)
	{
		x = vec.x;
		y = vec.y;
	}

	template <typename T>
	Vector2(const T val_x, const T val_y)
	{
		x = val_x;
		y = val_y;
	}

	//
	// Functions
	//

	void NormalizeAngles()
	{
		while (y > 180.0f)
			y -= 360.0f;
		while (y < -180.0f)
			y += 360.0f;
		if (x > 89.0f)
			x = 89.0f;
		if (x < -89.0f)
			x = -89.0f;
	}

	void ClampAngles()
	{
		if (x < -180.0f)
			x += 360.0f;
		if (x > 180.0f)
			x -= 360.0f;
		if (y < -180.0f)
			y += 360.0f;
		if (y > 180.0f)
			y -= 360.0f;
		if (x > 89.0f && x <= 180.0f)
			x = 89.0f;
	}

	void Zero()
	{
		x = y = 0.0f;
	}

	//
	// Operators
	//

	Vector2& operator=(const Vector2& vec)
	{
		x = vec.x;
		y = vec.y;
		return *this;
	}

	Vector2 operator+(const Vector2& vec)
	{
		return Vector2(x + vec.x, y + vec.y);
	}

	Vector2& operator+=(const Vector2& vec)
	{
		x += vec.x;
		y += vec.y;
		return *this;
	}

	Vector2 operator-(const Vector2& vec)
	{
		return Vector2(x - vec.x, y - vec.y);
	}

	Vector2& operator-=(const Vector2& vec)
	{
		x -= vec.x;
		y -= vec.y;
		return *this;
	}

	template <typename T>
	Vector2 operator*(const T val)
	{
		return Vector2(x * val, y * val);
	}

	template <typename T>
	Vector2& operator*=(const T val)
	{
		x *= val;
		y *= val;
		return *this;
	}

	template <typename T>
	Vector2 operator/(const T val)
	{
		return Vector2(x / val, y / val);
	}

	template <typename T>
	Vector2& operator/=(const T val)
	{
		x /= val;
		y /= val;
		return *this;
	}
};