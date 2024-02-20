#include "philo.h"

int	ft_philo_init(t_data *data, char *argv[])
{
	int	i;

	i = 0;
	data->philo_num = ft_atol(argv[1]);
	if (data->philo_num > 200 || data->philo_num == 0)
		return (0);
	data->time_to_die = ft_atol(argv[2]);
    data->time_to_eat = ft_atol(argv[3]);
    data->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		data->time_must_eat = ft_atol(argv[5]);
	else
		data->time_must_eat = -1;
	data->philos = malloc(sizeof(t_philo) * data->philo_num);
	if (!data->philos)
		return (0);
	while(i < data->philo_num && data->philo_num != 1)
	{
		data->philos[i].info = data;
		data->philos[i].r_fork = 0;
		data->philos[i].l_fork = 0;
		data->philos[i].id = i + 1;
		i++;
	}
	data->philos[0].r_fork = 0;
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
	t_data data;

    if (ft_check_args(argc, argv) == 0)
		return (0);
	if (ft_philo_init(&data, argv) == 0)
		return (0);
	if (ft_start_process(&data) == 0)
	{
		free(data.philos);
		return (0);
	}
	free(data.philos);
	printf("succsess");
}