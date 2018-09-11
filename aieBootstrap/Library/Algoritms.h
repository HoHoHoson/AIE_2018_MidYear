#pragma once

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
}