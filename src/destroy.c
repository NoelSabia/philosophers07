/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsabia <nsabia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:05:15 by nsabia            #+#    #+#             */
/*   Updated: 2024/01/18 18:51:38 by nsabia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	destroy(t_philo *philo)
{
	size_t	i;

	i = 0;
	while (i < philo->num_of_philos)
	{
		pthread_detach(philo->id[i]);
		i++;
	}
	exit(0);
}
