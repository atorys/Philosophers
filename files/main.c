#include "includes/philo.h"

int main(int argc, char **argv)
{
	if (!valid_args(argc, argv))
		return (error_case(HELP));

	return (1);
}