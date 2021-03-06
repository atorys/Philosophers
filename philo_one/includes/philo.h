#ifndef PHILO_H
# define PHILO_H

/*
 * -------------------------------  INCLUDES  ---------------------------------
 */
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>

/*
 * -------------------------------  DEFINES  ----------------------------------
 */

# define HELP "\033[0;33mError!!!\nTry this: \033[0;39m./philo  number_of_philosophers  \
time_to_die  time_to_eat  time_to_sleep  number_of_times_each_philo_must_eat\n"

# define ERR_COLOR		"\033[0;33m"
# define MALLOCERROR	"\033[0;31mMalloc failed.\n"
# define MUTEXERROR		"\033[0;31mPthread_mutex_init() failed.\n"

# define	TAKEFORK	"has taken a fork\n"
# define	EAT			"is eating\n"
# define	SLEEP		"is sleeping\n"
# define	THINK		"is thinking\n"
# define	DIE			"died\n"

/*
 * ------------------------------  STRUCTURES  ---------------------------------
 */

typedef struct s_process	t_process;

/**
 * single philosopher node
 *
 * @param id:			philosopher number N, uint
 * @param thread:		pthread_t
 *
 * @param fork_left: 	pointer to mutex_t N+1
 * @param fork_right:	pointer to mutex_t N
 *
 * @param save_point:	last time philosopher called eating()
 * @param plates_was_eaten: eating() calls
 *
 * @param table:		pointer to main structure
 */
typedef struct s_philosopher
{
	unsigned int		id;
	pthread_t			thread;

	pthread_mutex_t		*fork_left;
	pthread_mutex_t		*fork_right;

	unsigned long		save_point;
	unsigned int		plates_was_eaten;

	t_process			*table;
}				t_philo;

/**
 * main structure with input parameters info
 *
 * @param [input] number:		number of philosophers
 * @param [input] time2die:		possible lifetime without eating
 * @param [input] time2eat:		eating time
 * @param [input] time2sleep:	sleeping time
 * @param [input] times_eating:	each philosopher should eat at least X times
 *
 * @param start_point:	the moment when simulation has started
 *
 * @param socrates:		list of t_philo structure
 * @param forks:		list of mutex_t's size of philosophers' number
 *
 * @param message:				mutex_t for printing each philosopher's status
 * @param observer: 			pthread which checks how deadly each
 * 								philosopher is and how many times
 * @param is_somebody_dead:		check for observer's end
 * @param are_threads_ready:	check for observer's start
 */
struct s_process
{
	unsigned int	number;
	unsigned int	time2die;
	unsigned int	time2eat;
	unsigned int	time2sleep;
	unsigned int	times_eating;

	unsigned long	start_point;

	t_philo			*socrates;
	pthread_mutex_t	*forks;

	pthread_mutex_t	message;
	pthread_t		observer;
	bool			is_somebody_dead;
};

/*
 * ------------------------------  UTILITIES  ---------------------------------
 */

long long		ft_atoi(const char *str);
int				error_case(const char *message);
int				valid_args(int argc, char **argv);
void			writecall(unsigned int id, const char *message, \
						  								t_process *table);

/*
 * ---------------------------  TIME MANAGEMENT  ------------------------------
 */

unsigned long	current_time(void);

/*
 * ----------------------------  MAIN FUNCTIONS  ------------------------------
 */

int				init_threads_and_forks(t_process *table, int i, char **argv);
int				forks_on_table(t_process	*table);
void			run_threads(t_process *table);
void			*life(void *socrate);
void			*observe(void *thread);

#endif
