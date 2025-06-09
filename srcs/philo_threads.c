/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franc <franc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:30:38 by franc             #+#    #+#             */
/*   Updated: 2025/06/09 17:39:06 by franc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void one_philo(t_philo *philo)
{
	print_action(philo, "has taken a fork");
	ft_usleep(philo->data->time_to_die, philo);
}

void *philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->data->num_philos == 1)
	{
		one_philo(philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(1);
	while (!is_simulation_over(philo->data))
	{
		take_forks(philo);
		update_philo_state(philo);
		if (is_simulation_over(philo->data))
			break ;
		print_action(philo, "is sleeping");
		ft_usleep(phil->data->time_to_sleep, philo);
		if (is_simulation_over(philo->data))
			break ;
		print_action(philo, "is thinking");
	}
	return (NULL);
}
