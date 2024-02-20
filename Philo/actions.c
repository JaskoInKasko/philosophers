#include "philo.h"

/*void    ft_take_forks(t_philo *philo)
{
	pthread_mutex_init(&philo->info->m_fork, NULL);
	pthread_mutex_lock();
	philo->r_fork = 1;
	philo->l_fork = 1;
	pthread_mutex_unlock();
}*/

void    *routine(void *args)
{
    t_philo *philo;
    
    philo = (t_philo *) args;
    ft_take_forks(philo);
    //ft_eat();
    //ft_sleep();
    //ft_think();
    //if ((philo->time_last_eat = timestamp()) == -1)
	//	return (0);
    return (NULL);
}