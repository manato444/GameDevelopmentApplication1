#pragma once

//二次元ベクトルクラス
class Vector2D
{
public:
	float x;	//X座標
	float y;	//Y座標

public:
	Vector2D();
	Vector2D(float scalar);
	Vector2D(float mx, float my);
	~Vector2D();



public:
	Vector2D& operator = (const Vector2D& location);

	//加算
	const Vector2D operator + (const Vector2D& location) const;
	Vector2D& operator += (const Vector2D& location);

	//減算
	const Vector2D operator - (const Vector2D& location) const;
	Vector2D& operator -= (const Vector2D& location);

	//乗算
	const Vector2D operator * (const float& scalar) const;
	const Vector2D operator * (const Vector2D& location) const;

	Vector2D& operator *= (const float& scalar);
	Vector2D& operator *= (const Vector2D& location);

	//除算
	const Vector2D operator / (const float& scalar) const;
	const Vector2D operator / (const Vector2D& location) const;

	Vector2D& operator /= (const float& scalar);
	Vector2D& operator /= (const Vector2D& location);

	void ToInt(int* x, int* y) const;

};