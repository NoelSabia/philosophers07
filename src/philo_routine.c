/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsabia <nsabia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:22:09 by nsabia            #+#    #+#             */
/*   Updated: 2024/01/25 19:10:22 by nsabia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*philo_life(void *arg)
{
	t_philo_thread	*philo_thread;
	t_philo			*philo;

	philo_thread = (t_philo_thread *)arg;
	philo = philo_thread->philo;
	while (philo->philo_dead == 0)
	{
		philo_think(philo_thread, philo);
		if (philo->philo_dead == 1)
			return (NULL);
		philo_eat(philo_thread, philo);
		if (philo->philo_dead == 1)
			return (NULL);
		philo_sleep(philo_thread, philo);
		if (philo->philo_dead == 1)
			return (NULL);
	}
	return (NULL);
}

void	philo_think(t_philo_thread *philo_thread, t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_think_mutex);
	ft_usleep(philo->time_to_sleep);
	printf(ANSI_COLOR_RED"%zu %zu is thinking" RESET "\n",
		get_current_time() - philo->start_time, philo_thread->index);
	pthread_mutex_unlock(&philo->philo_think_mutex);
}

void	philo_eat(t_philo_thread *philo_thread, t_philo *philo)
{
	pthread_mutex_lock(&philo->time_to_eat_mutex);
	if (philo->num_of_philos == 1)
		ft_usleep(100000);
	if (philo_thread->index == 0 || philo_thread->index == philo->num_of_philos)
		philo_eat_edgecase(philo_thread, philo);
	else
	{
		pthread_mutex_lock(&philo->fork[philo_thread->index]);
		philo->last_eaten[philo_thread->index] = 0;
		printf(ANSI_COLOR_GREEN"%zu %zu has taken his fork" RESET
			"\n", get_current_time() - philo->start_time, philo_thread->index);
		pthread_mutex_lock(&philo->fork[philo_thread->index - 1]);
		printf(ANSI_COLOR_GREEN"%zu %zu has taken the left fork" RESET
			"\n", get_current_time() - philo->start_time, philo_thread->index);
		ft_usleep(philo->time_to_eat);
		pthread_mutex_unlock(&philo->fork[philo_thread->index]);
		printf(ANSI_COLOR_BLUE"%zu %zu has dropped his fork" RESET
			"\n", get_current_time() - philo->start_time, philo_thread->index);
		philo->meals_to_eat[philo_thread->index]--;
		philo->last_eaten[philo_thread->index] = get_current_time();
		pthread_mutex_unlock(&philo->fork[philo_thread->index - 1]);
		printf(ANSI_COLOR_BLUE"%zu %zu has dropped the left fork" RESET
			"\n", get_current_time() - philo->start_time, philo_thread->index);
		pthread_mutex_unlock(&philo->time_to_eat_mutex);
	}
}

void	philo_eat_edgecase(t_philo_thread *s_philo_thread, t_philo *philo)
{
	pthread_mutex_lock(&philo->fork[s_philo_thread->index]);
	philo->last_eaten[s_philo_thread->index] = 0;
	printf(ANSI_COLOR_GREEN"%zu %zu has taken his fork"RESET"\n",
		get_current_time() - philo->start_time, s_philo_thread->index);
	pthread_mutex_lock(&philo->fork[s_philo_thread->biggest]);
	printf(ANSI_COLOR_GREEN"%zu %zu has taken the left fork"RESET"\n",
		get_current_time() - philo->start_time, s_philo_thread->index);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(&philo->fork[s_philo_thread->index]);
	printf(ANSI_COLOR_BLUE"%zu %zu has dropped the left fork" RESET
		"\n", get_current_time() - philo->start_time, s_philo_thread->index);
	philo->meals_to_eat[s_philo_thread->index]--;
	philo->last_eaten[s_philo_thread->index] = get_current_time();
	pthread_mutex_unlock(&philo->fork[s_philo_thread->biggest]);
	printf(ANSI_COLOR_BLUE"%zu %zu has dropped his fork" RESET
		"\n", get_current_time() - philo->start_time, s_philo_thread->index);
}

void	philo_sleep(t_philo_thread *philo_thread, t_philo *philo)
{
	pthread_mutex_lock(&philo->time_to_sleep_mutex);
	ft_usleep(philo->time_to_sleep);
	printf(ANSI_COLOR_YELLOW"%zu %zu is sleeping" RESET "\n",
		get_current_time() - philo->start_time, philo_thread->index);
	pthread_mutex_unlock(&philo->time_to_sleep_mutex);
}
