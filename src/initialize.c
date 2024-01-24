/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsabia <nsabia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:21:04 by nsabia            #+#    #+#             */
/*   Updated: 2024/01/23 19:56:22 by nsabia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	initialize(t_philo *philo, char *argv[])
{
	user_input(philo, argv);
	size_t i;

	i = 0;
	if (philo->eat_count != -1)
	{
		while (i < philo->num_of_philos)
		{
			philo->meals_to_eat[i] = philo->eat_count;
			i++;
		}
	}
	initialize_mutexes(philo);
	initialize_threads(philo);
	join_threads(philo);
}

void	user_input(t_philo *philo, char *argv[])
{
	philo->start_time = get_current_time();
	philo->philo_dead = 0;
	philo->num_sleep = 1;
	philo->num_think = 1;
	philo->num_of_philos = safe_atoi(argv[1]);
	philo->time_to_die = safe_atoi(argv[2]);
	philo->time_to_eat = safe_atoi(argv[3]);
	philo->time_to_sleep = safe_atoi(argv[4]);
	if (argv[5])
		philo->eat_count = safe_atoi(argv[5]);
	else
		philo->eat_count = -1;
}

void	initialize_mutexes(t_philo *philo)
{
	size_t	i;

	i = 0;
	while (i < philo->num_of_philos)
	{
		pthread_mutex_init(&philo->fork[i], NULL);
		i++;
	}
	pthread_mutex_init(&philo->philo, NULL);
	pthread_mutex_init(&philo->dead, NULL);
}

void	initialize_threads(t_philo *philo)
{
	size_t			i;
	int				ret;
	t_philo_thread	philo_threads[MAX_PHILOS];

	i = 1;
	philo_threads->biggest = 0;
	while (i <= philo->num_of_philos)
	{
		philo_threads[i].philo = philo;
		philo_threads[i].index = i;
		if (i > philo_threads->biggest)
			philo_threads->biggest = i;
		ret = pthread_create(&philo->id[i], NULL,
				philo_life, &philo_threads[i]);
		if (ret != 0)
		{
			printf("Error: pthread_create: %s\n", strerror(ret));
			return ;
		}
		i++;
	}
	ret = pthread_create(&philo->id[i], NULL, monitoring, (void *)philo);
	if (ret != 0)
	{
		printf("Error: pthread_create: %s\n", strerror(ret));
		return;
	}
}

void	join_threads(t_philo *philo)
{
	size_t	i;
	int		ret;

	i = 1;
	while (i <= philo->num_of_philos)
	{
		ret = pthread_join(philo->id[i], NULL);
		if (ret != 0)
		{
			printf("Error: pthread_join: %s\n", strerror(ret));
			return ;
		}
		i++;
	}
	ret = pthread_join(philo->id[i], NULL);
	if (ret != 0)
	{
		printf("Error: pthread_join: %s\n", strerror(ret));
		return ;
	}
}
