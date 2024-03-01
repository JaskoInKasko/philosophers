#include "philo.h"

long int	timestamp(void)
{
	struct timeval tv;
    if (gettimeofday(&tv, NULL) == -1)
		return (-1);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_print_message(char *str, t_philo *philo)
{
	long int	time;
	time = timestamp() - philo->info->simultion_start;
	if (ft_strcmp(str, "is eating") == 0)
		philo->time_last_eat = timestamp();
	pthread_mutex_lock(&philo->info->write);
	printf("%ld %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->info->write);
}

int	ft_usleep(int ms, t_philo *philo)
{
	long int	time;
	time = timestamp();
	while (timestamp() - time < ms)
	{
		if ((timestamp() - philo->time_last_eat) >= philo->info->time_to_die)
		{
			printf("ID: %d %ld\n", philo->id, (timestamp() - philo->time_last_eat));
			ft_print_message(DIED, philo);
			philo->info->is_dead = 1;
			return (0);
		}
		usleep(ms / 10);
	}
	return (1);
}
