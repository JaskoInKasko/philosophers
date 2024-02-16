#include "philo.h"

int ft_start_process(t_philo *data)
{
	int	i;

	i = 0;
	//add timestamp here (gettimeofday());
	while (i < data->philo_num)
	{
		if (pthread_create(&data->philos[i].thread, NULL, &philo_status, &data) != 0)
			return (0);
		i++;
	}
	i = -1;
	while (++i < data->philo_num)
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			return (0);
	return (1);
}