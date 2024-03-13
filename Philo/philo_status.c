#include "philo.h"

int    ft_finnished_philo(t_philo *philo)
{
    pthread_mutex_lock(&philo->info->write);
    if(philo->times_has_eaten == philo->info->time_must_eat)
    {
        pthread_mutex_unlock(&philo->info->write);
        return (0);
    }
    pthread_mutex_unlock(&philo->info->write);
    return (1);
}

int ft_dead_philo(t_philo *philo)
{
    pthread_mutex_lock(&philo->info->write);
	if (philo->info->is_dead == 1)
	{
		pthread_mutex_unlock(&philo->info->write);
		return (0);
	}
    if (timestamp() - philo->time_last_eat > philo->info->time_to_die)
    {
        pthread_mutex_unlock(&philo->info->write);
        return (0);
    }
    pthread_mutex_unlock(&philo->info->write);
    return (1);
}

void	check_philo(t_data *data)
{
	int	i;
	int	ph_n;

	i = 0;
	ph_n = data->philo_num;
	while (1)
	{
		if (ft_finnished_philo(&data->philos[i]) == 0)
			return ;
		if (ft_dead_philo(&data->philos[i]) == 0)
		{
			ft_print_message(DIED, &data->philos[i]);
			return ;
		}
		i++;
		i %= ph_n;
	}
}