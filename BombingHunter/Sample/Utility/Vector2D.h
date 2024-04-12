#pragma once

class Vector2D
{
public:
	float x;
	float y;

public:
	Vector2D();
	Vector2D(float scalar);
	Vector2D(float mx, float my);
	~Vector2D();

public:
	Vector2D& operator = (const Vector2D& location);
	
	//â¡éZ
	const Vector2D operator + (const Vector2D& location) const;
	Vector2D& operator += (const Vector2D& location);

	//å∏éZ
	const Vector2D operator - (const Vector2D& location) const;
	Vector2D& operator -= (const Vector2D& location);

	//èÊéZ
	const Vector2D operator * (const float& scalar) const;
	const Vector2D operator * (const Vector2D& location) const;
	
	Vector2D& operator *= (const float& scalar);
	Vector2D& operator *= (const Vector2D& location);

	//èúéZ
	const Vector2D operator / (const float& scalar) const;
	const Vector2D operator / (const Vector2D& location) const;

	Vector2D& operator /= (const float& scalar);
	Vector2D& operator /= (const Vector2D& location);

	void ToInt(int* x, int* y) const;

};