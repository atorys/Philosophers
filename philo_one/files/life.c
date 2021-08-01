#include "../includes/philo.h"

static void	eating(t_philo *x)
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
	x->save_point = current_time();
	writecall(x->id, EAT, x->table);
	while (!x->table->is_somebody_dead && \
	current_time() - x->save_point <= x->table->time2eat)
	{
		if (current_time() - x->save_point > x->table->time2die)
			x->table->is_somebody_dead = true;
		usleep(300);
	}
	x->plates_was_eaten++;
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

static void	sleeping(t_philo *x)
{
	unsigned long	pseudosleep;

	pseudosleep = current_time();
	writecall(x->id, SLEEP, x->table);
	while (!x->table->is_somebody_dead && \
	current_time() - pseudosleep <= x->table->time2sleep)
	{
		if (current_time() - x->save_point > x->table->time2die)
			x->table->is_somebody_dead = true;
		usleep(300);
	}
}

void	*life(void *socrate)
{
	t_philo	*x;

	x = (t_philo *)socrate;
	while (!x->table->are_threads_ready)
		usleep(300);
	while (!x->table->is_somebody_dead)
	{
		eating(x);
		if (!x->table->is_somebody_dead)
			sleeping(x);
		if (!x->table->is_somebody_dead)
			writecall(x->id, THINK, x->table);
	}
}
