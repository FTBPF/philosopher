/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franc <franc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:03:44 by franc             #+#    #+#             */
/*   Updated: 2025/06/09 18:06:41 by franc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int is_valid(long n)
{
	if (n <= 0 || n > 2147483647)
		return (0);
	return (1);
}

static int is_digit(const char *s)
{
	int	i;

	if (!s || !*s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	check_arg(const char *s)
{
	int	n;

	if (!is_digit(s))
		return (0);
	n = ft_atol(s);
	if (!is_valid(n))
		return (0);
	return (1);
}

int	ft_parsing(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (!check_arg(av[i]))
			return (0);
		i++;
	}
	return (1);
}
