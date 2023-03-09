#pragma once

#include <iostream>
#include <vector>

class Vector2D
{
private:
	float x_ = 0.0f;
	float y_ = 0.0f;
public:
	Vector2D(float, float);
	Vector2D(const int, const int);

	Vector2D() = default;
	//~Vector2D();

	[[nodiscard]] float SqrMagnitude() const;
	[[nodiscard]] float Magnitude() const;
	[[nodiscard]] Vector2D Normalized() const;
	[[nodiscard]] float Distance(Vector2D vector2) const;

	[[nodiscard]] Vector2D ReturnClosestPoint(const std::vector<Vector2D>&) const;
	[[nodiscard]] Vector2D OrthoRight() const;
	[[nodiscard]] Vector2D OrthoLeft() const;

	//OPERATORS
	Vector2D operator+(const Vector2D) const;
	Vector2D operator-(const Vector2D) const;
	Vector2D operator-() const;

	Vector2D operator+=(const Vector2D);
	Vector2D operator-=(const Vector2D);

	Vector2D operator*(const float) const;
	Vector2D operator/(const float) const;

	bool operator>(const Vector2D) const;
	bool operator<(const Vector2D) const;

	[[nodiscard]] Vector2D Rotate(float radiant) const;


	//GET SET
	[[nodiscard]] float X() const { return x_; }
	[[nodiscard]] float Y() const { return y_; }
	void SetX(const float x) { this->x_ = x; }
	void SetY(const float y) { this->y_ = y; }
	void SetValues(float x, float y);
};