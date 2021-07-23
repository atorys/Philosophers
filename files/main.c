#include "includes/philo.h"

int	main(int argc, char **argv)
{
	t_info	table;
	pthread_t p;

	if (!valid_args(argc, argv))
		return (error_case(HELP));
	if (!init_threads_and_forks(&table, argc, argv))
		return (error_case(MALLOCERROR));
	if (!forks_on_table(&table))
		return (error_case(MUTEXERROR));
	table.start_time = current_time();
	argc = -1;
//	pthread_create(&table.philosophers[0]->philosopher, NULL, run, &table.philosophers[0]);
	while (++argc < table.number)
	{
		printf("preparing %d philo\n", argc+1);
		table.philosophers[argc].start_point = current_time();
		table.philosophers[argc].philosopher = NULL;
		pthread_create(&table.philosophers[argc].philosopher, NULL, run, &table.philosophers[argc]);
	}
	return (1);
}
