#include "includes/philo.h"

void	*check(void *thread)
{
	t_process		*table;
	unsigned int 	n;

	table = (t_process *)thread;
//	while (!table->are_threads_ready)
//		usleep(10);
	n = 0;
	while (n < table->number && !table->is_somebody_dead)
	{
		if (current_time() - table->socrates[n++].save_point > table->time2die)
		{
			table->is_somebody_dead = true;
			put_message(n, DIE, table, "\033[0;31m");
		}
		if (n == table->number)
			n = 0;
	}
}

static	void	run_threads(t_process *table)
{
	int	n;

	table->start_time = current_time();
	n = -1;
	while (++n < table->number)
	{
		table->socrates[n].save_point = current_time();
		pthread_create(&table->socrates[n].thread, NULL, life, \
											&table->socrates[n]);
	}
	table->are_threads_ready = true;
	pthread_create(&table->observer, NULL, check, table);
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
}
