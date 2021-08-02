#include "../includes/philo.h"

unsigned int	str_join_nbr(unsigned int start, char *str, unsigned long nbr)
{
	unsigned long	temp_nbr;
	size_t			length;
	size_t			end;

	length = 0;
	temp_nbr = nbr;
	if (temp_nbr == 0)
		length++;
	while (temp_nbr != 0 && ++length)
		temp_nbr /= 10;
	end = start + length;
	if (nbr == 0)
		str[start] = '0';
	while (length-- >= 0 && nbr > 0)
	{
		str[start + length] = (char)(nbr % 10 + '0');
		nbr /= 10;
	}
	return (end);
}

/**
 * string concatenation for one write() call
 * @param id:		philosopher's number
 * @param message:	one of 5 possible actions
 * @param table:	main structure
 */
void	writecall(unsigned int id, const char *message, t_process	*table)
{
	char			status[100];
	unsigned int	length;
	unsigned int	i;
	long long		tt;

	tt = current_time() - table->start_point;
	length = str_join_nbr(0, &status[0], (unsigned long)tt);
	status[length++] = ' ';
	length = str_join_nbr(length, &status[0], id);
	status[length++] = ' ';
	i = -1;
	while (message[++i])
		status[length++] = message[i];
	status[length] = '\n';
	pthread_mutex_lock(&table->message);
	if (tt >= 0)
		write(1, status, length);
	if (message != DIE)
		pthread_mutex_unlock(&table->message);
	else
		table->is_somebody_dead = true;
}
