#include "Vector2D.h"

Vector2D::Vector2D(const float x, const float y) : x_(x), y_(y)
{
}

Vector2D::Vector2D(const int x, const int y)
{
	x_ = static_cast<float>(x);
	y_ = static_cast<float>(y);
}

float Vector2D::SqrMagnitude() const
{
	return x_ * x_ + y_ * y_;
}

float Vector2D::Magnitude() const
{
	return std::sqrt(SqrMagnitude());
}

Vector2D Vector2D::Normalized() const
{
	Vector2D NormVec(0, 0);
	NormVec.x_ = this->x_ / this->Magnitude();
	NormVec.y_ = this->y_ / this->Magnitude();
	return NormVec;

}

float Vector2D::Distance(const Vector2D vector2) const
{
	return std::sqrt(std::pow(x_ - vector2.X(), 2.0f) + std::pow(y_ - vector2.Y(), 2.0f));

}

Vector2D Vector2D::ReturnClosestPoint(const std::vector<Vector2D>& vectorVector2d) const
{
	Vector2D ClosestPoint;
	for (const auto ThisPoint : vectorVector2d)
	{

		if (this->Distance(ThisPoint) < std::numeric_limits<float>::max())
			ClosestPoint = ThisPoint;
	}
	return ClosestPoint;
}

Vector2D Vector2D::OrthoRight() const
{
	return this->Rotate(3.0f * 3.1415f / 2.0f);
}

Vector2D Vector2D::OrthoLeft() const
{
	return this->Rotate(3.1415f / 2.0f);
}



#pragma region OPERATORS
Vector2D Vector2D::operator+(const Vector2D vec) const
{
	return {this->x_ + vec.x_, this->y_ + vec.y_};
}

Vector2D Vector2D::operator-(const Vector2D vec) const
{
	return {this->x_ - vec.x_, this->y_ - vec.y_};
}

Vector2D Vector2D::operator-() const
{
	return {-this->x_, -this->y_};
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
Vector2D Vector2D::operator* (const float flt) const
{
	return {this->x_ * flt, this->y_ * flt};
}

Vector2D Vector2D::operator/ (const float flt) const
{
	return {this->x_ / flt, this->y_ / flt};
}

bool Vector2D::operator>(const Vector2D vec) const
{
	const float first = this->SqrMagnitude();
	const float second = vec.SqrMagnitude();

	return first > second;
}

bool Vector2D::operator<(const Vector2D vec) const
{
	const float first = this->SqrMagnitude();
	const float second = vec.SqrMagnitude();

	return first < second;
}

Vector2D Vector2D::Rotate(const float radiant) const
{
	return {
		this->X() * std::cos(radiant) - this->Y() * sin(radiant),
		this->X() * sin(radiant) + this->Y() * cos(radiant)
	};
}
#pragma endregion

void Vector2D::SetValues(const float x, const float y)
{
	this->x_ = x;
	this->y_ = y;
}
