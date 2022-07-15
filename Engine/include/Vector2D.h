#pragma once

#include <iostream>
#include <vector>
#include <math.h>

class Vector2D
{
private:
	float _x = 0.0f;
	float _y = 0.0f;
	//Vector2D _normalized;
public:
	Vector2D(float, float);
	Vector2D() = default;
	//~Vector2D();

	float SqrMagnitude() const;
	float Magnitude() const;
	Vector2D Normalized() const;
	float Distance(Vector2D vector2);

	Vector2D ReturnClosestPoint(std::vector<Vector2D>);
	Vector2D OrthoRight();
	Vector2D OrthoLeft();

	//OPERATORS
	Vector2D operator+(const Vector2D) const;
	Vector2D operator-(const Vector2D);
	Vector2D operator-();

	Vector2D operator+=(const Vector2D);
	Vector2D operator-=(const Vector2D);

	Vector2D operator*(const float);
	Vector2D operator/(const float);

	bool operator>(const Vector2D);
	bool operator<(const Vector2D);

	Vector2D Rotate(float radiant);


	//GET SET
	float X() { return _x; }
	float Y() { return _y; }
	void SetX(float x) { this->_x = x; }
	void SetY(float y) { this->_y = y; }
	void SetValues(float x, float y);
};