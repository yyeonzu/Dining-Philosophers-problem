#include "philosopher.h"

int get_time()
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

void a_few_moments_later(int end_time)
{
	while (end_time > get_time())
	{
		usleep(100);
	}
}