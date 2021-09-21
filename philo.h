#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>


# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DIE 5

typedef	struct	s_args
{
	long				number_philo;
	long				time_die;
	long				time_eat;
	long				time_sleep;
	long				num_meal;
	unsigned long long	current_time;
	pthread_mutex_t 	*forks;
	pthread_mutex_t 	write;
	pthread_mutex_t		is_eating;
	struct t_philo 		*philo;
}t_args;

typedef struct s_philo
{
	pthread_t			tr;
	int					philo_id;
	unsigned long long	start;
	unsigned long long	last_time_eat;
	int					nb_of_meals;
	int					eat;
	t_args				*args;
}t_philo;


int		ft_strlen(char *str);
void	ft_exit(t_args *args);

void	start(t_args *args);

int		parsing(int ac, char **av, t_args *args);

void	eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	think(t_philo *philo);
void	*work(void	*philostruct);

unsigned long long	time_passed(unsigned long long start);
unsigned long long time_now(void);
void				sleepu(unsigned long long end);

int		print(t_philo *philo, int to_write, unsigned long long time_ms);

void	init_mutex(t_args *args);
int		is_good_to_parse(char **av);
t_philo *init_philo(t_args *args);

int	ft_atoi(const char *str);
int		ft_strlen(char *str);

void	destiny(t_args *args ,t_philo *philo);