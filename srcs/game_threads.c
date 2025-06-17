/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frteixei <frteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:10:35 by frteixei          #+#    #+#             */
/*   Updated: 2025/06/17 16:28:41 by frteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_philo_death(t_data *data, int i)
{
	size_t	cur_time;

	cur_time = get_time();
	pthread_mutex_lock(&data->print_mutex);
	if ((cur_time - data->philos[i].last_meal) > (size_t)data->time_to_die)
	{
		pthread_mutex_lock(&data->dead_mutex);
		data->dead_flag = 1;
		printf("%zu %d died\n", cur_time - data->start_time,
			data->philos[i].id);
		pthread_mutex_unlock(&data->dead_mutex);
		pthread_mutex_unlock(&data->print_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->print_mutex);
	return (0);
}

static int	check_all_philos_full(t_data *data)
{
	int	i;
	int	all_ate;

	i = 0;
	all_ate = 1;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->print_mutex);
		if (data->philos[i].meal_count < data->max_meals || data->max_meals ==
			-1)
			all_ate = 0;
		pthread_mutex_unlock(&data->print_mutex);
		i++;
	}
	return (all_ate);
}

void	*game_routine(void *arg)
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
			printf("All philosophers have eaten the maximum meals number of meals\n");
			pthread_mutex_unlock(&data->dead_mutex);
			pthread_mutex_unlock(&data->print_mutex);
			break ;
		}
		usleep(1);
	}
	return (NULL);
}
