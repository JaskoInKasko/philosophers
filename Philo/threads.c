#include "philo.h"

int ft_start_process(t_data *data)
{
	int	i;

	i = 0;
	data->simulation_start = timestamp();
	while (i < data->philo_num)
	{
		data->philos[i].time_last_eat = timestamp();
		if (pthread_create(&data->philos[i].thread, NULL, routine, (void *) &data->philos[i]) != 0)
			return (ft_print_error(2), 0);
		i++;
	}
	check_philo(data);
	i = -1;
	while (++i < data->philo_num)
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			return (ft_print_error(3), 0);
	return (1);
}