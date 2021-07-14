#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_pholosopher
{
	unsigned int	id;
	pthread_mutex_t fork_left;
	pthread_mutex_t fork_right;
}			t_philosopher;

typedef struct s_info
{
	t_philosopher	*phs;
}				t_info;

long long	ft_atoi(const char *str);

#endif