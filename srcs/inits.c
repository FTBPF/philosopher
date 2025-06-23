/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frteixei <frteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 16:42:53 by franc             #+#    #+#             */
/*   Updated: 2025/06/23 13:41:42 by frteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meal_count = 0;
		data->philos[i].last_meal = data->start_time;
		data->philos[i].right_fork = &data->forks[i];
		data->philos[i].left_fork = &data->forks[(i + 1) % data->num_philos];
		data->philos[i].data = data;
	}
}

static int	parse_arguments(t_data *data, int argc, char **argv)
{
	data->num_philos = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		data->max_meals = ft_atol(argv[5]);
	else
		data->max_meals = -1;
	data->dead_flag = 0;
	data->start_time = get_time();
	return (0);
}

static int	allocate_resources(t_data *data)
{
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
	{
		printf("Error: error allocating memory for forks\n");
		return (1);
	}
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
	{
		free(data->forks);
		printf("Error: error allocating memory for philos\n");
		return (1);
	}
	return (0);
}

static int	init_mutexes(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->dead_mutex, NULL) != 0)
		return (pthread_mutex_destroy(&data->print_mutex), 1);
	i = -1;
	while (++i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0
			|| pthread_mutex_init(&data->philos[i].philo_mutex, NULL) != 0)
		{
			while (--i >= 0)
			{
				pthread_mutex_destroy(&data->forks[i]);
				pthread_mutex_destroy(&data->philos[i].philo_mutex);
			}
			pthread_mutex_destroy(&data->print_mutex);
			pthread_mutex_destroy(&data->dead_mutex);
			return (1);
		}
	}
	return (0);
}

int	init_data(t_data *data, int argc, char **argv)
{
	if (parse_arguments(data, argc, argv) || allocate_resources(data))
		return (1);
	if (init_mutexes(data))
	{
		free(data->philos);
		free(data->forks);
		return (1);
	}
	init_philo(data);
	return (0);
}
