#include "../includes/philo.h"

void	*observe(void *thread)
{
	t_process		*table;
	unsigned int	index;
	unsigned int	plates_check;

	table = (t_process *)thread;
	index = 0;
	plates_check = 0;
	while (!table->is_somebody_dead)
	{
		if (index == table->number)
		{
			if (table->times_eating > 0 && plates_check == table->number)
				return (NULL);
			index = 0;
			plates_check = 0;
		}
		if (current_time() - table->socrates[index++].save_point > \
																table->time2die)
			writecall(index, DIE, table);
		if (table->times_eating > 0 && \
			table->socrates[index - 1].plates_was_eaten >= table->times_eating)
			plates_check++;
		usleep(1000);
	}
	return (NULL);
}
