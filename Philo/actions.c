#include "philo.h"

void    ft_take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->m_fork[philo->r_fork]);
	pthread_mutex_lock(&philo->info->m_fork[philo->l_fork]);
	ft_print_message(TAKE_FORKS, philo);
	ft_print_message(TAKE_FORKS, philo);
}

void	ft_eat(t_philo *philo)
{
	ft_take_forks(philo);
	ft_print_message(EATING, philo);
	usleep(philo->info->time_to_eat * 1000);
	//pthread_mutex_lock(&philo->info->eating);
	philo->times_has_eaten++;
	//pthread_mutex_unlock(&philo->info->eating);
	pthread_mutex_unlock(&philo->info->m_fork[philo->r_fork]);
	pthread_mutex_unlock(&philo->info->m_fork[philo->l_fork]);
	if (philo->times_has_eaten == philo->info->time_must_eat)
		return ;
	usleep(1000);
	ft_print_message(SLEEPING, philo);
	usleep(philo->info->time_to_sleep * 1000);
	ft_print_message(THINKING, philo);
}

void	*routine(void *args)
{
	t_philo *philo;

	philo = (t_philo *) args;
	while(philo->times_has_eaten != philo->info->time_must_eat)
	{
		ft_eat(philo);
	}
	//ft_sleep();
	//ft_think();
	//if ((philo->time_last_eat = timestamp()) == -1)
	//	return (0);
	return (NULL);
}