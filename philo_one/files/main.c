#include "../includes/philo.h"

void	run_threads(t_process *table)
{
	int	index;

	index = -1;
	table->start_point = current_time();
	while (++index < table->number)
	{
		pthread_create(&table->socrates[index].thread, NULL, life, \
											&table->socrates[index++]);
	}
	index = 0;
	while (++index < table->number)
	{
		pthread_create(&table->socrates[index].thread, NULL, life, \
											&table->socrates[index++]);
	}
	pthread_create(&table->observer, NULL, observe, table);
	pthread_join(table->observer, NULL);
}

int	main(int argc, char **argv)
{
	t_process	table;
	int			index;

	if (valid_args(argc, argv) != 1)
		return (1);
	if (!init_threads_and_forks(&table, argc, argv))
		return (error_case(MALLOCERROR));
	if (!forks_on_table(&table))
		return (error_case(MUTEXERROR));
	run_threads(&table);
	index = -1;
	while (++index < table.number)
		pthread_detach(table.socrates[index].thread);
	pthread_detach(table.observer);
	return (0);
}
