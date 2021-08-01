#include "../includes/philo.h"

void	*observe(void *thread)
{
	t_process		*table;
	unsigned int 	index;
	unsigned int	plates_check;

	table = (t_process *)thread;
	while (!table->are_threads_ready)
		usleep(300);
	index = 0;
	plates_check = 0;
	while (index < table->number && !table->is_somebody_dead)
	{
		if (current_time() - table->socrates[index++].save_point > table->time2die)
		{
			table->is_somebody_dead = true;
			writecall(index, DIE, table);
			return (NULL);
		}
		if (table->times_eating > 0 && table->socrates[index].plates_was_eaten >= table->times_eating)
			plates_check++;
		if (index == table->number)
		{
			if (table->times_eating > 0 && plates_check == table->number)
			{
				table->is_somebody_dead = true;
				pthread_mutex_lock(&table->message);
				return (NULL);
			}
			index = 0;
			plates_check = 0;
		}
	}
}
