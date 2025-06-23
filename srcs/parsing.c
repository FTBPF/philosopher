/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frteixei <frteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:03:44 by franc             #+#    #+#             */
/*   Updated: 2025/06/23 16:35:26 by frteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_valid(long n)
{
	if (n <= 0 || n > 2147483647)
		return (0);
	return (1);
}

static int	is_digit(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	check_arg(const char *str)
{
	int	n;

	if (!is_digit(str))
		return (0);
	n = ft_atol(str);
	if (!is_valid(n))
		return (0);
	return (1);
}

int	ft_parsing(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!check_arg(argv[i]))
			return (0);
		i++;
	}
	return (1);
}
