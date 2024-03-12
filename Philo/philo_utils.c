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
	pthread_mutex_lock(&philo->info->write);
	time = timestamp() - philo->info->simulation_start;
	if (ft_strcmp(str, "is eating") == 0)
		philo->time_last_eat = timestamp();
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

void	check_philo(t_data *data)
{
	int	i;

	i = 0;
	while (1)
	{
		if (data->philos[i].times_has_eaten == data->time_must_eat)
			return ;
		if ((timestamp() - data->philos[i].time_last_eat) >= data->time_to_die)
		{
			ft_print_message(DIED, &data->philos[i]);
			return ;
		}
		i++;
		i %= data->philo_num;
	}
}

void	ft_usleep(int ms, t_philo *philo)
{
	long int	time;

	(void)philo; //remove later
	time = timestamp();
	while (timestamp() - time < ms)
		usleep(ms / 10);
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
	while(++i < data->philo_num)
		pthread_mutex_destroy(&data->m_fork[i]);
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->eating);
	free(data->m_fork);
}