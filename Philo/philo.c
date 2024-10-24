#include "philo.h"

int	ft_data_init(t_data *data, char *argv[])
{
	int	i;

	i = -1;
	data->philo_num = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
    data->time_to_eat = ft_atol(argv[3]);
    data->time_to_sleep = ft_atol(argv[4]);
	data->is_dead = 0;
	if ((data->philo_num > 200 || data->philo_num <= 0)
		|| data->time_to_die < 60 || data->time_to_eat < 60
		|| data->time_to_sleep < 60)
		return (ft_print_error(0), 0);
	if (argv[5])
		data->time_must_eat = ft_atol(argv[5]);
	else
		data->time_must_eat = -1;
	data->m_fork = malloc(sizeof(pthread_mutex_t) * (data->philo_num));
	if (!data->m_fork)
		return (ft_print_error(1), 0);
	while(++i < data->philo_num)
		pthread_mutex_init(&data->m_fork[i], NULL);
	pthread_mutex_init(&data->write, NULL);
	return (1);
}

int	ft_philo_init(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->philo_num);
	if (!data->philos)
		return (free(data->m_fork), ft_print_error(1), 0);
	while(i < data->philo_num)
	{
		data->philos[i].times_has_eaten = 0;
		data->philos[i].info = data;
		data->philos[i].r_fork = (i + 1) % data->philo_num;
		if (data->philo_num != 1)
			data->philos[i].l_fork = i;
		data->philos[i].id = i + 1;
		i++;
	}
	return (1);
}

int	ft_check_args(int argc, char *argv[])
{
	int	arg_index;
	int	letter;

	arg_index = 1;
	if (argc >= 5 && argc <= 6)
	{
		while(argv[arg_index] != NULL)
		{
			letter = 0;
			while(argv[arg_index][letter] != '\0')
			{	
				if(!(argv[arg_index][letter] >= '0' && argv[arg_index][letter] <= '9'))
					return (ft_print_error(0), 0);
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
	t_data data;

    if (ft_check_args(argc, argv) == 0)
		return (0);
	if (ft_data_init(&data, argv) == 0 || ft_philo_init(&data) == 0)
		return (0);
	ft_start_process(&data);
	ft_data_clean(&data);
}