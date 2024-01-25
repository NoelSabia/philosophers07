/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsabia <nsabia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:38:30 by nsabia            #+#    #+#             */
/*   Updated: 2024/01/25 18:57:21 by nsabia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>

/*Defines*/
#define MAX_PHILOS 200
#define ANSI_COLOR_BLACK 	"\x1b[30m"
#define ANSI_COLOR_RED     	"\x1b[31m"
#define ANSI_COLOR_GREEN   	"\x1b[32m"
#define ANSI_COLOR_YELLOW  	"\x1b[33m"
#define ANSI_COLOR_BLUE    	"\x1b[34m"
#define RESET   			"\x1b[0m"

/*Structures*/
typedef struct s_philo
{
	pthread_t		id[MAX_PHILOS];

	int				philo_dead;
	pthread_mutex_t	dead;

	size_t			num_of_philos;
	pthread_mutex_t	philo;

	size_t			time_to_die;
	pthread_mutex_t	time_to_die_mutex;

	size_t			time_to_eat;
	pthread_mutex_t	time_to_eat_mutex;

	size_t			num_sleep;
	size_t			time_to_sleep;
	pthread_mutex_t	time_to_sleep_mutex;

	int				eat_count;

	size_t			num_think;
	pthread_mutex_t	philo_think_mutex;
	pthread_mutex_t	fork[MAX_PHILOS];
	size_t			start_time;
	size_t			last_eaten[MAX_PHILOS];
	int				meals_to_eat[MAX_PHILOS];
}						t_philo;

typedef struct s_philo_thread
{
	t_philo	*philo;
	size_t	index;
	size_t	biggest;
}				t_philo_thread;

/*Functions*/
int		safe_atoi(char *str);
void	initialize(t_philo *philo, char *argv[]);
void	user_input(t_philo *philo, char *argv[]);
void	initialize_mutexes(t_philo *philo);
void	initialize_threads(t_philo *philo);
void	join_threads(t_philo *philo);
void	*philo_life(void *philo);
void	philo_think(t_philo_thread *philo_thread, t_philo *philo);
void	philo_eat(t_philo_thread *philo_thread, t_philo *philo);
void	philo_eat_edgecase(t_philo_thread *s_philo_thread, t_philo *philo);
void	philo_sleep(t_philo_thread *philo_thread, t_philo *philo);
void	*monitoring(void *arg);
int		ft_usleep(size_t milliseconds);
size_t	get_current_time(void);
void	destroy(t_philo *philo);
