#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# define HELP "\033[0;33mError!!!\nTry this: \033[0;39m./philo  number_of_philosophers  \
time_to_die  time_to_eat  time_to_sleep  number_of_times_each_philo_must_eat\n"
# define MALLOCERROR "\033[0;33mMalloc failed."
# define TAKEFORK " has taken a fork\n"
# define EAT " is eating\n"
# define SLEEP " is sleeping\n"
# define THINK " is thinking\n"
# define DIE " \033[0;41mdied.\n"


typedef struct s_philosopher
{
	unsigned int	id;
	pthread_t		philosopher;
	pthread_mutex_t *fork_left;
	pthread_mutex_t *fork_right;
}			t_philosopher;

typedef struct s_info
{
	t_philosopher	**philosophers;
	pthread_mutex_t	*forks;

	unsigned int 	number_philosophers;
	unsigned int 	time_2_die;
	unsigned int 	time_2_eat;
	unsigned int 	time_2_sleep;
	unsigned int 	times_eating;

}				t_info;

long long	ft_atoi(const char *str);
int			error_case(char *message);
int			valid_args(int argc, char **argv);


#endif
