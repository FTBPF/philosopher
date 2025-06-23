/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/06/09 15:38:14 by marvin            #+#    #+#             */
/*   Updated: 2025/06/09 15:38:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				meal_count;
	size_t			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	philo_mutex;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	int				dead_flag;
	size_t			start_time;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	dead_mutex;
}	t_data;

long	get_time(void);
long	ft_atol(const char *str);
void	*philo_routine(void *arg);
void	take_forks(t_philo *philo);
void	*monitor_simulation(void *arg);
int		is_simulation_over(t_data *data);
int		ft_parsing(int argc, char **argv);
void	update_philo_state(t_philo *philo);
void	ft_usleep(size_t milli, t_philo *philo);
void	print_action(t_philo *philo, char *action);
int		init_data(t_data *data, int argc, char **argv);

#endif