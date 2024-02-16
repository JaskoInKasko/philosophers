#include <sys/time.h>

int main(void)
{
    struct timeval i;
    struct timezone j;

    gettimeofday(&i, &j);
    printf("Seconds since 1/1/1970: %lu\n",i.tv_sec);
    printf("Microseconds: %ld\n",i.tv_usec);
    printf("Minutes west of Greenwich: %d\n",j.tz_minuteswest);
    printf("Daylight Saving Time adjustment: %d\n",j.tz_dsttime);
    return (0);
}
