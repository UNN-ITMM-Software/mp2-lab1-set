#include "AdditionalFunctions.h"

size_t mylog2(size_t n)
{
	if (n == 0)
		throw std::logic_error("n must be > 0");
	size_t ret = 0;
	while (n > 1)
	{
		n >>= 1;
		ret++;
	}
	return ret;
}
