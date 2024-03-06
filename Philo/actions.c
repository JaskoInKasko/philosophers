#include "philo.h"

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->m_fork[philo->r_fork]);
	pthread_mutex_lock(&philo->info->m_fork[philo->l_fork]);
	if (ft_monitoring_usleep(0, philo) == 0)
	{
		ft_philo_clean(philo, 0);
		return ;
	}
	ft_print_message(TAKE_FORKS, philo);
	ft_print_message(TAKE_FORKS, philo);
	ft_print_message(EATING, philo);
	if (ft_monitoring_usleep(philo->info->time_to_eat, philo) == 0)
	{
		ft_philo_clean(philo, 0);
		return ;
	}
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
		ft_monitoring_usleep(philo->info->time_to_sleep, philo);
}

void	ft_think(t_philo *philo)
{
	long int	t_eat;
	long int	t_sleep;
	long int	t_think;

	t_eat = philo->info->time_to_eat;
	t_sleep = philo->info->time_to_sleep;
	t_think = 0;
	ft_print_message(THINKING, philo);
	if (philo->info->philo_num % 2 == 0)
	{
		if (t_eat >= t_sleep)
			t_think = t_eat - t_sleep;
		else
			t_think = 0;
	}
	else
	{
		if (t_eat == t_sleep)
			t_think = t_eat;
		if (t_eat > t_sleep || t_eat < t_sleep)
			t_think = (t_eat * 2) - t_sleep;
		if (t_think < 0)
			t_think = 0;
	}
	ft_monitoring_usleep(t_think, philo);
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