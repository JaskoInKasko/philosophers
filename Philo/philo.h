#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# define TAKE_FORKS "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED "died"

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				r_fork;
	int				l_fork;
	struct s_data	*info;
	int				times_has_eaten; // update everytime they eat "increment++"
	long int		time_last_eat; // update everytime they eat "timestamp()"
	long int		time_to_think;
} t_philo;

typedef struct s_data
{   
    t_philo			      *philos;
    int				philo_num;
	long int		time_to_die;
    long int		time_to_eat;
    long int		time_to_sleep;
	int				time_must_eat; // compare everytime when they ate
	long int		simultion_start; // time_last_eat - simulation_start
	int				is_dead;
	pthread_mutex_t	*m_fork;
	pthread_mutex_t	write;
	pthread_mutex_t	eating;
} t_data;

//		PHILO
int			ft_start_process(t_data *data);

//		LIBFT
long int	ft_atol(const char *nptr);
int			ft_strcmp(const char *s1, const char *s2);

//      UTILS
long int	timestamp(void);
void		ft_print_message(char *str, t_philo *philo);
int			ft_monitoring_usleep(int ms, t_philo *philo);
//      ACTIONS
void		*routine(void *data);

#endif