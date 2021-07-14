#include "includes/philo.h"

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
