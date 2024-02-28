#include "philo.h"

size_t	ft_strlen(const char *str)
{
	int	c;

	c = 0;
	if (str == NULL)
		return (0);
	while (str[c] != '\0')
		c++;
	return (c);
}

long int	ft_atol(const char *nptr)
{
	long int	res;
	int			nb;

	nb = 1;
	if (ft_strlen(nptr) > 10)
		return (-1);
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
		if ((res * nb) < -2147483648 || (res > 2147483647 && nb == 1))
			return (-1);
		nptr++;
	}
	res = res * nb;
	return (res);
}

long int	timestamp(void)
{
	struct timeval tv;
    if (gettimeofday(&tv, NULL) == -1)
		return (-1);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_print_message(char *str, t_philo *philo)
{
	philo->time_last_eat = timestamp() - philo->info->simultion_start;
	pthread_mutex_lock(&philo->info->write);
	printf("%ld %d %s\n", philo->time_last_eat, philo->id, str);
	pthread_mutex_unlock(&philo->info->write);
}

void	ft_usleep(int ms)
{
	long int	time;

	time = timestamp();
	while (timestamp() - time < ms)
		usleep(ms / 10);
}
