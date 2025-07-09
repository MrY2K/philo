/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_routines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 21:41:06 by achoukri          #+#    #+#             */
/*   Updated: 2025/07/09 22:01:20 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/structs.h"
#include "include/prototypes.h"

void	philo_log(t_philo *p, const char *msg)
{
	long	timestamp;

	pthread_mutex_lock(&p->rules->state_lock);
	if (p->rules->stop)
	{
		pthread_mutex_unlock(&p->rules->state_lock);
		return ;
	}
	pthread_mutex_unlock(&p->rules->state_lock);
	timestamp = ft_now_ms() - p->rules->start_time;
	pthread_mutex_lock(&p->rules->print_lock);
	printf("%ld %d %s\n", timestamp, p->id, msg);
	pthread_mutex_unlock(&p->rules->print_lock);
}

int	handle_one_philo(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	if (philos->rules->number_of_philosophers == 1)
	{
		philo_log(philos, "is thinking");
		pthread_mutex_lock(philos->left_fork);
		philo_log(philos, "has taken a fork");
		while (1) 
		{
			pthread_mutex_lock(&philos->rules->state_lock);
			if (philos->rules->stop)
			{
				pthread_mutex_unlock(&philos->rules->state_lock);
				break ;
			}
			pthread_mutex_unlock(&philos->rules->state_lock);
			usleep(1000);
		}
		pthread_mutex_unlock(philos->left_fork);
		return (-1);
	}
	return (0);
}

void	setup_fork_order(t_philo *p, pthread_mutex_t **first,
				pthread_mutex_t **second)
{
	if (p->left_fork < p->right_fork)
	{
		*first = p->left_fork;
		*second = p->right_fork;
	}
	else
	{
		*first = p->right_fork;
		*second = p->left_fork;
	}
}
