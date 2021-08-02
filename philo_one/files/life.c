#include "../includes/philo.h"

static void	take_forks(t_philo *x)
{
	if (x->id % 2)
	{
		pthread_mutex_lock(x->fork_right);
		writecall(x->id, TAKEFORK, x->table);
		pthread_mutex_lock(x->fork_left);
		writecall(x->id, TAKEFORK, x->table);
	}
	else
	{
		pthread_mutex_lock(x->fork_left);
		writecall(x->id, TAKEFORK, x->table);
		pthread_mutex_lock(x->fork_right);
		writecall(x->id, TAKEFORK, x->table);
	}
}

static void	eating(t_philo *x)
{
	take_forks(x);
	x->save_point = current_time();
	writecall(x->id, EAT, x->table);
	x->plates_was_eaten++;
	while (current_time() - x->save_point < x->table->time2eat)
		usleep(500);
	if (x->id % 2)
	{
		pthread_mutex_unlock(x->fork_left);
		pthread_mutex_unlock(x->fork_right);
	}
	else
	{
		pthread_mutex_unlock(x->fork_right);
		pthread_mutex_unlock(x->fork_left);
	}
}

void	*life(void *socrate)
{
	t_philo			*x;
	unsigned long	pseudosleep;

	x = (t_philo *)socrate;
	x->save_point = current_time();
	while (1)
	{
		eating(x);
		pseudosleep = current_time();
		writecall(x->id, SLEEP, x->table);
		while (current_time() - pseudosleep < x->table->time2sleep)
			usleep(500);
		writecall(x->id, THINK, x->table);
	}
}
