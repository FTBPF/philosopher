/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frteixei <frteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:10:35 by frteixei          #+#    #+#             */
/*   Updated: 2025/06/23 15:31:17 by frteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_philo_death(t_data *data, int i)
{
	size_t	cur_time;

	cur_time = get_time();
	pthread_mutex_lock(&data->philos[i].philo_mutex);
	pthread_mutex_lock(&data->print_mutex);
	if ((cur_time - data->philos[i].last_meal) > (size_t)data->time_to_die)
	{
		pthread_mutex_lock(&data->dead_mutex);
		data->dead_flag = 1;
		printf("%zu %d died\n", cur_time - data->start_time,
			data->philos[i].id);
		pthread_mutex_unlock(&data->dead_mutex);
		pthread_mutex_unlock(&data->print_mutex);
		pthread_mutex_unlock(&data->philos[i].philo_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->print_mutex);
	pthread_mutex_unlock(&data->philos[i].philo_mutex);
	return (0);
}

static int	check_all_philos_full(t_data *data)
{
	int	i;

	if (data->max_meals == -1)
		return (0);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->philos[i].philo_mutex);
		if (data->philos[i].meal_count < data->max_meals)
		{
			pthread_mutex_unlock(&data->philos[i].philo_mutex);
			return (0);
		}
		pthread_mutex_unlock(&data->philos[i].philo_mutex);
		i++;
	}
	return (1);
}

void	*monitor_simulation(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (1)
	{
		i = -1;
		while (++i < data->num_philos)
			if (check_philo_death(data, i))
				return (NULL);
		if (check_all_philos_full(data))
		{
			pthread_mutex_lock(&data->print_mutex);
			pthread_mutex_lock(&data->dead_mutex);
			data->dead_flag = 1;
			printf("All philosophers have eaten the ");
			printf("maximum meals number of meals\n");
			pthread_mutex_unlock(&data->dead_mutex);
			pthread_mutex_unlock(&data->print_mutex);
			break ;
		}
		usleep(1);
	}
	return (NULL);
}

static void	one_philo(t_philo *philo)
{
	print_action(philo, "has taken a fork");
	ft_usleep(philo->data->time_to_die, philo);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

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
		ft_usleep(philo->data->time_to_sleep, philo);
		if (is_simulation_over(philo->data))
			break ;
		print_action(philo, "is thinking");
	}
	return (NULL);
}
