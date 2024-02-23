/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsabia <nsabia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:22:09 by nsabia            #+#    #+#             */
/*   Updated: 2024/02/23 11:31:56 by nsabia           ###   ########.fr       */
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
		if (philo_eat(philo_thread, philo) == 0)
			return (NULL);
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
	print_message("is thinking", philo, philo_thread->index);
	if (philo_thread->index % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork[philo_thread->index]);
		print_message("has taken a fork", philo, philo_thread->index);
		if (philo_thread->index == 1)
			pthread_mutex_lock(&philo->fork[philo->num_of_philos]);	
		else
			pthread_mutex_lock(&philo->fork[philo_thread->index - 1]);
		print_message("has taken a fork", philo, philo_thread->index);
	}
	else
	{
		if (philo_thread->index == 1)
			pthread_mutex_lock(&philo->fork[philo->num_of_philos]);	
		else
			pthread_mutex_lock(&philo->fork[philo_thread->index - 1]);
		print_message("has taken a fork", philo, philo_thread->index);
		pthread_mutex_lock(&philo->fork[philo_thread->index]);
		print_message("has taken a fork", philo, philo_thread->index);
	}
}

int	philo_eat(t_philo_thread *philo_thread, t_philo *philo)
{

	if (philo->num_of_philos == 1)
	{
		philo->last_eaten[philo_thread->index] = philo->time_to_die + 100;
		return (0);
	}
	print_message("is eating", philo, philo_thread->index);
	ft_usleep(philo->time_to_eat);
	philo->meals_to_eat[philo_thread->index - 1]--;
	philo->last_eaten[philo_thread->index] = get_current_time();
	if (philo_thread->index == 1)
		pthread_mutex_unlock(&philo->fork[philo->num_of_philos]);	
	else 
		pthread_mutex_unlock(&philo->fork[philo_thread->index - 1]);
	pthread_mutex_unlock(&philo->fork[philo_thread->index]);
	return (1);
}

void	philo_sleep(t_philo_thread *philo_thread, t_philo *philo)
{
	print_message("is sleeping", philo, philo_thread->index);
	ft_usleep(philo->time_to_sleep);
}
