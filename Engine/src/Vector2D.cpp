#include "Vector2D.h"

Vector2D::Vector2D(float x, float y) : _x(x), _y(y)
{
}

float Vector2D::SqrMagnitude() const
{
	return _x * _x + _y * _y;
}

float Vector2D::Magnitude() const
{
	return std::sqrt(SqrMagnitude());
}

Vector2D Vector2D::Normalized() const
{
	Vector2D NormVec(0, 0);
	NormVec._x = this->_x / this->Magnitude();
	NormVec._y = this->_y / this->Magnitude();
	return NormVec;

}

float Vector2D::Distance(Vector2D vector2)
{
	return std::sqrt(std::pow(_x - vector2.X(), 2.0f) + std::pow(_y - vector2.Y(), 2.0f));

}

Vector2D Vector2D::ReturnClosestPoint(std::vector<Vector2D> vectorVector2d)
{
	float closest = std::numeric_limits<float>::max();
	Vector2D closestPoint;
	for (auto thisPoint : vectorVector2d)
	{

		if (this->Distance(thisPoint) < closest)
			closestPoint = thisPoint;
	}
	return closestPoint;
}

Vector2D Vector2D::OrthoRight()
{
	return this->Rotate(3.0f * 3.1415f / 2.0f);
}

Vector2D Vector2D::OrthoLeft()
{
	return this->Rotate(3.1415f / 2.0f);
}


/*{[REGION OPERATORS]}*/
#pragma region OPERATORS
Vector2D Vector2D::operator+(const Vector2D vec) const
{
	return {this->_x + vec._x, this->_y + vec._y};
}

Vector2D Vector2D::operator-(const Vector2D vec)
{
	return {this->_x - vec._x, this->_y - vec._y};
}

Vector2D Vector2D::operator-()
{
	return {-this->_x, -this->_y};
}

Vector2D Vector2D::operator+=(const Vector2D vec)
{
	*this = *this + vec;
	return (*this);
}

Vector2D Vector2D::operator-=(const Vector2D vec)
{
	*this = *this - vec;
	return (*this);
}

/*[FLOATS OP]*/
Vector2D Vector2D::operator* (const float flt)
{
	return {this->_x * flt, this->_y * flt};
}

Vector2D Vector2D::operator/ (const float flt)
{
	return {this->_x / flt, this->_y / flt};
}

bool Vector2D::operator>(const Vector2D vec)
{
	const float first = this->SqrMagnitude();
	const float second = vec.SqrMagnitude();

	return first > second;
}

bool Vector2D::operator<(const Vector2D vec)
{
	const float first = this->SqrMagnitude();
	const float second = vec.SqrMagnitude();

	return first < second;
}

Vector2D Vector2D::Rotate(float radiant)
{
	return {
		this->X() * std::cos(radiant) - this->Y() * sin(radiant),
		this->X() * sin(radiant) + this->Y() * cos(radiant)
	};
}
#pragma endregion

void Vector2D::SetValues(float x, float y)
{
	this->_x = x;
	this->_y = y;
}
