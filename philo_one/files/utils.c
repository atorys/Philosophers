#include "../includes/philo.h"

int	error_case(const char *message)
{
	int	i;

	i = 0;
	while (message[i])
		i++;
	write(2, ERR_COLOR, 7);
	write(2, message, i);
	return (-1);
}

int	valid_args(int argc, char **argv)
{
	int	index;

	if (argc != 5 && argc != 6)
		return (error_case(HELP));
	while (argv[--argc] && argc > 0)
	{
		index = -1;
		if (argc == 1 && ft_atoi(argv[argc]) > 200)
			return (error_case("Too many philosophers ;(\n"));
		if (ft_atoi(argv[argc]) > 2147483647 || ft_atoi(argv[argc]) == 0)
			return (error_case("Invalid arguments ;(\n"));
		while (argv[argc][++index])
			if (!(argv[argc][index] >= '0' && argv[argc][index] <= '9'))
				return (error_case("Try another parameters ;(\n"));
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

unsigned long	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((unsigned long)(time.tv_sec * 1000 + time.tv_usec / 1000));
}
