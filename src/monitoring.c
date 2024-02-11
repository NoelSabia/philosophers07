/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsabia <nsabia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:22:12 by nsabia            #+#    #+#             */
/*   Updated: 2024/02/11 20:45:58 by nsabia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	check_if_dead(t_philo *philo)
{
	size_t			i;
	size_t			time;
	size_t			result;

	i = 1;
	while (i <= philo->num_of_philos)
	{
		if (philo->last_eaten[i] == 0)
		{
			i++;
			continue ;
		}
		result = get_current_time() - philo->last_eaten[i];
		if ((result > philo->time_to_die) && (philo->last_eaten[i] != 0))
		{
			time = get_current_time() - philo->start_time;
			printf(ANSI_COLOR_BLACK"%zu %zu died" RESET "\n", time, i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_if_all_ate(t_philo *philo)
{
	size_t	i;
	size_t	eaten;

	i = 1;
	eaten = 0;
	while (i <= philo->num_of_philos)
	{
		if (philo->meals_to_eat[i] <= 0)
			eaten++;
		i++;
	}
	if (eaten == philo->num_of_philos)
		return (1);
	return (0);
}

void	*monitoring(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	usleep(1);
	while (1)
		if ((philo->eat_count > 0 && check_if_all_ate(philo) == 1)
			|| check_if_dead(philo) == 1)
			break ;
	philo->philo_dead = 1;
	return (NULL);
}
