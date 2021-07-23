#include "includes/philo.h"

static void eating(t_philosopher *x)
{
	pthread_mutex_lock(x->fork_right);
	put_message(x->id, TAKEFORK, x->table);
	pthread_mutex_lock(x->fork_left);
	put_message(x->id, TAKEFORK, x->table);
	put_message(x->id, EAT, x->table);
	x->save_point = current_time();
	while (current_time() - x->save_point <= x->table->time2eat) {
		usleep(100);
	}
	pthread_mutex_unlock(x->fork_left);
	pthread_mutex_unlock(x->fork_right);
}

static void sleeping(t_philosopher *x)
{
	unsigned long	pseudosleep;

	pseudosleep = current_time();
	put_message(x->id, SLEEP, x->table);
	while (current_time() - pseudosleep <= x->table->time2sleep)
		usleep(1);
}
static void thinking(t_philosopher *x)
{
	put_message(x->id, THINK, x->table);
}

void	*run(void *philosopher)
{
	t_philosopher	*x;

	x = (t_philosopher *)philosopher;
	printf("running %d philo\n", x->id);
	if (x->id % 2)
		eating(x);
	while (1)
	{
		sleeping(x);
		thinking(x);
		eating(x);
	}
}

void put_message(unsigned int id, char *message, t_info	*table)
{
	pthread_mutex_lock(&table->message);
	printf("%5lu %3u %s\n", table_time(table->start_time), id, message);
	pthread_mutex_unlock(&table->message);
}