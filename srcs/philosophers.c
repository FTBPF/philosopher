/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frteixei <frteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:04:52 by frteixei          #+#    #+#             */
/*   Updated: 2025/06/23 17:04:52 by frteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_philos_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, &philo_routine,
				&data->philos[i]) != 0)
		{
			printf("Error: Failed to create philosopher thread %d\n", i);
			data->dead_flag = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

static int	create_monitor_thread(t_data *data, pthread_t *monitor_thread)
{
	if (pthread_create(monitor_thread, NULL, &monitor_simulation, data) != 0)
	{
		printf("Error: Failed to create monitor thread\n");
		data->dead_flag = 1;
		return (1);
	}
	return (0);
}

static void	wait_for_threads(t_data *data, pthread_t *monitor_thread)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
		{
			printf("Error: Failed to join philosopher thread %d\n", i);
			data->dead_flag = 1;
		}
		i++;
	}
	if (pthread_join(*monitor_thread, NULL) != 0)
	{
		printf("Error: Failed to join monitor thread\n");
		data->dead_flag = 1;
	}
}

static void	end_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].philo_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->dead_mutex);
	free(data->philos);
	free(data->forks);
	data->philos = NULL;
	data->forks = NULL;
}

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	monitor_thread;

	if (argc < 5 || argc > 6)
	{
		printf("Error: Invalid number of arguments\n");
		return (1);
	}
	if (!ft_parsing(argc, argv))
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	if (init_data(&data, argc, argv))
	{
		printf("Error: Failed to initialize data\n");
		return (1);
	}
	if (create_philos_threads(&data))
		return (1);
	if (create_monitor_thread(&data, &monitor_thread))
		return (1);
	wait_for_threads(&data, &monitor_thread);
	end_simulation(&data);
	return (0);
}
