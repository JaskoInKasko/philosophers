#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>

typedef struct s_data
{
	pthread_t	thread;
	int			r_fork;
	int			l_fork;
} t_data;

typedef struct s_philo
{   
    t_data		*philos;
    int			philo_num;
    long int	time_to_eat;
    long int	time_to_sleep;
    long int	time_to_think;
    long int	time_to_die;
	long int	time_must_eat;
} t_philo;

//		PHILO
int			ft_start_process(t_philo *data);

//      UTILS
long int	ft_atol(const char *nptr);

//      ACTIONS
void    *philo_status();

#endif