#include "philo.h"

int ft_start_process(t_data *data)
{
	int	i;

	i = 0;
	if ((data->philos->time_last_eat = timestamp()) == -1)
		return (0);
	while (i < data->philo_num)
	{
		if (pthread_create(&data->philos[i].thread, NULL, routine, (void *) &data) != 0)
			return (0);
		i++;
	}
	i = -1;
	while (++i < data->philo_num)
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			return (0);
	return (1);
}