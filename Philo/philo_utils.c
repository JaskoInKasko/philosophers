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
	time = timestamp() - philo->info->simulation_start;
	if (ft_strcmp(str, "is eating") == 0)
		philo->time_last_eat = timestamp();
	pthread_mutex_lock(&philo->info->write);
	if (philo->info->is_dead == 1)
	{
		ft_philo_clean(philo, 1);
		return ;
	}
	if (ft_strcmp(str, "died") == 0)
	{
		philo->info->is_dead = 1;
		ft_philo_clean(philo, 1);
	}
	printf("%ld %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->info->write);
}

int	ft_monitoring_usleep(int ms, t_philo *philo)
{
	long int	time;

	time = timestamp();
	if ((timestamp() - philo->time_last_eat) >= philo->info->time_to_die)
	{
		ft_print_message(DIED, philo);
		return (0);
	}
	while (timestamp() - time < ms)
	{
		if ((timestamp() - philo->time_last_eat) >= philo->info->time_to_die)
		{
			ft_print_message(DIED, philo);
			return (0);
		}
		usleep(ms / 10);
	}
	return (1);
}

void	ft_philo_clean(t_philo *philo, int n)
{
	if (n == 0)
	{
		pthread_mutex_unlock(&philo->info->m_fork[philo->r_fork]);
		pthread_mutex_unlock(&philo->info->m_fork[philo->l_fork]);
	}
	if (n == 1)
		pthread_mutex_unlock(&philo->info->write);
}

void	ft_data_clean(t_data *data)
{
	int	i;

	i = -1;
	free(data->philos);
	while(++i < data->philo_num + 1)
		pthread_mutex_destroy(&data->m_fork[i]);
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->eating);
	free(data->m_fork);
}