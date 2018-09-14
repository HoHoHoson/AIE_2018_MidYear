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
			temp = min;
		if (value > max)
			temp = max;
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
		int pow10 = pow(10, decimalPlaces + 1);
		int integer = value * pow10;
		int remainder = integer % 10;

		if (remainder == 0)
		{
			rounded = integer / pow10;
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

		rounded = integer; 
		return rounded / pow10;
	}

	static float toRadian(float degrees)
	{
		return (degrees * (M_PI / 180));
	}
}