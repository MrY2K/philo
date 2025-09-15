/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:17:38 by achoukri          #+#    #+#             */
/*   Updated: 2025/06/25 18:34:24 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int		ft_atoi_improved(const char *str, int *flag);

static int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

static void	ft_flag_err(int *flag)
{
	if (flag)
		*flag = -1;
}

static int	skip_spaces(const char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	return (i);
}

static int	handle_sign(const char *str, int *i)
{
	int	sign;

	sign = 1;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

int	ft_atoi_improved(const char *str, int *flag)
{
	int			sign;
	long long	result;
	int			digits;
	int			i;

	sign = 1;
	result = 0;
	digits = 0;
	i = skip_spaces(str);
	sign = handle_sign(str, &i);
	while (str[i] >= '0' && str[i] <= '9')
	{
		digits++;
		if ((result > INT_MAX / 10)
			|| (result == INT_MAX / 10 && (str[i] - '0') > INT_MAX % 10))
			return (ft_flag_err(flag), -69);
		result = result * 10 + str[i++] - '0';
	}
	if (digits == 0)
		if (flag)
			return (ft_flag_err(flag), -69);
	if (flag && str[i] != '\0')
		return (ft_flag_err(flag), -69);
	return ((int)(result * sign));
}
