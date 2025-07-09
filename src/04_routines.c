/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_routines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 02:29:59 by achoukri          #+#    #+#             */
/*   Updated: 2025/07/09 22:45:30 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/structs.h"
#include "include/prototypes.h"

static int	check_philo_death(t_philo *philos, t_data *rules, int i)
{
	long	last;
	long	since_last;

	pthread_mutex_lock(&rules->state_lock);
	last = philos[i].last_meal;
	pthread_mutex_unlock(&rules->state_lock);
	since_last = ft_now_ms() - last;
	if (since_last >= rules->time_to_die)
	{
		philo_log(&philos[i], "died");
		pthread_mutex_lock(&rules->state_lock);
		rules->stop = 1;
		pthread_mutex_unlock(&rules->state_lock);
		return (1);
	}
	return (0);
}

static int	check_philo_eaten(t_philo *philos, t_data *rules, int i)
{
	int	eaten;

	if (rules->number_of_times_each_p_must_eat > 0)
	{
		pthread_mutex_lock(&rules->state_lock);
		eaten = philos[i].eat_count;
		pthread_mutex_unlock(&rules->state_lock);
		if (eaten >= rules->number_of_times_each_p_must_eat)
			return (1);
	}
	return (0);
}

static int	check_all_eaten(t_data *rules, int full_count)
{
	if (rules->number_of_times_each_p_must_eat > 0
		&& full_count == rules->number_of_philosophers)
	{
		pthread_mutex_lock(&rules->state_lock);
		rules->stop = 1;
		pthread_mutex_unlock(&rules->state_lock);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philos;
	t_data	*rules;
	int		full_count;
	int		i;

	philos = (t_philo *)arg;
	rules = philos[0].rules;
	while (1)
	{
		full_count = 0;
		i = -1;
		while (++i < rules->number_of_philosophers)
		{
			if (check_philo_death(philos, rules, i))
				return (NULL);
			if (check_philo_eaten(philos, rules, i))
				full_count++;
		}
		if (check_all_eaten(rules, full_count))
			return (NULL);
		usleep(100);
	}
	return (NULL);
}
