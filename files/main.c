#include "includes/philo.h"

int	main(int argc, char **argv)
{
	t_info	matrix;

	if (!valid_args(argc, argv))
		return (error_case(HELP));
	if (!init_threads_and_forks(&matrix, argc, argv))
		return (error_case(MALLOCERROR));
	return (1);
}
