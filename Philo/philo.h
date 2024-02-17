#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
 #include <sys/time.h>

typedef struct s_philo
{
	pthread_t	thread;
	int			id;
	int			r_fork;
	int			l_fork;
	long int	time_last_eat;
} t_philo;

typedef struct s_data
{   
    t_philo		*philos;
    int			philo_num;
    long int	time_to_eat;
    long int	time_to_sleep;
    long int	time_to_die;
	long int	time_must_eat;
} t_data;

//		PHILO
int			ft_start_process(t_data *data);

//      UTILS
long int	ft_atol(const char *nptr);
long int	timestamp(void);

//      ACTIONS
void		*routine(void *data);

#endif