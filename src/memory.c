#include "memory.h"

u32_t u32_lowest_bit(u32_t inValue)
{
	u32_t result = 0;

	if ((inValue & 0xFFFF) == 0)
	{
		result += 16;
		inValue >>= 16;
	}

	if ((inValue & 0xFF) == 0)
	{
		result += 8;
		inValue >>= 8;
	}

	if ((inValue & 0xF) == 0)
	{
		result += 4;
		inValue >>= 4;
	}

	if ((inValue & 0x3) == 0)
	{
		result += 2;
		inValue >>= 2;
	}

	result += ((~inValue) & 0x1);

	return result;
}

u32_t u32_highest_bit(u32_t inValue)
{
	u32_t result = 0;

	if ((inValue & 0xFFFF0000) == 0)
	{
		result += 16;
		inValue <<= 16;
	}
	if ((inValue & 0xFF000000) == 0)
	{
		result += 8;
		inValue <<= 8;
	}
	if ((inValue & 0xF0000000) == 0)
	{
		result += 4;
		inValue <<= 4;
	}
	if ((inValue & 0xC0000000) == 0)
	{
		result += 2;
		inValue <<= 2;
	}

	result += ((~inValue) & 0x80000000) != 0;

	return 31 - result;
}
