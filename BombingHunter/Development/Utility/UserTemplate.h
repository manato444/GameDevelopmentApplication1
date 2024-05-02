#pragma once

/******************************************
* 関数テンプレート
* あらゆる型に対して適応できるコード
*******************************************/

template <typename T>
T Abs(T value)
{
	T result;

	if (value > 0)
	{
		result = value;
	}
	else
	{
		result = -value;
	}

	return result;
}

template <typename T>
T Max(T a, T b)
{
	T result;

	if (a < b)
	{
		result = b;
	}
	else
	{
		result = a;
	}

	return result;
}

template <typename T>
T Min(T a, T b)
{
	T result;
	if (a > b)
	{
		result = b;
	}
	else
	{
		result = a;
	}

	return result;
}
