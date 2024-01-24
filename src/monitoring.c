/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsabia <nsabia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:22:12 by nsabia            #+#    #+#             */
/*   Updated: 2024/01/24 12:42:00 by nsabia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

// int	check_if_dead(t_philo *philo)
// {
	
// }

int check_if_all_ate(t_philo *philo)
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
	ft_usleep(1);
	while (1)
		if (check_if_all_ate(philo) == 1)
			break;
		// if (check_if_dead(philo) == 1 || check_if_all_ate(philo, philo_thread) == 1)
		// 	break;
	philo->philo_dead = 1;
	return (NULL);
}
