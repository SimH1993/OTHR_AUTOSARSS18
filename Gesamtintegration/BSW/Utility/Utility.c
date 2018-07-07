//System includes
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h" 

//User includes
#include "Utility.h"


//Public functions
void *memcpy(void *dest, const void *src, U32 len)
{
	U8 *d = dest;
	const U8 *s = src;
	
	while (len--)
		*d++ = *s++;

	return dest;
}

int memcmp(const void *str1, const void *str2, U32 count)
{
	const U8 *s1 = (const U8*)str1;
	const U8 *s2 = (const U8*)str2;

	while (count-- > 0)
	{
		if (*s1++ != *s2++)
			return s1[-1] < s2[-1] ? -1 : 1;
	}
	
	return 0;
}
