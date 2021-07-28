#include "includes/philo.h"

int	main(int argc, char **argv)
{
	t_info	table;

	if (!valid_args(argc, argv))
		return (error_case(HELP));
	if (!init_threads_and_forks(&table, argc, argv))
		return (error_case(MALLOCERROR));
	if (!forks_on_table(&table))
		return (error_case(MUTEXERROR));
	table.start_time = current_time();
	argc = -1;
	while (++argc < table.number)
	{
		table.philosophers[argc].start_point = current_time();
		table.philosophers[argc].philosopher = NULL;
		pthread_create(&table.philosophers[argc].philosopher, NULL, run, &table.philosophers[argc]);
	}
	while (1)
		usleep(1000);
	return (1);
}
