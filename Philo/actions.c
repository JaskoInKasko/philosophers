#include "philo.h"

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->m_fork[philo->r_fork]);
	pthread_mutex_lock(&philo->info->m_fork[philo->l_fork]);
	ft_print_message(TAKE_FORKS, philo);
	ft_print_message(TAKE_FORKS, philo);
	ft_print_message(EATING, philo);
	if (ft_monitoring_usleep(philo->info->time_to_eat, philo) == 0)
		return ;
	pthread_mutex_lock(&philo->info->eating);
	philo->times_has_eaten++;
	pthread_mutex_unlock(&philo->info->eating);
	pthread_mutex_unlock(&philo->info->m_fork[philo->r_fork]);
	pthread_mutex_unlock(&philo->info->m_fork[philo->l_fork]);
}

void	ft_sleep(t_philo *philo)
{
	if (philo->info->is_dead == 1)
		return ;
	ft_print_message(SLEEPING, philo);
	if (philo->times_has_eaten != philo->info->time_must_eat)
		if (ft_monitoring_usleep(philo->info->time_to_sleep, philo) == 0)
			return ;
}

void	ft_think(t_philo *philo)
{
	ft_print_message(THINKING, philo);
	if (philo->info->philo_num % 2 == 0)
	{
		philo->time_to_think = philo->info->time_to_eat - philo->info->time_to_sleep;
		ft_monitoring_usleep(philo->time_to_think, philo);
	}
	else
	{
		philo->time_to_think = (philo->info->time_to_eat * 2) - philo->info->time_to_sleep;
		if (philo->time_to_think < 0)
			philo->time_to_think = 0;
		ft_monitoring_usleep(philo->time_to_think * 0.42, philo);
	}
}

void	*routine(void *args)
{
	t_philo *philo;

	philo = (t_philo *) args;
	if (philo->id % 2 != 0)
		ft_monitoring_usleep(42, philo);
	while(philo->times_has_eaten != philo->info->time_must_eat
		&& philo->info->is_dead != 1)
	{
		if (philo->id % 2 != 1)
		{
			ft_eat(philo);
			ft_sleep(philo);
			if (philo->times_has_eaten != philo->info->time_must_eat && philo->info->is_dead != 1)
				ft_think(philo);
		}
		else
		{
			ft_eat(philo);
			if (philo->times_has_eaten != philo->info->time_must_eat && philo->info->is_dead != 1)
				ft_sleep(philo);
			if (philo->times_has_eaten != philo->info->time_must_eat && philo->info->is_dead != 1)
				ft_think(philo);
		}
	}
	return (NULL);
}