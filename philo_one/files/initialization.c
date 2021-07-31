#include "includes/philo.h"

static void	set_parameters(t_process *table, int argc, char **argv)
{
	table->number = (unsigned int)ft_atoi(argv[1]);
	table->time2die = (unsigned int)ft_atoi(argv[2]);
	table->time2eat = (unsigned int)ft_atoi(argv[3]);
	table->time2sleep = (unsigned int)ft_atoi(argv[4]);
	if (argc == 6)
		table->times_eating = (unsigned int)ft_atoi(argv[5]);
	else
		table->times_eating = 0;
	table->is_somebody_dead = false;
	table->are_threads_ready = false;
}

int	init_threads_and_forks(t_process *table, int index, char **argv)
{
	set_parameters(table, index, argv);
	table->socrates = (t_philo *)malloc(sizeof(t_philo) * table->number);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->number);
	if (!table->socrates || !table->forks)
		return (0);
	index = -1;
	while (++index < table->number)
	{
		table->socrates[index].id = index + 1;
		table->socrates[index].thread = NULL;
		if (table->times_eating != 0)
			table->socrates[index].plates_was_eaten = 0;
		else
			table->socrates[index].plates_was_eaten = -1;
		table->socrates[index].table = table;
	}
	table->observer = NULL;
	return (1);
}

int	forks_on_table(t_process *table)
{
	int	index;

	index = -1;
	while (++index < table->number)
	{
		if (pthread_mutex_init(&table->forks[index], NULL) != 0)
			return (0);
		table->socrates[index].fork_right = &table->forks[index];
		if (index == table->number - 1)
			table->socrates[index].fork_left = &table->forks[0];
		else
			table->socrates[index].fork_left = &table->forks[index + 1];
	}
	if (pthread_mutex_init(&table->message, NULL) != 0)
		return (0);
	return (1);
}
