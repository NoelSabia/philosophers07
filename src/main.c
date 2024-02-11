/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsabia <nsabia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:56:41 by nsabia            #+#    #+#             */
/*   Updated: 2024/02/11 19:08:49 by nsabia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	arg_checker(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		printf("Error: wrong number of arguments\n");
		return (0);
	}
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] != 0)
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("Error: Wrong argument!\n");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	helper(t_philo *philo)
{
	if (philo->num_of_philos <= 0)
	{
		printf("Error: wrong number of philosophers\n");
		return (0);
	}
	if (philo->time_to_die <= 0)
	{
		printf("Error: wrong time to die\n");
		return (0);
	}
	if (philo->time_to_eat <= 0)
	{
		printf("Error: wrong time to eat\n");
		return (0);
	}
	if (philo->time_to_sleep <= 0)
	{
		printf("Error: wrong time to sleep\n");
		return (0);
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_philo			philo;

	if (arg_checker(argc, argv) == 0)
		return (0);
	initialize(&philo, argv);
	destroy(&philo);
	return (0);
}
