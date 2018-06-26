void *memcpy(void *dest, const void *src, U32 len);
int memcmp(const void *str1, const void *str2, U32 count);
char *strcpy(char *dest, const char *src);
char *strcat(char *dest, const char *src);

static inline int clamp(int x, int low, int high)
{
	if(x < low)
		return low;
	if(x > high)
		return high;
	
	return x;
}

static inline int min(int x, int y)
{
	if(x < y)
		return x;
	
	return y;
}

static inline int max(int x, int y)
{
	if(x > y)
		return x;
	
	return y;
}

static inline int abs(int x)
{
	if(x < 0)
		return x*-1;
	
	return x;
}