#include "philo.h"

int	ft_philo_init(t_philo *philo, char *argv[])
{
	int	i;

	i = 0;
	if ((philo->philo_num = ft_atol(argv[1])) > 200)
		return (0);
	philo->time_to_die = ft_atol(argv[2]);
    philo->time_to_eat = ft_atol(argv[3]);
    philo->time_to_sleep = ft_atol(argv[4]);
    philo->time_to_think = 0;
	if(argv[5])
		philo->time_must_eat = ft_atol(argv[5]);
	else
		philo->time_must_eat = 0;
	philo->philos = malloc(sizeof(t_data) * philo->philo_num);
	if (!philo->philos)
		return (0);
	while(i < philo->philo_num)
	{
		philo->philos[i].l_fork = 0;
		philo->philos[i].r_fork = 0;
		i++;
	}
	return  (1);
}

int	ft_check_args(int argc, char *argv[])
{
	int	arg_index;
	int	letter;

	arg_index = 1;
	if (argc >= 2 && argc <= 6)
	{
		while(argv[arg_index] != NULL)
		{
			letter = 0;
			while(argv[arg_index][letter] != '\0')
			{	
				if(!(argv[arg_index][letter] >= '0' && argv[arg_index][letter] <= '9'))
					return (0);
				letter++;
			}
			arg_index++;
		}
		return (1);
	}
	return (0);
}

int main(int argc, char *argv[])
{
	t_philo philo;
    if (ft_check_args(argc, argv) == 0)
		return (0);
	if (ft_philo_init(&philo, argv) == 0)
		return (0);
	if (ft_start_process(&philo) == 0)
		return (0);
	printf("succsess");
}