#include "includes/philo.h"

static void	set_parameters(t_info	*table, int argc, char **argv);

int	init_threads_and_forks(t_info	*table, int index, char **argv)
{
	set_parameters(table, index, argv);
	table->philosophers = (t_philosopher **)malloc(sizeof(t_philosopher *) * table->number);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->number);
	if (!table->philosophers || !table->forks)
		return (0);
	return (1);
}

static void set_parameters(t_info	*table, int argc, char **argv)
{
	table->number = (unsigned int)ft_atoi(argv[1]);
	table->time2die = (unsigned int)ft_atoi(argv[2]);
	table->time2eat = (unsigned int)ft_atoi(argv[3]);
	table->time2sleep = (unsigned int)ft_atoi(argv[4]);
	if (argc == 6)
		table->times_eating = (unsigned int)ft_atoi(argv[5]);
	else
		table->times_eating = 0;
}

int	forks_on_table(t_info	*table)
{
	int	index;

	index = -1;
	while (++index < table->number)
	{
		table->philosophers[index] = malloc(sizeof(t_philosopher));
		if (!table->philosophers[index])
			return (-1);
		table->philosophers[index]->id = index + 1;
		if (pthread_mutex_init(&table->forks[index], NULL) != 0)
			return (0);
		table->philosophers[index]->fork_right = &table->forks[index];
		if (index == table->number - 1)
			table->philosophers[index]->fork_left = &table->forks[0];
		else
			table->philosophers[index]->fork_left = &table->forks[index + 1];
		table->philosophers[index]->table = table;
	}
	if (pthread_mutex_init(&table->message, NULL) != 0)
		return (0);
	return (1);
}
