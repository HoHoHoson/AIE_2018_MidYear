#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

namespace HLib
{
	template<typename T, typename Y, typename P>
	static void clamp(T& value, const Y& min, const P& max)
	{
		T temp = value;
		if (value < min)
			temp = (T)min;
		if (value > max)
			temp = (T)max;
		value = temp;
	}

	template<typename T>
	static void bubbleSort(T * arrayOfValues, int numValues)
	{
		bool isSwapped;
		do
		{
			isSwapped = false;
			for (int i = 0; i < numValues - 1; ++i)
			{
				T temp;
				if (arrayOfValues[i] < arrayOfValues[i + 1])
				{
					temp = arrayOfValues[i];
					arrayOfValues[i] = arrayOfValues[i + 1];
					arrayOfValues[i + 1] = temp;
					isSwapped = true;
				}
			}
		} while (isSwapped);
	}

	template<typename T>
	static T roundTo(const T& value, unsigned int decimalPlaces = 0)
	{
		T rounded;
		int pow10 = (int)pow(10, decimalPlaces + 1);
		int integer = (int)(value * pow10);
		int remainder = integer % 10;

		if (remainder == 0)
		{
			rounded = (T)(integer / pow10);
			return rounded;
		}

		if (remainder < 0)
			if (remainder > -5)
				integer -= remainder;
			else
				integer += (-10 - remainder);
		else
			if (remainder < 5)
				integer -= remainder;
			else
				integer += (10 - remainder);

		rounded = (T)integer;
		return rounded / pow10;
	}

	static float toRadian(float degrees)
	{
		return (float)(degrees * (M_PI / 180));
	}

	static float toDegrees(float radians)
	{
		return (float)(radians / (M_PI / 180));
	}

	template<typename T, typename Y>
	static float MagPow2_2D(const T& v1, const Y& v2)
	{
		float x = v1[0] - v2[0]; 
		float y = v1[1] - v2[1];

		float magPow2 = powf(x, 2) + powf(y, 2);

		return magPow2;
	}
	template<typename T>
	static float MagPow2_2D(const T& v)
	{
		return powf(v[0], 2) + powf(v[1], 2);
	}
}