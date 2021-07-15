#include "includes/philo.h"

int error_case(char *message)
{
	int i;

	i = 0;
	while (message[i])
		i++;
	return ((int)write(1, message, i));
}

int	valid_args(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (0);
	argc = 0;
	argv++;
	while (*argv && ++argc)
	{
		if (argc == 1 && ft_atoi(*argv) > 200)
			return (error_case("\033[0;33mToo many philosophers ;(\n"));
		if (ft_atoi(*argv) > 2147483647 || ft_atoi(*argv) == 0)
			return (error_case("\033[0;33m Invalid arguments ;(\n"));
		while (*(*argv))
		{
			if (!(**argv >= '0' && **argv <= '9'))
				return (error_case("\033[0;33mTry another parameters ;(\n"));
			(*argv)++;
		}
		argv++;
	}
	return (1);
}

long long	ft_atoi(const char *str)
{
	long long	digit;
	int			flag;

	digit = 0;
	flag = 1;
	while (*str == ' ')
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			flag = -1;
	while (*str >= '0' && *str <= '9' && *str)
		digit = (digit * 10) + (*str++ - '0');
	return (flag * digit);
}

long	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long)(time.tv_sec * 1000 + time.tv_usec / 1000));
}
