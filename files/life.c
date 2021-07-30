#include "includes/philo.h"

static void	eating(t_philo *x)
{
	pthread_mutex_lock(x->fork_right);
	put_message(x->id, TAKEFORKR, x->table, "\033[38;2;248;130;55m");
	pthread_mutex_lock(x->fork_left);
	put_message(x->id, TAKEFORKL, x->table, "\033[38;2;184;140;230m");
	x->save_point = current_time();
	put_message(x->id, EAT, x->table, "\033[38;2;167;183;65m");
	while (!x->table->is_somebody_dead && current_time() - x->save_point <= x->table->time2eat)
	{
		if (current_time() - x->save_point > x->table->time2die)
			x->table->is_somebody_dead = true;
//		usleep(1);
	}
	x->plates_was_eaten++;
	pthread_mutex_unlock(x->fork_left);
	pthread_mutex_unlock(x->fork_right);
}

static void	sleeping(t_philo *x)
{
	unsigned long	pseudosleep;

	pseudosleep = current_time();
	put_message(x->id, SLEEP, x->table, "\033[38;2;240;130;200m");
	while (!x->table->is_somebody_dead && current_time() - pseudosleep <= x->table->time2sleep)
		if (current_time() - x->save_point > x->table->time2die)
			x->table->is_somebody_dead = true;
}

static void	thinking(t_philo *x)
{
	if (!x->table->is_somebody_dead)
		put_message(x->id, THINK, x->table, "\033[38;2;100;160;187m");
}

void	*life(void *socrate)
{
	t_philo	*x;

	x = (t_philo *)socrate;
	if (x->id % 2 && !x->table->is_somebody_dead)
		eating(x);
	while (!x->table->is_somebody_dead)
	{
		if (!x->table->is_somebody_dead)
			sleeping(x);
		thinking(x);
		eating(x);
	}
}
