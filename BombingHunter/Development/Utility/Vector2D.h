#pragma once

//�񎟌��x�N�g���N���X
class Vector2D
{
public:
	float x;	//X���W
	float y;	//Y���W

public:
	Vector2D();
	Vector2D(float scalar);
	Vector2D(float mx, float my);
	~Vector2D();



public:
	Vector2D& operator = (const Vector2D& location);

	//���Z
	const Vector2D operator + (const Vector2D& location) const;
	Vector2D& operator += (const Vector2D& location);

	//���Z
	const Vector2D operator - (const Vector2D& location) const;
	Vector2D& operator -= (const Vector2D& location);

	//��Z
	const Vector2D operator * (const float& scalar) const;
	const Vector2D operator * (const Vector2D& location) const;

	Vector2D& operator *= (const float& scalar);
	Vector2D& operator *= (const Vector2D& location);

	//���Z
	const Vector2D operator / (const float& scalar) const;
	const Vector2D operator / (const Vector2D& location) const;

	Vector2D& operator /= (const float& scalar);
	Vector2D& operator /= (const Vector2D& location);

	void ToInt(int* x, int* y) const;

};