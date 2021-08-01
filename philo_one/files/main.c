#include "../includes/philo.h"

static	void	run_threads(t_process *table)
{
	int	index;

	table->start_point = current_time();
	pthread_create(&table->observer, NULL, observe, table);
	index = -1;
	while (++index < table->number)
	{
		table->socrates[index].save_point = current_time();
		pthread_create(&table->socrates[index].thread, NULL, life, \
											&table->socrates[index]);
	}
	table->are_threads_ready = true;
	pthread_join(table->observer, NULL);
}

int	main(int argc, char **argv)
{
	t_process	table;

	if (!valid_args(argc, argv))
		return (error_case(HELP));
	if (!init_threads_and_forks(&table, argc, argv))
		return (error_case(MALLOCERROR));
	if (!forks_on_table(&table))
		return (error_case(MUTEXERROR));
	run_threads(&table);
	return (0);
}
