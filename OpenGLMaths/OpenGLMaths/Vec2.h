#pragma once
#include <math.h>

class Vec2 {

public:

	union {
		float data[2];
		struct {
			float x;
			float y;
		};
	};

	// Constructors

	// Vectors default to 0, 0, 0.
	Vec2() {
		x = 0;
		y = 0;
	}

	// Construct with values, 3D
	Vec2(float ax, float ay, float az) {
		x = ax;
		y = ay;
	}

	// Construct with values, 2D
	Vec2(float ax, float ay) {
		x = ax;
		y = ay;
	}

	// Copy constructor
	Vec2(const Vec2& o) {
		x = o.x;
		y = o.y;
	}

	// Addition

	Vec2 operator+(const Vec2& o) {
		return Vec2(x + o.x, y + o.y);
	}

	Vec2& operator+=(const Vec2& o) {
		x += o.x;
		y += o.y;
		return *this;
	}

	// Subtraction

	Vec2 operator-() {
		return Vec2(-x, -y);
	}

	Vec2 operator-(const Vec2 o) {
		return Vec2(x - o.x, y - o.y);
	}

	Vec2& operator-=(const Vec2 o) {
		x -= o.x;
		y -= o.y;
		return *this;
	}

	// Multiplication by scalars

	Vec2 operator*(const float s) {
		return Vec2(x * s, y * s);
	}

	Vec2& operator*=(const float s) {
		x *= s;
		y *= s;
		return *this;
	}

	// Division by scalars

	Vec2 operator/(const float s) {
		return Vec2(x / s, y / s);
	}

	Vec2& operator/=(const float s) {
		x /= s;
		y /= s;
		return *this;
	}

	// Dot product

	float operator*(const Vec2 o) {
		return (x * o.x) + (y * o.y);
	}

	// An in-place dot product does not exist because
	// the result is not a vector.


	// Length of vector
	float magnitude() {
		return sqrt(magnitude_sqr());
	}

	// Length of vector squared
	float magnitude_sqr() {
		return (x * x) + (y * y);
	}

	// Returns a normalised copy of the vector
	// Will break if it's length is 0
	Vec2 normalised() {
		return Vec2(*this) / magnitude();
	}

	// Modified the vector so it becomes normalised
	Vec2& normalise() {
		(*this) /= magnitude();
		return *this;
	}

	float dot(Vec2 b) {
		return (*this).x * b.x + (*this).y * b.y;
	}
};