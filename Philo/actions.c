#include "philo.h"

void    ft_take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->m_fork[philo->r_fork]);
    ft_print_message(TAKE_FORKS, philo);
    pthread_mutex_lock(&philo->info->m_fork[philo->l_fork]);
    ft_print_message(TAKE_FORKS, philo);
}

void    ft_eat(t_philo *philo)
{
    ft_take_forks(philo);
    pthread_mutex_lock(&philo->info->eating);
    ft_print_message(EATING, philo);
    usleep(philo->info->time_to_sleep);
    pthread_mutex_unlock(&philo->info->eating);
    pthread_mutex_unlock(&philo->info->m_fork[philo->r_fork]);
    pthread_mutex_unlock(&philo->info->m_fork[philo->l_fork]);

}

void    *routine(void *args)
{
    t_philo *philo;
    
    philo = (t_philo *) args;
    ft_eat(philo);
    //ft_sleep();
    //ft_think();
    //if ((philo->time_last_eat = timestamp()) == -1)
	//	return (0);
    return (NULL);
}