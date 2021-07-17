#include "includes/philo.h"

int	init_threads_and_forks(t_info	*matrix, int index, char **argv)
{
	matrix->number = (unsigned int)ft_atoi(argv[1]);
	matrix->time2die = (unsigned int)ft_atoi(argv[2]);
	matrix->time2eat = (unsigned int)ft_atoi(argv[3]);
	matrix->time2sleep = (unsigned int)ft_atoi(argv[4]);
	if (index == 6)
		matrix->times_eating = (unsigned int)ft_atoi(argv[5]);
	matrix->philosophers = malloc(sizeof(t_philosopher) * matrix->number);
	matrix->forks = malloc(sizeof(pthread_t) * matrix->number);
	if (!matrix->philosophers || !matrix->forks)
		return (0);
	index = -1;
	while (++index < matrix->number)
	{
		matrix->philosophers[index].id = index + 1;
		matrix->philosophers[index].fork_right = &matrix->forks[index];
		if (index == matrix->number - 1)
			matrix->philosophers[index].fork_left = &matrix->forks[0];
		else
			matrix->philosophers[index].fork_left = &matrix->forks[index + 1];
	}
	return (1);
}
