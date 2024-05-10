#pragma once

namespace Flow::Binary
{

	// Used for getting the size of an object in binary files
	template<typename T>
	inline size_t SizeOf(T value = T())
	{
		return sizeof(T);
	}

	template<>
	inline size_t SizeOf<std::string>(std::string value)
	{
		return sizeof(int32_t) + value.size();
	}

}