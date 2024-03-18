#include "philo.h"

long int	timestamp(void)
{
	struct timeval tv;

    gettimeofday(&tv, NULL);
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
		pthread_mutex_unlock(&philo->info->write);
		return ;
	}
	if (ft_strcmp(str, "died") == 0)
		philo->info->is_dead = 1;
	printf("%ld %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->info->write);
}

void	ft_usleep(int ms, t_philo *philo)
{
	long int	time;

	time = timestamp();
	while (timestamp() - time < ms)
	{
		if (ft_dead_philo(philo) == 0)
			return ;
		usleep(ms / 10);
	}
}

void	ft_print_error(int n)
{
	printf("ERROR:\n");
	if (n == 0)
	{
		printf("All arguments need to be a positive integer <= INT_MAX\n");
		printf("Philosophers <= 200\neat_time >= 60\nsleep_time >= 60\n");
		printf("[OPTIONAL ARGUMENT]times_to_eat\n");
	}
	if (n == 1)
		printf("malloc() failed!\n");
	if (n == 2)
		printf("pthread_create() failed!\n");
	if (n == 3)
		printf("pthread_join() failed!\n");
}
void	ft_data_clean(t_data *data)
{
	int	i;

	i = -1;
	free(data->philos);
	while(++i < data->philo_num)
		pthread_mutex_destroy(&data->m_fork[i]);
	pthread_mutex_destroy(&data->write);
	free(data->m_fork);
}