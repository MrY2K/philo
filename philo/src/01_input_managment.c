/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_input_managment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:17:29 by achoukri          #+#    #+#             */
/*   Updated: 2025/07/09 21:19:28 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

//parsing:
int	input_parsing(int ac, char **av);
int	validate_args(int ac, char **av);
int	validate_last_arg(int ac, char **av);

int	input_parsing(int ac, char **av)
{
	int	num_of_args;
	int	flag;
	int	last_arg;

	num_of_args = ac - 1;
	flag = 0;
	if (num_of_args < 4 || num_of_args > 5)
		return (BAD);
	if (validate_args(ac, av) == BAD)
		return (BAD);
	if (validate_last_arg(ac, av) == BAD)
		return (BAD);
	if (ac == 6)
	{
		last_arg = ft_atoi_improved(av[5], &flag);
		if (last_arg == 0)
			return (-1);
	}
	return (GOOD);
}

int	validate_args(int ac, char **av)
{
	int	i;
	int	arg;
	int	flag;

	i = 0;
	while (++i < ac)
	{
		flag = 0;
		arg = ft_atoi_improved(av[i], &flag);
		if (flag == -1 || arg <= 0)
			return (BAD);
	}
	return (GOOD);
}

int	validate_last_arg(int ac, char **av)
{
	int	arg;
	int	flag;

	if (ac != 6)
		return (0);
	flag = 0;
	arg = ft_atoi_improved(av[5], &flag);
	if (flag == -1 || arg < 0)
		return (BAD);
	return (GOOD);
}
