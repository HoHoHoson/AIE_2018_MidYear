#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

namespace HLib
{
	template<typename T, typename Y, typename P>
	static T clamp(const T& value, const Y& min, const P& max)
	{
		T temp = value;
		if (value < min)
			temp = min;
		if (value > max)
			temp = max;
		return temp;
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

	static float toRadian(float degrees)
	{
		return (degrees * (M_PI / 180));
	}
}