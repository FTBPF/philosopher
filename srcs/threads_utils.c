/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franc <franc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:39:37 by franc             #+#    #+#             */
/*   Updated: 2025/06/09 18:01:12 by franc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int is_simulation_over(t_data *data)
{
	int res;

	pthread_mutex_lock(&data->dead_mutex);
	res = data->dead_flag;
	pthread_mutex_unlock(&data->dead_mutex);
	return (res);
}

void print_action(t_philo *phil, char *action)
{
	if (is_simulation_over(philo->data))
		return ;
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!is_simulation_over(philo->data))
		printf("%zu %d %s\n", get_time() - philo->data->start_time, philo->id, action);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken right fork");
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken left fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken left fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken right fork");
	}
}

void update_philo_state(t_philo *philo)
{
	print_action(philo, "is eating");
	pthread_mutex_lock(&philo->data->print_mutex);
	philo->last_meal = get_time();
	philo->meal_count++;
	pthread_mutex_unlock(&philo->data->print_mutex);
	ft_usleep(philo->data->time_to_eat, philo);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}
