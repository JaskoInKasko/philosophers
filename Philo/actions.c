#include "philo.h"

void	single_philo_simulation(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->m_fork[philo->r_fork]);
	ft_print_message(TAKE_FORKS, philo);
	pthread_mutex_unlock(&philo->info->m_fork[philo->r_fork]);
}

void	ft_eat(t_philo *philo)
{
	if (philo->id % 2 != 1)
	{
		pthread_mutex_lock(&philo->info->m_fork[philo->r_fork]);
		pthread_mutex_lock(&philo->info->m_fork[philo->l_fork]);
	}
	else
	{
		pthread_mutex_lock(&philo->info->m_fork[philo->l_fork]);
		pthread_mutex_lock(&philo->info->m_fork[philo->r_fork]);
	}
	ft_print_message(TAKE_FORKS, philo);
	ft_print_message(TAKE_FORKS, philo);
	ft_print_message(EATING, philo);
	ft_usleep(philo->info->time_to_eat, philo);
	pthread_mutex_lock(&philo->info->write);
	philo->times_has_eaten++;
	pthread_mutex_unlock(&philo->info->write);
	pthread_mutex_unlock(&philo->info->m_fork[philo->r_fork]);
	pthread_mutex_unlock(&philo->info->m_fork[philo->l_fork]);
}

void	ft_sleep(t_philo *philo)
{
	ft_print_message(SLEEPING, philo);
	ft_usleep(philo->info->time_to_sleep, philo);
}

void	ft_think(t_philo *philo)
{
	long int	t_think;
	ft_print_message(THINKING, philo);
	if (philo->info->philo_num % 2 == 0)
		return ;
	else
	{
		t_think = (philo->info->time_to_eat * 2) - philo->info->time_to_sleep;
		if (t_think < 0)
			t_think = 0;
		ft_usleep(0.42 * t_think, philo);
	}
}

void	*routine(void *args)
{
	t_philo *philo;

	philo = (t_philo *) args;

	if (philo->info->philo_num == 1)
	{
		single_philo_simulation(philo);
		return (NULL);
	}
	if (philo->id % 2 != 0)
		ft_usleep(42, philo);
	while(1)
	{
		ft_eat(philo);
		if (ft_finnished_philo(philo) == 0 || ft_dead_philo(philo) == 0)
			return (NULL);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}