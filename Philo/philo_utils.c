#include "philo.h"

long int	ft_atol(const char *nptr)
{
	long int	res;
	int			nb;

	nb = 1;
	while (*nptr != '\0' && ((*nptr == ' ') || (*nptr >= 9 && *nptr <= 13)))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			nb = nb * (-1);
		nptr++;
	}
	res = 0;
	while (*nptr != '\0' && (*nptr >= '0' && *nptr <= '9'))
	{
		res = res * 10 + *nptr - 48;
		nptr++;
	}
	res = res * nb;
	return (res);
}

long int	timestamp(void)
{
	struct timeval current_time;
    if (gettimeofday(&current_time, NULL) == -1)
		return (-1);
    return (current_time.tv_sec * 1000);
}

/*long int	ft_get_time()
{

}*/
